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
const unsigned int CALIBRATION_DURATION_MS = 2000;


// Sensor data is logged during regular breathing program.
// Interval in milliseconds.
const unsigned int BREATHING_LOG_INTERVAL_ms = 30;


/* === */
