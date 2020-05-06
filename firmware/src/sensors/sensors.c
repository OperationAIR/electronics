#include <stdint.h>

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
#include "system_status.h"

struct {
    // raw values
    int32_t pressure_MFC;

    int32_t pressure_in;
    int32_t pressure_out;
    int32_t pressure_patient;

    // outputs
    int32_t p_MFC_pa;
    int32_t p_patient_pa;


    int32_t flow_MFC_air;
    int32_t flow_MFC_O2;

    int32_t battery_level;

    int32_t flow_out; //SCCPM

    int32_t inspiratory_hold_result;

    int32_t expiratory_hold_result;
} Sensors;

static int32_t g_offset_pressure_in = 0;
static int32_t g_offset_pressure_out = 0;

// See schematics
#define ADC_FACTOR_PRESSURE             (168.0/100.0)
#define ADC_FACTOR_FLOW_MFC             (168.0/100.0)
#define ADC_FACTOR_BATTERY              (11.5/1.5)

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
static const GPIO *g_btn;

void sensors_init(void) {

    UPS_status_init();
    calculated_init();

    g_btn = NULL;
    if(board_has_GPIO(GPIO_ID_USER_SWITCH)) {
        g_btn = board_get_GPIO(GPIO_ID_USER_SWITCH);
    }

    mprls_init(&mprls1, LPC_SSP0,
        board_get_GPIO(GPIO_ID_PSENSE_1_CS),
        board_get_GPIO(GPIO_ID_PSENSE_1_DRDY),
        board_get_GPIO(GPIO_ID_PSENSE_RESET));

    mprls_init(&mprls2, LPC_SSP0,
        board_get_GPIO(GPIO_ID_PSENSE_2_CS),
        board_get_GPIO(GPIO_ID_PSENSE_2_DRDY),
        board_get_GPIO(GPIO_ID_PSENSE_RESET));

    // Only trigger reset for mprls1: both sensors trigger on same reset
    mprls_enable(&mprls1, true);
    mprls_enable(&mprls2, false);

    ADC_init();

    if (I2C_PULL_UP_AVAILABLE) {
        if(!flowsensor_enable()) {
            system_status_set(SYSTEM_STATUS_ERROR_SENSOR_FLOW);
        }
    } else {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS
                | SYSTEM_STATUS_ERROR_SENSOR_FLOW);
    }

    delay_us(100*1000);
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

    return true;
}

void sensors_reset(void)
{
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
        if(mprls_read_and_clear_error(&mprls1)) {
            system_status_set(SYSTEM_STATUS_ERROR_SENSOR_P_INSP);
        }
        mprls_trigger_read(&mprls1);

    } else if(mprls_is_timeout(&mprls1)) {

        // Timeout! try to trigger next sample, but something is wrong here!

        // Set error flag 
        system_status_set(SYSTEM_STATUS_ERROR_SENSOR_P_INSP);

        mprls_trigger_read(&mprls1);
    }
}

static void _update_sensor_out(void)
{
    // sample sensor2
    if(mprls_is_ready(&mprls2)) {
        // read value and trigger next sample
        Sensors.pressure_out = mprls_read_data(&mprls2);
        if(mprls_read_and_clear_error(&mprls2)) {
            system_status_set(SYSTEM_STATUS_ERROR_SENSOR_P_EXP);
        }
        mprls_trigger_read(&mprls2);

    } else if(mprls_is_timeout(&mprls2)) {

        // Timeout! try to trigger next sample, but something is wrong here!

        // Set error flag 
        system_status_set(SYSTEM_STATUS_ERROR_SENSOR_P_EXP);

        mprls_trigger_read(&mprls2);
    }
}


static uint32_t count = 0;
void sensors_update(unsigned int dt)
{
    filter_adc(&Sensors.pressure_MFC, ADC_ID_PRESSURE_MFC,
            ADC_RANGE/SLEW_LIMIT_PRESSURE_MFC);

    const int p_mv = ADC_scale(Sensors.pressure_MFC, ADC_FACTOR_PRESSURE_MFC);

    // calibrated 10-4-2020 expirementally
//    Sensors.p_MFC_pa = (0.9 * Sensors.p_MFC_pa) + (0.1 * (16.56 * p_mv + 21523));

    // calibrated 6-5-2020 expirementally
    Sensors.p_MFC_pa = (0.9 * Sensors.p_MFC_pa) + (0.1 * (10.701107 * p_mv - 12355.72));

    if (I2C_PULL_UP_AVAILABLE) {
        if (count++ % 5 == 0) {
            // calculate flow in SLPM

            float flow_SLPM = flowsensor_read();

            // Flowsensor OK
            if(flow_SLPM >= 0) {

                flow_SLPM = flow_SLPM*3.14f*(0.015f/2)*(0.015f/2)*1000*60;
//                flow_SLPM = flow_SLPM*12.0f;

                // SLPM to SCCPM
                Sensors.flow_out = 1000*flow_SLPM;

            // Flowsensor ERROR
            } else {
                Sensors.flow_out = -1;
                system_status_set(SYSTEM_STATUS_ERROR_SENSOR_FLOW);
            }
        }
    } else {
        system_status_set(SYSTEM_STATUS_ERROR_I2C_BUS
                | SYSTEM_STATUS_ERROR_SENSOR_FLOW);
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

        const int v_pressure = ADC_scale(Sensors.pressure_patient, ADC_FACTOR_PRESSURE);

        // NOTE: this is calibrated experimentally, instead of datasheet-based (MPVZ5010)
        const int offset_mv = 167;
        const int scale_factor = 2157;
        Sensors.p_patient_pa = ((v_pressure-offset_mv)*scale_factor)/1000;



    }

    Sensors.inspiratory_hold_result = (int32_t)breathing_get_inspiratory_hold_result();
    Sensors.expiratory_hold_result = (int32_t)breathing_get_expiratory_hold_result();
}

int32_t sensors_read_pressure_MFC_pa(void)
{
    return Sensors.p_MFC_pa;
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
    return Sensors.p_patient_pa;
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

int32_t sensors_get_inspiratory_hold_result(void)
{
    return Sensors.inspiratory_hold_result;
}

int32_t sensors_get_expiratory_hold_result(void)
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

bool sensors_read_button_pressed(void)
{
    if(g_btn == NULL) {
        return false;
    }

    // Signal is high by default, pulled low on press
    return !GPIO_HAL_get(g_btn);
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

    data->system_status = system_status_get();
}

