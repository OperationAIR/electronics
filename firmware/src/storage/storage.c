#include "storage.h"
#include <chip.h>
#include <lpc_tools/irq.h>

#include "eeprom.h"

#define EEPROM_INT_SIZE 0x4

#define EEPROM_USE_COUNT_ADDRESS (EEPROM_ADDR_MIN + EEPROM_INT_SIZE)


static int32_t eeprom_read_uint(uint32_t address)
{
    uint32_t res = 0;
	if(!eeprom_read(address, &res, EEPROM_INT_SIZE)) {
        return 0;
    }

    return res;
}


int32_t storage_read_app_use_count(void)
{
    return eeprom_read_uint(EEPROM_USE_COUNT_ADDRESS);
}

void storage_increment_app_use_count(void)
{
    int32_t use_count = storage_read_app_use_count() + 1;
    bool mask = irq_disable();
    eeprom_write(EEPROM_USE_COUNT_ADDRESS, &use_count, EEPROM_INT_SIZE);
    irq_restore(mask);
}

