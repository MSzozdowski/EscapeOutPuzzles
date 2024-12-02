#include "Arduino.h"
#include "sensors_ir.h"
#include "door.h"

static sensors_state_t sensors_state = SENSORS_READY;
static uint8_t s1, s2, s3, s4;

void SENSORS_Process(void)
{
    switch (sensors_state)
    {
    case SENSORS_READY:
        s1 = analogRead(A7);
        s2 = analogRead(A6);
        s3 = analogRead(A5);
        s4 = analogRead(A4);
        if ((s1 < SENSOR_THRESHOLD || s2 < SENSOR_THRESHOLD || s3 < SENSOR_THRESHOLD || s4 < SENSOR_THRESHOLD))
        {
            sensors_state = SENSORS_DETECTED;
            DOOR_Open();
            if (s1 < SENSOR_THRESHOLD)
            {
                Serial.print("S1 detected! Value: ");
                Serial.println(s1);
            }

            if (s2 < SENSOR_THRESHOLD)
            {
                Serial.print("S2 detected! Value: ");
                Serial.println(s2);
            }

            if (s3 < SENSOR_THRESHOLD)
            {
                Serial.print("S3 detected! Value: ");
                Serial.println(s3);
            }

            if (s4 < SENSOR_THRESHOLD)
            {
                Serial.print("S4 detected! Value: ");
                Serial.println(s4);
            }
        }
        break;

    case SENSORS_DETECTED:
        if (DOOR_ReadyToOpen())
        {
            sensors_state = SENSORS_READY;
        }
        break;
    }
}