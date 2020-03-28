#include "board.h"
#include "board_GPIO_ID.h"
#include <lpc_tools/boardconfig.h>
#include <chip.h>
#include <stdio.h>

#include <lpc_tools/clock.h>
#include <lpc_tools/irq.h>
#include <mcu_timing/delay.h>

#include "global_settings.h"
#include "actuators/DPR.h"
#include "actuators/control_signals.h"
#include "usb/app_usb.h"
#include "watchdog.h"
#include "app.h"
#include "app_cli.h"
#include "log.h"
#include "clock.h"
#include "generated/firmware_version.h"

#include "cmsis_dsp_lib/arm_math.h"

#include <c_utils/ringbuffer.h>
#include "pi_communication.h"

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

DPR dpr;

int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

    clock_set_frequency(CLK_FREQ);
    SystemCoreClockUpdate();

    pi_comm_init();

    delay_init();
    logging_init();

    // USB init
    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }

    control_signals_init();

    const int hw_version = 0;

    app_init(hw_version);
    app_cli_init();
    watchdog_init();



    log_wtime("Operation Air firmware started");
    char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number: %s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
    log_wtime("Firmware version: %s", FIRMWARE_VERSION);


    DPR_init(&dpr, LPC_SSP1, board_get_GPIO(GPIO_ID_PREG_CS));

    const GPIO *led_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    const GPIO *led_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    GPIO_HAL_set(led_status, 1);
    GPIO_HAL_set(led_error, 1);


    uint8_t uart_buf[256];
    memset(uart_buf, 0, 256);

	snprintf((char*)uart_buf, sizeof(uart_buf) - 1, "Hallo Ventilator\n");
    pi_comm_send(uart_buf, strnlen((char*)uart_buf, sizeof(uart_buf)));
    // ringbuffer_write(&rb_Tx, uart_buf, strnlen(uart_buf, 256));
    // Chip_UART_IntEnable(LPC_USART, UART_IER_THREINT);
	// Chip_UART_SendRB(LPC_USART, &txring, buf, sizeof(buf) - 1);

    while (true)
    {
        pi_comm_tasks();
        add_cli_tasks();
        log_tasks();

        // Maybe only feed watchdog if some sanity checks succeed?
        watchdog_feed();
    }
    return 0;
}

void HardFault_Handler(void)
{
    // Should never happen: system has crashed.
    // Watchdog will reboot the system eventually...
    while (1);
}

