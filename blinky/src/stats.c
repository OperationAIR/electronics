#include "stats.h"
#include <chip.h>
#include <lpc_tools/irq.h>

#include "eeprom.h"

#define EEPROM_RESERVED_SPACE 0x40
#define EEPROM_INT_SIZE 0x4
#define EEPROM_USE_COUNT_ADDRESS (EEPROM_RESERVED_SPACE + 0x4)
#define EEPROM_ALL_TIME_USE_COUNT_ADDRESS (EEPROM_RESERVED_SPACE + 0x8)
#define EEPROM_MAINTENANCE_MODE_ADDRESS (EEPROM_RESERVED_SPACE + 0xC)
#define EEPROM_OVERHEATED_MODE_ADDRESS (EEPROM_RESERVED_SPACE + 0x10)
#define EEPROM_BATTERY_CRITICAL_MODE_ADDRESS (EEPROM_RESERVED_SPACE + 0x14)


static int32_t eeprom_read_uint(uint32_t address)
{
    uint32_t res = 0;
	uint8_t ret_code = Chip_EEPROM_Read(address, (uint8_t*)&res, EEPROM_INT_SIZE);
    if (ret_code != IAP_STA_CMD_SUCCESS) {
        return -1;
    }

    return res;
}

bool stats_get_maintenance_mode(void)
{
    return !!eeprom_read_uint(EEPROM_MAINTENANCE_MODE_ADDRESS);
}

void stats_set_maintenance_mode(bool onoff)
{
    uint32_t m = onoff;
    bool mask = irq_disable();
    Chip_EEPROM_Write(EEPROM_MAINTENANCE_MODE_ADDRESS, (uint8_t*)&m, EEPROM_INT_SIZE);
    irq_restore(mask);
}

bool stats_get_overheated_mode(void)
{
    return !!eeprom_read_uint(EEPROM_OVERHEATED_MODE_ADDRESS);
}

bool stats_get_battery_critical_mode(void)
{
    return !!eeprom_read_uint(EEPROM_BATTERY_CRITICAL_MODE_ADDRESS);
}

void stats_set_overheated_mode(bool onoff)
{
    uint32_t m = onoff;
    bool mask = irq_disable();
    Chip_EEPROM_Write(EEPROM_OVERHEATED_MODE_ADDRESS, (uint8_t*)&m, EEPROM_INT_SIZE);
    irq_restore(mask);
}

void stats_set_battery_critical_mode(bool onoff)
{
    uint32_t m = onoff;
    bool mask = irq_disable();
    Chip_EEPROM_Write(EEPROM_BATTERY_CRITICAL_MODE_ADDRESS, (uint8_t*)&m, EEPROM_INT_SIZE);
    irq_restore(mask);
}

int32_t stats_get_use_count()
{
    return eeprom_read_uint(EEPROM_USE_COUNT_ADDRESS);
}

int32_t stats_get_all_time_use_count()
{
    return eeprom_read_uint(EEPROM_ALL_TIME_USE_COUNT_ADDRESS);
}

void stats_clear_use_count()
{
    uint32_t zero = 0;
    bool mask = irq_disable();
    Chip_EEPROM_Write(EEPROM_USE_COUNT_ADDRESS, (uint8_t*)&zero, EEPROM_INT_SIZE);
    irq_restore(mask);
}

void stats_increment_use_count()
{
    int32_t n1 = stats_get_use_count() + 1;
    int32_t n2 = stats_get_all_time_use_count() + 1;
    bool mask = irq_disable();
    Chip_EEPROM_Write(EEPROM_USE_COUNT_ADDRESS, (uint8_t*)&n1, EEPROM_INT_SIZE);
    Chip_EEPROM_Write(EEPROM_ALL_TIME_USE_COUNT_ADDRESS, (uint8_t*)&n2, EEPROM_INT_SIZE);
    irq_restore(mask);

}
