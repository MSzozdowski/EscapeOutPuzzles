#ifndef ledstrip_h
#define ledstrip_h

#include "stdint.h"

#define LED_STRIP_PIN 3
#define NO_OF_LEDS  82

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

#define OFF 0x000000

void LED_STRIP_Init(void);
void LED_STRIP_SetColor(uint8_t start_id, uint8_t end_id, uint32_t color);

#endif