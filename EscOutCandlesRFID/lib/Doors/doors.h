#ifndef doors_h
#define doors_h

#define DOOR_OPEN_TIME 200
#define DOOR_RETRY_DELAY 750
#define DOOR_NEXT_TRY_TIME 2000
#define DOOR_DEBOUNCE_TIME 100

#define RELAY_PIN 3
#define LOCK_STATE_PIN 2

typedef enum
{
    DOOR_IDLE,
	START_OPENING,
	CHECK_OPEN_STATUS,
	WAIT_FOR_NEXT_OPEN,
	STOP_OPENING
}door_state_t;

void DOORS_Init(void);
void DOORS_Process(void);
void DOORS_Open(void);
bool DOORS_IsLastDoorOpenFailed(void);
bool DOORS_AreOpen(void);
#endif