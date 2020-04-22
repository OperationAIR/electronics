#include <lpc_tools/boardconfig.h>
#include <lpc_tools/irq.h>
#include <c_utils/assert.h>
#include <c_utils/f2strn.h>
#include <c_utils/max.h>

#include <string.h>

#include "board_config/board_GPIO_ID.h"
#include "board_config/board_ADC_ID.h"
#include "board_specific_config.h"

#include "actuators/control_signals.h"

#include "sensors/sensors.h"
#include "usb/app_usb.h"

#include "app.h"
#include "log.h"
#include "global_settings.h"
#include "system_status.h"

#include <mcu_timing/delay.h>
#include "storage/storage.h"
#include "crc/crc.h"
#include "clock.h"

#include "breathing.h"
#include "self_test.h"
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
    AppStatePreExpiratoryHold,
    AppStateExpiratoryHold,
    AppStatePostExpiratoryHold,
    AppStateError,
    AppStatePreSelfTest,
    AppStateSelfTest,
    AppStateSelfTestResult,
};

static struct {
    int version;
    volatile uint32_t time; // time in milliseconds since entering current state
    volatile enum AppState last_state;
    volatile enum AppState next_state;
    volatile bool test_requested;
    volatile bool run;
    uint32_t not_allowed_reasons;
    volatile unsigned int use_count;

    OperationSettings settings;

    volatile bool inspiratory_hold;
    volatile bool expiratory_hold;

    volatile bool settings_should_be_saved;
} g_app;


enum ErrorReasons {
    ErrorNone = 0,
    ErrorPressureOverload = (1 << 3),
    ErrorPressureUnderload = (1 << 4),
    ErrorMaintenance = (1 << 7)
};

static void log_not_allowed_reason(void)
{
    log_wtime("Device not allowed to start because: ??");

}


bool app_start_allowed(void)
{
    uint32_t reasons = ErrorNone;

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
        case AppStatePreExpiratoryHold:
            return "pre-expiratory-hold-manoeuvre";
        case AppStateExpiratoryHold:
            return "expiratory-hold-manoeuvre";
        case AppStatePostExpiratoryHold:
            return "post-expiratory-hold-manoeuvre";
        case AppStateError:
            return "not-allowed";
        case AppStatePreSelfTest:
            return "pre-self-test";
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

enum AppState app_state_pre_breathing(void);
enum AppState app_state_breathing(void);
enum AppState app_state_after_breathing(void);

enum AppState app_state_pre_inspiratory_hold(void);
enum AppState app_state_inspiratory_hold(void);
enum AppState app_state_post_inspiratory_hold(void);

enum AppState app_state_pre_expiratory_hold(void);
enum AppState app_state_expiratory_hold(void);
enum AppState app_state_post_expiratory_hold(void);

enum AppState app_state_error(void);
enum AppState app_state_pre_self_test(void);
enum AppState app_state_self_test(void);
enum AppState app_state_self_test_result(void);

void _go_to_state(enum AppState next_state);


bool app_is_running(void)
{
    return g_app.run;
}

char* app_get_state(void)
{
    return get_state_name(g_app.next_state);
}

void app_apply_settings(const OperationSettings *new_settings)
{
    const bool critical_section = irq_disable();
    settings_copy(&g_app.settings, new_settings);
    g_app.settings_should_be_saved = true;
    irq_restore(critical_section);
}

bool app_check_and_clear_settings_should_be_saved(void)
{
    const bool critical_section = irq_disable();

    const bool result = g_app.settings_should_be_saved;
    g_app.settings_should_be_saved = false;

    irq_restore(critical_section);

    return result;
}

OperationSettings* app_get_settings(void)
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
    if(g_app.test_requested) {
        return AppStatePreSelfTest;
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

    // At startup, do offset calibration.
    // During this time, the status led on PCB blinks.
    if (g_app.time == 0) {
        log_wtime("Calibrating offsets...");
        breathing_start_calibration();

        // disable reset pin so RPi cannot interrupt breathing program accidentally.
        board_disable_reset_pin();
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
    // Stop from GUI
    if(!g_app.settings.start) {
        return AppStateAfterBreathing;
    }

    // Start Inspiratory Hold
    if(g_app.inspiratory_hold && (breathing_get_cycle_state() == BreathCycleLastStepDone)) {
        return AppStatePreInspiratoryHold;
    }

    // Start Inspiratory Hold
    if(g_app.expiratory_hold && (breathing_get_cycle_state() == BreathCycleLastStepDone)) {
        return AppStatePreExpiratoryHold;
    }

    // Note: new settings are only updated at start of new breathing cycle
    breathing_run(&g_app.settings, DT_MS);

    return AppStateBreathing;

}

enum AppState app_state_after_breathing(void) {
    if (g_app.time == 0) {
        log_wtime("Stop Breathing Program");
        breathing_stop();

        // enable reset pin again so RPi is the boss again
        board_enable_reset_pin();
    }

    if ((g_app.time % 100) == 0) {
        control_LED_status_toggle();
    }

    if (g_app.time >= (BREATHING_FINAL_STOP_DURATION_MS / 2)) {
        breathing_power_off();

        log_wtime("Breathing is finished");

        storage_increment_app_use_count();
        control_LED_status_off();

        return AppStateIdle;
    }

    return AppStateAfterBreathing;
}

/**
 * Inspiratory hold
 */
enum AppState app_state_pre_inspiratory_hold(void) {
    pre_hold(&g_app.settings, DT_MS);
    return AppStateInspiratoryHold;
}

enum AppState app_state_inspiratory_hold(void)
{
    bool finised = inspiratory_hold_run(&g_app.settings, g_app.inspiratory_hold, DT_MS);
    if (finised) {
        g_app.inspiratory_hold = false;
        return  AppStatePostInspiratoryHold;
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

/**
 * Expiratory hold
 */
enum AppState app_state_pre_expiratory_hold(void) {
    pre_hold(&g_app.settings, DT_MS);
    return AppStateExpiratoryHold;
}

enum AppState app_state_expiratory_hold(void) {
    bool finised = expiratory_hold_run(&g_app.settings, g_app.expiratory_hold, DT_MS);
    if (finised) {
        g_app.expiratory_hold = false;
        return  AppStatePostExpiratoryHold;
    }

    return AppStateExpiratoryHold;
}

enum AppState app_state_post_expiratory_hold(void) {
    return AppStateBreathing;
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


enum AppState app_state_pre_self_test(void)
{
    pre_self_test();
    enum AppState next_state = AppStateSelfTest;
    return next_state;
}

enum AppState app_state_self_test(void)
{
    if (run_self_test(DT_MS)) {
        g_app.test_requested = false;
        enum AppState next_state = AppStateSelfTest;
        return next_state;
    }

    enum AppState next_state = AppStateIdle;
    return next_state;
}

enum AppState app_state_self_test_result(void)
{
//    g_app.test_requested = false;
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

    sensors_update(DT_MS);

    if (!g_app.run) {
        return;
    }

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
        case AppStatePreExpiratoryHold:
            next_state = app_state_pre_expiratory_hold();
            break;
        case AppStateExpiratoryHold:
            next_state = app_state_expiratory_hold();
            break;
        case AppStatePostExpiratoryHold:
            next_state = app_state_post_expiratory_hold();
            break;
        case AppStateError:
            next_state = app_state_error();
            break;
        case AppStatePreSelfTest:
            next_state = app_state_pre_self_test();
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
void app_halt(void)
{
    g_app.run = false;
}

void app_resume(void)
{
    g_app.run = true;
}


void app_init(int hw_version)
{
    breathing_init();

    g_app.last_state = AppStateNone;
    g_app.next_state = AppStateIdle;
    g_app.run = true;
    g_app.version = hw_version;

    g_app.use_count = storage_read_app_use_count();

    // MCU reset unexpectedly: try to recover settings from EEPROM
    bool settings_restored = false;
    if(system_status_get() & (SYSTEM_STATUS_BOOT_RESET_BY_ERROR
            | SYSTEM_STATUS_BOOT_RESET_BY_PWR_FAIL
            | SYSTEM_STATUS_BOOT_RESET_BY_UNKNOWN)) {

        OperationSettings settings;
        if(storage_read_settings(&settings)) {
            settings_restored = settings_update(&settings);
        }
    }

    // Apply default settings
    if(!settings_restored) {
        settings_default();
    }
    sensors_init();

    const uint32_t update_frequency = 1000/DT_MS;
    assert(systick_init(update_frequency));
}


// start from CLI
void app_program_force_start(void)
{
    log_debug("Starting...");
    g_app.settings.start = true;
    g_app.settings.peep = 800;
    g_app.settings.pressure = 2500;
    g_app.settings.frequency = 15;
    g_app.settings.ratio = 20;
    g_app.settings.oxygen = 21;


    uint16_t crc_state = 0xFFFF;
    const uint16_t crc = crc16_usb_stream_check(&crc_state, (uint8_t*)&g_app.settings, sizeof(OperationSettings)-2);
    g_app.settings.crc = crc;

    app_apply_settings(&g_app.settings);
}

// stom from CLI
void app_program_force_stop(void)
{
    log_debug("Stopping...");
    g_app.settings.start = false;
}

void app_start_self_test(void)
{
    if (!g_app.test_requested) {
        log_wtime("Self Test Request");
        g_app.test_requested = true;
    }
}

void app_start_inspiratory_hold(void) {
    if (g_app.next_state == AppStateBreathing) {
        g_app.inspiratory_hold = true;
//        log_cli("Inspiratory hold mode on");
    } else {
        log_cli("Inspiratory only possible during breathing");
    }
}

void app_stop_inspiratory_hold(void) {
    g_app.inspiratory_hold = false;
    if (g_app.next_state == AppStateInspiratoryHold) {
//        log_cli("Inspiratory hold mode off");
    } else {
        log_cli("Inspiratory hold not turned on");
    }
}

void app_start_expiratory_hold(void) {
    if (g_app.next_state == AppStateBreathing) {
        g_app.expiratory_hold = true;
//        log_cli("Inspiratory hold mode on");
    } else {
        log_cli("Expiratory only possible during breathing");
    }
}

void app_stop_expiratory_hold(void) {
    g_app.expiratory_hold = false;
    if (g_app.next_state == AppStateExpiratoryHold) {
//        log_cli("Inspiratory hold mode off");
    } else {
        log_cli("Expiratory hold not turned on");
    }
}

