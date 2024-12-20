#include "Arduino.h"
#include "leds.h"

void LEDS_Init(void)
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
}

void LEDS_LedOn(uint8_t led_no)
{
    digitalWrite(led_no, HIGH);
}

void LEDS_LedOff(uint8_t led_no)
{
    digitalWrite(led_no, LOW);
}

void LEDS_LedToggle(uint8_t led_no)
{
    digitalWrite(led_no, !digitalRead(led_no));
}

void LEDS_LedsToggleAll(void)
{
    uint8_t first_led_no = LED6;
    for(uint8_t i = 0; i < LED_NUMBER; i++)
        LEDS_LedToggle(first_led_no++);
}

void LEDS_LedsAllOn(void)
{
    uint8_t first_led_no = LED6;
    for(uint8_t i = 0; i < LED_NUMBER; i++)
        LEDS_LedOn(first_led_no++);
}

void LEDS_LedsAllOff(void)
{
    uint8_t first_led_no = LED6;
    for(uint8_t i = 0; i < LED_NUMBER; i++)
        LEDS_LedOff(first_led_no++);
}