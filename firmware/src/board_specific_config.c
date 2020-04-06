#include "board_specific_config.h"

#include "board_config/board_config_v0.h"
#include "board_config/board_config_v1.h"

#include "version.h"
#include "assert.h"

#include <stdint.h>

// Oscillator frequency, needed by chip libraries
const uint32_t OscRateIn = 12000000;
const uint32_t ExtRateIn = 0;

void board_setup(void)
{
    const int hw_version = version_hardware_get();

    switch(hw_version) {
        case 0:
            board_config_v0_setup();
            break;

        case 1:
            board_config_v1_setup();
            break;

        default:
            // unsupported board
            while(1);
    }
}

