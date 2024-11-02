#ifndef sensors_h
#define sensors_h

#include <stdint.h>

#define SENSOR1 A3
#define SENSOR2 A2
#define SENSOR3 A1
#define SENSOR4 A0
#define SENSOR5 A5
#define SENSOR6 A4

#define SENSOR_THRESHOLD_VALUE 50

uint8_t SENSOR_ReturnSensValue(uint8_t sens_no);

#endif