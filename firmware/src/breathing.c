#include <c_utils/assert.h>

#include "actuators/PWM.h"
#include "actuators/control_signals.h"

#include "global_settings.h"
#include "breathing.h"
#include "log.h"
#include "sensors/sensors.h"
#include "app.h"

#include <math.h>
#include <stdlib.h>

// valve2 == zuiger
// valve1 == blazer

static void breathing_start_sub_program(uint32_t program_index){}
static int pressure_control_loop_A(const BreathingSubProgram *prog);
static int pressure_control_loop_B(const BreathingSubProgram *prog);
static bool program_validation(void);


static struct {
    volatile int target_pressure;
    volatile uint32_t num_programs;
    volatile uint32_t breathing_time;
    volatile uint32_t cycle_time;
    volatile uint32_t current_sub_program;
    volatile uint32_t current_setpoint;
    PWM pwm;
    enum TestState test_state;
} breathing;


bool breathing_init(void)
{

    if (!program_validation()) {
        return false;
    }
    const uint32_t pwm_frequency = 20*1000;
    assert(PWM_init(&breathing.pwm, LPC_TIMER16_1,
                PWM_CH1, pwm_frequency, REQUIRED_PWM_RESOLUTION));

    breathing.current_sub_program = 0;
    breathing.num_programs = 0;

    for (int i=0; i<MAX_SUB_PROGRAMS; i++) {
        if(breathing_program.subprograms[i].type == BREATHING_PROGRAM_TYPE_NONE) {
            break;
        }
        breathing.num_programs++;
    }

    return true;
}


void breathing_start_program()
{
    // TODO start
}


void breathing_stop()
{
    // TODO stop
}

enum TestState breathing_test_get_result()
{
    return breathing.test_state;
}

void breathing_start_test()
{
    breathing.test_state = TestStateBuildPressure;
    breathing.breathing_time = 0;
    PWM_set(&breathing.pwm, PWM_CH1, SELF_TEST_MOTOR_POWER);
    PWM_start(&breathing.pwm);
}

enum TestState breathing_test()
{
    static uint32_t hold_time = 0;
    breathing.breathing_time++;
    const uint32_t time_ms = breathing.breathing_time;

    int pressure = sensors_read_pressure();
    if (breathing.test_state == TestStateBuildPressure) {
        if(SELF_TEST_LOG_INTERVAL_ms && time_ms && ((time_ms % SELF_TEST_LOG_INTERVAL_ms) == 0)) {
            log_wtime("%d kPa", pressure);
        }

        int error = SELF_TEST_TARGET_PRESSURE_kPa - pressure;

        if (error > 0) {

            // valve2 == zuiger
            // valve1 == blazer
            // increase pressure
            if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
            } else {
            }
        } else {
            // target reached
            log_wtime("Self test target reached: %d kPa", pressure);
            log_wtime("Start hold time");
            PWM_stop(&breathing.pwm);
            breathing.test_state = TestStateHold;
            // start hold time
            hold_time = 0;
        }

        // pressure buildup takes too long => abort
        if (time_ms > SELF_TEST_TIMEOUT_ms) {
            log_wtime("Error: Self Test Timed Out -> abort");
            breathing.test_state = TestStateFailed;
            breathing_stop();
        }
    } else if (breathing.test_state == TestStateHold) {
        hold_time++;
        if(time_ms && ((time_ms % 500) == 0)) {
            log_wtime("%d kPa", pressure);
        }
        if (pressure < SELF_TEST_PRESSURE_THRESHOLD_kPa) {
            // test failed
            breathing.test_state = TestStateFailed;
            log_wtime("Self test failed, venting pressure: %d kPa", pressure);
            // vent pressure
            if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
            } else {
            }
        }
        if (hold_time > SELF_TEST_HOLD_TIME_ms) {
            breathing.test_state = TestStateSuccess;

            log_wtime("Self test succeeded, venting pressure");
            // vent pressure
            if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
            } else {
            }
        }
    }



    return breathing.test_state;
}

int breathing_run()
{
    breathing.breathing_time++;

    const uint32_t time_ms = breathing.breathing_time;

    const int i = breathing.current_sub_program;
    const BreathingSubProgram *prog = &breathing_program.subprograms[i];

    if ((breathing.current_setpoint >= (prog->num_cycles * 2)) || (time_ms > prog->max_time)) {
        breathing.current_sub_program++;

        if (breathing.current_sub_program >= breathing.num_programs) {
            // all subprograms finished
            breathing_stop();
            //log_wtime("Stop Breathing Program [end]");
            return 0;
        }

        breathing_start_sub_program(breathing.current_sub_program);

    }

    int pressure = 0;
    if (prog->type == BREATHING_PROGRAM_TYPE_A) {
        pressure = pressure_control_loop_A(prog);
    } else if (prog->type == BREATHING_PROGRAM_TYPE_B) {
        pressure = pressure_control_loop_B(prog);
    }

    breathing.cycle_time++;

    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {
        log_wtime("%d", pressure);
    }

    return pressure;
}



static int pressure_control_loop_B(const BreathingSubProgram *prog)
{
    int pressure = sensors_read_pressure();
    int error = breathing.target_pressure - pressure;

    if (error < 0) {
        // decrease pressure
         if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
         } else {
         }
    } else {
        // increase pressure
        if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
        } else {
        }
    }

    if (breathing.target_pressure == prog->max_pressure) {
        if (breathing.cycle_time >= prog->cycle_time_pressure) {
            breathing.target_pressure = prog->min_pressure;
            PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_vaccuum);
            breathing.cycle_time = 0;
            breathing.current_setpoint++;
            log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
        }
    }
    if (breathing.target_pressure == prog->min_pressure) {
        if (breathing.cycle_time >= prog->cycle_time_vaccuum) {
            breathing.target_pressure = prog->max_pressure;
            PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_pressure);
            breathing.cycle_time = 0;
            breathing.current_setpoint++;
            log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
        }
    }

    return pressure;
}

// static void reset_cycle()
// {
//     breathing.cycle_time = 0;
//     breathing.current_setpoint++;
//     log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
// }


static int pressure_control_loop_A(const BreathingSubProgram *prog)
{
    int pressure = sensors_read_pressure();
    int error = breathing.target_pressure - pressure;

    if (error < 0) {
        //app_led_animation(&breathing_vaccuum_animation);
        // decrease pressure
        // valve2 == zuiger
        // valve1 == blazer
        if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
         } else {
         }
    } else {
        //app_led_animation(&breathing_pressure_up_animation);
        // increase pressure
        if (VALVE_FOR_OVER_PRESSURE == VALVE1) {
        } else {
        }
    }

    // PWM_get_resolution(&pwm);
    // PWM_set(&pwm, PWM_CH1, fabsf(error * g_app.P));

    if (abs(error) < 2) {
        if (breathing.target_pressure == prog->max_pressure) {
            breathing.target_pressure = prog->min_pressure;
            PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_vaccuum);
        } else if (breathing.target_pressure == prog->min_pressure) {
            breathing.target_pressure = prog->max_pressure;
            PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_pressure);
        }
        breathing.current_setpoint++;
        breathing.cycle_time = 0;
        log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
    } else {
        if (breathing.target_pressure == prog->max_pressure) {
            if (breathing.cycle_time >= prog->cycle_time_pressure) {
                breathing.target_pressure = prog->min_pressure;
                PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_vaccuum);
                breathing.cycle_time = 0;
                breathing.current_setpoint++;
                log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
            }
        }
        if (breathing.target_pressure == prog->min_pressure) {
            if (breathing.cycle_time >= prog->cycle_time_vaccuum) {
                breathing.target_pressure = prog->max_pressure;
                PWM_set(&breathing.pwm, PWM_CH1, prog->motor_power_pressure);
                breathing.cycle_time = 0;
                breathing.current_setpoint++;
                log_wtime("cycle %d, target: %d", breathing.current_setpoint/2, breathing.target_pressure);
            }
        }
    }

    return pressure;

}

static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
