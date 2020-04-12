#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdint.h>
#include <stdbool.h>

#include <c_utils/static_assert.h>



typedef struct __attribute__((packed)) {
    uint16_t start;                 // nonzero: breathing is started
    uint16_t peep;                  // exhale pressure in Pa
    uint16_t frequency;             // breathing cycles per minute
    uint16_t ratio;                 // ratio between inhale exhale (exhale is N/10 times longer)
    uint16_t pressure;              // inhale pressure in Pa
    uint16_t oxygen;                // oxygen percentage for mixer (0-100)

    // NOTE: when adding fields, make sure to update verify_settings
    // to verify their bounds.

    // NOTE: these are not used by firmware.
    // Alarms are determined by the RPI.
    uint16_t max_pressure_alarm;    
    uint16_t min_pressure_alarm;
    uint16_t max_TV_alarm;
    uint16_t min_TV_alarm;
    uint16_t max_fiO2_alarm;
    uint16_t min_fiO2_alarm;

    uint16_t crc;

} OperationSettings;

STATIC_ASSERT(sizeof(OperationSettings) == (13*2));


bool settings_update(const OperationSettings *new_settings);
void settings_default(void);
const char *settings_get_last_description(void);
void settings_copy(OperationSettings *dst, const OperationSettings *src);

#endif
