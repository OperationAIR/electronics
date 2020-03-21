#include "global_settings.h"

/**********************************************************
* || GLOBAL SETTINGS ||
* This file contains settings that can be configured to
* change the behaviour of the ventilator firmware.
/ ********************************************************/

/**
* BUTTON INTERVALS
* ================
*
* These constants define what happens when pressing
* the button for x milliseconds.
*
* NOTE: keep in this specific order (from low to high)
*/

// Start triggers on touch up after interval
const unsigned int BUTTON_TIME_PROGRAM_START_ms = 10;

// Abort triggers while button is still pressed
const unsigned int BUTTON_TIME_PROGRAM_ABORT_ms = 1*1000;

// Test triggers on touch up after interval
const unsigned int BUTTON_TIME_SELF_TEST_ms = 3*1000;

// Bootloader(reset) triggers while button is still pressed
// should be the longest interval, since it causes a reset
const unsigned int BUTTON_TIME_FIRMWARE_UPDATE_ms = 5*1000;

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
// OVERRIDE_NOT_ALLOWED when set to true, limits will be ignored
// and breathing program can start regardless of exceeded maxima.
const bool OVERRIDE_NOT_ALLOWED = false;
// WARINING: ONLY USE DURING DEVELOPMENT,

// Enable sleep to save power during idle state
const bool ENABLE_SLEEP = false;

// Enable wakeup on USB connect (to computer)
// Set to false for preventing random issues, with usb-connector
const bool ENABLE_USB_WAKEUP = false;

// Turn on led in deep sleep.
// ONLY FOR DEBUGGING
const bool ENABLE_SLEEP_LED = false;
const bool ENABLE_SLEEP_GPIO = false;


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

/**
* BREATHING SETTINGS
* =================
* The breathing program consists of multiple subprograms.
* The subprograms are defined in the `breathing_program` array below by settings
* the following properties
* {
    .type = BREATHING_PROGRAM_TYPE_A or BREATHING_PROGRAM_TYPE_B,

    // pressure up
    .motor_power_pressure = constant motor power while building pressure [0-100%],
    .max_pressure = maximum target pressure or limit [kPa]
    .cycle_time_pressure = maximum time building pressure per cycle

    // pressure down
    .motor_power_vaccuum = constant motor power while building vaccuum [0-100%],
    .min_pressure = maximum vacuum pressure or limit [kPa]
    .cycle_time_vaccuum = maximum time vaccuum per cycle

    .num_cycles = maximum number of cycles in subprogram
    .max_time = maximum time in milliseconds for subprogram
    },
*/

const BreathingProgram breathing_program = {

    .subprograms = {
        {
            .type = BREATHING_PROGRAM_TYPE_A,

            // pressure up
            .motor_power_pressure = 100,
            .max_pressure = 180,
            .cycle_time_pressure = 600,

            // pressure down
            .motor_power_vaccuum = 100,
            .min_pressure = 50,
            .cycle_time_vaccuum = 750,

            .num_cycles = 50,
            .max_time = 30*1000

        },
        {
            //program so breathing stops without air in mouthpiece
            .type = BREATHING_PROGRAM_TYPE_A,

            //pressure down
            .motor_power_vaccuum = 100,
            .min_pressure = 50,
            .cycle_time_vaccuum = 1000,

            .num_cycles = 1,
            .max_time = 1000
        }

    // ... add more subprograms here,
    // max number of subprograms is 10

    },
};


// The rate pressure is logged during regular breathing program.
// Interval in milliseconds.
const unsigned int BREATHING_LOG_INTERVAL_ms = 100;

/**
* Choose the valve that delivers the over pressure (blows)
* options: VALVE1, VALVE2
*/
enum VALVES VALVE_FOR_OVER_PRESSURE = VALVE1;

/* === */
