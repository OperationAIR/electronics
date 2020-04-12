#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stdbool.h>

#include "settings.h"


void storage_init(void);

int32_t storage_read_app_use_count(void);
void storage_increment_app_use_count(void);

bool storage_read_settings(OperationSettings *result);
bool storage_write_settings(const OperationSettings *settings);

#endif
