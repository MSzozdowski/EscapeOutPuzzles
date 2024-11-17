#include "Arduino.h"
#include "ledstrip.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(NO_OF_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

void LED_STRIP_Init(void)
{
  led_strip.begin();
  led_strip.show();
}

void LED_STRIP_SetColor(uint8_t start_id, uint8_t end_id, uint32_t color)
{
  if(end_id > NO_OF_LEDS - 1)
  {
    Serial.println("End ID is higher than LED NUMBER");
    return;
  }

  for(uint8_t i = start_id; i <= end_id; i++)
  {
    led_strip.setPixelColor(i, led_strip.Color(color >> 16, color >> 8, 0));
  }
  led_strip.show();  
}