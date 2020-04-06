#ifndef CONTROL_SIGNALS_H
#define CONTROL_SIGNALS_H

#include <stdbool.h>

void control_signals_init(void);


bool control_DPR_on(void);
bool control_DPR_off(void);
bool control_DPR_set_pa(int pressure_pa);
bool control_MFC_set(float flow_SLPM, float O2_fraction);

void control_LED_status_on(void);
void control_LED_status_off(void);
void control_LED_status_toggle(void);

void control_LED_error_on(void);
void control_LED_error_off(void);
void control_LED_error_toggle(void);

//void control_switch1_on(void);
void control_switch1_off(void);
void control_switch1_on(int pwm_value_below_10000);

void control_switch2_on(void);
void control_switch2_off(void);

#endif
