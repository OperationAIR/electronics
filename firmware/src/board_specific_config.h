#ifndef BOARD_SPECIFIC_CONFIG_H
#define BOARD_SPECIFIC_CONFIG_H

#include "board_config/board_GPIO_ID.h"
#include "board_config/board_ADC_ID.h"

void board_setup(void);

void board_disable_reset_pin(void);
void board_enable_reset_pin(void);

/**
 * If a non-recoverable error occurs, 
 * call this function to trigger an emergency reset.
 *
 * The emergency reset will try to put the actuators in
 * a save state and reboot the MCU.
 */
void board_trigger_emergency_reset(void);

#endif

