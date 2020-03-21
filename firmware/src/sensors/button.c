#include <chip.h>

#include <lpc_tools/GPIO_HAL_LPC.h>
#include <mcu_timing/delay.h>

#include "button.h"
#include "clock.h"
#include "global_settings.h"

volatile enum BUTTON_STATUS g_status;

#define GPIO_PININT_FALLING_INDEX		0
#define GPIO_PININT_RISING_INDEX		1
#define PININT_FALLING_IRQ_HANDLER	FLEX_INT0_IRQHandler /* PININT IRQ function name */
#define PININT_RISING_IRQ_HANDLER	FLEX_INT1_IRQHandler /* PININT IRQ function name */

static volatile uint64_t button_press;
static bool bootloader_ready = false;

static void reset_status()
{
    g_status = BUTTON_STATUS_NOTHING;
}

bool button_is_idle(void)
{
    // No button press 'in progress' or queued for handling
    return (!(button_press) && (g_status == BUTTON_STATUS_NOTHING));
}

enum BUTTON_STATUS button_get_status()
{
    if (button_press) {
        uint64_t button_interval_us = delay_calc_time_us(button_press, clock_get_time());

        // Actions on button pressed > predefined time
        if (button_interval_us > BUTTON_TIME_PROGRAM_ABORT_ms * 1000) {
            g_status = BUTTON_STATUS_STOP;
        }
        if ((button_interval_us > BUTTON_TIME_FIRMWARE_UPDATE_ms * 1000) && !bootloader_ready) {
            bootloader_ready = true;
            g_status = BUTTON_STATUS_BOOTLOADER_READY; //BUTTON_STATUS_BOOTLOADER;
        }
    }

    enum BUTTON_STATUS status = g_status;

    if (!button_press) {
        reset_status();
    }

    return status;
}

void PININT_FALLING_IRQ_HANDLER(void) {
    Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(GPIO_PININT_FALLING_INDEX));
    // reset_status(&g_status);
    button_press = clock_get_time();
}

void PININT_RISING_IRQ_HANDLER(void) {
    Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(GPIO_PININT_RISING_INDEX));

    if(!button_press) {
        return;
    }
    uint64_t button_interval_us = delay_calc_time_us(button_press, clock_get_time());

    // Actions on button going up
    if (bootloader_ready) {
        g_status = BUTTON_STATUS_BOOTLOADER;
        bootloader_ready = false;
    }

    if ((button_interval_us > BUTTON_TIME_PROGRAM_START_ms * 1000) &&
        (button_interval_us < BUTTON_TIME_PROGRAM_ABORT_ms * 1000)) {
        g_status = BUTTON_STATUS_START;
    }
    if ((button_interval_us > BUTTON_TIME_SELF_TEST_ms * 1000) &&
        (button_interval_us < BUTTON_TIME_FIRMWARE_UPDATE_ms * 1000)) {
        g_status = BUTTON_STATUS_TEST;
    }

    button_press = 0;

}

void button_init(const GPIO *button_pin) {

    reset_status();
    /* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PINT);

	// /* Configure interrupt channel for the GPIO pin in SysCon block */
	Chip_SYSCTL_SetPinInterrupt(GPIO_PININT_FALLING_INDEX, button_pin->port, button_pin->pin);

	// /* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH(GPIO_PININT_FALLING_INDEX));
	Chip_PININT_EnableIntLow(LPC_PININT, PININTCH(GPIO_PININT_FALLING_INDEX));
	NVIC_EnableIRQ(PIN_INT0_IRQn);


    /* Configure interrupt channel for the GPIO pin in SysCon block */
	Chip_SYSCTL_SetPinInterrupt(GPIO_PININT_RISING_INDEX, button_pin->port, button_pin->pin);

	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH(GPIO_PININT_RISING_INDEX));
	Chip_PININT_EnableIntHigh(LPC_PININT, PININTCH(GPIO_PININT_RISING_INDEX));

    NVIC_EnableIRQ(PIN_INT1_IRQn);

    /* Configure channel as wake up interrupt in SysCon block */
    // Chip_SYSCTL_EnablePINTWakeup(GPIO_PININT_INDEX);

}
