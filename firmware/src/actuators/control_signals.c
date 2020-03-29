#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/constrain.h>
#include <c_utils/assert.h>

#include "control_signals.h"
#include "DPR.h"
#include "actuators/PWM.h"
#include "board.h"
#include "board_GPIO_ID.h"

struct {
    const GPIO *LED_status;
    const GPIO *LED_error;

    const GPIO *switch1;
    const GPIO *switch2;

    DPR DPR;
    PWM pwm;
} Control;


void control_signals_init()
{
    Control.LED_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    Control.LED_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    Control.switch1 = board_get_GPIO(GPIO_ID_SWITCH_1);
    Control.switch2 = board_get_GPIO(GPIO_ID_SWITCH_2);

    DPR_init(&Control.DPR, LPC_SSP1, board_get_GPIO(GPIO_ID_PREG_CS));

    const int desired_pwm_resolution = 10000;
    const uint32_t pwm_frequency = 960;

    assert(PWM_init(&Control.pwm, LPC_TIMER16_0,
                PWM_CH1, pwm_frequency, desired_pwm_resolution));
}

bool control_DPR_on(void)
{
    PWM_set(&Control.pwm, PWM_CH1, 0);
    return PWM_start(&Control.pwm);
    //return DPR_enable(&Control.DPR);
}
bool control_DPR_off(void)
{
    PWM_stop(&Control.pwm);
    return true;
    //return DPR_disable(&Control.DPR);
}

#include "log.h"
bool control_DPR_set_pa(int pressure_pa)
{
    // correction for 1bar (voltage-controlled) DPR
    //
    //y = (x * 2.78) + 1000;
    //(y-1000)/2.78 = x
    //
    //pressure_pa = (pressure_pa - 1000) / 2.78;

    log_debug("PWM RESOLUTION=%d", PWM_get_resolution(&Control.pwm));


    // This assumes 4-20mA = 0-5000pa
    //int DAC_12bit = (pressure_pa*819)/1000;
    int pwm = constrain(pressure_pa, 0, 10000);

    return PWM_set(&Control.pwm, PWM_CH1, pwm);

    //return DPR_write(&Control.DPR, DAC_12bit);
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

