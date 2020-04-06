#ifndef CACLUATED_H
#define CACLUATED_H


#include "breathing.h"


/**
 * Virtual 'sensor' values that are calculated based on measurements
 * during the breathing process
 *
 * See sensors.h
 */

void calculated_init(void);

/**
 * Called from breathing_run every dt ms to update all calculations
 */
void calculated_update(enum BreathCycleState cycle_state, int dt);


int32_t calculated_volume_realtime_MFC_O2_CC(void);
int32_t calculated_volume_realtime_MFC_air_CC(void);
int32_t calculated_volume_realtime_MFC_CC(void);

int32_t calculated_volume_realtime_in_CC(void);
int32_t calculated_volume_realtime_out_CC(void);

/**
 * Calculate oxygen percentage [0-100] based on flow from
 * MassFlowControllers. Note: the value is filtered to simulate
 * the slow mixing in the mixing chamber. Percentage is fully settled
 * within 10 breathing cycles.
 */
int32_t calculated_oxygen_percent(void);
int32_t calculated_volume_in_CC(void);
int32_t calculated_volume_out_CC(void);
int32_t calculated_flow_out_avg_SCCPM(void);


#endif

