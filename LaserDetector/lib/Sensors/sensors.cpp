#include <Arduino.h>
#include "sensors.h"

uint8_t SENSOR_ReturnSensValue(uint8_t sens_no)
{
    uint8_t analog_read = analogRead(sens_no);
    return analog_read;    
}