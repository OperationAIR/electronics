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

// PID loop for DPR
float DPR_PID_Kp = 1.0;
float DPR_PID_Ki = 0.01;
float DPR_PID_Kd = 3.0;

static int g_signal_to_switch = 0;
static volatile int g_DPR_setpoint_pa = 0;
static arm_pid_instance_f32 DPR_PID;    // pressure regulator
static arm_pid_instance_f32 MFC_PID;    // mass flow controllers
static float g_sensor_state_1 = 0;
static float g_sensor_state_2 = 0;
static float g_to_DPR = 0;
static volatile enum BreathCycleState g_breath_cycle_state = BreathCycleStateNone;

// PID loop for MFC
float MFC_PID_Kp = 3.0;
float MFC_PID_Ki = 0.0;
float MFC_PID_Kd = 0.5;

#define CLOSE_TIME_MS 500

#define MFC_FLOW_MIN_SLPM   0.0

// TODO 50
#define MFC_FLOW_MAX_SLPM   50.0

const int g_MFC_setpoint_pa = 65000;

#include "sensors/flow.h"

int breathing_read_setpoint_pa(void)
{
    return g_DPR_setpoint_pa;
}

void breathing_print_DPR_PID(void)
{
    log_debug("DPR PID: %d, %d, %d",
            (int)DPR_PID_Kp,
            (int)DPR_PID_Ki,
            (int)DPR_PID_Kd);
}
void breathing_print_MFC_PID(void)
{
    log_debug("MFC PID: %d, %d, %d",
            (int)MFC_PID_Kp,
            (int)MFC_PID_Ki,
            (int)MFC_PID_Kd);
}

static void _init_DPR_PID(void)
{
    // Begin PID

    arm_pid_reset_f32(&DPR_PID);
    DPR_PID.Kp = DPR_PID_Kp;
    DPR_PID.Ki = DPR_PID_Ki;
    DPR_PID.Kd = DPR_PID_Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&DPR_PID, 1);
}
static void _init_MFC_PID(void)
{
    // Begin PID

    arm_pid_reset_f32(&MFC_PID);
    MFC_PID.Kp = MFC_PID_Kp;
    MFC_PID.Ki = MFC_PID_Ki;
    MFC_PID.Kd = MFC_PID_Kd;
    // init calculates the required coefficients based on the PID input
    // A0 = Kp + Ki + Kd
    // A1 = (-Kp ) - (2 * Kd )
    // A2 = Kd
    // The PID controller calculates the following transfer function
    // y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
    arm_pid_init_f32(&MFC_PID, 1);
}

void breathing_tune_DPR_PID(float kp, float ki, float kd)
{
    DPR_PID_Kp = kp;
    DPR_PID_Ki = ki;
    DPR_PID_Kd = kd;
    _init_DPR_PID();

    log_debug("DPR PID: %d, %d, %d",
            (int)DPR_PID_Kp,
            (int)DPR_PID_Ki,
            (int)DPR_PID_Kd);
}
void breathing_tune_MFC_PID(float kp, float ki, float kd)
{
    MFC_PID_Kp = kp;
    MFC_PID_Ki = ki;
    MFC_PID_Kd = kd;
    _init_MFC_PID();

    log_debug("PID: %d, %d, %d",
            (int)MFC_PID_Kp,
            (int)MFC_PID_Ki,
            (int)MFC_PID_Kd);
}

static struct {
    volatile uint32_t cycle_time;
    volatile uint32_t breathing_time;
    enum TestState test_state;
    volatile uint32_t timestamp_start_close;
} breathing;


bool breathing_init(void)
{
    if (!program_validation()) {
        return false;
    }

    return true;
}

void breathing_start_calibration(void)
{
    // open Valve: startup auto-calibrate requires 0psi pressure in the system
    control_switch1_on(10000);
}
void breathing_finish_calibration(void)
{
    sensors_calibrate_offset();
}

bool breathing_start_program(void)
{
    g_breath_cycle_state = BreathCycleStateNone;
    breathing.breathing_time = 0;
    breathing.cycle_time = 0;

    _init_DPR_PID();
    _init_MFC_PID();

    control_MFC_set(0, 0.0);

    // init state to sane value
    g_sensor_state_1 = sensors_read_pressure_1_pa();
    g_sensor_state_2 = sensors_read_pressure_2_pa();

    return control_DPR_on();
    // TODO start
}


// Stop breathing, let air pressure equalize to zero
void breathing_stop(void)
{
    g_breath_cycle_state = BreathCycleStateNone;
    control_DPR_off();

    // open Valve: let all air out.
    // TODO: is this the required behaviour? or should the pressure be
    // kept at peep for as long as possible
    control_switch1_on(10000);

    control_MFC_set(0, 0.0);
}

void breathing_power_off(void)
{
    control_DPR_off();
    control_MFC_set(0, 0.0);
    control_switch1_off();
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

static struct {
    int peep;
    int pressure;

    unsigned int time_high_ms;
    unsigned int time_low_ms;
    unsigned int time_total_ms;

    float oxygen_fraction;

} cfg;

static void _update_cfg(const OperationSettings *config)
{
    // Apply config. TODO only at start of cycle
    cfg.peep = config->peep;
    cfg.pressure = config->pressure;

    // calculate duration of inhale/exhale in ms
    const int freq_per_min = config->frequency;
    const float ratio = config->ratio;
    cfg.time_high_ms = (60000/(freq_per_min*(1+ratio)));
    cfg.time_low_ms = ratio * cfg.time_high_ms;
    cfg.time_total_ms = cfg.time_high_ms + cfg.time_low_ms;

    // Oxygen fraction from 0-100 to 0.0-1.0
    cfg.oxygen_fraction  = (config->oxygen * 0.01);
}

void breathing_run(const OperationSettings *config)
{
    const int dt = 2;
    breathing.breathing_time+=dt;

    const uint32_t time_ms = breathing.breathing_time;

    if(breathing.cycle_time > cfg.time_total_ms) {
        breathing.cycle_time = 0;
    }

    if(breathing.cycle_time == 0) {
        breathing.timestamp_start_close = 0;

        _update_cfg(config);

        // reset PID at start of peak
        _init_DPR_PID();
    }



    //
    // DPR control loop
    //


    g_signal_to_switch = 0;

    // pressure in Pa
    const int target_high = cfg.pressure;
    const int setpoint_low = cfg.peep;

    // ramp is 50ms
    const int ramp_time = 50;
    const int delta_p = (target_high - setpoint_low);
    const int setpoint_high = min(setpoint_low + (breathing.cycle_time*(delta_p/ramp_time)), target_high);

    g_sensor_state_1 = (0.7*g_sensor_state_1) + (0.3*sensors_read_pressure_1_pa());
    g_sensor_state_2 = (0.7*g_sensor_state_2) + (0.3*sensors_read_pressure_2_pa());

    // TODO FIXME: just sensor 2
    //int DPR_pressure = (g_sensor_state_1 + g_sensor_state_2)/2;
    int DPR_pressure = (g_sensor_state_1);// + g_sensor_state_2)/2;

    // start building pressure
    if(breathing.cycle_time <= cfg.time_high_ms) {
        g_breath_cycle_state = BreathCycleStatePeakPressure;
        control_switch1_off();
        g_DPR_setpoint_pa = setpoint_high;
        //control_DPR_set_pa(g_DPR_setpoint_pa);

        // Note: cycle_time increases in steps of 'dt'.
        // If the next time would be past time_high,
        // the expiration should start.
        if((breathing.cycle_time + dt) > cfg.time_high_ms) {

            // start of lower pressure

            control_switch1_on(10000);
            g_DPR_setpoint_pa = setpoint_low;
            //control_DPR_set_pa(g_DPR_setpoint_pa);
        }

    // during low pressure
    } else if(breathing.cycle_time > cfg.time_high_ms) {
        g_breath_cycle_state = BreathCycleStatePeep;
        // close valve if pressure goes below peep
        if(DPR_pressure < setpoint_low) {
            if(breathing.timestamp_start_close == 0) {
                breathing.timestamp_start_close = breathing.cycle_time;
            }

        }

        // Close softly after closing has been initialized
        if(breathing.timestamp_start_close > 0) {
            const int time_since_close = (breathing.cycle_time - breathing.timestamp_start_close);
            if(time_since_close >= 0) {

                const int close_time = min(CLOSE_TIME_MS, cfg.time_low_ms/3);

                int pwm_value = (10000*time_since_close)/close_time;
                pwm_value = constrain(pwm_value, 0, 10000);
                g_signal_to_switch = pwm_value;
                control_switch1_on(10000-pwm_value);
            }
        }
    }

    float error = g_DPR_setpoint_pa - DPR_pressure;

    float DPR_PID_out = arm_pid_f32(&DPR_PID, error);
    // End PID

    g_to_DPR = DPR_PID_out + 5500;

    float to_DPR = constrain((g_to_DPR), 0, 10000);
    //float to_DPR = g_DPR_setpoint_pa;
    control_DPR_set_pa(to_DPR);

    //
    // MFC control loop
    //

    int MFC_pressure_pa = sensors_read_pressure_MFC_pa();
    float MFC_error_mbar = (g_MFC_setpoint_pa - MFC_pressure_pa)/100.0;
    float MFC_PID_out = arm_pid_f32(&MFC_PID, MFC_error_mbar);
    MFC_PID_out = constrain(MFC_PID_out, MFC_FLOW_MIN_SLPM, MFC_FLOW_MAX_SLPM);

    /*
    log_debug("MFC: error=%d mbar PID_out=%d",
            (int)MFC_error_mbar,
            (int)MFC_PID_out);
            */

    control_MFC_set(MFC_PID_out, cfg.oxygen_fraction);

    //
    // Serial 'plot' output
    //

    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {
//        float flow = flowsensor_test();
//        log_debug("%d",
//                  (int) flow);

        // MFC plot


        // DPR plot
        //
        /*
        log_debug("%d,%d,%d,%d",
                (int)g_DPR_setpoint_pa,
                (int)g_sensor_state_1,
                (int)g_sensor_state_2,
                (int)g_signal_to_switch,
                //(int)DPR_pressure,
                (int)to_DPR);
        */
//        log_debug("%d, %d, %d",
//                  (int) sensors_read_flow());
//                    g_MFC_setpoint_pa,
//                    MFC_pressure_pa);
//                  (int) cfg.oxygen_fraction*100);

        // DPR plot
        //

        log_debug("%d,%d",
//                (int)g_DPR_setpoint_pa,
//                (int)g_sensor_state_1,
//                (int)g_sensor_state_2);
//                (int)g_signal_to_switch,
//                (int)DPR_pressure,
//                (int)to_DPR);
                  (int) sensors_read_flow());

    }

    breathing.cycle_time+=dt;
}


enum BreathCycleState breathing_get_cycle_state(void)
{
    return g_breath_cycle_state;
}




static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
