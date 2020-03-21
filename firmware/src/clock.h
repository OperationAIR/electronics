#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

/**
 * Return 64-bit time since boot in microseconds
 */
uint64_t clock_get_time(void);

/**
 * Return time since boot in seconds
 */
uint32_t clock_get_time_s(void);

void clock_add_watchdog_count(void);


void clock_add_seconds(int32_t inc_s);
#endif