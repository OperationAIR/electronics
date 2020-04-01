#include "i2c_dac.h"
#include <c_utils/assert.h>
#include <stddef.h>
#include <c_utils/f2strn.h>

// TODO RM
#include "log.h"

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

    i2cdac_set(ADDDRESS_O2, 0);
    i2cdac_set(ADDDRESS_AIR, 0);
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


static void _flowsensor_boot(void) {
    // The flowsensor may be in 'bootloader mode' after first power-on.
    // This command switches the sensor to 'sensor mode'.
    uint8_t rx[1];
    const uint8_t boot_addr = 0x42;
    const uint8_t boot_reg = 0x45;
    // If this fails, the sensor was probably already in 'sensor mode'.
    Chip_I2C_MasterCmdRead(DEFAULT_I2C, boot_addr, boot_reg, rx, sizeof(rx));
}

static bool _flowsensor_selftest(void) {
    uint8_t rx[1] = {0};
    const uint8_t sensor_addr = 0x55;
    const uint8_t boot_reg = 0x19;
    size_t bytes_received = Chip_I2C_MasterCmdRead(DEFAULT_I2C, sensor_addr, boot_reg, rx, sizeof(rx));

    return ((bytes_received == 1) && (rx[0] == sensor_addr));
}

static float _read_sensor(uint8_t data_reg) {
    const uint8_t sensor_addr = 0x55;

    union {
        float value;
        uint8_t bytes[4];
    } conversion;


    size_t result = Chip_I2C_MasterCmdRead(DEFAULT_I2C, sensor_addr, data_reg,
            conversion.bytes, sizeof(conversion.bytes));
    if(result != sizeof(conversion.bytes)) {
        return 0.0;
    }
    return conversion.value;
}

static float _read_flow(void)
{
     return _read_sensor(0x1);
}
static float _read_temp_celcius(void)
{
     return _read_sensor(0x2);
}


bool flowsensor_enable(void)
{
    // boot sensor in case it is not already booted
    _flowsensor_boot();

    if(!_flowsensor_selftest()) {
        log_debug("Flowsensor: enable FAIL");
        return false;
    }
    log_debug("Flowsensor: enable OK");
    return true;
}

void flowsensor_test(void)
{
    const bool ok = flowsensor_enable();
    if(!ok) {
        return;
    }

    const float temp_celcius = _read_temp_celcius();
    const float flow = _read_flow();

    char temp_str[32];
    f2strn(temp_celcius, temp_str, sizeof(temp_str), 3);

    char flow_str[32];
    f2strn(flow, flow_str, sizeof(flow_str), 3);


    log_debug("Flowsensor: temp='%s' C, flow='%s'",
            temp_str,
            flow_str);
}

