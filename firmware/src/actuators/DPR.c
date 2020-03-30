#include "DPR.h"
#include <lpc_tools/GPIO_HAL.h>
#include <mcu_timing/delay.h>
#include <c_utils/min.h>

#include <string.h>




// SPI 0,0 mode: clock idles in low state
#define SPI_MODE      (SSP_CLOCK_MODE0)

// Frequency: ADS5410 is specified up to 30MHz
#define MPR_SENSOR_BITRATE   (20000000)


enum DAC_command {
    DAC_CMD_READ_STATUS     = 0,
    DAC_CMD_READ_DATA       = 1,
    DAC_CMD_READ_CONTROL    = 2,

    DAC_CMD_NOP             = 0,
    DAC_CMD_DATA            = 1,
    DAC_CMD_READBACK        = 2,
    DAC_CMD_CONTROL         = 0b01010101,
    DAC_CMD_RESET           = 0b01010110,
};


enum DAC_control {
    DAC_CTRL_REXT           = (1 << 13),
    DAC_CTRL_OUTEN          = (1 << 12),

    // 3-bit value at offset 5
    DAC_CTRL_MASK_SR_STEP = 0b11,
    DAC_CTRL_SHIFT_SR_STEP  = 5,

    // 4-bit value at offset 8
    DAC_CTRL_MASK_SR_CLOCK = 0b1111,
    DAC_CTRL_SHIFT_SR_CLOCK = 8,

    DAC_CTRL_SREN           = (1 << 4),
    DAC_CTRL_DCEN           = (1 << 3),

    DAC_CTRL_RANGE_4_20_MA  = 0b101,
    DAC_CTRL_RANGE_0_20_MA  = 0b110,
    DAC_CTRL_RANGE_0_24_MA  = 0b111,

};

// Forward declarations
static bool _reset(DPR *ctx);
static bool _write(DPR *ctx, enum DAC_command cmd, uint16_t value);
static int _read_register(DPR *ctx,  enum DAC_command cmd);

static size_t SPI_rw_blocking(DPR *ctx, uint8_t* buffer, size_t sizeof_buffer)
{
    GPIO_HAL_set(ctx->cs_pin, LOW);
    uint8_t rx[sizeof_buffer];
    memset(rx, 0, sizeof(rx));

    Chip_SSP_DATA_SETUP_T xf_setup = {

        .tx_data = buffer,
        .tx_cnt = 0,
        .rx_data = rx,
        .rx_cnt = 0,
        .length = sizeof_buffer,
    };

	Chip_SSP_Int_FlushData(ctx->SSP);
    const size_t result = Chip_SSP_RWFrames_Blocking(ctx->SSP, &xf_setup);

    // latch pulse at end of 24-bit transfer: DPR chip is not standard SPI...
    GPIO_HAL_set(ctx->cs_pin, HIGH);
    delay_us(10);
    GPIO_HAL_set(ctx->cs_pin, LOW);

    memcpy(buffer, rx, sizeof_buffer);
    return result;
}

bool DPR_init(DPR *ctx, LPC_SSP_T *LPC_SSP, const GPIO *cs_pin)
{

    ctx->SSP = LPC_SSP;
    ctx->cs_pin = cs_pin;

    static SSP_ConfigFormat ssp_format;
    Chip_SSP_Init(LPC_SSP);
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_BITS_8;
	ssp_format.clockMode = SPI_MODE;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, true);
    Chip_SSP_SetBitRate(LPC_SSP, MPR_SENSOR_BITRATE);

	Chip_SSP_Enable(LPC_SSP);
    return true;
}

bool DPR_disable(DPR *ctx)
{
    bool ok = DPR_write(ctx, 0);
    ok&= _reset(ctx);
    return ok;
}

bool DPR_enable(DPR *ctx)
{
    if(!_reset(ctx)) {
        return false;
    }

    // See datasheet for slew rate control. 0xA 0x7 is 50ms rise time
    const int SR_CLOCK = 0b0010  << DAC_CTRL_SHIFT_SR_CLOCK;
    const int SR_STEP = 0x1 << DAC_CTRL_SHIFT_SR_STEP;
    const uint16_t ctrl = (DAC_CTRL_OUTEN
            | DAC_CTRL_RANGE_4_20_MA
            | DAC_CTRL_SREN
            | SR_CLOCK
            | SR_STEP);

    // Write control register
    if(!_write(ctx, DAC_CMD_CONTROL, ctrl)) {
        return false;
    }
    // Verify control register
    int readback_ctrl = _read_register(ctx, DAC_CMD_READ_CONTROL);
    if((int)ctrl != readback_ctrl) {
        return false;
    }

    // Init to 0: lowest value
    if(!DPR_write(ctx, 0)) {
        return false;
    }

    return true;
}

int DPR_status(DPR *ctx)
{
    return _read_register(ctx, DAC_CMD_READ_STATUS);
}

bool DPR_write(DPR *ctx, unsigned int value)
{
    // clamp input to valid 12-bit range (0-4096)
    value = min(value, 0xFFF);
  
    // max 3 retries in case of bus error or readback fail
    for(size_t i=0;i<3;i++) {


        const uint16_t data = (value << 4);
        if(_write(ctx, DAC_CMD_DATA, data)) {

            // Verify data register
            const int readback_data = _read_register(ctx, DAC_CMD_READ_DATA);
            if((int)data == readback_data) {
                return true;
            }
        }
    }

    // write failed!
    return false;
}




static bool _write(DPR *ctx, enum DAC_command cmd, uint16_t value)
{
    uint8_t tx_buffer[] = {cmd, (value >> 8), (value & 0xFF)};

    return (sizeof(tx_buffer) == SPI_rw_blocking(ctx, tx_buffer, sizeof(tx_buffer)));
}

static bool _reset(DPR *ctx)
{
    const bool ok = _write(ctx, DAC_CMD_RESET, 0x0001);

    // Wait for internal calibration to complete
    delay_us(40);

    return ok;
}

static int _read_register(DPR *ctx,  enum DAC_command cmd)
{
    uint8_t tx_buffer[] = {0x02, 0x00, cmd};
    bool ok = (sizeof(tx_buffer) == SPI_rw_blocking(ctx, tx_buffer, sizeof(tx_buffer)));


    uint8_t buffer[] = {DAC_CMD_NOP, DAC_CMD_NOP, DAC_CMD_NOP};
    ok&= (sizeof(buffer) == SPI_rw_blocking(ctx, buffer, sizeof(buffer)));

    if(!ok) {
        return -1;
    }

    /*
    log_wtime("DPR reg %d: %d %d %d",
            (int)cmd,
            (int)buffer[0],
            (int)buffer[1],
            (int)buffer[2]);
            */
    return ((buffer[1] << 8) | buffer[2]);
}

