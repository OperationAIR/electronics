#ifndef MPRLS_PRESSURE_H
#define MPRLS_PRESSURE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <chip.h>
#include <lpc_tools/GPIO_HAL.h>

#define MPRLS_STATUS_POWERED (0x40) ///< Status SPI powered bit
#define MPRLS_STATUS_BUSY (0x20)    ///< Status busy bit
#define MPRLS_STATUS_FAILED (0x04)  ///< Status bit for integrity fail
#define MPRLS_STATUS_MATHSAT (0x01) ///< Status bit for math saturation

// enum MPRLS_STATUS {
//     MPRLS_STATUS_POWERED = 0x40,
//     MPRLS_STATUS_BUSY= 0x40,
// }

typedef struct {
    LPC_SSP_T *SSP;
    const GPIO *cs_pin;
    const GPIO *drdry_pin;
    const GPIO *reset_pin;
} MPRLS;

void mprls_init(MPRLS *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin, const GPIO *drdy_pin, const GPIO *reset_pin);
bool mprls_enable(MPRLS *ctx);

uint32_t mprls_read_blocking(MPRLS *ctx);

#endif