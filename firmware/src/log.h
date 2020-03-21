#ifndef _LOG_H_
#define _LOG_H_

#include <stddef.h>
#include <stdbool.h>


#define LOG_MAX_LENGTH 120
#define LOG_SERIAL_NUMBER_SIZE 4
#define SERIAL_NUM_STR_SIZE (4*10+4+1)

void logging_init(void);
void log_tasks(void);
bool log_is_idle(void);
void log_wtime(const char format[], ...);

/**
 * Log data to cli.
 * Blocks up to 100ms if the queue is full.
 *
 * @return      True if succesfull
 */
bool log_cli(const char format[], ...);

bool log_would_succeed(size_t msg_len);
void log_get_time_as_str(char *str);

void log_debug(const char format[], ...);
void log_debug_disable(void);
void log_debug_enable(void);

/**
 * Returns the chip partID
 */
uint32_t* log_get_serialnumber(void);

/**
 * Prints serial number in buffer
 *
 * make sure that l is at least `SERIAL_NUM_STR_SIZE` long.
 *
 * return buf
 */
char* log_get_serialnumber_str(char *buf, size_t l);
#endif
