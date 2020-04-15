#ifndef WATCHDOG_H
#define WATCHDOG_H

// after this amount of time, the system reboots
#define WATCHDOG_TIMEOUT_MS 2000

void watchdog_init(void);
void watchdog_feed(void);


#endif