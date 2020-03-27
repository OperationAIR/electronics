#include <c_utils/ringbuffer.h>
#include <c_utils/max.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <mcu_timing/delay.h>
#include <chip.h>

#include "log.h"
#include "cdc_vcom.h"
#include "clock.h"

uint8_t g_log_buffer[1024];
uint32_t g_serialnumber[5];
Ringbuffer g_log_queue;

// length of the time string
#define TIME_STR_LEN    (17)
// required buffer size to store time string: strlen + NULL byte
#define TIME_STR_SIZE   (TIME_STR_LEN+1)

#define TSECONDS (1e6)
#define TMINUTES (60*TSECONDS)
#define THOURS (60*TMINUTES)
#define TDAYS (24*THOURS)



#define LOG_DST_BIT (0x80)

// destinations: may be combined with OR
typedef enum {

    LOG_DST_NONE    = 0,

    LOG_DST_USB     = (1 << 0),

    LOG_DST_ALL     = 0x7F,     // all possible options combined

} LogDst;
LogDst g_last_dst;

bool debug_enabled = true;

bool cli_enabled = true;

bool wtime_enabled = true;


void log_get_time_as_str(char *str)
{
    uint64_t t_us = clock_get_time();
    uint32_t days = t_us / TDAYS;
    t_us -= days * TDAYS;
    uint32_t hours = t_us / THOURS;
    t_us -= hours * THOURS;
    uint32_t minutes = t_us / TMINUTES;
    t_us -= minutes * TMINUTES;
    uint32_t seconds = t_us / TSECONDS;
    t_us -= seconds * TSECONDS;
    uint32_t mili_seconds = t_us / 1e3;

    snprintf(str, TIME_STR_SIZE, "%03lu:%02lu:%02lu:%02lu.%03lu ",
           days+1, hours, minutes, seconds, mili_seconds);
}

void log_debug_disable()
{
    debug_enabled = false;
}

void log_debug_enable()
{
    debug_enabled = true;
}

void logging_init(void)
{
    g_last_dst = LOG_DST_NONE;
    ringbuffer_init(&g_log_queue, g_log_buffer, 1, sizeof(g_log_buffer));
}

bool log_would_succeed(size_t msg_len)
{
    const size_t overhead = 1 + 2; // take into account dst + \r\n, excl prefix
    size_t free = ringbuffer_free_count(&g_log_queue);
    if (free < overhead || ((free-overhead) < msg_len)) {
        return false;
    }
    return true;
}


// note: msg_len is including all overhead..
static bool log_wait_untill_available(size_t msg_len)
{
    int t;
    const int timeout = 100;
    for (t = 0; t < timeout; t++)
    {

        delay_us(1 * 1000);
        if (log_would_succeed(msg_len))
        {
            break;
        }
        log_tasks();
    }
    if (t >= timeout)
    {
        return false;
    }
    return true;
}

static void log_write_to_queue(LogDst destination,
        const char *prefix, const char *format, va_list va)
{
    Ringbuffer *queue = &g_log_queue;
    uint32_t freecount = ringbuffer_free_count(queue);
    size_t max_size = min(freecount, LOG_MAX_LENGTH);

    char log_str[max_size];

    int prefix_len = strlen(prefix);
    size_t overhead = prefix_len + 2; // take into account prefix + \r\n
    if ((size_t )overhead >= max_size) {
        // Log Failed, no memory... sorry
        return;
    }

    strlcpy(log_str, prefix, sizeof(log_str));
    max_size -= overhead;

    int n = vsnprintf(log_str+prefix_len, max_size, format, va);
    if (n > 0) {
        // If the buffer is not long enough,
        // vsnprintf truncates the line and ends with '\0'.
        if ((size_t)n >= max_size) {
            n = max_size - 1;
        }

        // append newline
        log_str[prefix_len+n] = '\r';
        log_str[prefix_len+n+1] = '\n';
    } else {
        strlcpy(log_str+prefix_len, "Encoding error\n", max_size);
    }

    const uint8_t dst = (LOG_DST_BIT | destination);
    ringbuffer_write(queue, &dst, sizeof(dst));
    ringbuffer_write(queue, log_str, n+overhead);
}

// log something to the queue (if it fits in the queue...)
void log_wtime(const char format[], ...)
{
    if (!wtime_enabled) {
        return;
    }


    va_list va;
    va_start(va, format);

    char prefix[TIME_STR_SIZE];
    log_get_time_as_str(prefix);
    log_write_to_queue(LOG_DST_ALL, prefix, format, va);
    va_end(va);
}

// log something to the queue (if it fits in the queue...)
bool log_cli(const char format[], ...)
{
   if (!cli_enabled) {
        return true;
    }

    va_list va;
    va_start(va, format);

    const bool ok = log_wait_untill_available(LOG_MAX_LENGTH);
    if(ok) {
        log_write_to_queue(LOG_DST_USB, "", format, va);
    }
    va_end(va);

    return ok;
}

void log_debug(const char format[], ...)
{
    if (!debug_enabled) {
        return;
    }

    va_list va;
    va_start(va, format);

    // debug without time prefix
    const char *prefix = "";//[TIME_STR_SIZE];
    //log_get_time_as_str(prefix);
    log_write_to_queue(LOG_DST_ALL, prefix, format, va);
    va_end(va);
}


/**
 * Process the log queue: try to make progress
 *
 * @return      the amount of bytes written to destination(s)
 *              (the data read from queue excluding the LOG_DST_XX bytes)
 */
static size_t log_task_process_queue(void)
{
    // NOTE: this buffer size should be <= EP size (?)
    // Tested working with size 32..
    char data[64];

    // NOTE: bytes_read will be >= data_len, because the data on queue contains
    // metadata about the destination (bytes with LOG_DST_BIT set)
    size_t bytes_read = 0;
    size_t data_len = 0;
    uint8_t current_dst = g_last_dst;

    // peek up to sizeof(data) bytes from queue
    for(bytes_read=0;bytes_read<sizeof(data);bytes_read++) {
        uint8_t *ptr = ringbuffer_get_readable_offset(&g_log_queue, bytes_read);
        if(!ptr) {
            break;
        }
        uint8_t byte = *ptr;

        if(byte & LOG_DST_BIT) {

            current_dst = byte & (~LOG_DST_BIT);

            // dst change: stop reading and process all data up to this point
            if(bytes_read && (current_dst != g_last_dst)) {
                break;
            }

            continue;
        }
        if(current_dst == LOG_DST_NONE) {
            continue;
        }
        data[data_len++] = byte;
    }
    g_last_dst = current_dst;
    if(!data_len) {
        return 0;
    }

    // try to send data to vcom if connected
    if((current_dst & LOG_DST_USB) && vcom_connected()) {
        data_len = vcom_write((uint8_t*)data, data_len);
    }

    // free up some space in the ringbuffer
    for(size_t n=0;n<bytes_read;n++) {
        ringbuffer_advance(&g_log_queue);
    }

    return data_len;
}

void log_tasks(void)
{
    while(log_task_process_queue());
}

bool log_is_idle(void)
{
    return ringbuffer_is_empty(&g_log_queue);
}

uint32_t* log_get_serialnumber(void)
{
    if (!g_serialnumber[1]) {
        Chip_IAP_ReadUID(g_serialnumber);
    }
    return g_serialnumber;
}

char* log_get_serialnumber_str(char *buf, size_t l)
{
    uint32_t *sn = log_get_serialnumber();
	uint32_t u0 = *sn++;
	uint32_t u1 = *sn++;
	uint32_t u2 = *sn++;
	uint32_t u3 = *sn;
    snprintf(buf, l, "%010lu-%010lu-%010lu-%010lu", u0, u1, u2, u3);
    return buf;
}
