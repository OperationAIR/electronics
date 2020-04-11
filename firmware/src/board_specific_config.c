#include "board_specific_config.h"

#include "board_config/board_config_v0.h"
#include "board_config/board_config_v1.h"
#include "actuators/control_signals.h"

#include <lpc_tools/boardconfig.h>


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

void board_disable_reset_pin(void)
{
    PinMuxConfig rst =  { 0, 0, IOCON_FUNC1};
    Chip_IOCON_PinMuxSet(LPC_IOCON, rst.pingrp, rst.pinnum, rst.modefunc);
}

void board_enable_reset_pin(void)
{
    PinMuxConfig rst =  { 0, 0, IOCON_FUNC0};
    Chip_IOCON_PinMuxSet(LPC_IOCON, rst.pingrp, rst.pinnum, rst.modefunc);
}

void board_trigger_emergency_reset(void)
{
    // Close inspiration valve: avoid uncontrolled rising pressure during reset
    control_valve_insp_off();

    // Close expiration valve: try to keep the PEEP if any
    control_valve_exp_off();

    // Turn on error led to signal failure
    control_LED_error_on();

    // Try to turn off MFCs to avoid triggering the overpressure valve
    control_MFC_off();

    // reset the MCU
    NVIC_SystemReset();

    // NOTE: if any of the above fails/blocks, the Watchdog timer
    // will reset the MCU as a last line of defense
}
