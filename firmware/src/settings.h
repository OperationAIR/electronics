#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    uint16_t start;                 // nonzero: breathing is started
    uint16_t peep;                  // exhale pressure in Pa
    uint16_t frequency;             // breathing cycles per minute
    uint16_t ratio;                 // ratio between inhale exhale (exhale is N/10 times longer)
    uint16_t pressure;              // inhale pressure in Pa
    uint16_t oxygen;                // oxygen percentage for mixer (0-100)

    // These may be checked in firmware later(?)
    // For now they are done on the RPI
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
