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
#include "power_management.h"
#include "sensors/button.h"
#include "clock.h"
#include "generated/firmware_version.h"

#define CLK_FREQ (48e6)

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
    if (!app_usb_init())
    {
        delay_us(2000 * 1000);
    }

    control_signals_init();

    const GPIO *hw_pin = board_get_GPIO(GPIO_ID_HW_VERSION0);
    int hw_version = !GPIO_HAL_get(hw_pin) + 1;

    app_init(hw_version);
    app_cli_init();
    watchdog_init();

    log_wtime("Operation Air firmware started");
    char buf[SERIAL_NUM_STR_SIZE];
    log_wtime("serial number: %s", log_get_serialnumber_str(buf, SERIAL_NUM_STR_SIZE));
    log_wtime("Firmware version: %s", FIRMWARE_VERSION);

    while (true)
    {
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

