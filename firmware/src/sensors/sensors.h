#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_ADC_ID.h"

void sensors_init(void);

void sensors_reset(void);
void sensors_update(void);

int32_t sensors_read_pressure(void);

#endif
