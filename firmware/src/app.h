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

// Force start/stop (e.g. from debug CLI)
void app_program_force_start(void);
void app_program_force_stop(void);

void app_start_inspiratory_hold(void);
void app_stop_inspiratory_hold(void);

void app_start_expiratory_hold(void);
void app_stop_expiratory_hold(void);


void app_start_self_test(void);


/**
 * Apply new operation settigns in a safe way
 * This function uses a critical section to update all settings in
 * a atomic way.
 */
void app_apply_settings(const OperationSettings *new_settings);

/**
 * Get current Operation Settings in use by app
 */
OperationSettings* app_get_settings(void);

/**
 * Check if app has new settings that should be saved to NV storage.
 *
 * Storing settings to Non-Volatile storage may take some time, so it
 * is recommended to do that from a low-priority context
 */
bool app_check_and_clear_settings_should_be_saved(void);

#endif
