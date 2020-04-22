#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H


enum SystemStatus {
    SYSTEM_STATUS_UNKNOWN               = 0,

    // Boot info: one of these should be set at boot
    SYSTEM_STATUS_BOOT_POWER_ON         = (1 << 0),     // Power-On-Reset
    SYSTEM_STATUS_BOOT_RESET_BY_PI      = (1 << 1),     // External reset (triggered by RPI)
    SYSTEM_STATUS_BOOT_RESET_BY_ERROR   = (1 << 2),     // Watchdog reset (firmware bug)
    SYSTEM_STATUS_BOOT_RESET_BY_PWR_FAIL= (1 << 3),     // BOD reset (3.3V unstable)
    SYSTEM_STATUS_BOOT_RESET_BY_UNKNOWN = (1 << 4),     // SYSRST or unknown

    // Errors in sensors or actuators:
    SYSTEM_STATUS_ERROR_SENSOR_P_INSP   = (1 << 5),     // Inspiration pressure sensor error
    SYSTEM_STATUS_ERROR_SENSOR_P_EXP    = (1 << 6),     // Expiration pressure sensor error
    SYSTEM_STATUS_ERROR_SENSOR_P_PATIENT= (1 << 7),     // Patient pressure sensor error
    SYSTEM_STATUS_ERROR_SENSOR_FLOW     = (1 << 8),     // Flow sensor error

    SYSTEM_STATUS_ERROR_ACTUATOR_MFC_AIR= (1 << 16),    // Air MFC (DAC) error
    SYSTEM_STATUS_ERROR_ACTUATOR_MFC_O2 = (1 << 17),    // O2 MFC (DAC) error

    SYSTEM_STATUS_ERROR_MFC_OVERPRESSURE= (1 << 18),    // MFC output pressure too high

    // NOTE: new status flags may be added here
    //


    // Generic errors
    SYSTEM_STATUS_ERROR_EEPROM          = (1 << 29),    // EEPROM error: settings may not be remembered after reset
    SYSTEM_STATUS_ERROR_I2C_BUS         = (1 << 30),    // I2C bus is in invalid state

    // Warning: the firmware is not a release build
    SYSTEM_STATUS_DEBUG_ENABLED         = (1 << 31),    // Debug build should not be released
};


void system_status_init(void);
void system_status_set(enum SystemStatus status_flag);
enum SystemStatus system_status_get(void);


#endif

