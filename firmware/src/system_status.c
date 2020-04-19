#include "system_status.h"

#include <stdbool.h>
#include <memory.h>
#include <chip.h>

static struct {
    bool init;

    enum SystemStatus status;

} g_status;

void system_status_init(void)
{
    memset(&g_status, 0, sizeof(g_status));

    const uint32_t reason = Chip_SYSCTL_GetSystemRSTStatus();
    Chip_SYSCTL_ClearSystemRSTStatus(reason);
    
    // Initialize status with boot info
    if(reason & SYSCTL_RST_WDT) {
        system_status_set(SYSTEM_STATUS_BOOT_RESET_BY_ERROR);

    } else if(reason & SYSCTL_RST_BOD) {
        system_status_set(SYSTEM_STATUS_BOOT_RESET_BY_PWR_FAIL);

    } else if(reason & SYSCTL_RST_POR) {
        system_status_set(SYSTEM_STATUS_BOOT_POWER_ON);

    } else if(reason & SYSCTL_RST_EXTRST) {
        system_status_set(SYSTEM_STATUS_BOOT_RESET_BY_PI);

    } else {
        system_status_set(SYSTEM_STATUS_BOOT_RESET_BY_UNKNOWN);
    }

    // Set 'debug' flag if non-release build option(s) are used
#if (!EN_WATCHDOG)
    g_status.status|= SYSTEM_STATUS_DEBUG_ENABLED;
#endif

    g_status.init = true;

}

void system_status_set(enum SystemStatus status_flag) {
    g_status.status|= status_flag;
}

enum SystemStatus system_status_get(void)
{
    if(!g_status.init) {
        return SYSTEM_STATUS_UNKNOWN;
    }

    return g_status.status;
}

