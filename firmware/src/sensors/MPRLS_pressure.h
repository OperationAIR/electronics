#ifndef MPRLS_PRESSURE_H
#define MPRLS_PRESSURE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <chip.h>
#include <lpc_tools/GPIO_HAL.h>

typedef struct {
    LPC_SSP_T *SSP;
    const GPIO *cs_pin;
    const GPIO *drdry_pin;
    const GPIO *reset_pin;
} MPRLS;

void mprls_init(MPRLS *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin, const GPIO *drdy_pin, const GPIO *reset_pin);
bool mprls_enable(MPRLS *ctx);

/**
 * Returns pressure measurement in [pa]
 */
uint32_t mprls_read_blocking(MPRLS *ctx);

#endif