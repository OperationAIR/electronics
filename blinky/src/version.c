#include "version.h"
#include "generated/firmware_version.h"
#include <lpc_tools/GPIO_HAL.h>
#include <lpc_tools/GPIO_HAL_LPC.h>

#include <lpc_tools/boardconfig.h>
#include <c_utils/static_assert.h>
#include <c_utils/array.h>
#include <stddef.h>

#include <chip.h>

#ifndef FIRMWARE_VERSION
    #error "Please define FIRMWARE_VERSION in the Makefile"
#endif



const char * version_firmware_get_str(void)
{
    return FIRMWARE_VERSION;
}


#define HW_NUM_VERSION_BITS (1)

static const PinMuxConfig hw_bit_pinmuxing[] = {

        // Hardware version bits
        { 0, 20, (IOCON_FUNC0 
                | IOCON_MODE_PULLUP)}   // HW_VERSION_B0
};

STATIC_ASSERT(HW_NUM_VERSION_BITS == (sizeof(hw_bit_pinmuxing) / \
        sizeof(hw_bit_pinmuxing[0])));

static const GPIO hw_bit_pins[] = {
    // port , pin
    {0      , 20    },
};

STATIC_ASSERT(HW_NUM_VERSION_BITS == (sizeof(hw_bit_pins) / \
        sizeof(hw_bit_pins[0])));



int version_hardware_get(void)
{
    // NOTE: this function should not have dependencies on board_get_GPIO etc
    // because it is needed very early during startup.
    // Therefore we need to do pinmuxing etc ourselves.

    // apply pinmuxing
    for(size_t i=0;i<array_length(hw_bit_pinmuxing);i++) {
        const PinMuxConfig cfg = hw_bit_pinmuxing[i];
        Chip_IOCON_PinMuxSet(LPC_IOCON, cfg.pingrp, cfg.pinnum, cfg.modefunc);
    }

    // Calculate version no
    int version = 0;
    for (size_t bit=0;bit<HW_NUM_VERSION_BITS;bit++) {

        const GPIO IO = hw_bit_pins[bit];
        Chip_GPIO_SetPinDIRInput(LPC_GPIO, IO.port, IO.pin);

        version|= ((!Chip_GPIO_GetPinState(LPC_GPIO,
                    IO.port, IO.pin)) << bit);
    }
    
    return version;
}

