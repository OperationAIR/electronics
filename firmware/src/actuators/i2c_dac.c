#include "i2c_dac.h"

// lpc11ux only has 1 i2c peripheral
#define DEFAULT_I2C          I2C0

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
void i2cdac_init(int speed)
{

	Chip_SYSCTL_PeriphReset(RESET_I2C0);

	/* Initialize I2C */
	Chip_I2C_Init(DEFAULT_I2C);
	Chip_I2C_SetClockRate(DEFAULT_I2C, speed);

	i2c_set_mode(0);
}

void i2cdac_set(uint8_t address, uint16_t value)
{
    //log_debug("I2cDAC: set 0x%X to %d", (unsigned int)address, (int)value);
    // TODO how long can this block at maximum?
    // Should a timeout be added??

    // only use lower 12 bits
    uint16_t v = value & 0x0FFF;

    // I2C send/receive structure
	I2C_XFER_T xfer;

	// Transfer buffer
	uint8_t tx[3];

	/* Setup I2C parameters to send 4 bytes of data */
	xfer.slaveAddr = address;
	tx[0] = 0x40; // set 12bit dac output command
    tx[1] = v / 16;
    tx[2] = (v % 16) << 4;

	xfer.txBuff = &tx[0];

	/* Send data */
	Chip_I2C_MasterSend(DEFAULT_I2C, xfer.slaveAddr, xfer.txBuff, 3);


}
