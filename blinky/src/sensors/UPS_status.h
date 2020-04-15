#ifndef UPS_STATUS_H
#define UPS_STATUS_H

enum UPSStatus {
    UPS_STATUS_UNKNOWN              = (0),
    UPS_STATUS_OK                   = (1 << 31),
    UPS_STATUS_BATTERY_POWERED      = (1 << 30),
    UPS_STATUS_FAIL                 = (1 << 29)
};

void UPS_status_init(void);
enum UPSStatus UPS_status_get(void);



#endif

