#include "global_settings.h"

/**********************************************************
* || GLOBAL SETTINGS ||
* This file contains settings that can be configured to
* change the behaviour of the ventilator firmware.
/ ********************************************************/




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

// Offset calibration at startup takes this amount of time
const unsigned int CALIBRATION_DURATION_MS = 5000;

// When breathing is stopped, valve is opened for this duration before closing
const unsigned int BREATHING_FINAL_STOP_DURATION_MS = 3000;

// Sensor data is logged during regular breathing program.
// Interval in milliseconds.
const unsigned int BREATHING_LOG_INTERVAL_ms = 10;

// Averaging calculations (see calculated.c) are averaged over this time
const unsigned int CALCULATED_AVERAGING_TIME_MS = 10000;

// used for programming without I2C pull-up
// TODO remove in final version
const bool I2C_PULL_UP_AVAILABLE = false;
/* === */
