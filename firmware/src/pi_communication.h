#ifndef PI_COMMUNICATION_H
#define PI_COMMUNICATION_H

enum VentilatorError {
    VentilatorErrorInvalidSettings = 0xE4404001
};

void pi_comm_tasks(Ringbuffer *rb_Rx);

#endif