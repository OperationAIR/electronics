#include "settings.h"
#include <stdbool.h>
#include <string.h>

#include "app.h"

typedef struct {
    uint16_t min;
    uint16_t max;
} AllowedRange;

struct ValidSettings {
    AllowedRange peep;
    AllowedRange frequency;
    AllowedRange pressure;
    AllowedRange ratio;
    AllowedRange oxygen;
    AllowedRange max_pressure_alarm;
    AllowedRange min_pressure_alarm;
    AllowedRange max_TV_alarm;
    AllowedRange min_TV_alarm;
    AllowedRange max_fiO2_alarm;
    AllowedRange min_fiO2_alarm;
};

static struct ValidSettings g_bounds = {
    .peep = {.min = 5, .max = 25},
    .frequency = {.min = 10, .max = 35},
    .pressure = {.min = 10, .max = 35},
    .max_pressure_alarm = {.min = 10, .max = 50},
    .min_pressure_alarm = {.min = 5, .max = 30},
    .max_TV_alarm = {.min = 100, .max = 800},
    .min_TV_alarm = {.min = 100, .max = 300},
    .max_fiO2_alarm = {.min = 40, .max = 80},
    .min_fiO2_alarm = {.min = 20, .max = 45},
};

static inline bool check_bounds(uint16_t value, AllowedRange *bounds)
{
    return (value >= bounds->min) && (value <= bounds->max);
}

static bool verify_settings(OperationSettings *settings)
{
    bool ok = true;
        ok &= check_bounds(settings->peep, &g_bounds.peep);

    ok &= check_bounds(settings->frequency, &g_bounds.frequency);
    ok &= check_bounds(settings->pressure, &g_bounds.pressure);
    ok &= check_bounds(settings->max_pressure_alarm, &g_bounds.max_pressure_alarm);
    ok &= check_bounds(settings->min_pressure_alarm, &g_bounds.min_pressure_alarm);
    ok &= check_bounds(settings->max_TV_alarm, &g_bounds.max_TV_alarm);
    ok &= check_bounds(settings->min_TV_alarm, &g_bounds.min_TV_alarm);
    ok &= check_bounds(settings->max_fiO2_alarm, &g_bounds.max_fiO2_alarm);
    ok &= check_bounds(settings->min_fiO2_alarm, &g_bounds.min_fiO2_alarm);
    //TODO check new settings fields
    return ok;
}

bool settings_update(OperationSettings *new_settings)
{

    if (verify_settings(new_settings)) {
        app_apply_settings(new_settings);
        return true;
    }

    return false;

}

void settings_copy(OperationSettings *dst, OperationSettings *src)
{
    dst->start = src->start;
    dst->frequency = src->frequency;
    dst->peep = src->peep;
    dst->ratio = src->ratio;
    dst->pressure = src->pressure;
    dst->oxygen = src->oxygen;

    dst->max_pressure_alarm = src->max_pressure_alarm;
    dst->min_pressure_alarm = src->min_pressure_alarm;
    dst->max_TV_alarm = src->max_TV_alarm;
    dst->min_TV_alarm = src->min_TV_alarm;
    dst->max_fiO2_alarm = src->max_fiO2_alarm;
    dst->max_fiO2_alarm = src->max_fiO2_alarm;
    dst->min_fiO2_alarm = src->min_fiO2_alarm;
    dst->crc = src->crc;
}