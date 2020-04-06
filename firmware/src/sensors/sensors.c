#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/max.h>

#include "sensors.h"
#include "actuators/control_signals.h"
#include "ADC.h"
#include "flow.h"

#include "MPRLS_pressure.h"
#include "board.h"
#include "board_GPIO_ID.h"

// TODO RM
#include "log.h"


struct {
    int32_t pressure_MFC;
    int32_t pressure_1;
    int32_t pressure_2;
    int32_t pressure_regulator;
    float flow;
} Sensors;

static bool g_error = false;
static int32_t g_offset_pressure_1 = 0;
static int32_t g_offset_pressure_2 = 0;

// See schematics
#define ADC_FACTOR_PRESSURE             (168.0/100.0)

// TODO FIXME: voltage divider for flow/MFC input is be wrong!
// Datasheet table shows 1-5V instead of assumed 0-12!!
#define ADC_FACTOR_PRESSURE_MFC         (13.3/3.3)
#define ADC_FACTOR_PREG_PRESSURE        (1.0)

// Slew rate limits (in app ticks / full ADC range)
// Tweak these to limit noise spikes.
// 1 = lowest value (effectively no filtering)
// 1024 (ADC_RANGE) = highest value (strong filter)
#define SLEW_LIMIT_PRESSURE_MFC             (10)
#define SLEW_LIMIT_PRESSURE         (5)
#define SLEW_LIMIT_PREG_PRESSURE    (400)

#define PRESSURE_SENSORS_DIGITAL    (1)

#if(PRESSURE_SENSORS_DIGITAL)
static MPRLS mprls1;
static MPRLS mprls2;
#endif

void sensors_init(void) {

#if(PRESSURE_SENSORS_DIGITAL)
    mprls_init(&mprls1, LPC_SSP0,
        board_get_GPIO(GPIO_ID_PSENSE_1_CS),
        board_get_GPIO(GPIO_ID_PSENSE_1_DRDY),
        board_get_GPIO(GPIO_ID_PSENSE_RESET));

    mprls_init(&mprls2, LPC_SSP0,
        board_get_GPIO(GPIO_ID_PSENSE_2_CS),
        board_get_GPIO(GPIO_ID_PSENSE_2_DRDY),
        board_get_GPIO(GPIO_ID_PSENSE_RESET));

    mprls_enable(&mprls1);
    mprls_enable(&mprls2);

    uint32_t p1 = mprls_read_blocking(&mprls1);
    uint32_t p2 = mprls_read_blocking(&mprls2);
    log_debug("Pres: %u, %u", p1, p2);
#endif

    ADC_init();

//    flowsensor_enable();

    sensors_reset();
}

bool sensors_calibrate_offset(void)
{
    // reset offsets to zero. This is done because we dont
    // want the sensors_read_XXX() calls below to include any previous offset.
    g_offset_pressure_1 = 0;
    g_offset_pressure_2 = 0;

    g_offset_pressure_1 = sensors_read_pressure_1_pa();
    g_offset_pressure_2 = sensors_read_pressure_2_pa();

    return g_error;
}

void sensors_reset(void)
{
    g_error = false;
    Sensors.pressure_MFC = -1;
    Sensors.pressure_1 = -1;
    Sensors.pressure_2 = -1;
    Sensors.pressure_regulator = -1;

    g_offset_pressure_1 = 0;
    g_offset_pressure_2 = 0;

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

static uint32_t count = 0;
void sensors_update(void)
{
    filter_adc(&Sensors.pressure_MFC, ADC_ID_PRESSURE_MFC,
            ADC_RANGE/SLEW_LIMIT_PRESSURE_MFC);

    if (count++ % 5 == 0) {
        Sensors.flow = read_flow_sensor();
        Sensors.flow = Sensors.flow*3.14f*(0.0155f/2)*(0.0155f/2)*1000*60;
    }

//    Sensors.flow = read_flow_sensor();
//    Sensors.flow = flowsensor_test();


#if(PRESSURE_SENSORS_DIGITAL)

    // sample sensor1
    if(mprls_is_ready(&mprls1)) {
        // read value and trigger next sample
        Sensors.pressure_1 = mprls_read_data(&mprls1);
        mprls_trigger_read(&mprls1);

    } else if(mprls_is_timeout(&mprls1)) {

        // Timeout! try to trigger next sample, but something is wrong here!
        // TODO handle error

        g_error = true;
        mprls_trigger_read(&mprls1);
    }

    // sample sensor2
    if(mprls_is_ready(&mprls2)) {
        // read value and trigger next sample
        Sensors.pressure_2 = mprls_read_data(&mprls2);
        mprls_trigger_read(&mprls2);

    } else if(mprls_is_timeout(&mprls2)) {

        // Timeout! try to trigger next sample, but something is wrong here!
        // TODO handle error

        g_error = true;
        mprls_trigger_read(&mprls2);
    }

#else
    filter_adc(&Sensors.pressure_1, ADC_ID_PRESSURE_1,
            ADC_RANGE/SLEW_LIMIT_PRESSURE);
    filter_adc(&Sensors.pressure_2, ADC_ID_PRESSURE_2,
            ADC_RANGE/SLEW_LIMIT_PRESSURE);
#endif
    filter_adc(&Sensors.pressure_regulator, ADC_ID_PREG_PRESSURE,
            ADC_RANGE/SLEW_LIMIT_PREG_PRESSURE);
}

static float p_MFC_mbar;
const float MFC_scale_factor = 1024/5000.0;

int32_t sensors_read_pressure_MFC_pa(void)
{
    const int p_mv = ADC_scale(Sensors.pressure_MFC, ADC_FACTOR_PRESSURE_MFC);
    const int p_raw = (MFC_scale_factor*p_mv);

    // Calibrate raw input voltage --> real pressure [mBarcx]
    p_MFC_mbar = 0.9 * p_MFC_mbar + 0.1 * (1.3223 * p_raw - 141.4876);

    return (100 * p_MFC_mbar);
}

// Virtual 'sensor' that returns the current setpoint
#include "breathing.h"
int32_t sensors_read_pressure_target_pa(void)
{
    return breathing_read_setpoint_pa();
}

int32_t sensors_read_pressure_1_pa(void)
{
    int32_t result = 0;
#if(PRESSURE_SENSORS_DIGITAL)
    result = Sensors.pressure_1;
#else
    // NXP MPVZ5010
    const int v_pressure = ADC_scale(Sensors.pressure_1, ADC_FACTOR_PRESSURE);

    // NOTE: this is calibrated experimentally, instead of datasheet-based (MPVZ5010)
    const int offset_mv = 167;
    const int scale_factor = 2157;
    result = ((v_pressure-offset_mv)*scale_factor)/1000;

    /*
    // See MPVZ5010 datasheet
    const int vcc = 5000;
    int pressure_pa = ((1.079*v_pressure) - 195.211);
    return pressure_pa;
    */
#endif

    return result - g_offset_pressure_1;
}

int32_t sensors_read_pressure_2_pa(void)
{
    int32_t result = 0;
#if(PRESSURE_SENSORS_DIGITAL)
    result = Sensors.pressure_2;
#else

    const int v_pressure = ADC_scale(Sensors.pressure_2, ADC_FACTOR_PRESSURE);

    // NOTE: this is calibrated experimentally, instead of datasheet-based (MPVZ5010)
    const int offset_mv = 167;
    const int scale_factor = 2157;
    result = ((v_pressure-offset_mv)*scale_factor)/1000;

    /*
    // See MPVZ5010 datasheet
    const int vcc = 5000;
    int pressure_pa = ((1000*v_pressure) - (40*vcc)) / (0.09*vcc);
    return pressure_pa;
    */
#endif

    return result - g_offset_pressure_2;
}

float sensors_read_flow(void) {
    return Sensors.flow;
}

int32_t sensors_read_pressure_regulator(void)
{

    // TODO see See RP200_C_??? specs (which version do we have? what is the range?):
    // - ADC_FACTOR_PREG_PRESSURE
    const int v_pressure = ADC_scale(Sensors.pressure_regulator, ADC_FACTOR_PREG_PRESSURE);

    const int resistor_ohm = 150;
    const int dpr_range_pa = 5000;
    const int offset_ma = 4;
    return ((v_pressure*dpr_range_pa)/resistor_ohm - (dpr_range_pa*offset_ma))/16;

    // TODO implement
    return -1;
}


void sensors_read_all(SensorsAllData *data)
{
    data->pressure_1_pa = sensors_read_pressure_1_pa();

    data->pressure_2_pa = sensors_read_pressure_2_pa();

    data->oxygen = 0;   //TODO calculate from MFC feedback

    data->flow = (int32_t)sensors_read_flow();

//    flowsensor_test();
}


