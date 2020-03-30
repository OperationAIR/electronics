#include <lpc_tools/boardconfig.h>
#include <lpc_tools/irq.h>
#include <c_utils/assert.h>
#include <c_utils/f2strn.h>
#include <c_utils/max.h>

#include <string.h>

#include "board.h"
#include "board_GPIO_ID.h"
#include "board_ADC_ID.h"

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

enum AppState {
    AppStateNone = -1,
    AppStateIdle = 0,
    AppStatePreBreathing,
    AppStateBreathing,
    AppStateAfterBreathing,
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

bool app_is_idle(void)
{
    return ((g_app.last_state == AppStateIdle) || (g_app.last_state == AppStateNone))
        && ((g_app.next_state == AppStateIdle) || (g_app.next_state == AppStateNone));
}

enum AppState app_state_idle(void)
{
    if(g_app.start_requested) {
        g_app.start_requested = false;
        return AppStatePreBreathing;
    }

    return AppStateIdle;
}

enum AppState app_state_pre_breathing(void)
{
    g_app.current_max_pressure = 0;

    log_wtime("Start Breathing Program");
    if(!breathing_start_program()) {
        return AppStateError;
    }
    control_LED_status_on();

    return AppStateBreathing;
}

enum AppState app_state_breathing(void)
{
    if(g_app.stop_requested) {
        g_app.stop_requested = false;
        return AppStateAfterBreathing;
    }

    breathing_run();


    return AppStateBreathing;

}

enum AppState app_state_after_breathing(void)
{
    log_wtime("Stop Breathing Program");
    breathing_stop();

    stats_increment_use_count();
    control_LED_status_off();

    return AppStateIdle;
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

    if (!g_app.run) {
        return;
    }

    sensors_update();

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

    const uint32_t update_frequency = 500;
    assert(systick_init(update_frequency));
}

void app_program_start(void)
{
    if (!g_app.start_requested) {
       // log_debug("Start Request");
        g_app.stop_requested = false;
        g_app.start_requested = true;
    }
}

void app_program_stop(void)
{
    if (!g_app.stop_requested) {
        log_debug("Stop Request");
        g_app.start_requested = false;
        g_app.stop_requested = true;
    }
}

void app_self_test(void)
{
    if (!g_app.test_requested) {
        log_wtime("Self Test Request");
        g_app.test_requested = true;
    }
}

