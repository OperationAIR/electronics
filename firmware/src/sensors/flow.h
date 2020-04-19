#ifndef FLOW_H
#define FLOW_H


#include <stdbool.h>

bool flowsensor_enable(void);
float flowsensor_test(void);
float flowsensor_read(void);

#endif

