#ifndef DPR_H
#define DPR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <chip.h>
#include <lpc_tools/GPIO_HAL.h>


typedef struct {
    LPC_SSP_T *SSP;
    const GPIO *cs_pin;

} DPR;


/**
 * Initialize Digital Pressure Regulator
 *
 */
bool DPR_init(DPR *ctx,
        LPC_SSP_T *LPC_SSP, const GPIO *cs_pin);


/**
 * Check that the DPR DAC works and set it to lowest value
 *
 * If false is returned, you should check the hardware connections.
 */
bool DPR_enable(DPR *ctx);
bool DPR_disable(DPR *ctx);


/**
 * Write a value to the DAC: range between 0-4096
 */
bool DPR_write(DPR *ctx, unsigned int value);


/**
 *  Get DPR status int
 */
int DPR_status(DPR *ctx);


#endif

