#include "settings.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "app.h"
#include "crc/crc.h"

typedef struct {
    int min;
    int max;
    const char *desc;
} AllowedRange;

struct ValidSettings {
    AllowedRange peep;
    AllowedRange pressure;
    AllowedRange pc_above_peep;
    AllowedRange frequency;
    AllowedRange oxygen;
    AllowedRange ratio;
};

char g_description[60];

static struct ValidSettings g_bounds = {

    // NOTE: bounds based on feedback from pre-clinical trials at Erasmus MC,
    // (see github issue #15)
    .peep               = {.min = 450,  .max = 3000,    .desc = "peep"},
    .pressure           = {.min = 900,  .max = 7000,    .desc = "pressure"},
    .pc_above_peep      = {.min = 450,  .max = 4000,    .desc = "PC above peep"},
    .frequency          = {.min = 5,    .max = 40,      .desc = "frequency"},
    .ratio              = {.min = 5,    .max = 30,      .desc = "ratio"},
    .oxygen             = {.min = 21,   .max = 100,     .desc = "oxygen"},
};

static inline bool check_bounds(uint16_t value, AllowedRange *bounds)
{
    const bool ok = (value >= bounds->min) && (value <= bounds->max);

    if(!ok) {
        snprintf(g_description, sizeof(g_description),
                "%s: %d is not within [%d, %d]!\n",
                bounds->desc,
                (int)value,
                bounds->min,
                bounds->max);
    }

    return ok;
}

static bool verify_settings(const OperationSettings *settings)
{
    bool ok = true;
    g_description[0] = 0;


    ok &= check_bounds(settings->peep, &g_bounds.peep);
    ok &= check_bounds(settings->pressure, &g_bounds.pressure);
    ok &= check_bounds((settings->pressure - settings->peep), &g_bounds.pc_above_peep);

    ok &= check_bounds(settings->frequency, &g_bounds.frequency);
    ok &= check_bounds(settings->oxygen, &g_bounds.oxygen);
    ok &= check_bounds(settings->ratio, &g_bounds.ratio);

    return ok;
}

void settings_default(void)
{
    OperationSettings defaults = {
        .start      = 0,
        .peep       = (10 * 98.0665),
        .frequency  = 15,
        .ratio      = (2 * 10),
        .pressure   = (25 * 98.0665),
        .oxygen     = 40

    };

    uint16_t crc_state = 0xFFFF;
    const uint16_t crc = crc16_usb_stream_check(&crc_state, (uint8_t*)&defaults, sizeof(OperationSettings)-2);
    defaults.crc = crc;

    settings_update(&defaults);

}

bool settings_update(const OperationSettings *new_settings)
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


void settings_copy(OperationSettings *dst, const OperationSettings *src)
{
    // NOTE: why is this not just a memcpy??
    dst->start = src->start;
    dst->frequency = src->frequency;
    dst->peep = src->peep;
    dst->ratio = src->ratio;
    dst->pressure = src->pressure;
    dst->oxygen = src->oxygen;

    dst->crc = src->crc;
}
