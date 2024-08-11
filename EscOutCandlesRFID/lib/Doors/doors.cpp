#include "Arduino.h"
#include "doors.h"

static door_state_t door_state = DOOR_IDLE;
static bool request_to_open = false;
static unsigned long last_tick;
static bool last_open_failed = false;

static void RELAY_On(void);
static void RELAY_Off(void);

void DOORS_Init(void)
{
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LOCK_STATE_PIN, INPUT);
}

void DOORS_Process(void)
{
    static uint8_t retry_counter = 0;
    switch (door_state)
    {
    case DOOR_IDLE:
        if (request_to_open)
        {
            door_state = START_OPENING;
            RELAY_On();
            last_tick = millis();
        }
        break;

    case START_OPENING:
        if (millis() - last_tick > DOOR_OPEN_TIME)
        {
            door_state = CHECK_OPEN_STATUS;
            RELAY_Off();
            last_tick = millis();
        }
        break;

    case CHECK_OPEN_STATUS:
        if (millis() - last_tick > DOOR_DEBOUNCE_TIME)
        {
            if (DOORS_AreOpen() == true)
            {
                door_state = STOP_OPENING;
            }
            else
            {
                if (retry_counter++ < 3)
                    door_state = WAIT_FOR_NEXT_OPEN;
                else
                {
                    door_state = STOP_OPENING;
                    last_open_failed = true;
                }
            }
            last_tick = millis();
        }
        break;

    case WAIT_FOR_NEXT_OPEN:
        if (millis() - last_tick > DOOR_RETRY_DELAY)
        {
            door_state = DOOR_IDLE;
        }
        break;

    case STOP_OPENING:
        if (millis() - last_tick > DOOR_NEXT_TRY_TIME)
        {
            door_state = DOOR_IDLE;
            retry_counter = 0;
            request_to_open = false;
            last_open_failed = false;
        }
        break;
    }
}

void DOORS_Open(void)
{
    request_to_open = true;
}

bool DOORS_IsLastDoorOpenFailed(void)
{
    return last_open_failed;
}

static void RELAY_On(void)
{
    digitalWrite(RELAY_PIN, HIGH);
}

static void RELAY_Off(void)
{
    digitalWrite(RELAY_PIN, LOW);
}

bool DOORS_AreOpen(void)
{
    // 1 - doors are opened
    // 0 - doors are closed
    if (digitalRead(LOCK_STATE_PIN) == HIGH)
        return true;
    else
        return false;
}