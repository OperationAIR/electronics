#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <stddef.h>


#define EEPROM_ADDR_MIN     64
#define EEPROM_ADDR_MAX     4096


/**
 * Read a block of data from EEPROM.
 * 
 * NOTE: valid EEPROM address is between EEPROM_ADDR_MIN and EEPROM_ADDR_MAX
 */
bool eeprom_read(uint32_t address, void *buffer, size_t sizeof_buffer);

/**
 * Write a block of data to EEPROM.
 * 
 * NOTE: valid EEPROM address is between EEPROM_ADDR_MIN and EEPROM_ADDR_MAX
 */
bool eeprom_write(uint32_t address, const void *buffer, size_t sizeof_buffer);

#endif

