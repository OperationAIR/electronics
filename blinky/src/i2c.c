#include "i2c.h"

#include <chip.h>
#include <mcu_timing/profile.h>

#define I2C_SPEED_100KHZ         100000
#define I2C_SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    I2C_SPEED_100KHZ


void I2C_IRQHandler(void)
{
    PROFILE

    Chip_I2C_MasterStateHandler(DEFAULT_I2C);
}

void i2c_init(void)
{
	Chip_SYSCTL_PeriphReset(RESET_I2C0);

	/* Initialize I2C */
	Chip_I2C_Init(DEFAULT_I2C);
	Chip_I2C_SetClockRate(DEFAULT_I2C, I2C_DEFAULT_SPEED);

    Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, Chip_I2C_EventHandler);
    NVIC_EnableIRQ(I2C0_IRQn);
}

