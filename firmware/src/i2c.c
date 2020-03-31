#include "i2c.h"

#include <chip.h>

#define I2C_SPEED_100KHZ         100000
#define I2C_SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    I2C_SPEED_100KHZ

static int mode_poll;	/* Poll/Interrupt mode flag */


/* Set I2C mode to polling/interrupt */
static void i2c_set_mode(int polling)
{
	if (!polling) {
		mode_poll &= ~(1 << DEFAULT_I2C);
		Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, Chip_I2C_EventHandler);
		NVIC_EnableIRQ(I2C0_IRQn);
	}
	else {
		mode_poll |= 1 << DEFAULT_I2C;
		NVIC_DisableIRQ(I2C0_IRQn);
		Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, Chip_I2C_EventHandlerPolling);
	}
}

/**
 * @brief	I2C Interrupt Handler
 * @return	None
 */
void I2C_IRQHandler(void)
{
    Chip_I2C_MasterStateHandler(DEFAULT_I2C);
}

/* Initialize the I2C bus */
void i2c_init(void)
{
	Chip_SYSCTL_PeriphReset(RESET_I2C0);

	/* Initialize I2C */
	Chip_I2C_Init(DEFAULT_I2C);
	Chip_I2C_SetClockRate(DEFAULT_I2C, I2C_DEFAULT_SPEED);

	i2c_set_mode(0);
}

