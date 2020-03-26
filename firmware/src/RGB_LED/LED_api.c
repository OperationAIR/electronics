#include "LED_api.h"
#include "RGB_driver_APA102.h"
#include <c_utils/assert.h>

APA102 LED;

static APA102 *g_led;
static RGBColor current_color = {0, 0, 0};

static void copy_color(RGBColor *dst, const RGBColor *src)
{
    dst->red = src->red;
    dst->green = src->green;
    dst->blue = src->blue;
}

void LED_api_init()
{
    assert(RGB_driver_APA102_init(&LED, LPC_SSP0));
    g_led = &LED;
}

void LED_set(const RGBColor *color)
{
    RGB_driver_APA102_begin(g_led);
    RGB_driver_APA102_set_color(g_led, *color);
	RGB_driver_APA102_commit(g_led);
    copy_color(&current_color, color);

}

void LED_set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    RGBColor color = {r, g, b};
    LED_set(&color);
}

void LED_set_brightness(int brightness)
{
    RGB_driver_APA102_set_brightness(g_led, brightness);
}

void LED_get_color(RGBColor *color)
{
    copy_color(color, &current_color);
}