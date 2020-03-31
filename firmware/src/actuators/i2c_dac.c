#include "i2c_dac.h"
#include "i2c.h"
#include <c_utils/assert.h>
#include <stddef.h>


// TODO RM
#include "log.h"


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

