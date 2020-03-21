#ifndef CONTROL_SIGNALS_H
#define CONTROL_SIGNALS_H

#include <stdbool.h>

void control_signals_init(void);

void control_valve1_open(void);
void control_valve1_close(void);
bool control_valve1_get_state(void);

void control_valve2_open(void);
void control_valve2_close(void);
bool control_valve2_get_state(void);

void control_valves_toggle(void);

#endif