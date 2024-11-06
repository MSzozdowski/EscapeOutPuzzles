#include <Arduino.h>
#include "reed_switch.h"
#include "doors.h"
#include "leds.h"

#include "stdint.h"

#define D12 12
#define D11 11
#define D10 10
#define D9 9
#define D8 8
#define D7 7
#define D6 6
#define D5 5

void ReedSwCallback(reed_sw* reed_sw);

reed_sw reed_sw1;
reed_sw reed_sw2;
reed_sw reed_sw3;
reed_sw reed_sw4;
reed_sw reed_sw5;
reed_sw reed_sw6;
reed_sw reed_sw7;
reed_sw reed_sw8;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  LEDS_Init(LED_BUILTIN);

  for(uint8_t i = D5; i <= D12; i++)
  {pinMode(i, INPUT_PULLUP);}

 // REED_SW_Init(&reed_sw1, D12, 1);
 // REED_SW_Init(&reed_sw2, D11, 2);
  REED_SW_Init(&reed_sw3, D10, 3);
  REED_SW_Init(&reed_sw4, D9, 4);
  REED_SW_Init(&reed_sw5, D8, 5);
  REED_SW_Init(&reed_sw6, D7, 6);
  REED_SW_Init(&reed_sw7, D6, 7);
  REED_SW_Init(&reed_sw8, D5, 8);
  
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
}

void ReedSwCallback(reed_sw* reed_sw)
{
    Serial.print("Reed switch selected: ");
    Serial.println(reed_sw ->reed_sw_id);
    LEDS_LedToggle(LED_BUILTIN);
}