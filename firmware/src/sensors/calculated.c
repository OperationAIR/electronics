#include "calculated.h"
#include "sensors.h"
#include "global_settings.h"

#include <memory.h>

static struct {
    enum BreathCycleState cycle_state;

    int32_t volume_in_CC;
    int32_t volume_out_CC;
    int32_t flow_out_avg_CCPM;

    int32_t oxygen_promille;

    // internal calculation state during a breathing cycle
    struct {
        // volume is in CC * 60000
        int32_t volume_O2;
        int32_t volume_air;

        // volume is in L * 60000
        int32_t volume_out;
    } cycle_calc;

    struct {
        unsigned int time_ms;

        int32_t volume_out;

    } avg_calc;
} g_ctx;


void calculated_init(void)
{
   memset(&g_ctx, 0, sizeof(g_ctx)); 
}

int32_t calculated_oxygen_percent(void)
{
    return g_ctx.oxygen_promille / 10;
}
int32_t calculated_volume_in_CC(void)
{
    return g_ctx.volume_in_CC;
}
int32_t calculated_volume_out_CC(void)
{
    return g_ctx.volume_out_CC;
}
int32_t calculated_flow_out_avg_SCCPM(void)
{
    return g_ctx.flow_out_avg_CCPM;
}

int32_t calculated_volume_realtime_MFC_O2_CC(void)
{
    return g_ctx.cycle_calc.volume_O2 / 60000;
}

int32_t calculated_volume_realtime_MFC_air_CC(void)
{
    return g_ctx.cycle_calc.volume_air / 60000;
}

int32_t calculated_volume_realtime_in_CC(void)
{
    return ((g_ctx.cycle_calc.volume_O2 + g_ctx.cycle_calc.volume_air) / 60000);
}

int32_t calculated_volume_realtime_out_CC(void)
{
    return (g_ctx.cycle_calc.volume_out / 60000);
}

void calculated_update(enum BreathCycleState cycle_state, int dt)
{
    // Start of new breathing cycle
    if((g_ctx.cycle_state != cycle_state) && (cycle_state == BreathCycleStatePeakPressure)) {

        const int32_t volume_O2_CC = calculated_volume_realtime_MFC_O2_CC();
        const int32_t volume_air_CC = calculated_volume_realtime_MFC_air_CC();
        const int32_t volume_total_in_CC = volume_O2_CC + volume_air_CC;

        const int32_t oxygen_promille = (210*volume_air_CC + 1000*volume_O2_CC)/volume_total_in_CC;


        // lowpass filter with new = 0.7*prev + 0.3*measured:
        // should fully settle within 10 cycles.
        // This approximates what happens in the mixing chamber
        g_ctx.oxygen_promille = (7*g_ctx.oxygen_promille + 3*oxygen_promille)/10;

        // Total inspiratory flow over one cycle
        // (from MFC, assuming no leaks or overpressure events)
        g_ctx.volume_in_CC = calculated_volume_realtime_in_CC();

        // Total expiratory flow over one cycle
        // (integrated flow sensor values)
        g_ctx.volume_out_CC = calculated_volume_realtime_out_CC();

        // Reset sensor state for next breathing cycle
        memset(&g_ctx.cycle_calc, 0, sizeof(g_ctx.cycle_calc));

    }

    g_ctx.avg_calc.time_ms+=dt;
    if(g_ctx.avg_calc.time_ms >= CALCULATED_AVERAGING_TIME_MS) {

        // NOte: avg_calc volumes are in (CC * 60000). To calculate avg CCPM,
        // we need the volume in CC * (60000/AVERAGING_TIME_MS).
        g_ctx.flow_out_avg_CCPM = (g_ctx.avg_calc.volume_out / g_ctx.avg_calc.time_ms);

        // Reset averaging state for next time period
        memset(&g_ctx.avg_calc, 0, sizeof(g_ctx.avg_calc));
    }
    // integrate volume during CALCULATED_AVERAGING_TIME_MS
    g_ctx.avg_calc.volume_out+= (dt*sensors_read_flow_out_SCCPM());

    //avg_calc
    //g_ctx.volume_out_avg

    g_ctx.cycle_state = cycle_state;


    // Integrate MFC output flow over one cycle
    // volume is in CC * 60000
    g_ctx.cycle_calc.volume_O2+=  (dt*sensors_read_flow_MFC_O2_SCCPM());
    g_ctx.cycle_calc.volume_air+= (dt*sensors_read_flow_MFC_air_SCCPM());

    // Integrate exhale flow over one cycle
    // volume is in CC * 60000
    g_ctx.cycle_calc.volume_out+= (dt*sensors_read_flow_out_SCCPM());

}


