/*
 * @brief Common EEPROM support functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "eeprom.h"
#include "system_status.h"

#define IAP_EEPROM_WRITE (61)
#define IAP_EEPROM_READ (62)
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Write data to EEPROM */
static uint32_t Chip_EEPROM_Write(uint32_t dstAdd, uint8_t *ptr, uint32_t byteswrt)
{
	uint32_t command[5], result[4];

	command[0] = IAP_EEPROM_WRITE;
	command[1] = dstAdd;
	command[2] = (uint32_t) ptr;
	command[3] = byteswrt;
	command[4] = SystemCoreClock / 1000;
	iap_entry(command, result);

	return result[0];
}

/* Read data from EEPROM */
static uint32_t Chip_EEPROM_Read(uint32_t srcAdd, uint8_t *ptr, uint32_t bytesrd)
{
	uint32_t command[5], result[4];

	command[0] = IAP_EEPROM_READ;
	command[1] = srcAdd;
	command[2] = (uint32_t) ptr;
	command[3] = bytesrd;
	command[4] = SystemCoreClock / 1000;
	iap_entry(command, result);

	return result[0];
}

static bool _within_bounds(uint32_t address, uint32_t length)
{
    // address should be within eeprom bounds
    if(address < EEPROM_ADDR_MIN) {
        return false;
    }
    if(address >= EEPROM_ADDR_MAX) {
        return false;
    }

    // length should be reasonable
    if(length > (EEPROM_ADDR_MAX - EEPROM_ADDR_MIN)) {
        return false;
    }

    // Note: previous check of length prevents overflow in this check
    if((address + length) >= EEPROM_ADDR_MAX) {
        return false;
    }

    return true;
}

bool eeprom_read(uint32_t address, void *buffer, size_t sizeof_buffer)
{
    bool ok = false;
    if(_within_bounds(address, sizeof_buffer)) {
        ok = (IAP_STA_CMD_SUCCESS == Chip_EEPROM_Read(address, (uint8_t*)buffer, sizeof_buffer));
    }

    if(!ok) {
        system_status_set(SYSTEM_STATUS_ERROR_EEPROM);
    }
    return ok;
}
bool eeprom_write(uint32_t address, const void *buffer, size_t sizeof_buffer)
{
    bool ok = false;
    if(_within_bounds(address, sizeof_buffer)) {
        ok = (IAP_STA_CMD_SUCCESS == Chip_EEPROM_Write(address, (uint8_t*)buffer, sizeof_buffer));
    }

    if(!ok) {
        system_status_set(SYSTEM_STATUS_ERROR_EEPROM);
    }
    return ok;
}

