#include <c_utils/assert.h>

#include "actuators/PWM.h"
#include "actuators/control_signals.h"
#include "sensors/sensors.h"

#include "global_settings.h"
#include "breathing.h"
#include "log.h"
#include "app.h"

#include <math.h>
#include <stdlib.h>


static int pressure_control_loop(void);
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
    // TODO: begin self-test
}

enum TestState breathing_test()
{
    // TODO self-test procedure

    return breathing.test_state;
}

int breathing_run()
{
    breathing.breathing_time++;

    const uint32_t time_ms = breathing.breathing_time;

    int pressure = pressure_control_loop();

    breathing.cycle_time++;

    if(BREATHING_LOG_INTERVAL_ms && time_ms && ((time_ms % BREATHING_LOG_INTERVAL_ms) == 0)) {
        log_wtime("breathing...");
    }

    return pressure;
}



static int pressure_control_loop(void)
{
    // TODO control loop

    return 0;
}


static bool program_validation(void)
{
    // TODO implement: validate program settings for maximum robustness
    // for now, we assume all settings are sane

    return true;
}
