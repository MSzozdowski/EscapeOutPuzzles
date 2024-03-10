#include <Arduino.h>

#include "door.h"
#include "sensors_ir.h"

//#include "avr8-stub.h"
//#include "app_api.h"

void setup()
{
 // debug_init();
  
  Serial.begin(9600);
  while(!Serial);

  DOOR_Init();
  pinMode(3, OUTPUT);
  Serial.println("Game initialized");
}

void loop()
{
  DOOR_Process();
  SENSORS_Process();
}
