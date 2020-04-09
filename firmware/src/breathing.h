#ifndef BREATHING_H
#define BREATHING_H

#include "settings.h"

enum BreathCycleState {
    BreathCycleStateNone            = 0,
    BreathCycleStatePeakPressure    = 1,
    BreathCycleStatePeep            = 2,
    BreathCycleLastStepDone         = 3,
} BreathCycleState;


bool breathing_init(void);

void breathing_start_calibration(void);
void breathing_finish_calibration(void);

bool breathing_start_program(void);
void breathing_stop(void);
void breathing_power_off(void);

void breathing_tune_DPR_PID(float kp, float ki, float kd);
void breathing_tune_MFC_PID(float kp, float ki, float kd);
void breathing_tune_EXP_PID(float kp, float ki, float kd);
void breathing_print_DPR_PID(void);
void breathing_print_MFC_PID(void);
void breathing_print_EXP_PID(void);


int breathing_read_setpoint_pa(void);
enum BreathCycleState breathing_get_cycle_state(void);

float breathing_get_inspiratory_hold_result(void);
float breathing_get_expiratory_hold_result(void);


/**
 * Runs the breathing control loop.
 * This function needs to be called from the app timer at fixed frequency
 */
void breathing_run(const OperationSettings *config, const int dt);

void pre_hold(const OperationSettings *config, const int dt);
bool inspiratory_hold_run(const OperationSettings *config, bool hold_pressed, const int dt);
bool post_inspiratory_hold(const OperationSettings *config, const int dt);

bool expiratory_hold_run(const OperationSettings *config, bool hold_pressed, const int dt);
bool post_expiratory_hold(const OperationSettings *config, const int dt);

#endif
