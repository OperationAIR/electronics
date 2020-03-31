#ifndef I2C_DAC_H
#define I2C_DAC_H

#include <chip.h>


void i2cdac_init(int speed);
void i2cdac_set(uint8_t address, uint16_t value);

void flowsensor_test(void);

#endif
