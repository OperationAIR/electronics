#ifndef PI_COMMUNICATION_H
#define PI_COMMUNICATION_H

#include <stdint.h>
#include <stdlib.h>

enum VentilatorError {
    VentilatorErrorInvalidSettings = 0xE4404001
};

void pi_comm_init(void);
void pi_comm_tasks(void);
void pi_comm_send(uint8_t *buffer, size_t len);

#endif