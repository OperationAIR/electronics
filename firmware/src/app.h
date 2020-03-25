#ifndef APP_H
#define APP_H
#include "global_settings.h"

void app_init(int hw_version);

void app_resume(void);
void app_halt(void);
bool app_is_running(void);

char* app_get_state(void);

bool app_can_sleep(void);
bool app_is_idle(void);

/**
 * Notify the app that the CPU has woken up after deep sleep
 */
void app_wakeup(void);

void app_self_test(void);

void app_program_start(void);
void app_program_stop(void);


void app_clear_maintenance_mode(void);
bool app_is_maintenance_mode(void);

void app_clear_overheated_mode(void);
bool app_is_overheated_mode(void);

void app_clear_battery_critical_mode(void);
bool app_is_battery_critical_mode(void);

void app_reset_use_count(void);

uint32_t get_last_pressure(void);

#endif
