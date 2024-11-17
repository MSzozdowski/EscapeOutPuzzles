#ifndef ledstrip_h
#define ledstrip_h

#include "stdint.h"

#define LED_STRIP_PIN 3
#define NO_OF_LEDS  8

#define RED 0x0F0000
#define GREEN 0x000F00
#define OFF 0x000000

void LED_STRIP_Init(void);
void LED_STRIP_SetColor(uint8_t start_id, uint8_t end_id, uint32_t color);

#endif