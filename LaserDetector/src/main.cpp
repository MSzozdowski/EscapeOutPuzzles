#include <Arduino.h>
#include "leds.h"
#include "sensors.h"
#include "doors.h"

#define DISPLAY_SENS_DATA 500
#define LED_SOLVE_BLINK_TIMES 8
#define LED_BLINK_TIME 250

typedef enum
{
  WAIT_FOR_SENS1,
  WAIT_FOR_SENS2,
  WAIT_FOR_SENS3,
  WAIT_FOR_SENS4,
  WAIT_FOR_SENS5,
  WAIT_FOR_SENS6,
  SOLVED_LED_BLINK,
  DOOR_OPEN,
  WAIT_FOR_NEXT_GAME
} stages_e;

void setup()
{
  LEDS_Init();
  DOORS_Init();
  Serial.begin(9600);
  Serial.println("Laser detector game initialized");
}

unsigned long tick = millis();
uint8_t sensor_value = 255;
stages_e game_stage = WAIT_FOR_SENS1;

void loop()
{
  DOORS_Process();

  switch (game_stage)
  {
  case WAIT_FOR_SENS1:
    sensor_value = SENSOR_ReturnSensValue(SENSOR1);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor1 detected!: ");
      Serial.println(sensor_value);
      game_stage = WAIT_FOR_SENS2;
      sensor_value = 255;
      LEDS_LedOn(LED1);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor1 value:");
      Serial.println(sensor_value);
      tick = millis();
    }

    break;

  case WAIT_FOR_SENS2:
    sensor_value = SENSOR_ReturnSensValue(SENSOR2);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor2 detected!: ");
      Serial.println(sensor_value);
      game_stage = WAIT_FOR_SENS3;
      sensor_value = 255;
      LEDS_LedOn(LED2);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor2 value:");
      Serial.println(sensor_value);
      tick = millis();
    }
    break;

  case WAIT_FOR_SENS3:
    sensor_value = SENSOR_ReturnSensValue(SENSOR3);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor3 detected!: ");
      Serial.println(sensor_value);
      game_stage = WAIT_FOR_SENS4;
      sensor_value = 255;
      LEDS_LedOn(LED3);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor3 value:");
      Serial.println(sensor_value);
      tick = millis();
    }
    break;

  case WAIT_FOR_SENS4:
    sensor_value = SENSOR_ReturnSensValue(SENSOR4);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor4 detected!: ");
      Serial.println(sensor_value);
      game_stage = WAIT_FOR_SENS5;
      sensor_value = 255;
      LEDS_LedOn(LED4);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor4 value:");
      Serial.println(sensor_value);
      tick = millis();
    }
    break;

  case WAIT_FOR_SENS5:
    sensor_value = SENSOR_ReturnSensValue(SENSOR5);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor5 detected!: ");
      Serial.println(sensor_value);
      game_stage = WAIT_FOR_SENS6;
      sensor_value = 255;
      LEDS_LedOn(LED5);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor5 value:");
      Serial.println(sensor_value);
      tick = millis();
    }
    break;

  case WAIT_FOR_SENS6:
    sensor_value = SENSOR_ReturnSensValue(SENSOR6);
    if (sensor_value < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor6 detected!: ");
      Serial.println(sensor_value);
      game_stage = SOLVED_LED_BLINK;
      sensor_value = 255;
      LEDS_LedOn(LED6);
    }

    if (millis() - tick > DISPLAY_SENS_DATA)
    {
      Serial.print("Sensor6 value:");
      Serial.println(sensor_value);
      tick = millis();
    }
    break;

  case SOLVED_LED_BLINK:
    static uint8_t toggle_no = 0;

    if (millis() - tick > LED_BLINK_TIME)
    {
      LEDS_LedsToggleAll();
      tick = millis();
      toggle_no++;
    }

    if (toggle_no >= LED_SOLVE_BLINK_TIMES)
    {
      game_stage = DOOR_OPEN;
      toggle_no = 0;
    }
    break;

  case DOOR_OPEN:
    DOORS_Open();
    LEDS_LedsToggleAll();
    Serial.println("Open doors");
    game_stage = WAIT_FOR_NEXT_GAME;
    break;

  case WAIT_FOR_NEXT_GAME:
    if(DOORS_DoorsReady())
    {
      game_stage = WAIT_FOR_SENS1;
      Serial.println("New game started");
    }
    break;
  default:
    break;
  }
}