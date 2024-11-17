#ifndef microphone_h
#define microphone_h

#include <stdint.h>

#define MICROPHONE_PIN A0

#define AVERAGE_ARRAY_SIZE 10
#define MICROPHONE_SAMPLE_INTERVAL 100

uint8_t MICROPHONE_ReturnSensValue(void);
void MICROPHONE_Process(void);
uint8_t MICROPHONE_GetAverage(void);

#endif