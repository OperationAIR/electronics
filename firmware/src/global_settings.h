#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdbool.h>
#include <stdint.h>

const unsigned int BUTTON_TIME_PROGRAM_START_ms;
const unsigned int BUTTON_TIME_PROGRAM_ABORT_ms;
const unsigned int BUTTON_TIME_SELF_TEST_ms;
const unsigned int BUTTON_TIME_FIRMWARE_UPDATE_ms;

const int AUTO_START_INTERVAL;
const bool OVERRIDE_NOT_ALLOWED;
const bool ENABLE_CHARGING_TRACE;
const bool ENABLE_SLEEP;
const bool ENABLE_USB_WAKEUP;
const bool ENABLE_SLEEP_LED;
const bool ENABLE_SLEEP_GPIO;


const int PRESSURE_OVERLOAD_LIMIT_kPa;
const int PRESSURE_UNDERLOAD_LIMIT_kPa;
const int TEMPERATURE_LIMIT_C;

const int BATTERY_LOW_mv;
const int BATTERY_CRITICAL_mv;
const int BATTERY_NO_START_mv;

const bool SELF_TEST_ENABLED;
const unsigned int SELF_TEST_MOTOR_POWER;
const unsigned int SELF_TEST_HOLD_TIME_ms;
const unsigned int SELF_TEST_TIMEOUT_ms;
const int SELF_TEST_PRESSURE_THRESHOLD_kPa;
const int SELF_TEST_TARGET_PRESSURE_kPa;
const unsigned int SELF_TEST_LOG_INTERVAL_ms;
const unsigned int PRE_BREATHING_DELAY_ms;

#define MAX_SUB_PROGRAMS 4
#define REQUIRED_PWM_RESOLUTION 100

#define CHARGE_THRESHOLD_OFFSET_mv 30
#define MINIMUM_VUSB_CHARGING_mv 4100
#define MINIMUM_VUSB_NOT_CHARGING_mv 4800

enum VALVES {
    VALVE1 = 1,
    VALVE2 = 2
};

enum VALVES VALVE_FOR_OVER_PRESSURE;
const unsigned int BREATHING_LOG_INTERVAL_ms;

typedef enum BreathingProgramType {
    BREATHING_PROGRAM_TYPE_NONE = 0,
    BREATHING_PROGRAM_TYPE_A,
    BREATHING_PROGRAM_TYPE_B
} BreathingProgramType;

typedef struct BreathingSubProgram {
    BreathingProgramType type;
    unsigned int motor_power_pressure;
    unsigned int motor_power_vaccuum;
    unsigned int cycle_time_pressure;
    unsigned int cycle_time_vaccuum;
    int max_pressure;
    int min_pressure;
    unsigned int num_cycles;
    unsigned int max_time;
} BreathingSubProgram;

typedef struct BreathingProgram {
    BreathingSubProgram subprograms[MAX_SUB_PROGRAMS];
} BreathingProgram;


const BreathingProgram breathing_program;

const unsigned int ERROR_TIME_ms;
const unsigned int AFTER_BREATHING_TIME_ms;




typedef struct __attribute__((packed)) {
    uint16_t peep;
    uint16_t frequency;
    uint16_t tidal_volume;
    uint16_t pressure;
    uint16_t max_pressure_alarm;
    uint16_t min_pressure_alarm;
    uint16_t max_tv_alarm;
    uint16_t min_tv_alarm;
    uint16_t max_fi02_alarm;
    uint16_t min_fi02_alarm;
} OperationSettings;


#endif
