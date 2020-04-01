#ifndef I2C_DAC_H
#define I2C_DAC_H

#include <chip.h>

#define I2C_SPEED_100KHZ         100000
#define I2C_SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    I2C_SPEED_100KHZ

#define ADDDRESS_O2         0x62
#define ADDDRESS_AIR        0x63

void i2cdac_init(int speed);
void i2cdac_set(uint8_t address, uint16_t value);

void flowsensor_test(void);

#endif
