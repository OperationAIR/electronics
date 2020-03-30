#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    uint16_t start; // breathing is started
    uint16_t peep; // exhale pressure
    uint16_t frequency; // breathing cycles per minute
    uint16_t ratio; // ratio between inhale exhale
    uint16_t pressure; // inhale pressure
    uint16_t oxygen; // oxygen percentage for mixer
    uint16_t max_pressure_alarm;
    uint16_t min_pressure_alarm;
    uint16_t max_TV_alarm;
    uint16_t min_TV_alarm;
    uint16_t max_fiO2_alarm;
    uint16_t min_fiO2_alarm;
    uint16_t crc;
} OperationSettings;


bool settings_update(OperationSettings *new_settings);

void settings_copy(OperationSettings *dst, OperationSettings *src);

#endif