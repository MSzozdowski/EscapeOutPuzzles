#include <Arduino.h>
#include "leds.h"
#include "sensors.h"
#include "doors.h"

#define DISPLAY_SENS_DATA 500
#define LED_SOLVE_BLINK_TIMES 7
#define LED_BLINK_TIME 250
#define DELAY_BEETWEEN_STATES 500

typedef enum
{
  WAIT_FOR_SENS,
  DELAY_FOR_NEXT,
  SOLVED_LED_BLINK,
  DOOR_OPEN,
  WAIT_FOR_NEXT_GAME
} stages_e;

void displayCurrentArray(void);
void clearCurrentArray(void);
uint8_t checkIsGoingToSolve(uint8_t arr_id);

void setup()
{
  LEDS_Init();
  DOORS_Init();
  Serial.begin(9600);
  Serial.println("Laser detector game initialized");
}

unsigned long tick = millis();

uint8_t sensor_value1 = 255;
uint8_t sensor_value2 = 255;
uint8_t sensor_value3 = 255;
uint8_t sensor_value4 = 255;
uint8_t sensor_value5 = 255;
uint8_t sensor_value6 = 255;

stages_e game_stage = WAIT_FOR_SENS;

uint8_t solution_array[7] = {1, 2, 3, 4, 5, 2, 6};
uint8_t current_array[7] = {0, 0, 0, 0, 0, 0, 0};

uint8_t array_index = 0;
uint8_t sens_detected_flag = 0;
uint8_t temp_sens_value = 0;
uint8_t last_sens_detected = 0;
void loop()
{
  DOORS_Process();

  switch (game_stage)
  {
  case WAIT_FOR_SENS:
    sensor_value1 = SENSOR_ReturnSensValue(SENSOR1);
    sensor_value2 = SENSOR_ReturnSensValue(SENSOR2);
    sensor_value3 = SENSOR_ReturnSensValue(SENSOR3);
    sensor_value4 = SENSOR_ReturnSensValue(SENSOR4);
    sensor_value5 = SENSOR_ReturnSensValue(SENSOR5);
    sensor_value6 = SENSOR_ReturnSensValue(SENSOR6);

    if (sensor_value1 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor1 detected!: ");
      Serial.println(sensor_value1);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 1;
      last_sens_detected = 1;
    }
    else if (sensor_value2 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor2 detected!: ");
      Serial.println(sensor_value2);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 2;
      last_sens_detected = 2;
    }
    else if (sensor_value3 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor3 detected!: ");
      Serial.println(sensor_value3);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 3;
      last_sens_detected = 3;
    }
    else if (sensor_value4 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor4 detected!: ");
      Serial.println(sensor_value4);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 4;
      last_sens_detected = 4;
    }
    else if (sensor_value5 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor5 detected!: ");
      Serial.println(sensor_value5);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 5;
      last_sens_detected = 5;
    }
    else if (sensor_value6 < SENSOR_THRESHOLD_VALUE)
    {
      Serial.print("Sensor6 detected!: ");
      Serial.println(sensor_value6);
      game_stage = DELAY_FOR_NEXT;
      LEDS_LedsAllOn();
      sens_detected_flag = 1;
      current_array[array_index] = 6;
      last_sens_detected = 6;
    }

    if (sens_detected_flag)
    {
      tick = millis();
      array_index++;
      sens_detected_flag = 0;
      displayCurrentArray();
    }

    break;

  case DELAY_FOR_NEXT:
    if (last_sens_detected == 1)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR1);
    }
    else if (last_sens_detected == 2)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR2);
    }
    else if (last_sens_detected == 3)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR3);
    }
    else if (last_sens_detected == 4)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR4);
    }
    else if (last_sens_detected == 5)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR5);
    }
    else if (last_sens_detected == 6)
    {
      temp_sens_value = SENSOR_ReturnSensValue(SENSOR6);
    }

    if (millis() - tick > DELAY_BEETWEEN_STATES && temp_sens_value >= SENSOR_THRESHOLD_VALUE)
    {
      LEDS_LedsAllOff();
      game_stage = WAIT_FOR_SENS;
      tick = millis();
      
      if(checkIsGoingToSolve(array_index) == 0)
      {
        array_index = 0;
        clearCurrentArray();
      }
      else if(array_index == 7)
      {
        array_index = 0;
        clearCurrentArray();
        game_stage =  SOLVED_LED_BLINK;
      }
      Serial.print("Array id:");
      Serial.println(array_index);
      delay(1000);
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
    Serial.println("Open doors");
    game_stage = WAIT_FOR_NEXT_GAME;
    break;

  case WAIT_FOR_NEXT_GAME:
    if (DOORS_DoorsReady())
    {
      LEDS_LedsToggleAll();
      game_stage = WAIT_FOR_SENS;
      Serial.println("New game started");
    }
    break;
  default:
    break;
  }
}

void displayCurrentArray(void)
{
  Serial.print("Current array: ");
  for (uint8_t i = 0; i < 7; i++)
  {
    Serial.print(current_array[i]);
    Serial.print(", ");
  }
  Serial.println("");
}

void clearCurrentArray(void)
{
  for (uint8_t i = 0; i < 7; i++)
  {
    current_array[i] = 0;
  }
}

uint8_t checkIsGoingToSolve(uint8_t arr_id)
{
  for(uint8_t i = 0; i < arr_id; i++)
  {
    if(current_array[i] != solution_array[i])
    {
      Serial.print("Wrong position: ");
      Serial.println(i);
      return 0;
    }
  }
  return 1;
}