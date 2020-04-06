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

/**
 * Read sensor data with the functions below.
 * Convention is to end the function with the (SI) unit of measurement
 * to avoid confusion.
 *
 * Note: any process that outputs a meaningfull value
 * is considered a 'sensor'. Not all of these sensors are 1-to-1 mapped
 * to actual hardware-based sensors: some are based on calculations or
 * conbined values from multiple sensors
 */
float sensors_read_flow_SLPM(void);
int32_t sensors_read_flow_MFC_O2_SCCPM(void);
int32_t sensors_read_flow_MFC_air_SCCPM(void);

int32_t sensors_read_pressure_1_pa(void);
int32_t sensors_read_pressure_2_pa(void);
int32_t sensors_read_pressure_MFC_pa(void);
int32_t sensors_read_pressure_target_pa(void);

int32_t sensors_read_oxygen_percent(void);


// Realtime volumes: value since start of cycle, at THIS moment
// (usefull for plots)
int32_t sensors_read_volume_realtime_MFC_O2_CC(void);
int32_t sensors_read_volume_realtime_MFC_air_CC(void);

// Tidal volumes: total volume during last cycle
int32_t sensors_read_volume_cycle_in_CC(void);
int32_t sensors_read_volume_cycle_out_CC(void);


// Read all data relevant for communication to RPI
void sensors_read_all(SensorsAllData *data);

#endif
