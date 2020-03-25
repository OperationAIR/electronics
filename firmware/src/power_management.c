#include <chip.h>
#include "watchdog.h"
#include "global_settings.h"
#include "clock.h"
#include "app_usb.h"

// includes for debugging
#include <mcu_timing/delay.h>

void power_management_deep_sleep()
{
    const bool enable_usb_wakeup = (
        ENABLE_USB_WAKEUP
        // USB not suspended: somehow not ready for deep sleep
        && (LPC_USB->DEVCMDSTAT & (1 << 17)));

    if (enable_usb_wakeup) {

        // Configure USB for wake up event
        // See manual 11.7.6 USB wake-up
        // TODO add a timeout here
        Chip_SYSCTL_SetUSBCLKCTRL(0, 0);            // 1. AP_CLK to 0
        // 2. USB suspend is already checked above

        // 3. Poll untill need_clock goes low (should take up to 2ms)
        delay_timeout_t usb_timeout;
        delay_timeout_set(&usb_timeout, 5000);
        while(Chip_SYSCTL_GetUSBCLKStatus()) {

            // Timeout: apparently USB is not ready for sleep after all
            if (delay_timeout_done(&usb_timeout)) {
                return;
            }
        }
        NVIC_EnableIRQ(USB_WAKEUP_IRQn);            // 4. Enable and clear wakeup IRQ
        NVIC_ClearPendingIRQ(USB_WAKEUP_IRQn);
        Chip_SYSCTL_SetUSBCLKCTRL(0, 1);            // 5. Configure wakeup polarity

        Chip_SYSCTL_EnablePeriphWakeup(SYSCTL_WAKEUP_USB_WAKEUP); // 6. Enable wakeup
        // 7. See below
        // 8. See below

    } else {

        // No USB wakeup: deinit / power down the USB hardware
        app_usb_deinit();
    }



    Chip_WWDT_ClearStatusFlag(LPC_WWDT, WWDT_WDMOD_WDINT);
    NVIC_ClearPendingIRQ(WDT_IRQn);
    NVIC_EnableIRQ(WDT_IRQn);

    /* We can optionally call Chip_SYSCTL_SetDeepSleepPD() to power down the
		   BOD and WDT if we aren't using them in deep sleep modes. */
	Chip_SYSCTL_SetDeepSleepPD(SYSCTL_DEEPSLP_BOD_PD);

    Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_IRC);

    // Configure Wake up events
    Chip_SYSCTL_EnablePINTWakeup(0);
    Chip_SYSCTL_EnablePINTWakeup(1);
    Chip_SYSCTL_EnablePeriphWakeup(SYSCTL_WAKEUP_WWDTINT);


    /* We should call Chip_SYSCTL_SetWakeup() to setup any peripherals we want
        to power back up on wakeup. For this example, we'll power back up the IRC,
        FLASH, the system oscillator, and the PLL */

    // NOTE: USB does not use the USBPLL,
    // so don't wakeup SYSCTL_SLPWAKE_USBPLL_PD
    Chip_SYSCTL_SetWakeup(~(
        SYSCTL_SLPWAKE_FLASH_PD |
        SYSCTL_SLPWAKE_SYSOSC_PD |
        SYSCTL_SLPWAKE_ADC_PD |
        SYSCTL_SLPWAKE_SYSPLL_PD |
        SYSCTL_SLPWAKE_IRC_PD |
        SYSCTL_SLPWAKE_IRCOUT_PD));


    // Enter MCU Deep Sleep mode
    Chip_PMU_DeepSleepState(LPC_PMU);

    // Quickly feed the watchdog as it may be nearly expired
    watchdog_feed();

    // If wake up was because of watchdog interrupt
    // count it to keep track of time
    if (NVIC_GetPendingIRQ(WDT_IRQn)) {
        clock_add_watchdog_count();
        Chip_WWDT_ClearStatusFlag(LPC_WWDT, WWDT_WDMOD_WDINT);
        NVIC_ClearPendingIRQ(WDT_IRQn);
    }


    // Wake up..
    Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);


    NVIC_DisableIRQ(WDT_IRQn);
    NVIC_DisableIRQ(USB_WAKEUP_IRQn);


    // USB hardware was disabled and needs to be re-enabled
    if(!enable_usb_wakeup) {
        app_usb_init();
    }
}


void power_management_sleep()
{
    SCB->SCR &= ~(1UL << SCB_SCR_SLEEPDEEP_Pos);
    Chip_PMU_SleepState(LPC_PMU);
}

void USBWakeup_IRQHandler(void)
{

}
