#ifndef STATS_H
#define STATS_H

#include <stdint.h>
#include <stdbool.h>

int32_t stats_get_use_count(void);
int32_t stats_get_all_time_use_count(void);

void stats_clear_use_count(void);
void stats_increment_use_count(void);

bool stats_get_maintenance_mode(void);
void stats_set_maintenance_mode(bool onoff);

bool stats_get_overheated_mode(void);
void stats_set_overheated_mode(bool onoff);

bool stats_get_battery_critical_mode(void);
void stats_set_battery_critical_mode(bool onoff);
#endif
