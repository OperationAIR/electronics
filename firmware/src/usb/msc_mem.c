#include <string.h>
#include "usbd/usbd_rom_api.h"

#include "fat_fs_emulation.h"

extern USBD_API_T* gUSB_API;


// NOTE: this 'string' is built from 3 parts:
// - 8 bytes vendorID
// - 16 bytes product ID
// - 4 bytes product revision
// These fields should be exactly the length above (pad with ' ' if required).
const uint8_t InquiryStr[31+1] = "Jitter  "
    "Operation Air data "
    "1.0 ";

//uint8_t *Memory = (uint8_t *)MSC_IMAGE_ADDR;

void translate_rd(uint32_t offset, uint8_t **buff_adr, uint32_t length, uint32_t high_offset)
{
    uint8_t *buffer = *buff_adr;
    fat_fs_emulation_read(offset, buffer, length);

    /*
	uint32_t i;
	for (i = 0; i < length; i++)
	{
		(*buff_adr)[i] = Memory[offset + i];
	}
    */
}

// void (*MSC_Write)( uint32_t offset, uint8_t** src, uint32_t length, uint32_t high_offset);
void translate_wr(uint32_t offset, uint8_t **buff_adr, uint32_t length,  uint32_t high_offset)
{
    // Read-only: nothing to do here
    /*
	uint32_t i;

	for (i = 0; i < length; i++)
	{
		Memory[offset + i] = (*buff_adr)[i];
	}
    */
}

// ErrorCode_t (*MSC_Verify)( uint32_t offset, uint8_t buf[], uint32_t length, uint32_t high_offset);
ErrorCode_t translate_verify(uint32_t offset, uint8_t *src, uint32_t length,  uint32_t high_offset)
{
    // Read-only: nothing to do here
    /*
	if (memcmp((void *)&Memory[offset], src, length))
		return ERR_FAILED;

    */
	return LPC_OK;
}

/* Main Program */

ErrorCode_t usb_msc_mem_init(USBD_HANDLE_T hUsb, USB_INTERFACE_DESCRIPTOR *pIntfDesc, uint32_t *mem_base, uint32_t *mem_size)
{
	USBD_MSC_INIT_PARAM_T msc_param;
	ErrorCode_t ret = LPC_OK;


	memset((void *)&msc_param, 0, sizeof(USBD_MSC_INIT_PARAM_T));
	msc_param.mem_base = *mem_base;
	msc_param.mem_size = *mem_size;
	/* mass storage paramas */
	msc_param.InquiryStr = (uint8_t *)InquiryStr;
	msc_param.BlockCount = MSC_BlockCount;
	msc_param.BlockSize = MSC_BlockSize;
	msc_param.MemorySize = MSC_MemorySize;

	if ((pIntfDesc == 0) ||
		(pIntfDesc->bInterfaceClass != USB_DEVICE_CLASS_STORAGE) ||
		(pIntfDesc->bInterfaceSubClass != MSC_SUBCLASS_SCSI))
		return ERR_FAILED;

	msc_param.intf_desc = (uint8_t *)pIntfDesc;
	/* user defined functions */
	msc_param.MSC_Write = translate_wr;
	msc_param.MSC_Read = translate_rd;
	msc_param.MSC_Verify = translate_verify;

	// uint32_t reqMemSize = gUSB_API->msc->GetMemSize(&msc_param);
	ret = gUSB_API->msc->init(hUsb, &msc_param);
	/* update memory variables */
	*mem_base = msc_param.mem_base;
	*mem_size = msc_param.mem_size;

	return ret;
}
