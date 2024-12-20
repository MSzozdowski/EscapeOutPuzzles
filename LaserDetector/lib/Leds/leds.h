#ifndef leds_h
#define leds_h

#include <stdint.h>

#define LED1 7
#define LED2 6
#define LED3 5
#define LED4 4
#define LED5 3
#define LED6 2

#define LED_NUMBER 6

void LEDS_Init(void);
void LEDS_LedOn(uint8_t led_no);
void LEDS_LedOff(uint8_t led_no);
void LEDS_LedToggle(uint8_t led_no);
void LEDS_LedsToggleAll(void);
void LEDS_LedsAllOn(void);
void LEDS_LedsAllOff(void);
#endif