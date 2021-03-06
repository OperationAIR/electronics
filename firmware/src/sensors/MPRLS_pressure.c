#include "MPRLS_pressure.h"
#include <lpc_tools/GPIO_HAL.h>
#include <mcu_timing/delay.h>
#include <string.h>



// SPI 0,0 mode: clock idles in low state
#define SPI_MODE      (SSP_CLOCK_MODE0)

// Frequency: MPRLS sensor is specified up to 800khz
// // TODO why 100khz??
#define MPRLS_SENSOR_BITRATE   (100000)

#define MPRLS_TIMEOUT_US        (7500)


#define MPRLS_NOP 0xF0
#define MPRLS_OUTPUT_MEASUREMENT_CMD 0xAA
#define MPRLS_OUTPUT_TRIGGER_DATA_LENGTH 3
#define MPRLS_OUTPUT_MEASUREMENT_DATA_LENGTH 4


#define MPRLS_STATUS_POWERED (0x40) ///< Status SPI powered bit
#define MPRLS_STATUS_BUSY (0x20)    ///< Status busy bit
#define MPRLS_STATUS_FAILED (0x04)  ///< Status bit for integrity fail
#define MPRLS_STATUS_MATHSAT (0x01) ///< Status bit for math saturation


void mprls_init(MPRLS *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin, const GPIO *drdy_pin, const GPIO *reset_pin)
{
    ctx->SSP = LPC_SSP;
    ctx->cs_pin = cs_pin;
    ctx->drdry_pin = drdy_pin;
    ctx->reset_pin = reset_pin;
    ctx->error = false;

    static SSP_ConfigFormat ssp_format;
    Chip_SSP_Init(LPC_SSP);
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_BITS_8;
	ssp_format.clockMode = SPI_MODE;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, true);
    Chip_SSP_SetBitRate(LPC_SSP, MPRLS_SENSOR_BITRATE);

	Chip_SSP_Enable(LPC_SSP);
}

bool mprls_read_and_clear_error(MPRLS *ctx)
{
    const bool error = ctx->error;
    ctx->error = false;
    return error;
}

uint8_t mprls_trigger_read(MPRLS *ctx)
{
    uint8_t buffer[MPRLS_OUTPUT_TRIGGER_DATA_LENGTH];
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = MPRLS_OUTPUT_MEASUREMENT_CMD;

    uint32_t status = 0;

    GPIO_HAL_set(ctx->cs_pin, LOW);
	Chip_SSP_Int_FlushData(ctx->SSP);
    Chip_SSP_DATA_SETUP_T xf_setup = {
        .tx_data = buffer,
        .tx_cnt = 0,
        .rx_data = &status,
        .rx_cnt = 0,
        .length = MPRLS_OUTPUT_TRIGGER_DATA_LENGTH,
    };

    Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup);

    GPIO_HAL_set(ctx->cs_pin, HIGH);

    delay_timeout_set(&ctx->timeout, MPRLS_TIMEOUT_US);

    return (status >> 24) & 0xFF;
}


// Outputmax. = 15099494 counts (90% of 224 counts or 0xE66666)
// Outputmin. = 1677722 counts (10% of 224 counts or 0x19999A)
#define OUTPUT_MIN 1677722
#define OUTPUT_MAX 15099494
#define P_MAX_psi 1
#define P_MIN_psi 0
#define PSI_TO_PA (6894.757)


/**
 * Scale raw measurement value to pa
 *
 *  Pressure = (Output - Output_min) * (Pmax - Pmin)
 *             ------------------------------------- + Pmin
 *                      Output_max - Output_min
 *
 *  return PSI_TO_PA(Pressure)
 */
static inline int32_t scale(uint32_t raw)
{
    int32_t A = ((raw - OUTPUT_MIN) * (P_MAX_psi - P_MIN_psi));
    int32_t B = (OUTPUT_MAX - OUTPUT_MIN);
    float res_psi = A/(float)B;

    return (int32_t)(res_psi * PSI_TO_PA);
}

int32_t mprls_read_data(MPRLS *ctx)
{
    // Step 3
    uint8_t buffer[MPRLS_OUTPUT_MEASUREMENT_DATA_LENGTH];
    memset(buffer, 0, sizeof(buffer));
    uint8_t rx[4];
    memset(buffer, 0, sizeof(rx));
    GPIO_HAL_set(ctx->cs_pin, LOW);

    Chip_SSP_Int_FlushData(ctx->SSP);
    buffer[0] = MPRLS_NOP;

    Chip_SSP_DATA_SETUP_T xf_setup = {

        .tx_data = buffer,
        .tx_cnt = 0,
        .rx_data = &rx,
        .rx_cnt = 0,
        .length = 4,
    };

    Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup);

    GPIO_HAL_set(ctx->cs_pin, HIGH);

    const uint8_t status = rx[0];
    if (status & MPRLS_STATUS_FAILED) {
        ctx->error = true;
    }

    uint32_t pres = rx[1] << 16 | rx[2] << 8 | rx[3];

    return scale(pres);
}

bool mprls_enable(MPRLS *ctx, bool reset)
{
    if(reset) {
        GPIO_HAL_set(ctx->reset_pin, HIGH);
        GPIO_HAL_set(ctx->reset_pin, LOW);
        delay_us(10*1000);
        GPIO_HAL_set(ctx->reset_pin, HIGH);
        delay_us(10*1000);
    }

    uint8_t status = mprls_trigger_read(ctx);

    return status & MPRLS_STATUS_POWERED;
}

bool mprls_is_ready(MPRLS *ctx)
{
    return GPIO_HAL_get(ctx->drdry_pin);
}

bool mprls_is_timeout(MPRLS *ctx) {
    return delay_timeout_done(&ctx->timeout);
}

int32_t mprls_read_blocking(MPRLS *ctx)
{
    mprls_trigger_read(ctx);


    // wait for ready pin.
    while(!mprls_is_ready(ctx)) {
        // error if never ready
        if (mprls_is_timeout(ctx)) {
            ctx->error = true;
           return 0;
        }
    }

    return mprls_read_data(ctx);
}

