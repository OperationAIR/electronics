#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H


enum SystemStatus {
    SYSTEM_STATUS_UNKNOWN               = 0,

    // Boot info: one of these should be set at boot
    SYSTEM_STATUS_BOOT_POWER_ON         = (1 << 0),     // Power-On-Reset
    SYSTEM_STATUS_BOOT_RESET_BY_PI      = (1 << 1),     // External reset
    SYSTEM_STATUS_BOOT_RESET_BY_ERROR   = (1 << 2),     // Watchdog reset (firmware bug)
    SYSTEM_STATUS_BOOT_RESET_BY_PWR_FAIL= (1 << 3),     // BOD reset (3.3V unstable)
    SYSTEM_STATUS_BOOT_RESET_BY_UNKNOWN = (1 << 4),     // SYSRST or unknown




    SYSTEM_STATUS_DEBUG_ENABLED         = (1 << 31),    // Debug build should not be released

};


void system_status_init(void);
void system_status_set(enum SystemStatus status_flag);
enum SystemStatus system_status_get(void);


#endif

