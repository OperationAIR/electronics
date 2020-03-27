#ifndef CONTROL_SIGNALS_H
#define CONTROL_SIGNALS_H

#include <stdbool.h>

void control_signals_init(void);

void control_LED_status_on(void);

bool control_DPR_enable(void);
bool control_DPR_set_pa(int pressure_pa);

void control_LED_status_off(void);

void control_LED_error_on(void);
void control_LED_error_off(void);

void control_switch1_on(void);
void control_switch1_off(void);
bool control_switch1_get_state(void);

void control_switch2_on(void);
void control_switch2_off(void);
bool control_switch2_get_state(void);

#endif
