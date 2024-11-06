#include "Arduino.h"
#include "leds.h"

void LEDS_Init(uint8_t pin)
{
    pinMode(pin, OUTPUT);
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