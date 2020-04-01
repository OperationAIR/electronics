#ifndef BREATHING_H
#define BREATHING_H

enum TestState {
    TestStateNone,
    TestStateBuildPressure,
    TestStateHold,
    TestStateSuccess,
    TestStateFailed
};

bool breathing_init(void);

void breathing_start_calibration(void);
void breathing_finish_calibration(void);

bool breathing_start_program(void);
void breathing_stop(void);
void breathing_power_off(void);

void breathing_tune_DPR_PID(float kp, float ki, float kd);
void breathing_tune_MFC_PID(float kp, float ki, float kd);
void breathing_print_DPR_PID(void);
void breathing_print_MFC_PID(void);

/**
 * Runs the breathing control loop.
 * This function needs to be called from the app timer at fixed frequency
 */
void breathing_run(void);

void breathing_start_test(void);
enum TestState breathing_test(void);
enum TestState breathing_test_get_result(void);

#endif
