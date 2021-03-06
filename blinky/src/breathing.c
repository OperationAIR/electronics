#include <c_utils/assert.h>
#include <c_utils/max.h>
#include <c_utils/constrain.h>

#include "actuators/control_signals.h"
#include "sensors/sensors.h"
#include "sensors/calculated.h"

#include "global_settings.h"
#include "breathing.h"
#include "log.h"
#include "app.h"

#include <math.h>
#include <stdlib.h>

#include "cmsis_dsp_lib/arm_math.h"


static bool program_validation(void);

// PID loop for DPR
float DPR_PID_Kp = 1.4; //1
float DPR_PID_Ki = 0.01; //0.1
float DPR_PID_Kd = 0.25; //3.0

static int g_signal_to_switch = 0;
static volatile int g_pressure_setpoint_pa = 0;
static arm_pid_instance_f32 DPR_PID;    // pressure regulator
static arm_pid_instance_f32 MFC_PID;    // mass flow controllers
static arm_pid_instance_f32 EXP_PID;

static float g_pressure_state_insp = 0;
static float g_pressure_state_exp = 0;
static float g_pressure_system_pa = 0;
static float g_MFC_pressure_pa = 0;

static float g_to_DPR = 0;
static float g_to_EXP = 0;

static float g_inspiratory_hold_result = 0;
static float g_expiratory_hold_result = 0;

static volatile enum BreathCycleState g_breath_cycle_state = BreathCycleStateNone;

// PID loop for MFC
float MFC_PID_Kp = 3.0;
float MFC_PID_Ki = 0.0;
float MFC_PID_Kd = 0.5;

// PID loop for EXP
float EXP_PID_Kp = 3;
float EXP_PID_Ki = 0;
float EXP_PID_Kd = 10;

#define CLOSE_TIME_MS 4000

#define MFC_FLOW_MIN_SLPM   0.0

// TODO 50
#define MFC_FLOW_MAX_SLPM   50.0

const int g_MFC_setpoint_pa = 65000;


int breathing_read_setpoint_pa(void)
{
    return g_pressure_setpoint_pa;
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
void breathing_print_EXP_PID(void)
{
    log_debug("EXP PID: %d, %d, %d",
              (int)EXP_PID_Kp,
              (int)EXP_PID_Ki,
              (int)EXP_PID_Kd);
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

static void _init_EXP_PID(void)
{
    // Begin PID
    arm_pid_reset_f32(&EXP_PID);
    EXP_PID.Kp = EXP_PID_Kp;
    EXP_PID.Ki = EXP_PID_Ki;
    EXP_PID.Kd = EXP_PID_Kd;

    arm_pid_init_f32(&EXP_PID, 1);
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

void breathing_tune_EXP_PID(float kp, float ki, float kd)
{
    EXP_PID_Kp = kp;
    EXP_PID_Ki = ki;
    EXP_PID_Kd = kd;
    _init_EXP_PID();

    log_debug("PID: %d, %d, %d",
              (int)EXP_PID_Kp,
              (int)EXP_PID_Ki,
              (int)EXP_PID_Kd);
}

static struct {
    volatile uint32_t cycle_time;
    volatile uint32_t breathing_time;
    volatile uint32_t hold_time;
    volatile uint32_t timestamp_start_close;
    volatile bool breathing_cycle_finished;
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
    control_valve_exp_on(10000);
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
    _init_EXP_PID();

    control_MFC_on(0, 0.0);

    // init state to sane value
    g_pressure_state_insp = sensors_read_pressure_insp_pa();
    g_pressure_state_exp = sensors_read_pressure_exp_pa();


//    return control_DPR_on();
    return true;
    // TODO start
}


// Stop breathing, let air pressure equalize to zero
void breathing_stop(void)
{
    g_breath_cycle_state = BreathCycleStateNone;

    control_valve_insp_off();

    // open Valve: let all air out.
    // TODO: is this the required behaviour? or should the pressure be
    // kept at peep for as long as possible
    control_valve_exp_off();

    control_MFC_on(0, 0.0);
}

void breathing_power_off(void)
{
    control_valve_insp_off();
    control_MFC_on(0, 0.0);
    control_valve_exp_off();
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
    const float ratio = (config->ratio/10.0);
    cfg.time_high_ms = (60000/(freq_per_min*(1+ratio)));
    cfg.time_low_ms = ratio * cfg.time_high_ms;
    cfg.time_total_ms = cfg.time_high_ms + cfg.time_low_ms;

    // Oxygen fraction from 0-100 to 0.0-1.0
    cfg.oxygen_fraction  = (config->oxygen * 0.01);
}

void _read_and_filter_pressure_sensor(void) {
    g_pressure_state_insp = (0.7*g_pressure_state_insp) + (0.3*sensors_read_pressure_insp_pa());
    g_pressure_state_exp = (0.7*g_pressure_state_exp) + (0.3*sensors_read_pressure_exp_pa());

    // TODO FIXME: just sensor 2
//    int DPR_pressure = (g_pressure_state_insp + g_pressure_state_exp)/2;
    g_pressure_system_pa = (g_pressure_state_insp);// + g_pressure_state_exp)/2;
}

void _DPR_control_loop(void) {
    float error = g_pressure_setpoint_pa - g_pressure_system_pa;

    float DPR_PID_out = arm_pid_f32(&DPR_PID, error);
    // End PID

    g_to_DPR = DPR_PID_out + 5500;

    float to_DPR = constrain((g_to_DPR), 0, 10000);
    //float to_DPR = g_pressure_setpoint_pa;
    control_valve_insp_on(to_DPR);
}

void _MFC_control_loop(void) {
    //
    // MFC control loop
    //

    g_MFC_pressure_pa = sensors_read_pressure_MFC_pa();
    float MFC_error_mbar = (g_MFC_setpoint_pa - g_MFC_pressure_pa)/100.0;
    float MFC_PID_out = arm_pid_f32(&MFC_PID, MFC_error_mbar);
    MFC_PID_out = constrain(MFC_PID_out, MFC_FLOW_MIN_SLPM, MFC_FLOW_MAX_SLPM);

    control_MFC_on(MFC_PID_out, cfg.oxygen_fraction);
}

void _inspiration(int dt) {
    g_breath_cycle_state = BreathCycleStatePeakPressure;
    control_valve_exp_off();

    g_pressure_setpoint_pa = cfg.pressure;
    //control_DPR_set_pa(g_pressure_setpoint_pa);

    // Note: cycle_time increases in steps of 'dt'.
    // If the next time would be past time_high,
    // the expiration should start.
    if((breathing.cycle_time + dt) > cfg.time_high_ms) {

        // start of lower pressure
        control_valve_exp_on(10000);
        g_pressure_setpoint_pa = cfg.peep;
        _init_EXP_PID();
    }
}

void _expiration(int dt) {
    g_breath_cycle_state = BreathCycleStatePeep;


//    float error = g_pressure_setpoint_pa - g_pressure_system_pa;
    float error = g_pressure_system_pa - g_pressure_setpoint_pa;

    float EXP_PID_out = arm_pid_f32(&EXP_PID, error);

//    g_to_EXP = EXP_PID_out + 5500;
    g_to_EXP = 5500+EXP_PID_out;

    float to_EXP = constrain((g_to_EXP), 0, 10000);

//    control_switch1_on( (int) (10000-to_EXP));
    control_valve_exp_on( (int) (to_EXP));

//    if(BREATHING_LOG_INTERVAL_ms && breathing.breathing_time && ((breathing.breathing_time % BREATHING_LOG_INTERVAL_ms) == 0)) {
//        log_debug("%d, %d, %d",
//                  (int) g_pressure_setpoint_pa,
//                  (int) g_pressure_system_pa,
//                  (int) (to_EXP));
//    }

}

/**
Functions needed to perform the breathing
*/
void breathing_run(const OperationSettings *config, const int dt)
{
    breathing.breathing_time+=dt;

    const uint32_t time_ms = breathing.breathing_time;

    // calculate tidal volume, oxygen percentage etc.
    // The outputs are available as virtual 'sensors' via sensors.h
    calculated_update((breathing.cycle_time == 0), dt);

    // start of breathing cycle
    if(breathing.cycle_time == 0) {
        breathing.timestamp_start_close = 0;

        _update_cfg(config);

        // reset PID at start of peak
        _init_DPR_PID();
    }

    g_signal_to_switch = 0;

    _read_and_filter_pressure_sensor();

    // start building pressure
    if(breathing.cycle_time <= cfg.time_high_ms) {
        _inspiration(dt);

    // during low pressure
    } else if(breathing.cycle_time > cfg.time_high_ms) {
        _expiration(dt);
    }

    _DPR_control_loop();
    _MFC_control_loop();

    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {

//        log_debug("%d, %d",
//                  (int) g_MFC_setpoint_pa,
//                  (int) g_MFC_pressure_pa);


//         DPR plot
//        log_debug("%d,%d,%d",
//                (int)g_pressure_setpoint_pa,
//                (int)g_pressure_state_insp,
//                (int)g_pressure_state_exp);
//                (int)10000-g_signal_to_switch,
//                (int)DPR_pressure,
//                (int)to_DPR);
    }


    breathing.cycle_time+=dt;

    if(breathing.cycle_time > cfg.time_total_ms) {
        g_breath_cycle_state = BreathCycleLastStepDone;
        breathing.cycle_time = 0;
    }
}

/**
Functions needed to perform the inspiratory-hold-manouvre
*/
void pre_hold(const OperationSettings *config, const int dt) {
    // Reload values, reset timers
    breathing.hold_time = 0;
    _update_cfg(config);
}

bool inspiratory_hold_run(const OperationSettings *config, bool hold_pressed, const int dt) {
    breathing.breathing_time+=dt;

    // Read sensor values
    _read_and_filter_pressure_sensor();

    if(breathing.cycle_time <= cfg.time_high_ms) {
        // Close all valves
        // Inspiratory phase

        g_breath_cycle_state = BreathCycleStatePeakPressure;
        control_valve_exp_off();
        g_pressure_setpoint_pa = cfg.pressure;

        _DPR_control_loop();

        breathing.cycle_time+=dt;

    } else {
        // Close valves for 2 seconds, average the pressure between 2 and 2.5 seconds
        control_valve_insp_off();

        // Go on till time is more than 7.5 sec or hold button is released
        if (!hold_pressed || (breathing.hold_time-cfg.time_high_ms) >= 7500) {
            log_cli("Inspiratory hold done");

            // save results
            g_inspiratory_hold_result = (g_pressure_state_insp + g_pressure_state_exp)/2;

            log_cli("Sensor mean value: '%d' cmH2O * 100", (int) (g_inspiratory_hold_result/0.98) );

            return true;
        }
    }

    _MFC_control_loop();

    breathing.hold_time+=dt;

    return false;
}

bool post_inspiratory_hold(const OperationSettings *config, const int dt)
{
    // expiration phase (exact the same as normal breathing
    _read_and_filter_pressure_sensor();

    control_valve_insp_on(10000);
    g_pressure_setpoint_pa = cfg.peep;

    _expiration(dt);

    _DPR_control_loop();
    _MFC_control_loop();

    breathing.cycle_time+=dt;

    if (breathing.cycle_time > cfg.time_total_ms) {
        breathing.cycle_time = 0;
        return true;
    }

    return false;
}

/**
Functions needed to perform the expiratory-hold-manouvre
*/
bool expiratory_hold_run(const OperationSettings *config, bool hold_pressed, const int dt) {
    breathing.breathing_time+=dt;
    control_valve_exp_off();
    control_valve_insp_off();

    // Read sensor values
    _read_and_filter_pressure_sensor();

    if (!hold_pressed || breathing.hold_time >= 7500 ) {
        log_cli("Inspiratory hold done");

        // save results
        g_expiratory_hold_result = (g_pressure_state_insp + g_pressure_state_exp)/2;

        log_cli("Sensors mean value: '%d' cmH2O * 100", (int) (g_expiratory_hold_result/0.98) );

        return true;
    }

    breathing.hold_time+=dt;

    _MFC_control_loop();
    return false;
}


enum BreathCycleState breathing_get_cycle_state(void)
{
    return g_breath_cycle_state;
}

float breathing_get_inspiratory_hold_result()
{
    return g_inspiratory_hold_result;
}

float breathing_get_expiratory_hold_result()
{
    return g_expiratory_hold_result;
}


static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
