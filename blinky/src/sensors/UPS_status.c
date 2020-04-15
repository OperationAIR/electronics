#include "UPS_status.h"

#include <lpc_tools/boardconfig.h>
#include "board_config/board_GPIO_ID.h"

#include <memory.h>

static struct {
    const GPIO *fail_pin;
    const GPIO *dischg_pin;
} g_UPS;
void UPS_status_init(void)
{
    memset(&g_UPS, 0, sizeof(g_UPS));

    if(board_has_GPIO(GPIO_ID_STATUS_FAIL)) {
        g_UPS.fail_pin = board_get_GPIO(GPIO_ID_STATUS_FAIL);
    }
    if(board_has_GPIO(GPIO_ID_STATUS_DISCHARGING)) {
        g_UPS.dischg_pin = board_get_GPIO(GPIO_ID_STATUS_DISCHARGING);
    }

}

enum UPSStatus UPS_status_get(void)
{
    if(g_UPS.fail_pin && g_UPS.dischg_pin) {
        if(GPIO_HAL_get(g_UPS.fail_pin)) {
            return UPS_STATUS_FAIL;
        }
        if(GPIO_HAL_get(g_UPS.dischg_pin)) {
            return UPS_STATUS_BATTERY_POWERED;
        }
        return UPS_STATUS_OK;
    }

    // PCB V0 does not have status info
    return UPS_STATUS_UNKNOWN;
}

