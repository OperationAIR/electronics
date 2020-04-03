#include <stdint.h>

#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/constrain.h>
#include <c_utils/assert.h>

#include "control_signals.h"
#include "DPR.h"
#include "actuators/PWM.h"
#include "actuators/i2c_dac.h"
#include "board.h"
#include "board_GPIO_ID.h"

struct {
    const GPIO *LED_status;
    const GPIO *LED_error;

    const GPIO *switch1;
    const GPIO *switch2;

    DPR DPR;
    PWM pwm;
    PWM output_pwm;
} Control;



static void _setO2DAC(int mv_O2);
static void _setAirDAC(int mv_O2);

void control_signals_init()
{
    Control.LED_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    Control.LED_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    Control.switch1 = board_get_GPIO(GPIO_ID_SWITCH_1);
    Control.switch2 = board_get_GPIO(GPIO_ID_SWITCH_2);

    DPR_init(&Control.DPR, LPC_SSP1, board_get_GPIO(GPIO_ID_PREG_CS));

    const int desired_pwm_resolution = 10000;
    const uint32_t pwm_frequency = 960;

    // timer 0, ch 1
    assert(PWM_init(&Control.pwm, LPC_TIMER16_0,
                PWM_CH1, pwm_frequency, desired_pwm_resolution));

    // timer 1, ch 1
    assert(PWM_init(&Control.output_pwm, LPC_TIMER16_1,
                PWM_CH1, pwm_frequency, desired_pwm_resolution));

    i2cdac_init(I2C_DEFAULT_SPEED);
}

bool control_DPR_on(void)
{
    PWM_set(&Control.pwm, PWM_CH1, 0);
    PWM_set(&Control.output_pwm, PWM_CH1, 0);
    bool ok  = PWM_start(&Control.pwm);
    ok&= PWM_start(&Control.output_pwm);

    return ok;
}

bool control_DPR_off(void)
{
    PWM_stop(&Control.pwm);
    PWM_stop(&Control.output_pwm);
    return true;
    //return DPR_disable(&Control.DPR);
}

bool control_MFC_set(float flow_SLPM, float O2_fraction)
{
    const float O2_ref = 0.21;
    if (O2_fraction < O2_ref) {
        O2_fraction = O2_ref;
    }

    int max_flow = 50;

    // flows in SLPM
    float flow_O2 = (O2_fraction-O2_ref)*flow_SLPM / (1-O2_ref);
    float flow_Air = (flow_SLPM-flow_O2);

    float mV_O2 = flow_O2/max_flow*5000;

    float mV_Air = flow_Air/max_flow*5000;

    // Set DAC
    _setO2DAC(mV_O2);
    _setAirDAC(mV_Air);

    // TODO can we check something? Do we know if I2C DAC is OK?
    return true;
}


static void _setO2DAC(int mv_O2)
{
    const int vcc_mv = 5000;
    int DAC_12bit = mv_O2*4095/(vcc_mv);

    i2cdac_set(ADDDRESS_O2, DAC_12bit);
}
static void _setAirDAC(int mv_air)
{
    const int vcc_mv = 5000;
    int DAC_12bit = mv_air*4095/(vcc_mv);

    i2cdac_set(ADDDRESS_AIR, DAC_12bit);
}

bool control_DPR_set_pa(int pressure_pa)
{
    int pwm = constrain(pressure_pa, 0, 10000);
    return PWM_set(&Control.pwm, PWM_CH1, pwm);
}

void control_LED_status_on(void)
{
    GPIO_HAL_set(Control.LED_status, HIGH);
}
void control_LED_status_off(void)
{
    GPIO_HAL_set(Control.LED_status, LOW);
}
void control_LED_status_toggle(void)
{
    GPIO_HAL_toggle(Control.LED_status);
}

void control_LED_error_on(void)
{
    GPIO_HAL_set(Control.LED_error, HIGH);
}
void control_LED_error_off(void)
{
    GPIO_HAL_set(Control.LED_error, LOW);
}

void control_switch1_on(int pwm_value_below_10000)
{
    int pwm = constrain(pwm_value_below_10000, 0, 10000);
    PWM_set(&Control.output_pwm, PWM_CH1, pwm);
    //GPIO_HAL_set(Control.switch1, HIGH);
}
void control_switch1_off(void)
{
    PWM_set(&Control.output_pwm, PWM_CH1, 0);
    //GPIO_HAL_set(Control.switch1, LOW);
}
bool control_switch1_get_state(void)
{
    return GPIO_HAL_get(Control.switch1);
}

void control_switch2_on(void)
{
    PWM_set(&Control.pwm, PWM_CH1, 10000);
    //GPIO_HAL_set(Control.switch2, HIGH);
}
void control_switch2_off(void)
{
    PWM_set(&Control.pwm, PWM_CH1, 0);
    //GPIO_HAL_set(Control.switch2, LOW);
}
bool control_switch2_get_state(void)
{
    return GPIO_HAL_get(Control.switch2);
}

