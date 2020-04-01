#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_ADC_ID.h"

typedef struct SensorsAllData {
    int32_t flow;
    int32_t pressure_1_pa;
    int32_t pressure_2_pa;
    int32_t oxygen;
} SensorsAllData;

void sensors_init(void);

bool sensors_calibrate_offset(void);
void sensors_reset(void);
void sensors_update(void);

int32_t sensors_read_pressure_1_pa(void);
int32_t sensors_read_pressure_2_pa(void);
int32_t sensors_read_pressure_MFC_pa(void);
int32_t sensors_read_pressure_target_pa(void);

// deprecated..?
int32_t sensors_read_pressure_regulator(void);

void sensors_read_all(SensorsAllData *data);
#endif
