#ifndef doors_h
#define doors_h

#define DOOR_OPEN_TIME 1000
#define DOOR_NEXT_TRY_TIME 5000

#define RELAY_PIN 12

typedef enum
{
	DOOR_INIT,
    DOOR_IDLE,
	START_OPENING,
	WAIT_FOR_NEXT_OPEN
}door_state_t;

void DOORS_Init(void);
void DOORS_Process(void);
void DOORS_Open(void);
bool DOORS_DoorsReady(void);

#endif