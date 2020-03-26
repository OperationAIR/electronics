#include <lpc_tools/boardconfig.h>
#include <c_utils/assert.h>
#include <c_utils/f2strn.h>
#include <c_utils/max.h>

#include "board.h"
#include "board_GPIO_ID.h"
#include "board_ADC_ID.h"

#include "actuators/control_signals.h"

#include "sensors/sensors.h"
#include "sensors/button.h"
#include "usb/app_usb.h"

#include "app.h"
#include "log.h"
#include "breathing.h"
#include "global_settings.h"
#include <mcu_timing/delay.h>
#include "power_management.h"
#include "stats.h"
#include "clock.h"

#define BATT_CHARGER_STARTUP_DELAY_MS 20*1000
#define BATT_CHARGER_DISCONNECT_DELAY_MS 10
#define BATT_CHARGER_PAUSE_DELAY_MS 500



#define SLEEP_DELAY_MS 30
#define POST_SLEEP_DELAY_US 200

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
    volatile int current_max_pressure;

    volatile uint32_t idle_blink; // timestamp for blink start
    volatile uint32_t last_idle_blink; // timestamp last blink start

} g_app;

uint32_t get_last_pressure()
{
    return g_app.current_max_pressure;
}

void app_button_poll(void);

enum ErrorReasons {
    ErrorNone = 0,
    ErrorPressureOverload = (1 << 3),
    ErrorPressureUnderload = (1 << 4),
    ErrorMaintenance = (1 << 7)
};

static void log_not_allowed_reason(void)
{
    log_wtime("Device not allowed to start because:");

    if (g_app.not_allowed_reasons & ErrorPressureOverload) {
        log_wtime("-> Pressure Overload: %d kPa", sensors_read_pressure());
    }
    if (g_app.not_allowed_reasons & ErrorPressureUnderload) {
        log_wtime("-> Pressure Underload: %d kPa", sensors_read_pressure());
    }
    if (g_app.not_allowed_reasons & ErrorMaintenance) {
        log_wtime("-> Device needs maintenance");
    }
}


bool app_start_allowed(void)
{
    uint32_t reasons = ErrorNone;
    const int pressure = sensors_read_pressure();

    if (pressure > PRESSURE_OVERLOAD_LIMIT_kPa) {
        reasons |= ErrorPressureOverload;
    }

    if (pressure < PRESSURE_UNDERLOAD_LIMIT_kPa) {
        reasons |= ErrorPressureUnderload;
    }

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

bool app_is_idle(void)
{
    return ((g_app.last_state == AppStateIdle) || (g_app.last_state == AppStateNone))
        && ((g_app.next_state == AppStateIdle) || (g_app.next_state == AppStateNone));
}
bool app_can_sleep(void)
{
    if(g_app.last_state != AppStateIdle) {
        return false;
    }
    if(g_app.next_state != AppStateIdle) {
        return false;
    }

    if (g_app.idle_blink != 0) {
        return false;
    }
    return true;
}
void app_wakeup(void)
{
    g_app.last_state = AppStateNone;
    sensors_reset();
}

enum AppState app_state_idle(void)
{
    if (g_app.time <= 1) {
        control_valve1_close();
        control_valve2_close();
    }

    enum AppState next_state = AppStateIdle;

    if (g_app.start_requested) {
        next_state = AppStatePreBreathing;
        g_app.start_requested = false;
    }
    if (g_app.test_requested) {
        if (app_start_allowed()) {
            next_state = AppStateSelfTest;
        } else if (OVERRIDE_NOT_ALLOWED) {
            log_wtime("OVERRIDE_NOT_ALLOWED set: Start test anyway");
            next_state = AppStateSelfTest;
        }else {
            log_wtime("Not Allowed");
            next_state = AppStateError;
        }
        g_app.test_requested = false;

    }


    return next_state;
}

enum AppState app_state_pre_breathing(void)
{
    enum AppState next_state = AppStatePreBreathing;

     // first time in state
    if (g_app.time == 0) {

    }

    if (g_app.time == PRE_BREATHING_DELAY_ms) {
       if (app_start_allowed()) {
            next_state = AppStateBreathing;
        } else if (OVERRIDE_NOT_ALLOWED) {
            log_wtime("OVERRIDE_NOT_ALLOWED set:, Starting anyway");
            next_state = AppStateBreathing;
        } else {
            log_wtime("Not Allowed");
            next_state = AppStateError;
        }

    }

    return next_state;

}

enum AppState app_state_breathing(void)
{
    enum AppState next_state = AppStateBreathing;

    // first time in state
    if (g_app.time == 0) {

        g_app.current_max_pressure = 0;

        log_wtime("Start Breathing Program");
        breathing_start_program();
    }

    if (!OVERRIDE_NOT_ALLOWED && !app_start_allowed()) {
        log_wtime("Stop Breathing Program [error]");
        breathing_stop();
        stats_increment_use_count();
        next_state = AppStateError;
    } else if(g_app.stop_requested) {
        log_wtime("Stop Breathing Program [user]");
        breathing_stop();
        next_state = AppStateAfterBreathing;
        g_app.stop_requested = false;
    } else {
        const int pressure = breathing_run();
        if (pressure) {
            g_app.current_max_pressure = MAX(pressure, g_app.current_max_pressure);
        } else {
            next_state = AppStateAfterBreathing;
            log_wtime("Stop Breathing Program [end]");
        }
    }
    return next_state;

}

enum AppState app_state_after_breathing(void)
{

    enum AppState next_state = AppStateAfterBreathing;

    if (g_app.time == 0) {
        control_valve1_close();
        control_valve2_close();
    }

    if (g_app.time > AFTER_BREATHING_TIME_ms) {
        // after timeout
        next_state = AppStateIdle;

        if (g_app.start_requested) {
            log_debug("Start Request Ignored (after breathing state)");
            g_app.start_requested = false;
        }
        if (g_app.test_requested) {
            log_debug("Test Request Ignored (after breathing state)");
            g_app.test_requested = false;
        }

        stats_increment_use_count();
    }
    return next_state;
}
RGBColor bright = {.red = 255, .green = 255, .blue = 255};

enum AppState app_state_error(void)
{
    enum AppState next_state = AppStateError;

     // first time in state
    if (g_app.time == 0) {
        control_valve1_close();
        control_valve2_close();
    }

   if (g_app.not_allowed_reasons & ErrorPressureOverload) {

        if (g_app.time > ERROR_TIME_ms) {
            g_app.maintenance = true;
            stats_set_maintenance_mode(true);
            g_app.not_allowed_reasons &= ~ErrorPressureOverload;
            g_app.time = 0;
        }
    } else if (g_app.not_allowed_reasons & ErrorPressureUnderload) {


        if (g_app.time > ERROR_TIME_ms) {
            g_app.maintenance = true;
            stats_set_maintenance_mode(true);
            g_app.not_allowed_reasons &= ~ErrorPressureUnderload;
            g_app.time = 0;
        }
    } else if (g_app.not_allowed_reasons & ErrorMaintenance) {
        if (g_app.time > ERROR_TIME_ms) {
            g_app.not_allowed_reasons &= ~ErrorMaintenance;
            g_app.time = 0;
        }
    } else {
        next_state = AppStateIdle;
    }

    if (g_app.time > ERROR_TIME_ms) {
        // after timeout
        next_state = AppStateIdle;
        g_app.not_allowed_reasons = ErrorNone;
    }

    if (g_app.start_requested) {
        log_debug("Start Request Ignored (not allowed state)");
        g_app.start_requested = false;
    }
    if (g_app.test_requested) {
        log_debug("Test Request Ignored (not allowed state)");
        g_app.test_requested = false;
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
    // app_button_poll();

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

    // TODO FIX THIS!
    button_init(board_get_GPIO(GPIO_ID_LED_STATUS));
    sensor_init(ADC_ID_PRESSURE_1);

    const uint32_t update_frequency = 1000;
    assert(systick_init(update_frequency));
}

void app_program_start(void)
{
    if (!g_app.start_requested) {
       // log_debug("Start Request");
        g_app.start_requested = true;
    }
}

void app_program_stop(void)
{
    if (!g_app.stop_requested) {
        log_debug("Stop Request");
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

void app_button_poll(void)
{
    // enum BUTTON_STATUS button = button_get_status();
    // no button
    return;

}
