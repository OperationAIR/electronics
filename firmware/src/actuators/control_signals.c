#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>

#include "control_signals.h"
#include "board.h"
#include "board_GPIO_ID.h"

struct {
    const GPIO *switch1;
    const GPIO *switch2;
} Control;


void control_signals_init()
{
    Control.switch1 = board_get_GPIO(GPIO_ID_SWITCH_1);
    Control.switch2 = board_get_GPIO(GPIO_ID_SWITCH_2);
}

void control_valve1_open(void)
{
    GPIO_HAL_set(Control.switch1, HIGH);
}

void control_valve1_close(void)
{
    GPIO_HAL_set(Control.switch1, LOW);
}

bool control_valve1_get_state(void)
{
    return GPIO_HAL_get(Control.switch1);
}

void control_valve2_open(void)
{
    GPIO_HAL_set(Control.switch2, HIGH);
}

void control_valve2_close(void)
{
    GPIO_HAL_set(Control.switch2, LOW);
}

bool control_valve2_get_state(void)
{
    return GPIO_HAL_get(Control.switch2);
}

