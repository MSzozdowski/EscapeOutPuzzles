#ifndef door_h
#define door_h

#include <stdint.h>

#define DOOR_PIN 12
#define DOOR_OPEN_TIME 1500
#define DOOR_NEXT_OPEN_TIME 1000

typedef enum
{
    DOOR_IDLE,
	DOOR_OPEN,
	DOOR_WAIT
}door_state_t;

void DOOR_Init(void);
void DOOR_Process(void);
void DOOR_Open(void);
bool DOOR_ReadyToOpen(void);
#endif