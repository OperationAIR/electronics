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

#include "cmsis_dsp_lib/arm_math.h"

#define CLK_FREQ (48e6)

arm_pid_instance_f32 pid_instance;

void test_pid()
{
    float Kp = 1;
    float Ki = 0.1;
    float Kd = 0.01;

    arm_pid_reset_f32(&pid_instance);

    pid_instance.Kp = Kp;
    pid_instance.Ki = Ki;
    pid_instance.Kd = Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&pid_instance, 1);

    float signal_in = 3.14;
    float signal_out = arm_pid_f32(&pid_instance, signal_in);

    log_wtime("PID in: %.3f", signal_in);

}

int main(void)
{
    board_setup();
    board_setup_NVIC();
    board_setup_pins();

    clock_set_frequency(CLK_FREQ);
    SystemCoreClockUpdate();

    delay_init();
    logging_init();

    test_pid();
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

