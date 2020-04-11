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
#include "version.h"

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

    pi_comm_init();

    delay_init();
    logging_init();

    // USB init
    delay_us(200 * 1000);

    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }

    i2c_init();
    control_signals_init();

    const int hw_version = version_hardware_get();

    app_init(hw_version);
    app_cli_init();
    watchdog_init();

    pi_comm_send_string("Hallo Ventilator!\n");

    control_LED_status_on();

    delay_us(1000*1000);
    control_LED_status_off();

    while (true)
    {
        pi_comm_tasks();
        add_cli_tasks();
        log_tasks();

        // Maybe only feed watchdog if some sanity checks succeed?
        watchdog_feed();

        delay_us(1);
    }
    return 0;
}

void HardFault_Handler(void)
{
    // Should never happen: system has crashed.
    // Watchdog will reboot the system eventually...
    while (1);
}

