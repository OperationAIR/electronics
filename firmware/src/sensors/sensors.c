
#include "sensors.h"
#include "actuators/control_signals.h"
#include "flow.h"
#include "ADC.h"

#include <c_utils/max.h>

struct {
    int32_t flow;
    int32_t pressure_1;
    int32_t pressure_2;
    int32_t pressure_regulator;
} Sensors;

// See schematics
#define ADC_FACTOR_PRESSURE             (168.0/100.0)

// TODO FIXME: voltage divider for flow may be wrong!
// Datasheet table shows 1-5V instead of assumed 0-12!!
#define ADC_FACTOR_FLOW                 (13.3/3.3)
#define ADC_FACTOR_PREG_PRESSURE        (1.0)

// Slew rate limits (in ms / full ADC range)
// Tweak these to limit noise spikes.
// 1 = lowest value (effectively no filtering)
// 1024 (ADC_RANGE) = highest value (strong filter)
#define SLEW_LIMIT_FLOW             (2)
#define SLEW_LIMIT_PRESSURE         (2)
#define SLEW_LIMIT_PREG_PRESSURE    (2)


void sensors_init(void) {

     ADC_init();
     sensors_reset();
}

void sensors_reset(void)
{
    Sensors.flow = -1;
    Sensors.pressure_1 = -1;
    Sensors.pressure_2 = -1;
    Sensors.pressure_regulator = -1;
    sensors_update();
}

static void filter_adc(int32_t* state, enum ADC_ID ID, int32_t slew_limit)
{
    const int32_t prev = *state;
    int32_t delta = (int32_t)ADC_read(ID) - prev;

    if(prev >= 0) {
        // Cap delta to +/- slew_limit unless it is the first sample since reset
        delta = max(min(delta, slew_limit),(-1*slew_limit));
    }
    *state+= delta;
}

void sensors_update(void)
{
    filter_adc(&Sensors.flow, ADC_ID_FLOW,
            ADC_RANGE/SLEW_LIMIT_FLOW);
    filter_adc(&Sensors.pressure_1, ADC_ID_PRESSURE_1,
            ADC_RANGE/SLEW_LIMIT_PRESSURE);
    filter_adc(&Sensors.pressure_2, ADC_ID_PRESSURE_2,
            ADC_RANGE/SLEW_LIMIT_PRESSURE);
    filter_adc(&Sensors.pressure_regulator, ADC_ID_PREG_PRESSURE,
            ADC_RANGE/SLEW_LIMIT_PREG_PRESSURE);
}

int32_t sensors_read_flow_sccm(void)
{
    const int v_flow = ADC_scale(Sensors.flow, ADC_FACTOR_FLOW);

    return flow_interpolate_sccm(v_flow);
}

int32_t sensors_read_pressure_1_pa(void)
{
    const int v_pressure = ADC_scale(Sensors.pressure_1, ADC_FACTOR_PRESSURE);

    // See MPVZ5010 datasheet
    const int vcc = 5000;
    int pressure_pa = ((1000*v_pressure) - (40*vcc)) / (0.09*vcc);
    return pressure_pa;
}

int32_t sensors_read_pressure_2_pa(void)
{
    const int v_pressure = ADC_scale(Sensors.pressure_2, ADC_FACTOR_PRESSURE);

    // See MPVZ5010 datasheet
    const int vcc = 5000;
    int pressure_pa = ((1000*v_pressure) - (40*vcc)) / (0.09*vcc);
    return pressure_pa;
}

int32_t sensors_read_pressure_regulator(void)
{

    // TODO see See RP200_C_??? specs (which version do we have? what is the range?):
    // - ADC_FACTOR_PREG_PRESSURE
    const int v_pressure = ADC_scale(Sensors.pressure_regulator, ADC_FACTOR_PREG_PRESSURE);

    // TODO implement
    return -1;
}

