
#include "sensors.h"
#include "actuators/control_signals.h"
#include "thermistor.h"
#include "ADC.h"

#include <c_utils/max.h>

struct {
    enum ADC_ID pressure_sense_pin;
    int32_t pressure_sense;
} Sensors;

#define PRESSURE_SENSE_ADC_FACTOR (168.0/100.0)

// Slew rate limits (in ms / full ADC range)
// Tweak these to limit noise spikes.
// 1 = lowest value (effectively no filtering)
// 1024 (ADC_RANGE) = highest value (strong filter)
#define SLEW_LIMIT_PRESSURE_SENSE   (2)


void sensor_init(enum ADC_ID pressure_sense_pin) {

     ADC_init();

     Sensors.pressure_sense_pin = pressure_sense_pin;

     sensors_reset();
}

void sensors_reset(void)
{
    Sensors.pressure_sense = -1;
    sensors_update();
}

void filter_adc(int32_t* state, enum ADC_ID ID, int32_t slew_limit)
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
    filter_adc(&Sensors.pressure_sense, Sensors.pressure_sense_pin,
            ADC_RANGE/SLEW_LIMIT_PRESSURE_SENSE);
}

int32_t sensors_read_pressure(void) {
    int Vpressure = ADC_scale(Sensors.pressure_sense, PRESSURE_SENSE_ADC_FACTOR);
    // See MPXHZ6250A datasheet
    int Vcc = 5000;
    int pressure_kPas = (Vpressure + 0.04 * Vcc) / (0.004*Vcc);
    return pressure_kPas;
}


