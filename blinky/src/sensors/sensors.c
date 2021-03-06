#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/max.h>

#include "sensors.h"
#include "calculated.h"
#include "actuators/control_signals.h"
#include "ADC.h"
#include "flow.h"
#include "breathing.h"

#include "MPRLS_pressure.h"
#include "board_config/board_GPIO_ID.h"

#include "global_settings.h"

struct {
    int32_t pressure_MFC;
    int32_t pressure_in;
    int32_t pressure_out;
    int32_t pressure_patient;

    int32_t flow_MFC_air;
    int32_t flow_MFC_O2;

    int32_t battery_level;

    int32_t flow_out; //SCCPM

    int32_t inspiratory_hold_result;

    int32_t expiratory_hold_result;
} Sensors;

static bool g_error = false;
static bool g_error_flow = false;
static bool g_error_mprls_out = false;
static bool g_error_mprls_in = false;

static int32_t g_offset_pressure_in = 0;
static int32_t g_offset_pressure_out = 0;

// See schematics
#define ADC_FACTOR_PRESSURE             (168.0/100.0)
#define ADC_FACTOR_FLOW_MFC             (168.0/100.0)
#define ADC_FACTOR_BATTERY              (11.5/1.5)

// TODO FIXME: voltage divider for flow/MFC input is be wrong!
// Datasheet table shows 1-5V instead of assumed 0-12!!
#define ADC_FACTOR_PRESSURE_MFC         (13.3/3.3)
#define ADC_FACTOR_PREG_PRESSURE        (1.0)

// Slew rate limits (in app ticks / full ADC range)
// Tweak these to limit noise spikes.
// 1 = lowest value (effectively no filtering)
// 1024 (ADC_RANGE) = highest value (strong filter)
#define SLEW_LIMIT_PRESSURE_MFC             (10)
#define SLEW_LIMIT_PRESSURE                 (5)
#define SLEW_LIMIT_PREG_PRESSURE            (400)
#define SLEW_LIMIT_MFC_FEEDBACK             (50)
#define SLEW_LIMIT_BATTERY_LEVEL            (500)


static MPRLS mprls1;
static MPRLS mprls2;

void sensors_init(void) {

    UPS_status_init();
    calculated_init();

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

    ADC_init();

    if (I2C_PULL_UP_AVAILABLE) {
        if(!flowsensor_enable()) {
            g_error_flow = true;
        }
    }

    sensors_reset();
}

bool sensors_calibrate_offset(void)
{
    // reset offsets to zero. This is done because we dont
    // want the sensors_read_XXX() calls below to include any previous offset.
    g_offset_pressure_in = 0;
    g_offset_pressure_out = 0;

    g_offset_pressure_in = sensors_read_pressure_insp_pa();
    g_offset_pressure_out = sensors_read_pressure_exp_pa();

    return true; //todo g_error;
}

void sensors_reset(void)
{
    g_error = false;
    g_error_flow = false;
    g_error_mprls_out = true;
    g_error_mprls_in = true;

    Sensors.pressure_MFC = -1;
    Sensors.pressure_in = -1;
    Sensors.pressure_out = -1;
    Sensors.pressure_patient = -1;

    Sensors.flow_out = -1;
    Sensors.flow_MFC_O2 = -1;
    Sensors.flow_MFC_air = -1;
    Sensors.battery_level = 0;

    g_offset_pressure_in = 0;
    g_offset_pressure_out = 0;

    sensors_update(1);
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


static void _update_sensor_in(void)
{
    // sample sensor1
    if(mprls_is_ready(&mprls1)) {
        // read value and trigger next sample
        Sensors.pressure_in = mprls_read_data(&mprls1);
        mprls_trigger_read(&mprls1);

    } else if(mprls_is_timeout(&mprls1)) {

        // Timeout! try to trigger next sample, but something is wrong here!
        // TODO handle error

        g_error_mprls_in = true;
        mprls_trigger_read(&mprls1);
    }
}

static void _update_sensor_out(void)
{
    // sample sensor2
    if(mprls_is_ready(&mprls2)) {
        // read value and trigger next sample
        Sensors.pressure_out = mprls_read_data(&mprls2);
        mprls_trigger_read(&mprls2);

    } else if(mprls_is_timeout(&mprls2)) {

        // Timeout! try to trigger next sample, but something is wrong here!
        // TODO handle error

        g_error_mprls_out = true;
        mprls_trigger_read(&mprls2);
    }
}


static uint32_t count = 0;
void sensors_update(unsigned int dt)
{
    filter_adc(&Sensors.pressure_MFC, ADC_ID_PRESSURE_MFC,
            ADC_RANGE/SLEW_LIMIT_PRESSURE_MFC);

    if (I2C_PULL_UP_AVAILABLE) {
        if (count++ % 5 == 0) {
            // calculate flow in SLPM
            float flow_SLPM = read_flow_sensor();
            flow_SLPM = flow_SLPM*3.14f*(0.015f/2)*(0.015f/2)*1000*60;

            // SLPM to SCCPM
            Sensors.flow_out = 1000*flow_SLPM;
        }
    }

    _update_sensor_in();
    _update_sensor_out();


    filter_adc(&Sensors.flow_MFC_O2, ADC_ID_MFC_O2,
            ADC_RANGE/SLEW_LIMIT_MFC_FEEDBACK);
    filter_adc(&Sensors.flow_MFC_air, ADC_ID_MFC_AIR,
            ADC_RANGE/SLEW_LIMIT_MFC_FEEDBACK);

    if(board_has_ADC(ADC_ID_BATTERY_LEVEL)) {
        filter_adc(&Sensors.battery_level, ADC_ID_BATTERY_LEVEL,
                ADC_RANGE/SLEW_LIMIT_BATTERY_LEVEL);
    }


    if(board_has_ADC(ADC_ID_PRESSURE_PATIENT)) {
        filter_adc(&Sensors.pressure_patient, ADC_ID_PRESSURE_PATIENT,
                ADC_RANGE/SLEW_LIMIT_PRESSURE);
    }

    Sensors.inspiratory_hold_result = (int32_t)breathing_get_inspiratory_hold_result();
    Sensors.expiratory_hold_result = (int32_t)breathing_get_expiratory_hold_result();
}

static float p_MFC_pa;
int32_t sensors_read_pressure_MFC_pa(void)
{
    const int p_mv = ADC_scale(Sensors.pressure_MFC, ADC_FACTOR_PRESSURE_MFC);

    // calibrated 10-4-2020 expirementally
    p_MFC_pa = (0.9 * p_MFC_pa) + (0.1 * (16.56 * p_mv + 21523));

    return p_MFC_pa;

}

// Virtual 'sensor' that returns the current setpoint
#include "breathing.h"
int32_t sensors_read_pressure_target_pa(void)
{
    return breathing_read_setpoint_pa();
}

int32_t sensors_read_pressure_insp_pa(void)
{
    int32_t result = 0;
    result = Sensors.pressure_in;

    return result - g_offset_pressure_in;
}

int32_t sensors_read_pressure_exp_pa(void)
{
    int32_t result = 0;
    result = Sensors.pressure_out;

    return result - g_offset_pressure_out;
}

int32_t sensors_read_pressure_patient_pa(void)
{
    const int v_pressure = ADC_scale(Sensors.pressure_patient, ADC_FACTOR_PRESSURE);

    // NOTE: this is calibrated experimentally, instead of datasheet-based (MPVZ5010)
    const int offset_mv = 167;
    const int scale_factor = 2157;
    int32_t result = ((v_pressure-offset_mv)*scale_factor)/1000;

    return result;
}

int32_t sensors_read_flow_out_SCCPM(void)
{
    return Sensors.flow_out;
}
int32_t sensors_read_flow_in_SCCPM(void)
{
    // Flow into patient is approximated as total flow from MFCs
    return (sensors_read_flow_MFC_O2_SCCPM() + sensors_read_flow_MFC_air_SCCPM());
}

int32_t sensors_read_flow_MFC_O2_SCCPM(void)
{
    const int v_MFC_O2 = sensors_read_raw_MFC_O2_mv();
    // O-5000 mV / 100.0 = 0-50 000 SCCPM

    return v_MFC_O2 * 10;
}

int32_t sensors_read_raw_MFC_O2_mv(void)
{
    return ADC_scale(Sensors.flow_MFC_O2, ADC_FACTOR_FLOW_MFC);
}
int32_t sensors_read_raw_MFC_air_mv(void)
{
    return ADC_scale(Sensors.flow_MFC_air, ADC_FACTOR_FLOW_MFC);
}


int32_t sensors_read_flow_MFC_air_SCCPM(void)
{
    const int v_MFC_air = sensors_read_raw_MFC_air_mv();
    // O-5000 mV / 100.0 = 0-50 000 SCCPM

    return v_MFC_air * 10;
}

int32_t sensors_read_flow_out_avg_SCCPM(void)
{
    return calculated_flow_out_avg_SCCPM();
}


/**
 * Calculated 'sensors': based on one or more other sensor values.
 * See calculated.c for implementation
 */

int32_t sensors_read_volume_realtime_MFC_O2_CC(void)
{
    return calculated_volume_realtime_MFC_O2_CC();
}
int32_t sensors_read_volume_realtime_MFC_air_CC(void)
{
    return calculated_volume_realtime_MFC_air_CC();
}
int32_t sensors_read_volume_realtime_in_CC(void)
{
    return calculated_volume_realtime_in_CC();
}
int32_t sensors_read_volume_realtime_out_CC(void)
{
    return calculated_volume_realtime_out_CC();
}

int32_t sensors_read_oxygen_percent(void)
{
    return calculated_oxygen_percent();
}

int32_t sensors_read_volume_cycle_in_CC(void)
{
    return calculated_volume_in_CC();
}
int32_t sensors_read_volume_cycle_out_CC(void)
{
    return calculated_volume_out_CC();
}

int32_t sensors_get_inspiratory_hold_result()
{
    return Sensors.inspiratory_hold_result;
}

int32_t sensors_get_expiratory_hold_result()
{
    return Sensors.expiratory_hold_result;
}

enum UPSStatus sensors_read_UPS_status(void)
{
    return UPS_status_get();
}

uint32_t sensors_read_UPS_voltage_mv(void)
{
    return ADC_scale(Sensors.battery_level, ADC_FACTOR_BATTERY);
}



void sensors_read_all(SensorsAllData *data)
{
    data->flow_inhale = sensors_read_flow_in_SCCPM();
    data->flow_exhale = sensors_read_flow_out_SCCPM();

    data->pressure_inhale = sensors_read_pressure_insp_pa();
    data->pressure_exhale = sensors_read_pressure_exp_pa();
    data->pressure_patient = sensors_read_pressure_patient_pa();
    data->pressure_mfc = sensors_read_pressure_MFC_pa();

    data->oxygen = sensors_read_oxygen_percent();
    data->tidal_volume_exhale = sensors_read_volume_cycle_out_CC();
    data->tidal_volume_inhale = sensors_read_volume_cycle_in_CC();

    data->minute_volume = sensors_read_flow_out_avg_SCCPM();

    data->cycle_state = breathing_get_cycle_state();
    data->power_status = (sensors_read_UPS_status()
            | sensors_read_UPS_voltage_mv());

    data->inspiratory_hold_result = sensors_get_inspiratory_hold_result();
    data->expiratory_hold_result = sensors_get_expiratory_hold_result();
}

