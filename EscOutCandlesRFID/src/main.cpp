#include <Arduino.h>

#include "EscOutCandles.h"
#include "doors.h"

void setup()
{
  DOORS_Init();
  digitalWrite(RELAY_PIN, HIGH);
  delay(200);
  digitalWrite(RELAY_PIN, LOW);
  EscOutCandles_Init();
  
  //DOORS_Open();
  
}

void loop()
{
  EscOutCandles_Process();
  DOORS_Process();
}


