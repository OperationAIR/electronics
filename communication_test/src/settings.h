#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    uint16_t peep;
    uint16_t frequency;
    uint16_t tidal_volume;
    uint16_t pressure;
    uint16_t max_pressure_alarm;
    uint16_t min_pressure_alarm;
    uint16_t max_tv_alarm;
    uint16_t min_tv_alarm;
    uint16_t max_fi02_alarm;
    uint16_t min_fi02_alarm;
} OperationSettings;


bool settings_update(OperationSettings *new_settings);


#endif