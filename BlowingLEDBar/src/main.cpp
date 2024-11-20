#include <Arduino.h>
#include "ledstrip.h"
#include "microphone.h"
#include "doors.h"

#define MICROPHONE_THRESHOLD_VALUE 90
#define CHECK_MICROPHONE_INTERVAL 100

#define ZERO_PERCENT 0
#define ONE_HUNDREAD_PERCENT 200

#define PUZZLE_SOLVE_WAIT_TIME 5000

typedef enum
{
  PUZZLE_INIT,
  PUZZLE_IDLE,
  PUZZLE_FILLING_LEDS,
  PUZZLE_FADING_LEDS,
  PUZZLE_SOLVED
} puzzle_state_t;

puzzle_state_t puzzle_state = PUZZLE_INIT;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  LED_STRIP_Init();
  DOORS_Init();
}

static unsigned long currentMillis = 0;
uint16_t progress = 0;
uint16_t mapped_progress = 0;
void loop()
{
  MICROPHONE_Process();
  DOORS_Process();

  switch (puzzle_state)
  {
  case PUZZLE_INIT:
    LED_STRIP_SetColor(0, NO_OF_LEDS, RED);
    puzzle_state = PUZZLE_IDLE;
    Serial.println("Puzzle init all leds are red");
    break;

  case PUZZLE_IDLE:
    if (MICROPHONE_GetAverage() > MICROPHONE_THRESHOLD_VALUE)
    {
      progress = 0;
      currentMillis = millis();
      puzzle_state = PUZZLE_FILLING_LEDS;
      Serial.println("Puzzle blowing detected");
    }
    break;

  case PUZZLE_FILLING_LEDS:
    if(millis() - currentMillis > CHECK_MICROPHONE_INTERVAL)
    {
      currentMillis = millis();
      if(MICROPHONE_GetAverage() > MICROPHONE_THRESHOLD_VALUE)
      {
        progress+=3;
        mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDREAD_PERCENT, 0, NO_OF_LEDS);
        LED_STRIP_SetColor(0, mapped_progress, BLUE);
        Serial.print("Mapped progress: ");
        Serial.println(mapped_progress);
        if(mapped_progress == NO_OF_LEDS)
        {
          puzzle_state = PUZZLE_SOLVED;
          DOORS_Open();
        }
      }
      else
      {
        puzzle_state = PUZZLE_FADING_LEDS;
      }
    }
    break;

  case PUZZLE_FADING_LEDS:
    if(millis() - currentMillis > CHECK_MICROPHONE_INTERVAL)
    {
      currentMillis = millis();
      if(MICROPHONE_GetAverage() < MICROPHONE_THRESHOLD_VALUE)
      {
        progress-=2;
        mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDREAD_PERCENT, 0, NO_OF_LEDS);
        LED_STRIP_SetColor(0, mapped_progress, BLUE);
        Serial.print("Mapped progress: ");
        Serial.println(mapped_progress);

        if(mapped_progress == 0)
        {
          puzzle_state = PUZZLE_INIT;
        }
      }
      else
      {
        puzzle_state = PUZZLE_FILLING_LEDS;
      }
    }
    break;

   case PUZZLE_SOLVED:
   if(millis() - currentMillis > PUZZLE_SOLVE_WAIT_TIME)
   {
    puzzle_state = PUZZLE_INIT;
   }
   break; 
  }
}