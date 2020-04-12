#include <chip.h>
#include <mcu_timing/delay.h>

#include "watchdog.h"


static uint32_t g_watchdog_interrupt_count = 0;

void WDT_IRQHandler(void)
{
    watchdog_feed();

    Chip_WWDT_ClearStatusFlag(LPC_WWDT, WWDT_WDMOD_WDINT);
    NVIC_ClearPendingIRQ(WDT_IRQn);

    // Should never happen: system has frozen!

    // 1. Watchdog will reboot the system in 0.3ms
    // 2. On startup, code will notice the system is reset by watchdog
    //      and sets the LED to indicate an error
    // 3. The code reboots into bootloader mode. This allows the
    //      system to be de-bricked by flashing a new firmware.
    // while(1);
}

void clock_add_watchdog_count(void)
{
    g_watchdog_interrupt_count++;
}

uint64_t clock_get_time(void)
{
    uint64_t t_us = delay_get_timestamp();
    uint64_t offset_us = ((uint64_t)g_watchdog_interrupt_count) * (WATCHDOG_TIMEOUT_MS * 1000);

    return (offset_us + t_us);
}

uint32_t clock_get_time_s(void)
{
    uint64_t time_us = clock_get_time();
    return (uint32_t) (time_us / 1000000);
}

void clock_add_seconds(int32_t inc_s)
{
    g_watchdog_interrupt_count += (inc_s / 2);
}
