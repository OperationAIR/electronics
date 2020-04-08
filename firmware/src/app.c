#include <lpc_tools/boardconfig.h>
#include <lpc_tools/irq.h>
#include <c_utils/assert.h>
#include <c_utils/f2strn.h>
#include <c_utils/max.h>

#include <string.h>

#include "board_config/board_GPIO_ID.h"
#include "board_config/board_ADC_ID.h"

#include "actuators/control_signals.h"

#include "sensors/sensors.h"
#include "usb/app_usb.h"

#include "app.h"
#include "log.h"
#include "global_settings.h"
#include <mcu_timing/delay.h>
#include "stats.h"
#include "clock.h"

#include "breathing.h"
#include "settings.h"

#include <mcu_timing/profile.h>

#define DT_MS (5)

enum AppState {
    AppStateNone = -1,
    AppStateIdle = 0,
    AppStatePreBreathing,
    AppStateBreathing,
    AppStateAfterBreathing,
    AppStatePreInspiratoryHold,
    AppStateInspiratoryHold,
    AppStatePostInspiratoryHold,
    AppStateError,
    AppStateSelfTest,
    AppStateSelfTestResult,
};

static struct {
    int version;
    volatile uint32_t time; // time in milliseconds since entering current state
    volatile enum AppState last_state;
    volatile enum AppState next_state;
    volatile bool start_requested;
    volatile bool stop_requested;
    volatile bool test_requested;
    volatile bool run;
    uint32_t not_allowed_reasons;
    volatile bool maintenance;          //TODO should be non-volatile
    volatile unsigned int use_count;
    volatile int current_max_pressure;  // TODO not really used

    volatile uint32_t idle_blink; // timestamp for blink start
    volatile uint32_t last_idle_blink; // timestamp last blink start
    OperationSettings settings;

    volatile bool inspiratory_hold;
} g_app;


uint32_t get_last_pressure()
{
    return g_app.current_max_pressure;
}

enum ErrorReasons {
    ErrorNone = 0,
    ErrorPressureOverload = (1 << 3),
    ErrorPressureUnderload = (1 << 4),
    ErrorMaintenance = (1 << 7)
};

static void log_not_allowed_reason(void)
{
    log_wtime("Device not allowed to start because:");

    /*
    if (g_app.not_allowed_reasons & ErrorPressureOverload) {
        log_wtime("-> Pressure Overload: %d kPa", sensors_read_pressure());
    }
    if (g_app.not_allowed_reasons & ErrorPressureUnderload) {
        log_wtime("-> Pressure Underload: %d kPa", sensors_read_pressure());
    }
    */
    if (g_app.not_allowed_reasons & ErrorMaintenance) {
        log_wtime("-> Device needs maintenance");
    }
}


bool app_start_allowed(void)
{
    uint32_t reasons = ErrorNone;
    /*
    const int pressure = sensors_read_pressure();

    if (pressure > PRESSURE_OVERLOAD_LIMIT_kPa) {
        reasons |= ErrorPressureOverload;
    }

    if (pressure < PRESSURE_UNDERLOAD_LIMIT_kPa) {
        reasons |= ErrorPressureUnderload;
    }
    */

    if (g_app.maintenance) {
        reasons |= ErrorMaintenance;
    }

    g_app.not_allowed_reasons = reasons;
    if (reasons != ErrorNone) {
        log_not_allowed_reason();
    }

    return reasons == 0;
}


static char* get_state_name(enum AppState state)
{
    switch(state) {
        case AppStateIdle:
            return "idle";
        case AppStateBreathing:
            return "breathing";
        case AppStatePreBreathing:
            return "pre-breathing";
        case AppStateAfterBreathing:
            return "after-breathing";
        case AppStatePreInspiratoryHold:
            return "pre-inspiratory-hold-manoeuvre";
        case AppStateInspiratoryHold:
            return "inspiratory-hold-manoeuvre";
        case AppStatePostInspiratoryHold:
            return "post-inspiratory-hold-manoeuvre";
        case AppStateError:
            return "not-allowed";
        case AppStateSelfTest:
            return "self-test";
        case AppStateSelfTestResult:
            return "self-test-result";
        default:
            return "unknown";
    }

}

// NOTE: when adding new states, make sure to correctly control_XX signals on t=0
enum AppState app_state_idle(void);
enum AppState app_state_charging(void);
enum AppState app_state_pre_breathing(void);
enum AppState app_state_breathing(void);
enum AppState app_state_after_breathing(void);
enum AppState app_state_pre_inspiratory_hold(void);
enum AppState app_state_inspiratory_hold(void);
enum AppState app_state_post_inspiratory_hold(void);
enum AppState app_state_error(void);
enum AppState app_state_self_test(void);
enum AppState app_state_self_test_result(void);
enum AppState app_state_pre_bootloader(void);
enum AppState app_state_overheat(void);

void _go_to_state(enum AppState next_state);


void app_clear_maintenance_mode(void)
{
    if (g_app.maintenance) {
        g_app.maintenance = false;
        stats_set_maintenance_mode(false);
        log_wtime("Maintenance mode cleared: ready for use");
    } else {
        log_wtime("Device not in Maintenance mode, no need to clear..");
    }
}

void app_reset_use_count(void)
{
    stats_clear_use_count();
    g_app.use_count = stats_get_use_count();
}

bool app_is_maintenance_mode(void)
{
    return g_app.maintenance;
}

bool app_is_running(void)
{
    return g_app.run;
}

char* app_get_state(void)
{
    return get_state_name(g_app.next_state);
}

void app_apply_settings(OperationSettings *new_settings)
{
    const bool critical_section = irq_disable();
    settings_copy(&g_app.settings, new_settings);
    irq_restore(critical_section);
}

OperationSettings* app_get_settings()
{
    return &g_app.settings;
}

bool app_is_idle(void)
{
    return ((g_app.last_state == AppStateIdle) || (g_app.last_state == AppStateNone))
        && ((g_app.next_state == AppStateIdle) || (g_app.next_state == AppStateNone));
}

enum AppState app_state_idle(void)
{
    // Start from CLI
    if(g_app.start_requested) {
        g_app.start_requested = false;
        return AppStatePreBreathing;
    }

    // Start from GUI
    if(g_app.settings.start) {
        return AppStatePreBreathing;
    }


    return AppStateIdle;
}

enum AppState app_state_pre_breathing(void)
{
    // Stop from GUI: abort calibration
    if(!g_app.settings.start) {
        breathing_power_off();
        control_LED_status_off();

        return AppStateIdle;
    }

    g_app.current_max_pressure = 0;

    // At startup, do offset calibration.
    // During this time, the status led on PCB blinks.
    if (g_app.time == 0) {
        log_wtime("Calibrating offsets...");
        breathing_start_calibration();
    }

    if((g_app.time % 50) == 0) {
        control_LED_status_toggle();
    }

    if (g_app.time >= (CALIBRATION_DURATION_MS/2)) {
        breathing_finish_calibration();

        log_wtime("Start Breathing Program");
        if(!breathing_start_program()) {
            return AppStateError;
        }
        control_LED_status_on();

        return AppStateBreathing;
    }
    return AppStatePreBreathing;
}

enum AppState app_state_breathing(void)
{
    // Stop from CLI
    if(g_app.stop_requested) {
        g_app.stop_requested = false;
        return AppStateAfterBreathing;
    }

    // Stop from GUI
    if(!g_app.settings.start) {
        return AppStateAfterBreathing;
    }

    // Start Inspiratory Hold
    if(g_app.inspiratory_hold && (breathing_get_cycle_state() == BreathCycleLastStepDone)) {
        return AppStatePreInspiratoryHold;
    }

    // Note: new settings are only updated at start of new breathing cycle
    breathing_run(&g_app.settings, DT_MS);

    return AppStateBreathing;

}

enum AppState app_state_after_breathing(void) {
    if (g_app.time == 0) {
        log_wtime("Stop Breathing Program");
        breathing_stop();
    }

    if ((g_app.time % 100) == 0) {
        control_LED_status_toggle();
    }

    if (g_app.time >= (BREATHING_FINAL_STOP_DURATION_MS / 2)) {
        breathing_power_off();

        log_wtime("Breathing is finished");

        stats_increment_use_count();
        control_LED_status_off();

        return AppStateIdle;
    }

    return AppStateAfterBreathing;
}

enum AppState app_state_pre_inspiratory_hold(void) {
    pre_inspiratory_hold(&g_app.settings, DT_MS);
    return AppStateInspiratoryHold;
}

enum AppState app_state_inspiratory_hold(void)
{
    bool finised = inspiratory_hold_run(&g_app.settings, DT_MS);
    if (finised) {
        g_app.inspiratory_hold = false;
        return  AppStatePostInspiratoryHold;
    }

    if (!g_app.inspiratory_hold) {
        return AppStatePostInspiratoryHold;
    }

    return AppStateInspiratoryHold;
}

enum AppState app_state_post_inspiratory_hold(void) {
    bool finised = post_inspiratory_hold(&g_app.settings, DT_MS);

    if (finised) {
        return AppStateBreathing;
    }
    return AppStatePostInspiratoryHold;
}

enum AppState app_state_error(void)
{
    enum AppState next_state = AppStateError;

    control_LED_error_on();

     // first time in state
    if (g_app.time == 0) {
        // do something here?
    }

    return next_state;
}


enum AppState app_state_self_test(void)
{

    enum AppState next_state = AppStateSelfTestResult;
    return next_state;
}

enum AppState app_state_self_test_result(void)
{
    enum AppState next_state = AppStateIdle;
    return next_state;
}


static bool systick_init(const uint32_t target_frequency)
{
    const uint32_t clk_freq = Chip_Clock_GetMainClockRate();
    const uint32_t ticks_per_cycle = clk_freq / target_frequency;

    return (0 == SysTick_Config(ticks_per_cycle));
}

void SysTick_Handler(void)
{
    PROFILE

    if (!g_app.run) {
        return;
    }

    sensors_update(DT_MS);

    // TODO the state-machine is not 7001-specific yet. Do we really need
    // all this complexity?

    const enum AppState last_state = g_app.next_state;
    enum AppState next_state = g_app.next_state;

    switch(g_app.next_state) {
        case AppStateIdle:
            next_state = app_state_idle();
            break;
        case AppStatePreBreathing:
            next_state = app_state_pre_breathing();
            break;
        case AppStateBreathing:
            next_state = app_state_breathing();
            break;
        case AppStateAfterBreathing:
            next_state = app_state_after_breathing();
            break;
        case AppStatePreInspiratoryHold:
            next_state = app_state_pre_inspiratory_hold();
            break;
        case AppStateInspiratoryHold:
            next_state = app_state_inspiratory_hold();
            break;
        case AppStatePostInspiratoryHold:
            next_state = app_state_post_inspiratory_hold();
            break;
        case AppStateError:
            next_state = app_state_error();
            break;
        case AppStateSelfTest:
            next_state = app_state_self_test();
            break;
        case AppStateSelfTestResult:
            next_state = app_state_self_test_result();
            break;
        default:
            next_state = app_state_idle();
    }

    g_app.time++;

    _go_to_state(next_state);
    g_app.last_state = last_state;
}

void _go_to_state(enum AppState next_state)
{
    if (next_state != g_app.next_state) {
        g_app.time = 0;
        log_debug("next state: [%s]", get_state_name(next_state));
        g_app.next_state = next_state;
    }
}
void app_halt()
{
    g_app.run = false;
}

void app_resume()
{
    g_app.run = true;
}


void app_init(int hw_version)
{
    if (!breathing_init()) {
        g_app.maintenance = true;
    }
    g_app.last_state = AppStateNone;
    g_app.next_state = AppStateIdle;
    g_app.run = true;
    g_app.version = hw_version;

    g_app.use_count = stats_get_use_count();
    g_app.maintenance = stats_get_maintenance_mode();

    sensors_init();

    const uint32_t update_frequency = 1000/DT_MS;
    assert(systick_init(update_frequency));
}

void app_program_start(void)
{
    if (!g_app.start_requested) {
        log_debug("Start Request");
        g_app.stop_requested = false;
        g_app.start_requested = true;
        g_app.settings.start = true;
        g_app.settings.peep = 1000;
        g_app.settings.pressure = 3000;
        g_app.settings.frequency = 15;
        g_app.settings.ratio = 2;
        g_app.settings.oxygen = 21;
    }
}

void app_program_stop(void)
{
    if (!g_app.stop_requested) {
        log_debug("Stop Request");
        g_app.start_requested = false;
        g_app.stop_requested = true;
        g_app.settings.start = false;
    }
}

void app_self_test(void)
{
    if (!g_app.test_requested) {
        log_wtime("Self Test Request");
        g_app.test_requested = true;
    }
}

void app_start_inspiratory_hold() {
    if (g_app.next_state == AppStateBreathing) {
        g_app.inspiratory_hold = true;
//        log_cli("Inspiratory hold mode on");
    } else {
        log_cli("Inspiratory only possible during breathing");
    }
}

void app_stop_inspiratory_hold() {
    g_app.inspiratory_hold = false;
    if (g_app.next_state == AppStateInspiratoryHold) {
//        log_cli("Inspiratory hold mode off");
    } else {
        log_cli("Inspiratory hold not turned on");
    }
}

