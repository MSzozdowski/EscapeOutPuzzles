#include <Arduino.h>
#include "microphone.h"

unsigned long tick = 0;

uint8_t array_of_samples[AVERAGE_ARRAY_SIZE] = {0};
uint8_t sample_index = 0;

uint8_t MICROPHONE_ReturnSensValue(void)
{
    uint8_t analog_read = analogRead(MICROPHONE_PIN);
    return analog_read;
}

void MICROPHONE_Process(void)
{

    if (millis() - tick > MICROPHONE_SAMPLE_INTERVAL)
    {
        tick = millis();
        uint8_t sample = MICROPHONE_ReturnSensValue();
        if (sample_index < AVERAGE_ARRAY_SIZE)
        {
            array_of_samples[sample_index] = sample;
            sample_index++;
        }
        else
        {
            sample_index = 0;
            array_of_samples[sample_index] = sample;
            sample_index++;
            Serial.print("Microphone average: ");
            Serial.println(MICROPHONE_GetAverage());
        }
    }
}

uint8_t MICROPHONE_GetAverage(void)
{
    uint16_t sum = 0;
    for (uint8_t i = 0; i < AVERAGE_ARRAY_SIZE; i++)
    {
        sum += array_of_samples[i];
    }

    uint8_t average = sum / AVERAGE_ARRAY_SIZE;
    return average;
}