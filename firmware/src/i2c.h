#ifndef I2C_H
#define I2C_H


#include <stdint.h>
#include <stdbool.h>

// lpc11ux only has 1 i2c peripheral
#define DEFAULT_I2C          I2C0

void i2c_init(void);
void i2c_read(uint8_t slaveAddr, uint8_t cmd, uint8_t *buff, int len);
void i2c_write(uint8_t slaveAddr, const uint8_t *buff, uint8_t len);

// has any error occurred? Also clears the error state
bool i2c_check_and_clear_error(void);

#endif

