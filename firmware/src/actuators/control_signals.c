#include <stdint.h>

#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/constrain.h>
#include <c_utils/assert.h>

#include "control_signals.h"
#include "actuators/PWM.h"
#include "actuators/i2c_dac.h"
#include "board_config/board_GPIO_ID.h"

#include "global_settings.h"
#include "system_status.h"

struct {
    const GPIO *LED_status;
    const GPIO *LED_error;

    PWM pwm_insp;
    PWM pwm_exp;
    PWM pwm_extra;
} Control;



void control_signals_init(void)
{
    Control.LED_status = board_get_GPIO(GPIO_ID_LED_STATUS);
    Control.LED_error = board_get_GPIO(GPIO_ID_LED_ERROR);

    const int desired_pwm_resolution = 10000;
    const uint32_t pwm_frequency = 960;

    // timer 0, ch 1
    assert(PWM_init(&Control.pwm_insp, LPC_TIMER16_0,
                PWM_CH1, pwm_frequency, desired_pwm_resolution));

    // timer 1, ch 1
    assert(PWM_init(&Control.pwm_exp, LPC_TIMER16_1,
                PWM_CH1, pwm_frequency, desired_pwm_resolution));

    // timer 0, ch 0
    assert(PWM_init(&Control.pwm_extra, LPC_TIMER16_0,
                PWM_CH0, pwm_frequency, desired_pwm_resolution));


    if (I2C_PULL_UP_AVAILABLE) {
        if(!i2cdac_init()) {
            system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS);
        }
    } else {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS);
    }

    control_PWM_on();
}

bool control_PWM_on(void)
{
    PWM_set(&Control.pwm_insp, PWM_CH1, 0);
    PWM_set(&Control.pwm_exp, PWM_CH1, 0);
    bool ok  = PWM_start(&Control.pwm_insp);
    ok&= PWM_start(&Control.pwm_exp);

    return ok;
}

bool control_PWM_off(void)
{
    PWM_stop(&Control.pwm_insp);
    PWM_stop(&Control.pwm_exp);
    return true;
}

void control_MFC_off(void) {
    control_MFC_on(0, 0.21);
}

void control_MFC_on(float flow_SLPM, float O2_fraction)
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
    if (I2C_PULL_UP_AVAILABLE) {
        control_raw_MFC_O2_mv(mV_O2);
        control_raw_MFC_air_mv(mV_Air);
    } else {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS);
    }
}



void control_raw_MFC_O2_mv(int mv_O2)
{
    const int vcc_mv = 5000;
    int DAC_12bit = mv_O2*4095/(vcc_mv);

    if(!i2cdac_set(ADDDRESS_O2, DAC_12bit)) {
        system_status_set(SYSTEM_STATUS_ERROR_ACTUATOR_MFC_O2);
    }
}
void control_raw_MFC_air_mv(int mv_air)
{
    const int vcc_mv = 5000;
    int DAC_12bit = mv_air*4095/(vcc_mv);

    if(!i2cdac_set(ADDDRESS_AIR, DAC_12bit)) {
        system_status_set(SYSTEM_STATUS_ERROR_ACTUATOR_MFC_AIR);
    }
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
void control_LED_error_toggle(void)
{
    GPIO_HAL_toggle(Control.LED_error);
}

void control_valve_insp_on(int pwm_value)
{
    int pwm_insp = constrain(pwm_value, 0, 10000);
    PWM_set(&Control.pwm_insp, PWM_CH1, pwm_insp);
}

void control_valve_insp_off(void)
{
    PWM_set(&Control.pwm_insp, PWM_CH1, 0);
}

void control_valve_exp_on(int pwm_value)
{
    int pwm_exp = constrain(pwm_value, 0, 10000);
    PWM_set(&Control.pwm_exp, PWM_CH1, pwm_exp);
}
void control_valve_exp_off(void)
{
    PWM_set(&Control.pwm_exp, PWM_CH1, 0);
}

void control_extra_on(int pwm_value)
{
    int pwm_exp = constrain(pwm_value, 0, 10000);
    PWM_set(&Control.pwm_extra, PWM_CH0, pwm_exp);
}

void control_extra_off(void)
{
   PWM_set(&Control.pwm_extra, PWM_CH0, 0);
}

void control_turn_on_rpi(void)
{
    GPIO_HAL_set(board_get_GPIO(GPIO_ID_RPI_ON_OFF), LOW);
    GPIO_HAL_set(board_get_GPIO(GPIO_ID_RPI_ON_OFF), HIGH);
}
