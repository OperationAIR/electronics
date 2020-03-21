#ifndef _LED_API_
#define _LED_API_

#include "RGB_LED.h"
#include <stdint.h>

void LED_api_init();
void LED_set(const RGBColor *color);
void LED_set_rgb(uint8_t r, uint8_t g, uint8_t b);
void LED_set_brightness(int brightness);
void LED_get_color(RGBColor *color);

#endif