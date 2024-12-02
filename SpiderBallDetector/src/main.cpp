#include <Arduino.h>
#include "ledstrip.h"
#include "door.h"

#define RESET_TIME 5000
#define DOOR_DELAY_TIME 1000
#define LAST_SHOT_TIME 1000
#define SENSOR_THRESHOLD 50
#define SERIAL_DISPLAY_TIME 2000
#define ARRAY_SIZE 6

typedef enum
{
  SENSORS_WAIT_FOR_BALL,
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
void led_strip_short_blink(void);

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
hole_type_t hole_game_current[ARRAY_SIZE] = {NONE, NONE, NONE, NONE, NONE, NONE};
hole_type_t solution_array[ARRAY_SIZE] = {LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN, RIGHT_UP, LEFT_UP};
void loop()
{
  DOOR_Process();
  switch (puzzle_state)
  {
  case SENSORS_WAIT_FOR_BALL:
    static uint8_t hole_index = 0;
    static bool throw_good = false;
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
      if (s1 < SENSOR_THRESHOLD || s2 < SENSOR_THRESHOLD) // Lewy górny - czerwony
      {
        Serial.println("Lewy górny detected!");
        tick_puzzle = millis();
        if(hole_index == 0)
        {
          hole_game_current[hole_index++] = LEFT_UP;
          display_current_array();
        }
        else if(hole_index == 1)
        {
          hole_index = 0;
          hole_game_current[hole_index++] = LEFT_UP;
          display_current_array();
        }
        else if(hole_index == 5)
        {
          hole_game_current[hole_index++] = LEFT_UP;
          display_current_array();
          puzzle_state = SENSORS_WAIT_FOR_DOORS_OPEN;
        }
        else
        {
          throw_good = false;
        }
        led_strip_short_blink();
      }

      if (s3 < SENSOR_THRESHOLD || s4 < SENSOR_THRESHOLD)
      {
        Serial.println("Lewy dolny detected!"); // Lewy dolny - niebieski
        tick_puzzle = millis();
        if(hole_index == 1)
        {
          hole_game_current[hole_index++] = LEFT_DOWN;
          display_current_array();
        }
        else
        {
          throw_good = false;
        }
        led_strip_short_blink();
      }

      if (s5 < SENSOR_THRESHOLD || s6 < SENSOR_THRESHOLD)
      {
        Serial.println("Prawy dolny detected!"); // Prawy dolny - zółty
        tick_puzzle = millis();
        if(hole_index == 3)
        {
          hole_game_current[hole_index++] = RIGHT_DOWN;
          display_current_array();
        }
        else
        {
          throw_good = false;
        }
        led_strip_short_blink();
      }

      if (s7 < SENSOR_THRESHOLD || s8 < SENSOR_THRESHOLD)
      {
        Serial.println("Prawy górny detected!"); // Prawy górny - zielony
        tick_puzzle = millis();
        if(hole_index == 2)
        {
          hole_game_current[hole_index++] = RIGHT_UP;
          display_current_array();
        }
        else if(hole_index == 4)
        {
          hole_game_current[hole_index++] = RIGHT_UP;
          display_current_array();
        }
        else
        {
          throw_good = false;
        }
        led_strip_short_blink();
      }
      
      if(throw_good == false)
      {
        throw_good = true;
        hole_index = 0;
        clear_current_array();
        display_current_array();
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

  case SENSORS_WAIT_FOR_DOORS_OPEN:
    if(millis() - tick_puzzle > DOOR_DELAY_TIME)
    {
      LED_STRIP_SetColor(0, NO_OF_LEDS, GREEN);
      tick_puzzle = millis();
      Serial.println("Solved!");
      DOOR_Open();
      puzzle_state = SENSOR_WAIT_FOR_RESET;
    }
  break;

  case SENSOR_WAIT_FOR_RESET:
    if(millis() - tick_puzzle > RESET_TIME)
    {
      LED_STRIP_SetColor(0, NO_OF_LEDS, RED);
      puzzle_state = SENSORS_WAIT_FOR_BALL;
    }
  break;

  default:
    break;
  }
}

void display_current_array(void)
{
  Serial.print("Current array: ");
  for(uint8_t i = 0; i < ARRAY_SIZE; i++)
  {
    Serial.print(hole_game_current[i]);
  }
  Serial.println("");
}

void clear_current_array(void)
{
  Serial.print("Clear array: ");
  for(uint8_t i = 0; i < ARRAY_SIZE; i++)
  {
    hole_game_current[i] = NONE;
    Serial.print(hole_game_current[i]);
  }
  Serial.println("");
}

void led_strip_short_blink(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  LED_STRIP_SetColor(0, NO_OF_LEDS, OFF);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  LED_STRIP_SetColor(0, NO_OF_LEDS, RED);
}