#include "board.h"
#include "board_GPIO_ID.h"
#include <lpc_tools/boardconfig.h>
#include <chip.h>

#include <lpc_tools/clock.h>
#include <lpc_tools/irq.h>
#include <mcu_timing/delay.h>

#include "global_settings.h"
#include "actuators/control_signals.h"
#include "usb/app_usb.h"
#include "watchdog.h"
#include "app.h"
#include "app_cli.h"
#include "log.h"
#include "clock.h"
#include "generated/firmware_version.h"

#include "cmsis_dsp_lib/arm_math.h"

#include "sensors/MPRLS_pressure.h"

#define CLK_FREQ (48e6)

void assert(bool should_be_true)
{
    if(should_be_true) {
        return;
    }

    // Something bad happened!
    // TODO alarm, reset? (enable watchdog, mcu will be reset..)
    while(1);
}


// I2C DAC DEMO

#define DEFAULT_I2C          I2C0

#define SPEED_100KHZ         100000

#define SPEED_400KHZ         400000

#define I2C_DEFAULT_SPEED    SPEED_100KHZ

static int mode_poll;	/* Poll/Interrupt mode flag */

/* Set I2C mode to polling/interrupt */

static void i2c_set_mode(I2C_ID_T id, int polling)

{

	if (!polling) {

		mode_poll &= ~(1 << id);

		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandler);

		NVIC_EnableIRQ(I2C0_IRQn);

	}

	else {

		mode_poll |= 1 << id;

		NVIC_DisableIRQ(I2C0_IRQn);

		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandlerPolling);

	}

}

/* Initialize the I2C bus */

static void i2c_app_init(I2C_ID_T id, int speed)

{

	Chip_SYSCTL_PeriphReset(RESET_I2C0);

	/* Initialize I2C */

	Chip_I2C_Init(id);

	Chip_I2C_SetClockRate(id, speed);

	i2c_set_mode(id, 0);

}

/* State machine handler for I2C0 and I2C1 */

static void i2c_state_handling(I2C_ID_T id)

{

	if (Chip_I2C_IsMasterActive(id)) {

		Chip_I2C_MasterStateHandler(id);

	}

	else {

		Chip_I2C_SlaveStateHandler(id);

	}

}

/**

 * @brief	I2C Interrupt Handler

 * @return	None

 */

void I2C_IRQHandler(void)

{

	i2c_state_handling(I2C0);

}



static void I2C_DAC_DEMO(void)
{
	i2c_app_init(I2C0, I2C_DEFAULT_SPEED);

	 /* I2C send/receive structure */

	static I2C_XFER_T xfer;

	/* Transfer and Receive buffers */

	static uint8_t tx[10];//, rx[10];

    memset(tx, 0, sizeof(tx));

	uint8_t address = 0x62;

	/* Setup I2C parameters to send 4 bytes of data */

	xfer.slaveAddr = address;

	tx[0] = 0x40;

    // 400 is ca 15 l/m
    uint16_t output = 400;

    tx[1] = output / 16;

    tx[2] = (output % 16) << 4;

	xfer.txBuff = &tx[0];

	/* Send data */

	Chip_I2C_MasterSend(I2C0, xfer.slaveAddr, xfer.txBuff, 3);



}



// I2C DAC END



int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

    clock_set_frequency(CLK_FREQ);
    SystemCoreClockUpdate();

    delay_init();
    logging_init();

    // USB init
    delay_us(200 * 1000);

    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }

    control_signals_init();

I2C_DAC_DEMO();

    const int hw_version = 0;

    app_init(hw_version);
    app_cli_init();
    watchdog_init();

    /*
    log_wtime("Operation Air firmware started");
    char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number: %s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
    log_wtime("Firmware version: %s", FIRMWARE_VERSION);
    */


    while (true)
    {
        add_cli_tasks();
        log_tasks();

        // Maybe only feed watchdog if some sanity checks succeed?
        watchdog_feed();

        delay_us(1000 * 1000);

    }
    return 0;
}

void HardFault_Handler(void)
{
    // Should never happen: system has crashed.
    // Watchdog will reboot the system eventually...
    while (1);
}

