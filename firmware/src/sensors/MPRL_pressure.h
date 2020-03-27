#ifndef MPRL_PRESSURE_H
#define MPRL_PRESSURE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <chip.h>
#include <lpc_tools/GPIO_HAL.h>

typedef struct {
    LPC_SSP_T *SSP;
    const GPIO *cs_pin;

} MPRL;

void mprl_init(MPRL *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin);
void mprl_enable(MPRL *ctx);


#endif