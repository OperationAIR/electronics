#ifndef FLOW_H
#define FLOW_H


#include <stdbool.h>

bool flowsensor_enable(void);
float flowsensor_test(void);
float flowsensor_read(void);
bool flowsensor_read_and_clear_error(void);

#endif

