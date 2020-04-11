#ifndef I2C_DAC_H
#define I2C_DAC_H

#include <chip.h>

#define ADDDRESS_O2         0x62
#define ADDDRESS_AIR        0x63

bool i2cdac_init(void);
bool i2cdac_set(uint8_t address, uint16_t value);

#endif
