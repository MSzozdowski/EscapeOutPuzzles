#ifndef leds_h
#define leds_h

#include <stdint.h>

void LEDS_Init(uint8_t pin);
void LEDS_LedOn(uint8_t led_no);
void LEDS_LedOff(uint8_t led_no);
void LEDS_LedToggle(uint8_t led_no);

#endif