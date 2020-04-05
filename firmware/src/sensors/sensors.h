#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_ADC_ID.h"

typedef struct SensorsAllData {
    int32_t flow;
    int32_t pressure_1_pa;
    int32_t pressure_2_pa;
    int32_t oxygen;
    int32_t cycle_state;        // PeeP / Peak / None
} SensorsAllData;

typedef struct _SensorsAllData {
    int32_t flow_inhale;        // Unknonwn (only average flow / total volume MFC)
    int32_t flow_exhale;        // ml / minute ?
    int32_t pressure_inhale;
    int32_t pressure_exhale;
    int32_t pressure_patient;
    int32_t pressure_mfc;
    int32_t oxygen;             // 0-100 (should never be below 21)
    int32_t tidal_volume;       // ml
    int32_t minute_volume;      // L / minute
    int32_t cycle_state;        // PeeP / Peak / None
    int32_t power_status;
} _SensorsAllData;

void sensors_init(void);

bool sensors_calibrate_offset(void);
void sensors_reset(void);
void sensors_update(unsigned int dt);

// virtual sensors, calculated from breathing.c
void sensors_set(int32_t volume_inhale_CC,
        int32_t volume_exhale_CC,
        float oxygen_fraction);

float sensors_read_flow_SLPM(void);
int32_t sensors_read_flow_MFC_O2_SCCPM(void);
int32_t sensors_read_flow_MFC_air_SCCPM(void);

int32_t sensors_read_pressure_1_pa(void);
int32_t sensors_read_pressure_2_pa(void);
int32_t sensors_read_pressure_MFC_pa(void);
int32_t sensors_read_pressure_target_pa(void);

int32_t sensors_read_oxygen_percent(void);

void sensors_read_all(SensorsAllData *data);

#endif
