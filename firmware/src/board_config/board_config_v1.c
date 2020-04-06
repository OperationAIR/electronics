//#include "board.h"
#include "board_GPIO_ID.h"
#include "board_ADC_ID.h"

#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/static_assert.h>
#include <mcu_timing/delay.h>

#include <chip.h>



static const NVICConfig NVIC_config[] = {
    {WDT_IRQn,              0},     // watchdog warning: high priority
    {TIMER_32_0_IRQn,       0},     // delay timer: high priority

    // TODO are these pin-ints used?
    {PIN_INT0_IRQn,         1},
    {PIN_INT1_IRQn,         1},

    {SysTick_IRQn,          2},

    {USB0_IRQn,             3},
};


// TODO adapt pinmuxing for V1 HW
static const PinMuxConfig pinmuxing[] = {

        // PSENSE (SPI0)
        {1,  29, (IOCON_FUNC1)},                            // PSENSE_SPI_CLK
        {0,  8, (IOCON_FUNC1 | IOCON_MODE_PULLUP)},         // PSENSE_SPI_MISO
        {0,  9, (IOCON_FUNC1)},                             // PSENSE_SPI_MOSI

        {1,  19, (IOCON_FUNC0)},                            // PSENSE_1_SPI_!CS
        {1,  22, (IOCON_FUNC0)},                            // PSENSE_2_SPI_!CS

        {1,  16, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN)},      // PSENSE_1_DRDY
        {1,  15, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN)},      // PSENSE_2_DRDY

        {1,  20, (IOCON_FUNC0)},                            // PSENSE_RESET


        // Switch outputs
        {0,  22, (IOCON_FUNC2 | IOCON_DIGMODE_EN)},         // SWITCH_EXHALE as PWM
        {1,  14, (IOCON_FUNC2)},                            // SWITCH_INHALE as PWM
        {1,  13, (IOCON_FUNC2)},                            // SWITCH_EXTRA as PWM


        // Analog inputs
        {0,  11, (IOCON_FUNC2 | IOCON_ADMODE_EN)},          // AD0: A_PSENSE_PATIENT
        {0,  12, (IOCON_FUNC2 | IOCON_ADMODE_EN)},          // AD1: A_MFC_PRESSURE
        {0,  13, (IOCON_FUNC2 | IOCON_ADMODE_EN)},          // AD2: A_MFC_FEEDBACK_O2
        {0,  14, (IOCON_FUNC2 | IOCON_ADMODE_EN)},          // AD3: A_MFC_FEEDBACK_AIR
        {0,  23, (IOCON_FUNC1 | IOCON_ADMODE_EN)},          // AD7: A_BATT_LEVEL


        // Power status & on/off
        {0,   7, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN)},      // POWER_STATUS_FAIL
        {0,   6, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN)},      // POWER_STATUS_DISCHARGING
        {1,  24, (IOCON_FUNC0)},                            // USER_SWITCH
        {0,  17, (IOCON_FUNC0)},                            // RPI_ON_OFF


        // UART
        {0,  18, (IOCON_FUNC1)},        // UART_RX
        {0,  19, (IOCON_FUNC1)},        // UART_TX


        // I2C
        {0,  4, (IOCON_FUNC1)},         // I2C_SCL
        {0,  5, (IOCON_FUNC1)},         // I2C_SDA

        // 0_0: keep default settings (reset pin)
        // 0_10: SWD
        // 0_15: SWD
        // 0,3: vbus 

        // ISP pin
        {0,  1, (IOCON_FUNC0
             | IOCON_MODE_PULLUP)},


        // LEDS
        {1,  23, (IOCON_FUNC0)},        // LED_STATUS
        {0,  21, (IOCON_FUNC0)},        // LED_ERROR


        // Extra I/O
        {0,  16, (IOCON_FUNC0)},        // EXTRA_IO_1
        {1,  21, (IOCON_FUNC0)},        // EXTRA_IO_2
        {1,  31, (IOCON_FUNC0)},        // EXTRA_IO_3
        {1,  28, (IOCON_FUNC0)},        // EXTRA_IO_4
};


static const GPIOConfig pin_config[] = {

    // Pressure sensors
    [GPIO_ID_PSENSE_RESET]          = {{1, 20}, GPIO_CFG_DIR_OUTPUT_HIGH},
    [GPIO_ID_PSENSE_1_CS]           = {{1, 19}, GPIO_CFG_DIR_OUTPUT_HIGH},
    [GPIO_ID_PSENSE_2_CS]           = {{0, 16}, GPIO_CFG_DIR_OUTPUT_HIGH},
    [GPIO_ID_PSENSE_1_DRDY]         = {{1, 25}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_PSENSE_2_DRDY]         = {{1, 23}, GPIO_CFG_DIR_INPUT},

    // Status LEDs
    [GPIO_ID_LED_STATUS]            = {{0, 17}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_LED_ERROR]             = {{0, 23}, GPIO_CFG_DIR_OUTPUT_LOW},

    // Power status & on/off
    [GPIO_ID_STATUS_FAIL]           = {{0,  7}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_STATUS_DISCHARGING]    = {{0,  6}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_USER_SWITCH]           = {{1, 24}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_RPI_ON_OFF]            = {{0, 17}, GPIO_CFG_DIR_OUTPUT_HIGH},

    // Extra I/O (on header)
    [GPIO_ID_EXTRA_1]               = {{1, 13}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_EXTRA_2]               = {{1, 16}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_EXTRA_3]               = {{0, 19}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_EXTRA_4]               = {{0, 18}, GPIO_CFG_DIR_OUTPUT_LOW},

};

// pin config struct should match GPIO_ID enum
STATIC_ASSERT( (GPIO_ID_MAX == (sizeof(pin_config)/sizeof(GPIOConfig))));

static const enum ADCConfig ADC_config[] = {

    [ADC_ID_PRESSURE_PATIENT]   = ADC_CFG_CH0,
    [ADC_ID_PRESSURE_MFC]       = ADC_CFG_CH1,
    [ADC_ID_MFC_O2]             = ADC_CFG_CH3,
    [ADC_ID_MFC_AIR]            = ADC_CFG_CH2,
    [ADC_ID_BATTERY_LEVEL]      = ADC_CFG_CH7,
};

// adc config struct should match ADC_ID enum
STATIC_ASSERT( (ADC_ID_MAX == (sizeof(ADC_config)/sizeof(ADC_config[0]))));

static const BoardConfig config = {
    .nvic_configs = NVIC_config,
    .nvic_count = sizeof(NVIC_config) / sizeof(NVIC_config[0]),

    .pinmux_configs = pinmuxing,
    .pinmux_count = sizeof(pinmuxing) / sizeof(pinmuxing[0]),

    .GPIO_configs = pin_config,
    .GPIO_count = sizeof(pin_config) / sizeof(pin_config[0]),

    .ADC_configs = ADC_config,
    .ADC_count = sizeof(ADC_config) / sizeof(ADC_config[0])
};


void board_config_v1_setup(void)
{
    board_set_config(&config);
}

