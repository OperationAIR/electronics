#include "settings.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "app.h"

typedef struct {
    int min;
    int max;
    const char *desc;
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

char g_description[60];

static struct ValidSettings g_bounds = {

    // TODO what are good values for the bounds?
    .peep               = {.min = 450,  .max = 2500,    .desc = "peep"},
    .frequency          = {.min = 10,   .max = 35,      .desc = "frequency"},
    .pressure           = {.min = 900,  .max = 8500,    .desc = "pressure"},
    .ratio              = {.min = 10,   .max = 100,     .desc = "ratio"},
    .oxygen             = {.min = 20,   .max = 100,     .desc = "oxygen"},
};

static inline bool check_bounds(uint16_t value, AllowedRange *bounds)
{
    const bool ok = (value >= bounds->min) && (value <= bounds->max);
    
    if(!ok) {
        snprintf(g_description, sizeof(g_description),
                "%s %d is not within (%d, %d)!\n",
                bounds->desc,
                (int)value,
                bounds->min,
                bounds->max);
    }

    return ok;
}

static bool verify_settings(OperationSettings *settings)
{
    bool ok = true;
    g_description[0] = 0;


    ok &= check_bounds(settings->peep, &g_bounds.peep);
    ok &= check_bounds(settings->frequency, &g_bounds.frequency);
    ok &= check_bounds(settings->pressure, &g_bounds.pressure);
    ok &= check_bounds(settings->ratio, &g_bounds.ratio);
    ok &= check_bounds(settings->oxygen, &g_bounds.oxygen);

    // Note: these are not used by FW!
    /*
    ok &= check_bounds(settings->max_pressure_alarm, &g_bounds.max_pressure_alarm);
    ok &= check_bounds(settings->min_pressure_alarm, &g_bounds.min_pressure_alarm);
    ok &= check_bounds(settings->max_TV_alarm, &g_bounds.max_TV_alarm);
    ok &= check_bounds(settings->min_TV_alarm, &g_bounds.min_TV_alarm);
    ok &= check_bounds(settings->max_fiO2_alarm, &g_bounds.max_fiO2_alarm);
    ok &= check_bounds(settings->min_fiO2_alarm, &g_bounds.min_fiO2_alarm);
    */
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

const char *settings_get_last_description(void)
{
    return g_description;
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
