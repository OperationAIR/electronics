#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>

#include "control_signals.h"
#include "board.h"
#include "board_GPIO_ID.h"

struct {
    const GPIO *dcdc;
    const GPIO *usb_pwr;
    const GPIO *valve1;
    const GPIO *valve2;
    const GPIO *charger_status;
    const GPIO *charger_disable;
} Control;


void control_signals_init()
{
    Control.dcdc = board_get_GPIO(GPIO_ID_DCDC_EN);
    Control.usb_pwr = board_get_GPIO(GPIO_ID_USB_PWR_EN);
    Control.valve1 = board_get_GPIO(GPIO_ID_VALVE1);
    Control.valve2 = board_get_GPIO(GPIO_ID_VALVE2);
    Control.charger_status = board_get_GPIO(GPIO_ID_CHARGER_STATUS);
    Control.charger_disable = board_get_GPIO(GPIO_ID_CHARGER_DISABLE);
}

void control_valve1_open(void)
{
    GPIO_HAL_set(Control.valve1, HIGH);
}

void control_valve1_close(void)
{
    GPIO_HAL_set(Control.valve1, LOW);
}

bool control_valve1_get_state(void)
{
    return GPIO_HAL_get(Control.valve1);
}

void control_valve2_open(void)
{
    GPIO_HAL_set(Control.valve2, HIGH);
}

void control_valve2_close(void)
{
    GPIO_HAL_set(Control.valve2, LOW);
}

bool control_valve2_get_state(void)
{
    return GPIO_HAL_get(Control.valve2);
}

void control_valves_toggle(void)
{
    GPIO_HAL_toggle(Control.valve1);
    GPIO_HAL_toggle(Control.valve2);
}

bool control_charger_get_status(void)
{
    return GPIO_HAL_get(Control.charger_status) == LOW;
}

void control_charger_enable(void)
{
    GPIO_HAL_set(Control.charger_disable, LOW);
}

void control_charger_disable(void)
{
    GPIO_HAL_set(Control.charger_disable, HIGH);
}

bool control_charger_enable_get_state(void)
{
    return GPIO_HAL_get(Control.charger_disable) == LOW;
}