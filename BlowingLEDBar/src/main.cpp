#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "ledstrip.h"
#include "microphone.h"

#define MICROPHONE_THRESHOLD_VALUE 100
#define LED_FILL_TIME 10000
#define LED_FADE_TIME 10000
#define NO_OF_LEDS 8
#define CHECK_MICROPHONE_INTERVAL 250

typedef enum
{
  PUZZLE_INIT,
  PUZZLE_IDLE,
  PUZZLE_FILLING_LEDS,
  PUZZLE_FADING_LEDS
} puzzle_state_t;

unsigned long lastCheckTime = 0;
unsigned long fillStartTime = 0;
unsigned long fadeStartTime = 0;

uint8_t ledFillProgress = 0;
uint8_t ledFadeProgress = NO_OF_LEDS;
puzzle_state_t puzzle_state = PUZZLE_INIT;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  LED_STRIP_Init();
}

static unsigned long currentMillis = 0;

void loop()
{

  MICROPHONE_Process();

  switch (puzzle_state)
  {
  case PUZZLE_INIT:
    LED_STRIP_SetColor(0, NO_OF_LEDS - 1, RED);
    puzzle_state = PUZZLE_IDLE;
    Serial.println("Puzzle init all leds are red");
    break;

  case PUZZLE_IDLE:
    if (MICROPHONE_GetAverage() > MICROPHONE_THRESHOLD_VALUE)
    {
      LED_STRIP_SetColor(0, NO_OF_LEDS - 1, OFF);
      fillStartTime = millis();
      ledFillProgress = 0;
      puzzle_state = PUZZLE_FILLING_LEDS;
      Serial.println("Puzzle blowing detected");
    }
    break;

  case PUZZLE_FILLING_LEDS:
    if (millis() - currentMillis > CHECK_MICROPHONE_INTERVAL)
    {
      currentMillis = millis();
      if (MICROPHONE_GetAverage() > MICROPHONE_THRESHOLD_VALUE)
      {
        ledFillProgress = map(currentMillis - fillStartTime, 0, LED_FILL_TIME, 0, NO_OF_LEDS);
        LED_STRIP_SetColor(0, ledFillProgress, GREEN);
        Serial.print("ledFillProgress: ");
        Serial.println(ledFillProgress);
      }
      else
      {
        puzzle_state = PUZZLE_FADING_LEDS;
        fadeStartTime = ledFillProgress;
        Serial.println("Blowing stopped - fade leds");
      }
    }

    break;

  case PUZZLE_FADING_LEDS:
    if (millis() - currentMillis > CHECK_MICROPHONE_INTERVAL)
    {
      currentMillis = millis();
      if (MICROPHONE_GetAverage() < MICROPHONE_THRESHOLD_VALUE)
      {
        ledFadeProgress = map(currentMillis - fadeStartTime, 0, LED_FADE_TIME, NO_OF_LEDS, 0);
        LED_STRIP_SetColor(0, NO_OF_LEDS - 1, OFF);
        LED_STRIP_SetColor(0, ledFadeProgress, GREEN);
        Serial.print("ledFadeProgress: ");
        Serial.println(ledFadeProgress);
        if(ledFadeProgress == 0)
        {
          puzzle_state = PUZZLE_INIT;
        }
      }
      else
      {
        puzzle_state = PUZZLE_FILLING_LEDS;
        fillStartTime = fadeStartTime;
        Serial.println("Blowing started again - fill leds");
      }
    }
    break;
  }
}