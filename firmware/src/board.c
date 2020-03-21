#include "board.h"
#include "board_GPIO_ID.h"
#include "board_ADC_ID.h"

#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <c_utils/static_assert.h>
#include <mcu_timing/delay.h>

#include <chip.h>

// Oscillator frequency, needed by chip libraries
const uint32_t OscRateIn = 12000000;


static const NVICConfig NVIC_config[] = {
    {WDT_IRQn,              0},     // watchdog warning: high priority
    {TIMER_32_0_IRQn,       0},     // delay timer: high priority

    {PIN_INT0_IRQn,         1},
    {PIN_INT1_IRQn,         1},

    {SysTick_IRQn,          2},

    {USB0_IRQn,             3},
};

static const PinMuxConfig pinmuxing[] = {


        {1, 20, (IOCON_FUNC0 | IOCON_MODE_PULLUP)}, // HW Version bit0, version 0 = prototype, version 1 = first production

        {0,  0, (IOCON_FUNC1
             | IOCON_MODE_PULLUP)},     // Reset or Button FUNC1 = GPIO
        {0,  1, (IOCON_FUNC0
             | IOCON_MODE_PULLUP)},     // ISP pin: default input pullup

        // RGB LED SPI
        {0,  6, (IOCON_FUNC2)},         // SCK0
        {0,  9, (IOCON_FUNC1)},         // MOSI0
        {1,  24, (IOCON_FUNC0)},        // !CS: GPIO

        {0,  11, (IOCON_FUNC1 | IOCON_ADMODE_EN)},  // AD0: USB Voltage sense
        {0,  12, (IOCON_FUNC2 | IOCON_ADMODE_EN)},  // AD1: Battery voltage sense
        {0,  13, (IOCON_FUNC2 | IOCON_ADMODE_EN)},  // AD2: Pressure level sense
        {0,  14, (IOCON_FUNC2 | IOCON_ADMODE_EN)},  // AD3: Battery temperature sense

        // FLASH SPI
        {0,  17, (IOCON_FUNC0)},        // !CS: GPIO
        {1,  15, (IOCON_FUNC3)},        // SCK1
        {1,  21, (IOCON_FUNC2)},        // MISO1
        {1,  22, (IOCON_FUNC2)},        // MOSI1

        // Power switches
        {0,  19, (IOCON_FUNC0)},        // USB_pwr_en: GPIO also switches charger on/off from hw v1
        {1,  28, (IOCON_FUNC0)},        // charger_disable: GPIO
        {1,  29, (IOCON_FUNC0)},        // DCDC_en: GPIO
        {1,  31, (IOCON_FUNC0
                | IOCON_MODE_PULLUP)},  // charger_status: GPIO input

        // MOTOR and valves
        {0,  22, (IOCON_FUNC2 |IOCON_DIGMODE_EN)},  // motor: CT16B1_MAT1: pwm (ADMODE??)
        // {0,  22, (IOCON_FUNC0)},     // motor: GPIO
        // {1,  13, (IOCON_FUNC2)},     // valve_2: CT16B0_MAT0: pwm
        {1,  13, (IOCON_FUNC0)},        // valve_2: GPIO
        // {1,  14, (IOCON_FUNC2)},     // valve_1: CT16B0_MAT1: pwm
        {1,  14, (IOCON_FUNC0)},        // valve_1: GPIO

        // {1,  23, (IOCON_FUNC0)},     // batt_disable: GPIO // DEPRECATED
};

static const GPIOConfig pin_config[] = {

    [GPIO_ID_HW_VERSION0] =     {{1,  20}, GPIO_CFG_DIR_INPUT},

    [GPIO_ID_BUTTON] =          {{0,  0}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_ISP] =             {{0,  1}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_LED_CS] =          {{1,  24}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_FLASH_CS] =        {{0,  17}, GPIO_CFG_DIR_OUTPUT_HIGH},
    [GPIO_ID_USB_PWR_EN] =      {{0,  19}, GPIO_CFG_DIR_OUTPUT_HIGH},


    // Charging disabled by default
    [GPIO_ID_CHARGER_DISABLE] = {{1,  28}, GPIO_CFG_DIR_OUTPUT_HIGH},

    // DCDC enabled by default
    [GPIO_ID_DCDC_EN] =         {{1,  29}, GPIO_CFG_DIR_OUTPUT_HIGH},

    [GPIO_ID_CHARGER_STATUS] =  {{1,  31}, GPIO_CFG_DIR_INPUT},
    [GPIO_ID_MOTOR] =           {{1,  22}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_VALVE1] =          {{1,  14}, GPIO_CFG_DIR_OUTPUT_LOW},
    [GPIO_ID_VALVE2] =          {{1,  13}, GPIO_CFG_DIR_OUTPUT_LOW},

    // Deprecated
    // [GPIO_ID_BATT_DISABLE] =    {{1,  23}, GPIO_CFG_DIR_OUTPUT_LOW},
};

// pin config struct should match GPIO_ID enum
STATIC_ASSERT( (GPIO_ID_MAX == (sizeof(pin_config)/sizeof(GPIOConfig))));

static const enum ADCConfig ADC_config[] = {
    [ADC_ID_PRESSURE]      = ADC_CFG_CH2,
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


void board_setup(void)
{
    board_set_config(&config);
}

void board_reset(void)
{
    // Wait for ISP pin to become low
    // in case of reset via button
    delay_us(1500*1000);
	NVIC_SystemReset();
}
