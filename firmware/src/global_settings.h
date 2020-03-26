#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdbool.h>
#include <stdint.h>

const unsigned int BUTTON_TIME_PROGRAM_START_ms;
const unsigned int BUTTON_TIME_PROGRAM_ABORT_ms;
const unsigned int BUTTON_TIME_SELF_TEST_ms;
const unsigned int BUTTON_TIME_FIRMWARE_UPDATE_ms;


const int PRESSURE_OVERLOAD_LIMIT_kPa;
const int PRESSURE_UNDERLOAD_LIMIT_kPa;
const int TEMPERATURE_LIMIT_C;

const bool SELF_TEST_ENABLED;
const unsigned int SELF_TEST_MOTOR_POWER;
const unsigned int SELF_TEST_HOLD_TIME_ms;
const unsigned int SELF_TEST_TIMEOUT_ms;
const int SELF_TEST_PRESSURE_THRESHOLD_kPa;
const int SELF_TEST_TARGET_PRESSURE_kPa;
const unsigned int SELF_TEST_LOG_INTERVAL_ms;
const unsigned int PRE_BREATHING_DELAY_ms;

const unsigned int BREATHING_LOG_INTERVAL_ms;


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
