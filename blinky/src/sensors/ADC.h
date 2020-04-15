#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "board_config/board_ADC_ID.h"

#define ADC_RANGE (1024.0)

void ADC_init(void);
uint16_t ADC_read(enum ADC_ID id);
int32_t ADC_scale(uint16_t raw, float factor);

#endif

