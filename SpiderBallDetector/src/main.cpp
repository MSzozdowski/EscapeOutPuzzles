#include <Arduino.h>
#include "ledstrip.h"
#include "door.h"

#define RESET_TIME 5000
#define DOOR_DELAY_TIME 1000
#define LAST_SHOT_TIME 2000
#define SENSOR_THRESHOLD 50
#define SERIAL_DISPLAY_TIME 2000
#define SOLUTION_DELAY 1500
#define ARRAY_SIZE 4

typedef enum
{
  SENSORS_WAIT_FOR_BALL,
  SENSORS_DELAY_AFTER_SOLUTION,
  SENSORS_WAIT_FOR_DOORS_OPEN,
  SENSOR_WAIT_FOR_RESET
} puzzle_state_t;

typedef enum
{
  NONE,
  LEFT_UP,
  LEFT_DOWN,
  RIGHT_UP,
  RIGHT_DOWN
} hole_type_t;



void display_current_array(void);
void clear_current_array(void);
void led_strip_update(uint8_t stage);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(12, OUTPUT); //DOOR PIN
  DOOR_Init(); 

  LED_STRIP_Init();
  LED_STRIP_SetColor(0, NO_OF_LEDS, RED);
}

bool debug_on = false;
static uint8_t s1, s2, s3, s4, s5, s6, s7, s8;
puzzle_state_t puzzle_state = SENSORS_WAIT_FOR_BALL;

unsigned long tick_puzzle = 0;
unsigned long tick_serial = 0;
uint8_t hole_index = 0;

void loop()
{
  DOOR_Process();
  switch (puzzle_state)
  {
  case SENSORS_WAIT_FOR_BALL:
    s1 = analogRead(A0);
    s2 = analogRead(A1);
    s3 = analogRead(A2);
    s4 = analogRead(A3);
    s5 = analogRead(A4);
    s6 = analogRead(A5);
    s7 = analogRead(A6);
    s8 = analogRead(A7);
    if (millis() - tick_puzzle > LAST_SHOT_TIME)
    {
      if ((s1 < SENSOR_THRESHOLD || s2 < SENSOR_THRESHOLD) && hole_index == 0) // Lewy górny - czerwony
      {
        Serial.println("Lewy górny detected!");
        tick_puzzle = millis();
        led_strip_update(0);
        hole_index = 1;
      }
      else if ((s3 < SENSOR_THRESHOLD || s4 < SENSOR_THRESHOLD) && hole_index == 1)
      {
        Serial.println("Lewy dolny detected!");                               // Lewy dolny - niebieski
        tick_puzzle = millis();
        led_strip_update(1);
        hole_index = 2;
      }
      else if ((s7 < SENSOR_THRESHOLD || s8 < SENSOR_THRESHOLD) && hole_index == 2)
      {
        Serial.println("Prawy górny detected!");                              // Prawy górny - żółty
        tick_puzzle = millis();
        led_strip_update(2);
        hole_index = 3;
      }
      else if ((s5 < SENSOR_THRESHOLD || s6 < SENSOR_THRESHOLD) && hole_index == 3)
      {
        Serial.println("Prawy dolny detected!");                              // Prawy dolny - zielony
        tick_puzzle = millis();
        led_strip_update(3);
        hole_index = 0;
        puzzle_state = SENSORS_DELAY_AFTER_SOLUTION;
      }
    }
    if(millis() - tick_serial > SERIAL_DISPLAY_TIME && debug_on == true)
    {
      tick_serial = millis();
      Serial.println("Sensors values: ");
      Serial.print("s1: ");
      Serial.println(s1);

      Serial.print("s2: ");
      Serial.println(s2);

      Serial.print("s3: ");
      Serial.println(s3);

      Serial.print("s4: ");
      Serial.println(s4);

      Serial.print("s5: ");
      Serial.println(s5);

      Serial.print("s6: ");
      Serial.println(s6);

      Serial.print("s7: ");
      Serial.println(s7);

      Serial.print("s8: ");
      Serial.println(s8);
    }
    break;

  case SENSORS_DELAY_AFTER_SOLUTION:
    if(millis() - tick_puzzle > SOLUTION_DELAY)
    {
      LED_STRIP_SetColor(0, NO_OF_LEDS, GREEN);
      LED_STRIP_Update();
      tick_puzzle = millis();
      puzzle_state = SENSORS_WAIT_FOR_DOORS_OPEN;
    }
  break;

  case SENSORS_WAIT_FOR_DOORS_OPEN:
    if(millis() - tick_puzzle > DOOR_DELAY_TIME)
    {
      tick_puzzle = millis();
      Serial.println("Solved!");
      DOOR_Open();
      puzzle_state = SENSOR_WAIT_FOR_RESET;
    }
  break;

  case SENSOR_WAIT_FOR_RESET:
    if(millis() - tick_puzzle > RESET_TIME)
    {
      LED_STRIP_SetColor(0, NO_OF_LEDS, OFF);
      LED_STRIP_Update();
      puzzle_state = SENSORS_WAIT_FOR_BALL;
    }
  break;

  default:
    break;
  }
}

void led_strip_update(uint8_t stage)
{
  LED_STRIP_SetColor(0, NO_OF_LEDS, OFF);
  LED_STRIP_Update();

  if(stage ==  0)
  {
    LED_STRIP_SetColor(0, 2, RED);
    Serial.println("Stage: 1");
  }
  else if(stage == 1)
  {
    LED_STRIP_SetColor(0, 2, RED);
    LED_STRIP_SetColor(3, 5, BLUE);
    Serial.println("Stage: 2");
  }
  else if(stage == 2)
  {
    LED_STRIP_SetColor(0, 2, RED);
    LED_STRIP_SetColor(3, 5, BLUE);
    LED_STRIP_SetColor(6, 8, YELLOW);
    Serial.println("Stage: 3");
  }
  else if(stage == 3)
  {
    LED_STRIP_SetColor(0, 2, RED);
    LED_STRIP_SetColor(3, 5, BLUE);
    LED_STRIP_SetColor(6, 8, YELLOW);
    LED_STRIP_SetColor(9, 11, GREEN);
    Serial.println("Stage: 4");
  }
  LED_STRIP_Update();
}