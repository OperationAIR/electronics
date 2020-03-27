#include "MPRL_pressure.h"
#include <lpc_tools/GPIO_HAL.h>
#include <mcu_timing/delay.h>



// SPI 0,0 mode: clock idles in low state
#define SPI_MODE      (SSP_CLOCK_MODE0)

// Frequency: ADS5410 is specified up to 30MHz
#define MPR_SENSOR_BITRATE   (100000)

void mprl_init(MPRL *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin, const GPIO *drdy_pin, const GPIO *reset_pin)
{
    ctx->SSP = LPC_SSP;
    ctx->cs_pin = cs_pin;
    ctx->drdry_pin = drdy_pin;
    ctx->reset_pin = reset_pin;

    static SSP_ConfigFormat ssp_format;
    Chip_SSP_Init(LPC_SSP);
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_BITS_8;
	ssp_format.clockMode = SPI_MODE;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, true);
    Chip_SSP_SetBitRate(LPC_SSP, MPR_SENSOR_BITRATE);

	Chip_SSP_Enable(LPC_SSP);
}

void mprl_enable(MPRL *ctx)
{
    GPIO_HAL_set(ctx->reset_pin, HIGH);
    GPIO_HAL_set(ctx->reset_pin, LOW);
    delay_us(10*1000);
    GPIO_HAL_set(ctx->reset_pin, HIGH);
    delay_us(10*1000);


    // Step 1
    uint8_t buffer[4];
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = 0xAA;
    uint8_t rx[4];
    memset(rx, 0, sizeof(rx));
    GPIO_HAL_set(ctx->cs_pin, LOW);

	Chip_SSP_Int_FlushData(ctx->SSP);

    Chip_SSP_DATA_SETUP_T xf_setup = {

        .tx_data = buffer,
        .tx_cnt = 0,
        .rx_data = rx,
        .rx_cnt = 0,
        .length = 3,
    };

    size_t result = Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup);


    GPIO_HAL_set(ctx->cs_pin, HIGH);

    // wait 5 ms for dataconversion to complete
    delay_us(5 * 1000);

    bool is_ready = GPIO_HAL_get(ctx->drdry_pin);

    // Step 2
    // memset(buffer, 0, sizeof(buffer));
    // memset(rx, 0, sizeof(rx));
    // GPIO_HAL_set(ctx->cs_pin, LOW);
    // buffer[0] = 0xF0;

    // Chip_SSP_DATA_SETUP_T xf_setup2 = {

    //     .tx_data = buffer,
    //     .tx_cnt = 0,
    //     .rx_data = rx,
    //     .rx_cnt = 0,
    //     .length = 1,
    // };

    // result = Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup2);

    // GPIO_HAL_set(ctx->cs_pin, HIGH);


      // Step 3
    memset(buffer, 0, sizeof(buffer));
    memset(rx, 0, sizeof(rx));
    GPIO_HAL_set(ctx->cs_pin, LOW);
    buffer[0] = 0xF0;

    Chip_SSP_DATA_SETUP_T xf_setup3 = {

        .tx_data = buffer,
        .tx_cnt = 0,
        .rx_data = rx,
        .rx_cnt = 0,
        .length = 4,
    };

    result = Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup3);

    GPIO_HAL_set(ctx->cs_pin, HIGH);
}