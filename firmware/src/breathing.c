#include <c_utils/assert.h>
#include <c_utils/max.h>
#include <c_utils/constrain.h>

#include "actuators/PWM.h"
#include "actuators/control_signals.h"
#include "sensors/sensors.h"

#include "global_settings.h"
#include "breathing.h"
#include "log.h"
#include "app.h"

#include <math.h>
#include <stdlib.h>

#include "cmsis_dsp_lib/arm_math.h"


static bool program_validation(void);

static struct {
// TODO this is obsolete
/*
    volatile int target_pressure;
    volatile uint32_t num_programs;
    volatile uint32_t current_sub_program;
    volatile uint32_t current_setpoint;
    PWM pwm;
*/
    volatile uint32_t cycle_time;
    volatile uint32_t breathing_time;
    enum TestState test_state;
} breathing;


bool breathing_init(void)
{

    if (!program_validation()) {
        return false;
    }

    return true;
}


void breathing_start_program(void)
{
    // TODO start
}


void breathing_stop(void)
{
    // TODO stop
}

enum TestState breathing_test_get_result(void)
{
    return breathing.test_state;
}

void breathing_start_test(void)
{
    // TODO: begin self-test
}

enum TestState breathing_test(void)
{
    // TODO self-test procedure

    return breathing.test_state;
}

static int g_setpoint_pa = 0;
static arm_pid_instance_f32 pid_instance;

void breathing_run(void)
{
    breathing.breathing_time+=2;

    const uint32_t time_ms = breathing.breathing_time;

    // Primitive 'control loop' 


    const unsigned int time_high = 1000;//570;
    const unsigned int time_low = 2000;//1142;
    const unsigned int time_total = time_high + time_low;

    breathing.cycle_time++;
    if(breathing.cycle_time > time_total) {
        breathing.cycle_time = 0;
    }

    const int setpoint_high = 2500;
    const int setpoint_low = 1000;

    // start building pressure
    if(breathing.cycle_time == 0) {
        control_switch1_off();
        g_setpoint_pa = setpoint_high;
        //control_DPR_set_pa(g_setpoint_pa);

    // start lower pressure
    } else if(breathing.cycle_time == time_high) {
        control_switch1_on();
        g_setpoint_pa = setpoint_low;
        //control_DPR_set_pa(g_setpoint_pa);
        
    // during low pressure
    } else if(breathing.cycle_time > time_high) {
        // close valve if pressure goes below peep
        if(sensors_read_pressure_1_pa() < setpoint_low) {
            control_switch1_off();
        }
    }

    int sensor_value = sensors_read_pressure_1_pa();
    float error = g_setpoint_pa - sensor_value;

    float Kp = 5.0;
    float Ki = 0.0;
    float Kd = 0.01;

    arm_pid_reset_f32(&pid_instance);
    pid_instance.Kp = Kp;
    pid_instance.Ki = Ki;
    pid_instance.Kd = Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&pid_instance, 1);

    float PID_out = arm_pid_f32(&pid_instance, error);
    float to_DPR = constrain((g_setpoint_pa + PID_out), 0, 5000);
    //float to_DPR = g_setpoint_pa;
    control_DPR_set_pa(to_DPR);


    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {
        log_debug("%d,%d,%d,%d",
                g_setpoint_pa,
                sensor_value,
                sensors_read_pressure_regulator(),
                (int)to_DPR);
    }
}




static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
