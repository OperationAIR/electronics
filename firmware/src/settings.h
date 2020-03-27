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
    uint16_t max_TV_alarm;
    uint16_t min_TV_alarm;
    uint16_t max_fiO2_alarm;
    uint16_t min_fiO2_alarm;
    uint16_t crc;
} OperationSettings;


bool settings_update(OperationSettings *new_settings);


#endif