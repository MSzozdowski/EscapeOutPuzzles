#include "Arduino.h"
#include "doors.h"

static door_state_t door_state = DOOR_INIT;
static bool request_to_open = false;
static unsigned long last_tick;

static void RELAY_On(void);
static void RELAY_Off(void);

void DOORS_Init(void)
{
    pinMode(RELAY_PIN, OUTPUT);
}

void DOORS_Process(void)
{
    switch (door_state)
    {
    case DOOR_INIT:
        RELAY_On();
        door_state = DOOR_IDLE;
    break;

    case DOOR_IDLE:
        
        if (request_to_open)
        {
            request_to_open = false;
            door_state = START_OPENING;
            RELAY_Off();
            last_tick = millis();
        }
        break;

    case START_OPENING:
        if (millis() - last_tick > DOOR_OPEN_TIME)
        {
            door_state = WAIT_FOR_NEXT_OPEN;
            RELAY_On();
            last_tick = millis();
        }
        break;

    case WAIT_FOR_NEXT_OPEN:
        if (millis() - last_tick > DOOR_NEXT_TRY_TIME)
        {
            door_state = DOOR_IDLE;
        }
        break;
    }
}

void DOORS_Open(void)
{
    request_to_open = true;
}

static void RELAY_On(void)
{
    digitalWrite(RELAY_PIN, HIGH);
}

static void RELAY_Off(void)
{
    digitalWrite(RELAY_PIN, LOW);
}