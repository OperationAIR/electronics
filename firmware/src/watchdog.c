#include "watchdog.h"

#include <lpc_tools/irq.h>

#include <chip.h>

// NOTE: why is this not defined in the chip library??
#define WWDT_WDMOD_LOCK        ((uint32_t) (1 << 5))



// a warning interrupt is triggered this amount of cycles before timeout
// (1023 is the maximum)
#define WATCHDOG_WARNING_CYCLES 1023

#define WWDT_FREQ_KHZ (12000/4)
void watchdog_init(void)
{
#if (EN_WATCHDOG)
    const bool irq_state = irq_disable();

    Chip_WWDT_Init(LPC_WWDT);
    Chip_WWDT_SelClockSource(LPC_WWDT,WWDT_CLKSRC_IRC);

    // NOTE: register is 24 bit, so values above 2^24 will not work...
    Chip_WWDT_SetTimeOut(LPC_WWDT, WATCHDOG_TIMEOUT_MS * WWDT_FREQ_KHZ);

    Chip_WWDT_SetWarning(LPC_WWDT, WATCHDOG_WARNING_CYCLES);

    Chip_WWDT_SetOption(LPC_WWDT, (WWDT_WDMOD_WDRESET | WWDT_WDMOD_LOCK));
    Chip_WWDT_ClearStatusFlag(LPC_WWDT, (WWDT_WDMOD_WDTOF | WWDT_WDMOD_WDINT));
    Chip_WWDT_Start(LPC_WWDT);

    irq_restore(irq_state);
#endif

}

void watchdog_feed(void)
{
#if (EN_WATCHDOG)

    const bool irq_state = irq_disable();
    Chip_WWDT_Feed(LPC_WWDT);
    irq_restore(irq_state);
 #endif
}
