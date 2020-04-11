#include <chip.h>
#include <string.h>

#include "app_usb.h"
#include "usbd_rom_api.h"

#include "usb_utils.h"
#include "cdc_vcom.h"

#include "log.h"
#include "generated/firmware_version.h"


#include <stdio.h>

/* USB descriptor arrays defined *_desc.c file */
extern const uint8_t USB_DeviceDescriptor[];
extern uint8_t USB_FsConfigDescriptor[];
extern const uint8_t USB_StringDescriptor[];
extern const uint8_t USB_DeviceQualifier[];

static USBD_HANDLE_T g_hUsb;
USBD_API_T* gUSB_API;

static volatile bool g_connected = false;


void USB_IRQHandler(void)
{
    uint32_t *addr = (uint32_t *) LPC_USB->EPLISTSTART;
    // WORKAROUND for artf32289 ROM driver BUG:
    // As part of USB specification the device should respond
    // with STALL condition for any unsupported setup packet. The host will send
    // new setup packet/request on seeing STALL condition for EP0 instead of sending
    // a clear STALL request. Current driver in ROM doesn't clear the STALL
    // condition on new setup packet which should be fixed.

    if ( LPC_USB->DEVCMDSTAT & _BIT(8) ) {	// if setup packet is received
        addr[0] &= ~(_BIT(29));	// clear EP0_OUT stall
        addr[2] &= ~(_BIT(29));	// clear EP0_IN stall
    }
	gUSB_API->hw->ISR(g_hUsb);
}

static ErrorCode_t usb_on_suspend(USBD_HANDLE_T hUsb)
{
	g_connected = false;
    vcom_reset();
    return LPC_OK;
}
static ErrorCode_t usb_on_configure(USBD_HANDLE_T hUsb)
{
	g_connected = true;
	return LPC_OK;
}

static ErrorCode_t usb_on_resume(USBD_HANDLE_T hUsb)
{
	//g_connected = true;
	return LPC_OK;
}

bool usb_is_connected(void)
{
	return g_connected;
}


// Workaround for USB_ROM.1 bug
typedef volatile struct _EP_LIST {
    uint32_t  buf_ptr;
    uint32_t  buf_length;
} EP_LIST;
ErrorCode_t workaround_stall(USBD_HANDLE_T hUsb)
{
    ErrorCode_t ret = LPC_OK;
    USB_CORE_CTRL_T *pCtrl = (USB_CORE_CTRL_T *) hUsb;
    EP_LIST      *epQueue;
    int32_t      i;
    /*    WORKAROUND for Case 2:
          Code clearing STALL bits in endpoint reset routine corrupts memory area
          next to the endpoint control data.
          */
    if (pCtrl->ep_halt != 0) { /* check if STALL is set for any endpoint */
        /* get pointer to HW EP queue */
        epQueue = (EP_LIST *) LPC_USB->EPLISTSTART;
        /* check if the HW STALL bit for the endpoint is cleared due to bug. */
        for (i = 1; i < pCtrl->max_num_ep; i++) {
            /* check OUT EPs */
            if ( pCtrl->ep_halt & (1 << i)) {
                /* Check if HW EP queue also has STALL bit = _BIT(29) is set */
                if (( epQueue[i << 1].buf_ptr & _BIT(29)) == 0) {
                    /* bit not set, cleared by BUG. So set it back. */
                    epQueue[i << 1].buf_ptr |= _BIT(29);
                }
            }
            /* Check IN EPs */
            if ( pCtrl->ep_halt & (1 << (i + 16))) {
                /* Check if HW EP queue also has STALL bit = _BIT(29) is set */
                if (( epQueue[(i << 1) + 1].buf_ptr & _BIT(29)) == 0) {
                    /* bit not set, cleared by BUG. So set it back. */
                    epQueue[(i << 1) + 1].buf_ptr |= _BIT(29);
                }
            }
        }
    }
    return ret;
}

static bool g_initialized;
void app_usb_deinit(void)
{
    if(!g_initialized) {
        return;
    }
    g_initialized = false;

    g_connected = false;

    gUSB_API->hw->Connect(g_hUsb, 0);
    gUSB_API->hw->Reset(g_hUsb);

    NVIC_DisableIRQ(USB0_IRQn);

    LPC_SYSCTL->SYSAHBCLKCTRL &= ~((0x1 << 14) | (0x1 << 27));

    //USB PHY power down
    Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_USBPAD_PD);

    // Disable clocks
    Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_USBRAM);
    Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_USB);

    //USB PLL power down (in case it was powered on)
    Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_USBPLL_PD);
}

bool app_usb_init(void)
{
    g_connected = false;

    gUSB_API = (USBD_API_T*)LPC_ROM_API->usbdApiBase; //0x1FFF1F24

	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;

	usb_clk_init(true);

	/* initilize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB0_BASE;

    // See errata USB_ROM.1: max_num_ep should be at least n+1, where n
    // is the amount of endpoints in use (ep1_in + ep1_out = 2).
	//usb_param.max_num_ep = USB_MAX_EP_NUM+1;

    // NOTE: USB_MAX_EP_NUM is not guaranteed to be enough: up to 10 enpoints
    // can be active (ep1-5 in + ep1-5 out)
	usb_param.max_num_ep = USB_MAX_EP_NUM + 1;

    usb_param.USB_Suspend_Event = usb_on_suspend;
	usb_param.USB_Resume_Event = usb_on_resume;
    usb_param.USB_Interface_Event = workaround_stall;       // See errata USB_ROM.1
	usb_param.USB_Configure_Event = usb_on_configure;


	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) &USB_DeviceDescriptor[0];
	desc.string_desc = (uint8_t *) &USB_StringDescriptor[0];
	/* Note, to pass USBCV test full-speed only devices should have both
	   descriptor arrays point to same location and device_qualifier set to 0.
	 */
	desc.high_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
	desc.full_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
	desc.device_qualifier = 0;

	/* USB Initialization */
	// uint32_t reqMemSize = gUSB_API->hw->GetMemSize(&usb_param);
	ret = gUSB_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

	USB_COMMON_DESCRIPTOR *pD;
	uint32_t next_desc_adr, total_len = 0;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc;
	pD = (USB_COMMON_DESCRIPTOR *)desc.high_speed_desc;
		next_desc_adr = (uint32_t)desc.high_speed_desc;

		while (pD->bLength)
		{
			if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE)
			{

				pIntfDesc = (USB_INTERFACE_DESCRIPTOR *)pD;

				switch (pIntfDesc->bInterfaceClass)
				{
				case CDC_COMMUNICATION_INTERFACE_CLASS:
					usb_param.mem_base = CDC_PARAM_MEM;
					usb_param.mem_size = CDC_PARAM_SIZE;
					ret = vcom_init(g_hUsb, &desc, &usb_param);
					break;
				}
				if (ret != LPC_OK)
					break; /* break while loop no point proceeding further */
			}
			pIntfDesc = 0;
			total_len += pD->bLength;
			next_desc_adr = (uint32_t)pD + pD->bLength;
			pD = (USB_COMMON_DESCRIPTOR *)next_desc_adr;
		}
	}


	if (ret == LPC_OK) {
		/*  enable USB interrrupts */
		NVIC_EnableIRQ(USB0_IRQn);
		/* now connect */
		gUSB_API->hw->Connect(g_hUsb, 1);
	}
    g_initialized = (ret == LPC_OK);
    return ret == LPC_OK;
}
