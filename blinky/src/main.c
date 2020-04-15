#include "board_specific_config.h"
#include "board_config/board_GPIO_ID.h"
#include <lpc_tools/boardconfig.h>
#include <chip.h>
#include <stdio.h>
#include <string.h>

#include <lpc_tools/clock.h>
#include <lpc_tools/irq.h>
#include <mcu_timing/delay.h>
#include <mcu_timing/profile.h>

#include "i2c.h"
#include "global_settings.h"
#include "actuators/control_signals.h"
#include "usb/app_usb.h"
#include "watchdog.h"
#include "app.h"
#include "app_cli.h"
#include "log.h"
#include "clock.h"
#include "generated/firmware_version.h"

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


int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

    clock_set_frequency(CLK_FREQ);
    SystemCoreClockUpdate();

    delay_init();

    pi_comm_init();

    const GPIO *LED_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    const GPIO *LED_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    delay_us(200 * 1000);
    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }
    delay_us(2000 * 1000);

    log_debug("Hello world\n");
    pi_comm_send_string("Hallo UART!\n");

    uint32_t count = 0;
    while (true)
    {
        GPIO_HAL_toggle(LED_status);
        GPIO_HAL_set(LED_error, 1);
        delay_us(100*1000);

        GPIO_HAL_set(LED_error, 0);
        delay_us(10*1000);

        log_debug(" iteration %u\n", count++);

        char *buf[100];
        snprintf(buf, 100, " Iteration %u\n", count);
        pi_comm_send_string(buf);
    }
    return 0;
}

void HardFault_Handler(void)
{
    // Should never happen: system has crashed.
    // Watchdog will reboot the system eventually...
    while (1);
}

