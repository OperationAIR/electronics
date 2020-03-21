#include "thermistor.h"

#include <stddef.h>

// This lookup is based on the datasheet for part B57230V2103F260:
// 10Kohm thermistor, R/T No. 8509.
const int temp_offset_degrees = -55;
const int temp_step_degrees = 5;
static const unsigned int lookup[] = {
    446049,
    332810,
    250440,
    190030,
    145359,
    112060,
    87041,
    68104,
    53665,
    42576,
    34001,
    27326,
    22096,
    17973,
    14703,
    12093,
    10000,
    8311,
    6941,
    5825,
    4911,
    4158,
    3536,
    3019,
    2588,
    2227,
    1924,
    1668,
    1451,
    1266,
    1108,
    973,
    857,
    757,
    671,
    596,
    531,
    474,
    424,
    381,
    343,
    309
};

int thermistor_interpolate_millidegrees(unsigned int resistance_ohm)
{
    const size_t num_entries = (sizeof(lookup)/sizeof(lookup[0]));
    
    int high = lookup[0];
    int low = lookup[0];
    int delta_milliohm = 0;

    size_t offset=0;
    for(;offset<num_entries;offset++) {
        const unsigned int current = lookup[offset];

        if(current <= resistance_ohm) {
            high = current;
            delta_milliohm = (1000*resistance_ohm) - (1000*current);
            break;
        }
        low = current;
    }

    int diff = (high - low);
    int delta_millideg = (diff) ? ((delta_milliohm * temp_step_degrees)/diff) : 0;

    int low_millideg = 1000*(temp_offset_degrees + (temp_step_degrees * offset));
    return low_millideg + delta_millideg;
}

