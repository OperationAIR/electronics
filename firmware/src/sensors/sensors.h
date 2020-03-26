#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_ADC_ID.h"

void sensor_init(enum ADC_ID pressure_sense_pin);

void sensors_reset(void);
void sensors_update(void);

int32_t sensors_read_pressure(void);

#endif
