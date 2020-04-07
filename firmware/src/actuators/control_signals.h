#ifndef CONTROL_SIGNALS_H
#define CONTROL_SIGNALS_H

#include <stdbool.h>

void control_signals_init(void);

bool control_MFC_set(float flow_SLPM, float O2_fraction);

void control_LED_status_on(void);
void control_LED_status_off(void);
void control_LED_status_toggle(void);

void control_LED_error_on(void);
void control_LED_error_off(void);
void control_LED_error_toggle(void);

bool control_valve_insp_on(int pwm_value);
void control_valve_insp_off(void);

void control_valve_exp_on(int pwm_value_below_10000);
void control_valve_exp_off(void);

// TODO pwm extra port
//void control_switch2_on(void);
//void control_switch2_off(void);

// Directly control MFC DAC (internal/test only)
void control_raw_MFC_O2_mv(int mv);
void control_raw_MFC_air_mv(int mv);


#endif
