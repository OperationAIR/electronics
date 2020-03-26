#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>

#include "control_signals.h"
#include "board.h"
#include "board_GPIO_ID.h"

struct {
    const GPIO *LED_status;
    const GPIO *LED_error;

    const GPIO *switch1;
    const GPIO *switch2;
} Control;


void control_signals_init()
{
    Control.LED_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    Control.LED_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    Control.switch1 = board_get_GPIO(GPIO_ID_SWITCH_1);
    Control.switch2 = board_get_GPIO(GPIO_ID_SWITCH_2);
}

void control_LED_status_on(void)
{
    GPIO_HAL_set(Control.LED_status, HIGH);
}
void control_LED_status_off(void)
{
    GPIO_HAL_set(Control.LED_status, LOW);
}

void control_LED_error_on(void)
{
    GPIO_HAL_set(Control.LED_error, HIGH);
}
void control_LED_error_off(void)
{
    GPIO_HAL_set(Control.LED_error, LOW);
}

void control_switch1_on(void)
{
    GPIO_HAL_set(Control.switch1, HIGH);
}
void control_switch1_off(void)
{
    GPIO_HAL_set(Control.switch1, LOW);
}
bool control_switch1_get_state(void)
{
    return GPIO_HAL_get(Control.switch1);
}

void control_switch2_on(void)
{
    GPIO_HAL_set(Control.switch2, HIGH);
}
void control_switch2_off(void)
{
    GPIO_HAL_set(Control.switch2, LOW);
}
bool control_switch2_get_state(void)
{
    return GPIO_HAL_get(Control.switch2);
}

