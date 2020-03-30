#ifndef APP_H
#define APP_H
#include "global_settings.h"
#include "settings.h"

void app_init(int hw_version);

void app_resume(void);
void app_halt(void);
bool app_is_running(void);

char* app_get_state(void);

bool app_is_idle(void);

void app_self_test(void);

void app_program_start(void);
void app_program_stop(void);


void app_clear_maintenance_mode(void);
bool app_is_maintenance_mode(void);

void app_clear_overheated_mode(void);
bool app_is_overheated_mode(void);


void app_reset_use_count(void);

/**
 * Apply new operation settigns in a safe way
 * This function uses a critical section to update all settings in
 * a atomic way.
 */
void app_apply_settings(OperationSettings *new_settings);

/**
 * Get current Operation Settings in use by app
 */
OperationSettings* app_get_settings(void);


uint32_t get_last_pressure(void);

#endif
