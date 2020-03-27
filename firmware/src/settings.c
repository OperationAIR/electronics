#include "settings.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
    uint16_t min;
    uint16_t max;
} AllowedRange;

struct ValidSettings {
    AllowedRange frequency;
    AllowedRange tidal_volume;
    AllowedRange pressure;
    AllowedRange max_pressure_alarm;
    AllowedRange min_pressure_alarm;
    AllowedRange max_TV_alarm;
    AllowedRange min_TV_alarm;
    AllowedRange max_fiO2_alarm;
    AllowedRange min_fiO2_alarm;
};

static struct ValidSettings g_bounds = {
    .frequency = {.min = 10, .max = 35},
    .tidal_volume = {.min = 100, .max = 800},
    .pressure = {.min = 10, .max = 35},
    .max_pressure_alarm = {.min = 10, .max = 50},
    .min_pressure_alarm = {.min = 5, .max = 30},
    .max_TV_alarm = {.min = 100, .max = 800},
    .min_TV_alarm = {.min = 100, .max = 300},
    .max_fiO2_alarm = {.min = 40, .max = 80},
    .min_fiO2_alarm = {.min = 20, .max = 45},
};

OperationSettings g_settings;
static inline bool check_bounds(uint16_t value, AllowedRange *bounds)
{
    return (value >= bounds->min) && (value <= bounds->max);
}

static bool verify_settings(OperationSettings *settings)
{
    bool ok = true;
    ok &= check_bounds(settings->frequency, &g_bounds.frequency);
    ok &= check_bounds(settings->tidal_volume, &g_bounds.tidal_volume);
    ok &= check_bounds(settings->pressure, &g_bounds.pressure);
    ok &= check_bounds(settings->max_pressure_alarm, &g_bounds.max_pressure_alarm);
    ok &= check_bounds(settings->min_pressure_alarm, &g_bounds.min_pressure_alarm);
    ok &= check_bounds(settings->max_TV_alarm, &g_bounds.max_TV_alarm);
    ok &= check_bounds(settings->min_TV_alarm, &g_bounds.min_TV_alarm);
    ok &= check_bounds(settings->max_fiO2_alarm, &g_bounds.max_fiO2_alarm);
    ok &= check_bounds(settings->min_fiO2_alarm, &g_bounds.min_fiO2_alarm);

    return ok;
}

bool settings_update(OperationSettings *new_settings)
{

    if (verify_settings(new_settings)) {
        memcpy(&g_settings, new_settings, sizeof(OperationSettings));
        return true;
    }

    return false;

}