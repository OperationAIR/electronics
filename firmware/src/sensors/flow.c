#include "flow.h"

#include <stddef.h>
#include <c_utils/min.h>

// This lookup is based on the datasheet for part 
// Honeywell AWM700
const int flow_offset_slpm = 0;
const int flow_step_slpm = 25;
static const unsigned int lookup[] = {
    1000,
    2990,
    3820,
    4300,
    4580,
    4720, // interpolated manually
    4860,
    4930, // interpolated manually
    5000,
};

int flow_interpolate_sccm(int sensor_voltage)
{
    if(sensor_voltage <= 0) {
        return flow_offset_slpm;
    }

    const size_t num_entries = (sizeof(lookup)/sizeof(lookup[0]));
    
    int high = lookup[0];
    int low = lookup[0];
    int delta_microvolt = 0;

    size_t offset=0;
    for(;offset<num_entries;offset++) {
        const int current = lookup[offset];

        if(current >= sensor_voltage) {
            high = current;
            delta_microvolt = (1000*sensor_voltage) - (1000*current);
            break;
        }
        low = current;
    }
    // do not go beyond end of table
    offset = min(offset, num_entries-1);

    int diff = (high - low);
    int delta_sccm = (diff) ? ((delta_microvolt * flow_step_slpm)/diff) : 0;

    int low_sccm = 1000*(flow_offset_slpm + (flow_step_slpm * offset));
    return low_sccm + delta_sccm;
}

