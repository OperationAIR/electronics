#ifndef BOARD_SPECIFIC_CONFIG_H
#define BOARD_SPECIFIC_CONFIG_H

#include "board_config/board_GPIO_ID.h"
#include "board_config/board_ADC_ID.h"

void board_setup(void);

void board_disable_reset_pin(void);
void board_enable_reset_pin(void);

#endif

