#include "Arduino.h"
#include "door.h"

static door_state_t door_state = DOOR_IDLE;
static bool request_to_open = false;
static unsigned long last_tick = 0;

void DOOR_Init(void)
{
    pinMode(OUTPUT, DOOR_PIN);
}

void DOOR_Process(void)
{
    switch (door_state)
    {
    case DOOR_IDLE:
        if (request_to_open)
        {
            digitalWrite(DOOR_PIN, HIGH);
            last_tick = millis();
            door_state = DOOR_OPEN;
            Serial.println("DOOR OPEN");
        }
        break;
    case DOOR_OPEN:
        if (millis() - last_tick > DOOR_OPEN_TIME)
        {
            digitalWrite(DOOR_PIN, LOW);
            last_tick = millis();
            door_state = DOOR_WAIT;
            Serial.println("DOOR CLOSE");
        }
        break;
    case DOOR_WAIT:
        if (millis() - last_tick > DOOR_NEXT_OPEN_TIME)
        {
            request_to_open = false;
            door_state = DOOR_IDLE;
            Serial.println("DOOR GO TO IDLE");
        }
        break;
    }
}

void DOOR_Open(void)
{
    request_to_open = true;
}

bool DOOR_ReadyToOpen(void)
{
    if (door_state == DOOR_IDLE)
        return true;
    return false;
}