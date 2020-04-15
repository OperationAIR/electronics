#ifndef _APP_USB_H
#define _APP_USB_H

bool app_usb_init(void);
void app_usb_deinit(void);
bool app_usb_tasks(void);
bool usb_is_connected(void);

#endif
