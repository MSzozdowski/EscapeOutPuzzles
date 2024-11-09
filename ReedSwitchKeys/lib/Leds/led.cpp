#include "Arduino.h"
#include "led.h"

led_state_t led_state;
uint8_t led_pin;
unsigned long tick;

void LED_Init(uint8_t pin)
{
    led_pin = pin;
    pinMode(OUTPUT, led_pin);
}

void LED_Process(void)
{
    switch (led_state)
    {
    case LED_IDLE:
        
        break;

    case LED_SHORT_BLINK:
        if(millis() - tick > LED_SHORT_BLINK_TIME)
        {
            LED_Off();
            led_state = LED_IDLE;
        }
    break;
    }
}

void LED_SetState(led_state_t led_st)
{
    led_state = led_st;
    tick = millis();

    if(led_state == LED_SHORT_BLINK)
    {
        LED_On();
    }
}

void LED_On(void)
{
    digitalWrite(led_pin, HIGH);
}

void LED_Off(void)
{
    digitalWrite(led_pin, LOW);
}

void LED_Toggle(void)
{
    digitalWrite(led_pin, !digitalRead(led_pin));
}