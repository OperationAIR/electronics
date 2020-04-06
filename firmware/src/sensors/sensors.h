#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_config/board_ADC_ID.h"



typedef struct SensorsAllData {
    int32_t flow_inhale;        // Inhale flow [mL / minute] (approximation)
    int32_t flow_exhale;        // Exhale flow [mL / minute]

    int32_t pressure_inhale;    // Inhale pressure [Pa]
    int32_t pressure_exhale;    // Exhale pressure [Pa]
    int32_t pressure_patient;   // Pressure at patient [Pa] (TODO: Not Implemented Yet)
    int32_t pressure_mfc;       // Pressure at MFC pressure vessel [Pa]

    int32_t oxygen;             // Oxygen percentage [0-100]
    int32_t tidal_volume;       // Tidal volume [mL] (Based on exhale flow)
    int32_t minute_volume;      // Average flow [mL / minute] (average over last 10 sec interval)
    int32_t cycle_state;        // PeeP / Peak / None
    int32_t power_status;       // Status of PSU (TODO: Not Implemented Yet)
} SensorsAllData;

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

// Flow into / out from patient
int32_t sensors_read_flow_in_SCCPM(void);
int32_t sensors_read_flow_out_SCCPM(void);

// Average over last 10 seconds
int32_t sensors_read_flow_out_avg_SCCPM(void);

// Flows at MFC
int32_t sensors_read_flow_MFC_O2_SCCPM(void);
int32_t sensors_read_flow_MFC_air_SCCPM(void);

int32_t sensors_read_pressure_in_pa(void);
int32_t sensors_read_pressure_out_pa(void);
int32_t sensors_read_pressure_patient_pa(void);
int32_t sensors_read_pressure_MFC_pa(void);
int32_t sensors_read_pressure_target_pa(void);

int32_t sensors_read_oxygen_percent(void);


// Realtime volumes: value since start of cycle, at THIS moment
// (usefull for plots)
int32_t sensors_read_volume_realtime_MFC_O2_CC(void);
int32_t sensors_read_volume_realtime_MFC_air_CC(void);

int32_t sensors_read_volume_realtime_in_CC(void);
int32_t sensors_read_volume_realtime_out_CC(void);

// Tidal volumes: total volume during last cycle
int32_t sensors_read_volume_cycle_in_CC(void);
int32_t sensors_read_volume_cycle_out_CC(void);


// Read all data relevant for communication to RPI
void sensors_read_all(SensorsAllData *data);

#endif
