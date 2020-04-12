#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stdbool.h>



int32_t storage_read_app_use_count(void);
void storage_increment_app_use_count(void);

#endif
