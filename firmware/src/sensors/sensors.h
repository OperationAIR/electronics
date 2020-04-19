#ifndef _SENSORS_H
#define _SENSORS_H

#include <stdint.h>
#include "board_config/board_ADC_ID.h"
#include "UPS_status.h"
#include <c_utils/static_assert.h>



typedef struct __attribute__((packed)) {
    int32_t flow_inhale;        // Inhale flow [mL / minute] (approximation)
    int32_t flow_exhale;        // Exhale flow [mL / minute]

    int32_t pressure_inhale;    // Inhale pressure [Pa]
    int32_t pressure_exhale;    // Exhale pressure [Pa]
    int32_t pressure_patient;   // Pressure at patient [Pa] (NOTE: may not be available)
    int32_t pressure_mfc;       // Pressure at MFC pressure vessel [Pa]

    int32_t oxygen;                 // Oxygen percentage [0-100]
    int32_t tidal_volume_inhale;    // Tidal volume [mL] (Based on inhale flow)
    int32_t tidal_volume_exhale;    // Tidal volume [mL] (Based on exhale flow)
    int32_t minute_volume;          // Average flow (exhale) [mL / minute] (average over last 10 sec interval)
    int32_t cycle_state;            // PeeP / Peak / None

    int32_t inspiratory_hold_result;// Value for end of inspiratory hold sensor 1
    int32_t expiratory_hold_result; // Value for end of expiratory hold sensor 1

    uint32_t power_status;          // Status of UPS: volatage [mV OR-ed with UPSStatus bits]
    uint32_t system_status;         // enum SystemStatus value(s) OR-ed together

} SensorsAllData;

STATIC_ASSERT(sizeof(SensorsAllData) == (15*4));


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

int32_t sensors_read_pressure_insp_pa(void);
int32_t sensors_read_pressure_exp_pa(void);
int32_t sensors_read_pressure_patient_pa(void);
int32_t sensors_read_pressure_MFC_pa(void);
int32_t sensors_read_pressure_target_pa(void);

int32_t sensors_read_oxygen_percent(void);

int32_t sensors_read_raw_MFC_O2_mv(void);
int32_t sensors_read_raw_MFC_air_mv(void);


// Realtime volumes: value since start of cycle, at THIS moment
// (usefull for plots)
int32_t sensors_read_volume_realtime_MFC_O2_CC(void);
int32_t sensors_read_volume_realtime_MFC_air_CC(void);

int32_t sensors_read_volume_realtime_in_CC(void);
int32_t sensors_read_volume_realtime_out_CC(void);

// Tidal volumes: total volume during last cycle
int32_t sensors_read_volume_cycle_in_CC(void);
int32_t sensors_read_volume_cycle_out_CC(void);

int32_t sensors_get_inspiratory_hold_result(void);
int32_t sensors_get_expiratory_hold_result(void);

bool sensors_read_button_pressed(void);

// Read all data relevant for communication to RPI
void sensors_read_all(SensorsAllData *data);


// Power supply status & voltage
// NOTE: prototype V0 hardware does not have UPS status info
enum UPSStatus sensors_read_UPS_status(void);
uint32_t sensors_read_UPS_voltage_mv(void);


#endif
