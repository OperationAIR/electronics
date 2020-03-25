#ifndef __APP_USB_CFG_H_
#define __APP_USB_CFG_H_

// Manifest constants used by USBD LIB stack. These values SHOULD NOT BE CHANGED
// for advance features which require usage of USB_CORE_CTRL_T structure.
// Since these are the values used for compiling USB stack.

#define USB_MAX_IF_NUM          8		/*!< Max interface number used for building USBDL_Lib. DON'T CHANGE. */
#define USB_MAX_EP_NUM          5		/*!< Max number of EP used for building USBD_Lib. DON'T CHANGE. */
#define USB_MAX_PACKET0         64		/*!< Max EP0 packet size used for building USBD_Lib. DON'T CHANGE. */
#define USB_FS_MAX_BULK_PACKET  64		/*!< MAXP for FS bulk EPs used for building USBD_Lib. DON'T CHANGE. */
#define USB_HS_MAX_BULK_PACKET  512		/*!< MAXP for HS bulk EPs used for building USBD_Lib. DON'T CHANGE. */
#define USB_DFU_XFER_SIZE       2048	/*!< Max DFU transfer size used for building USBD_Lib. DON'T CHANGE. */

// Define this memory area to be used by USBD_LIB stack.
// GetMemSize = 832 bytes, but this is incorrect. Required = 1472 bytes minimum
#define USB_STACK_MEM_BASE      0x20004000
#define USB_STACK_MEM_SIZE      0x0600

// GetMemSize = 76 bytes
#define CDC_PARAM_MEM   0x20004600
#define CDC_PARAM_SIZE  0x100

// USB Interface numbers and Endpoints
#define USB_CDC_CIF_NUM         0
#define USB_CDC_DIF_NUM         1
#define USB_CDC_IN_EP           0x81
#define USB_CDC_OUT_EP          0x01
#define USB_CDC_INT_EP          0x82

#endif /* __APP_USB_CFG_H_ */
