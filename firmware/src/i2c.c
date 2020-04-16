#include "i2c.h"

#include <chip.h>
#include <mcu_timing/delay.h>
#include <memory.h>

#define I2C_SPEED_100KHZ         100000
#define I2C_SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    I2C_SPEED_100KHZ


static bool g_i2c_error = false;

static void _set_error(void)
{
    g_i2c_error = true;
}
static void _clear_error(void)
{
    g_i2c_error = false;
}

void I2C_IRQHandler(void)
{
    Chip_I2C_MasterStateHandler(DEFAULT_I2C);
}

I2C_XFER_T g_xfer = {0};

static void _event_handler(I2C_ID_T id, I2C_EVENT_T event)
{

	// Only WAIT event needs to be handled
	if (event != I2C_EVENT_WAIT) {
		return;
	}

    delay_timeout_t timeout;
    delay_timeout_set(&timeout, 1000);
	volatile I2C_STATUS_T *stat = &g_xfer.status;

	// Wait for the status to change
	while (*stat == I2C_STATUS_BUSY) {
        if(delay_timeout_done(&timeout)) {
            //_set_error(); // may set error in context of 'wrong' sensor
            break;
        }
    }
}


static void _do_transfer(int len) {
    delay_timeout_t timeout;
    delay_timeout_set(&timeout, 1000);
    while (Chip_I2C_MasterTransfer(DEFAULT_I2C, &g_xfer) == I2C_STATUS_ARBLOST) {
        if(delay_timeout_done(&timeout)) {
            _set_error();
            return;
        }
    }
}



void i2c_init(void)
{
    _clear_error();

	Chip_SYSCTL_PeriphReset(RESET_I2C0);

	// Initialize I2C
	Chip_I2C_Init(DEFAULT_I2C);
	Chip_I2C_SetClockRate(DEFAULT_I2C, I2C_DEFAULT_SPEED);

    Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, _event_handler);
    NVIC_EnableIRQ(I2C0_IRQn);
}

void i2c_read(uint8_t slaveAddr, uint8_t cmd, uint8_t *buff, int len)
{
    memset(&g_xfer, 0, sizeof(g_xfer));
	g_xfer.slaveAddr = slaveAddr;
	g_xfer.txBuff = &cmd;
	g_xfer.txSz = 1;
	g_xfer.rxBuff = buff;
	g_xfer.rxSz = len;

    _do_transfer(len);

    const int remaining = g_xfer.rxSz;
    if(remaining) { 
        _set_error();
    }
}

//Chip_I2C_MasterSend(DEFAULT_I2C, slaveAddr, buff, len);
void i2c_write(uint8_t slaveAddr, const uint8_t *buff, uint8_t len)
{
    memset(&g_xfer, 0, sizeof(g_xfer));
	g_xfer.slaveAddr = slaveAddr;
	g_xfer.txBuff = buff;
	g_xfer.txSz = len;

    _do_transfer(len);

    const int remaining = g_xfer.txSz;
    if(remaining) { 
        _set_error();
    }
}


bool i2c_check_and_clear_error(void)
{
    bool err = g_i2c_error;

    _clear_error();

    return err;
}

