#include "global_settings.h"

/**********************************************************
* || GLOBAL SETTINGS ||
* This file contains settings that can be configured to
* change the behaviour of the ventilator firmware.
/ ********************************************************/


/**
* LIMITS AND THRESHOLDS
* =====================
*/

// The maximum allowed pressure (positive and negative)
// in the system,
// exceeding it will trigger Maintenance Mode
const int PRESSURE_OVERLOAD_LIMIT_kPa = 180;
const int PRESSURE_UNDERLOAD_LIMIT_kPa = 30;


/**
* DEBUG AND DEVELOPMENT OPTIONS
* =====================
*/



const unsigned int PRE_BREATHING_DELAY_ms = 200;

/**
* SELF Test
* =========
* Settings that affect the leak test.
* During this test pressure will build up until
* `SELF_TEST_TARGET_PRESSURE_kPa` is reached. Then motor will turn off
* and pressure level will be monitord for SELF_TEST_HOLD_TIME_ms time. If
* the pressure level does not fall below `SELF_TEST_PRESSURE_THRESHOLD_kPa`
* the test is succesful.
*/

const bool SELF_TEST_ENABLED = false;
// Motor power used (0-100%) during test. Lower is better to
// get a more gradual pressure build up.
const unsigned int SELF_TEST_MOTOR_POWER = 50;

// Target for pressure build up in [kPa]
const int SELF_TEST_TARGET_PRESSURE_kPa = 160;

// Threshold for leak test to pass. pressure should not get lower
// than this level. Unit is [kPa].
const int SELF_TEST_PRESSURE_THRESHOLD_kPa = 145;

// Pressure hold time in milliseconds
const unsigned int SELF_TEST_HOLD_TIME_ms = 10*1000;

// Self test timeout in milliseconds. If target pressure not reached
// within this time, the test aborts and fails.
const unsigned int SELF_TEST_TIMEOUT_ms = 30*1000;

// The rate pressure is logged during test. Interval in milliseconds.
const unsigned int SELF_TEST_LOG_INTERVAL_ms = 200;


// The rate pressure is logged during regular breathing program.
// Interval in milliseconds.
const unsigned int BREATHING_LOG_INTERVAL_ms = 100;


/* === */
