#include <c_utils/assert.h>
#include <c_utils/max.h>
#include <c_utils/constrain.h>

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

float breathing_Kp = 3.3;
float breathing_Ki = 0.025;
float breathing_Kd = 1.7;


static int g_setpoint_pa = 0;
static arm_pid_instance_f32 pid_instance;
static float g_sensor_state_1 = 0;
static float g_sensor_state_2 = 0;
static float g_to_DPR = 0;


void breathing_print_PID(void)
{
    log_debug("PID: %d, %d, %d",
            (int)breathing_Kp,
            (int)breathing_Ki,
            (int)breathing_Kd);
}

static void _init_PID(void)
{
    // Begin PID

    arm_pid_reset_f32(&pid_instance);
    pid_instance.Kp = breathing_Kp;
    pid_instance.Ki = breathing_Ki;
    pid_instance.Kd = breathing_Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&pid_instance, 1);
}

void breathing_tune_PID(float kp, float ki, float kd)
{
    breathing_Kp = kp;
    breathing_Ki = ki;
    breathing_Kd = kd;
    _init_PID();

    log_debug("PID: %d, %d, %d",
            (int)breathing_Kp,
            (int)breathing_Ki,
            (int)breathing_Kd);
}

static struct {
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



bool breathing_start_program(void)
{
    _init_PID();


    // init state to sane value
    g_sensor_state_1 = sensors_read_pressure_1_pa();
    g_sensor_state_2 = sensors_read_pressure_2_pa();

    return control_DPR_on();
    // TODO start
}


void breathing_stop(void)
{
    control_DPR_off();
    control_switch1_off();

    // TODO should we open switch1 temporarily to let the pressure out?
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


void breathing_run(void)
{
    const int dt = 2;

    breathing.breathing_time+=dt;

    const uint32_t time_ms = breathing.breathing_time;

    // Primitive 'control loop' 


    const unsigned int time_high = 666;//570;
    const unsigned int time_low = 1334;//1142;
    const unsigned int time_total = time_high + time_low;

    breathing.cycle_time++;
    if(breathing.cycle_time > time_total) {
        breathing.cycle_time = 0;

        // reset PID at start of peak
        _init_PID();
    }

    const int target_high = 3000;
    const int setpoint_low = 1000;

    // ramp is 50ms
    const int ramp_time = 50;
    const int delta_p = (target_high - setpoint_low);
    const int setpoint_high = min(setpoint_low + (breathing.cycle_time*(delta_p/ramp_time)), target_high);



    g_sensor_state_1 = (0.7*g_sensor_state_1) + (0.3*sensors_read_pressure_1_pa());
    g_sensor_state_2 = (0.7*g_sensor_state_2) + (0.3*sensors_read_pressure_2_pa());

    int pressure = (g_sensor_state_1 + g_sensor_state_2)/2;

    // start building pressure
    if(breathing.cycle_time < time_high) {
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
        if(pressure < setpoint_low) {
            control_switch1_off();
        }
    }

    float error = g_setpoint_pa - pressure;

    float PID_out = arm_pid_f32(&pid_instance, error);
    // End PID

    g_to_DPR = PID_out;//(0.95*g_to_DPR) + (0.05*PID_out);

    float to_DPR = constrain((g_to_DPR), 0, 10000);
    //float to_DPR = g_setpoint_pa;
    control_DPR_set_pa(to_DPR);


    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {
        log_debug("%d,%d",
                g_setpoint_pa,
                //(int)g_sensor_state_1,
                //(int)g_sensor_state_2,
                (int)pressure);
                //(int)to_DPR);
    }
}




static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
