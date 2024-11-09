#include <Arduino.h>
#include "reed_switch.h"
#include "doors.h"
#include "led.h"

#include "stdint.h"

#define D12 12
#define D11 11
#define D10 10
#define D9 9
#define D8 8
#define D7 7
#define D6 6
#define D5 5
#define LED 4

#define NUMBER_OF_REED_SW 8

void ReedSwCallback(reed_sw* reed_sw);
void PrintGameArray(void);
void ClearGameArray(void);

reed_sw reed_sw1;
reed_sw reed_sw2;
reed_sw reed_sw3;
reed_sw reed_sw4;
reed_sw reed_sw5;
reed_sw reed_sw6;
reed_sw reed_sw7;
reed_sw reed_sw8;


uint8_t solution_array[NUMBER_OF_REED_SW] = {6, 4, 2, 5, 7, 8, 1, 3};
uint8_t game_array[NUMBER_OF_REED_SW] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  LED_Init(LED);

  for(uint8_t i = D5; i <= D12; i++)
  {pinMode(i, INPUT_PULLUP);}

  REED_SW_Init(&reed_sw1, D9, 1);
  REED_SW_Init(&reed_sw2, D10, 2);
  REED_SW_Init(&reed_sw3, D11, 3);
  REED_SW_Init(&reed_sw4, D12, 4);
  REED_SW_Init(&reed_sw5, D5, 5);
  REED_SW_Init(&reed_sw6, D6, 6);
  REED_SW_Init(&reed_sw7, D7, 7);
  REED_SW_Init(&reed_sw8, D8, 8);
  
  ReedSwitchCallBack(ReedSwCallback);
  DOORS_Init();
}

void loop() {
	REED_SW_Process(&reed_sw1);
	REED_SW_Process(&reed_sw2);
	REED_SW_Process(&reed_sw3);
	REED_SW_Process(&reed_sw4);
  REED_SW_Process(&reed_sw5);
	REED_SW_Process(&reed_sw6);
	REED_SW_Process(&reed_sw7);
	REED_SW_Process(&reed_sw8);
  DOORS_Process();
  LED_Process();
}

void ReedSwCallback(reed_sw* reed_sw)
{
    Serial.print("Reed switch selected: ");
    Serial.println(reed_sw ->reed_sw_id);
    LED_SetState(LED_SHORT_BLINK);

    static uint8_t array_index = 0;

    game_array[array_index] = reed_sw ->reed_sw_id;

    if(game_array[array_index] == solution_array[array_index])
    {
      Serial.println("Good reed switch - increase index");
      array_index++;

      if(array_index == NUMBER_OF_REED_SW)
      {
        Serial.println("Solved, open the door and reset");
        DOORS_Open();
        ClearGameArray();
        array_index = 0;
      }
    }
    else
    {
      Serial.println("Wrong reed switch - clear array");
      ClearGameArray();
      array_index = 0;
    }

    PrintGameArray();
}

void PrintGameArray(void)
{
  Serial.print("Game array: ");
  for(uint8_t i = 0; i < NUMBER_OF_REED_SW; i++)
  {
    Serial.print(game_array[i]);
  }
  Serial.println("");
}

void ClearGameArray(void)
{
  for(uint8_t i = 0; i < NUMBER_OF_REED_SW; i++)
  {
    game_array[i] = 0;
  }
}