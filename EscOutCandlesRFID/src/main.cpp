#include <Arduino.h>

#include "EscOutCandles.h"
#include "doors.h"

void setup()
{
  EscOutCandles_Init();
  DOORS_Init();
  DOORS_Open();
}

void loop()
{
  EscOutCandles_Process();
  DOORS_Process();
}


