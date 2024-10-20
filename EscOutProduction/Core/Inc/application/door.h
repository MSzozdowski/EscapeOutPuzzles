/*
 * door.h
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

#define LOCK_OPEN_TIME 200
#define LOCK_RETRY_DELAY 750
#define LOCK_NEXT_TRY_TIME 2000
#define LOCK_DEBOUNCE_TIME 100

#define ELETROMAGNET_OPEN_TIME 750
#define ELECTROMAGNET_NEXT_DOOR_OPEN_TIME 2000

#include "stdbool.h"
typedef enum
{
	ELECTROMAGNET,
	LOCK
}door_type_t;

typedef enum
{
	LOCK_IDLE,
	LOCK_START_OPENING,
	LOCK_CHECK_OPEN_STATUS,
	LOCK_WAIT_FOR_NEXT_OPEN,
	LOCK_STOP_OPENING
}lock_state_t;

typedef enum
{
	ELECTROMAGNET_IDLE,
	ELECTROMAGNET_OPEN,
	ELECTROMAGNET_WAIT_FOR_NEXT_OPEN
}electromagnet_state_t;

void DOOR_Process(door_type_t door_type);
void DOOR_Open(void);
bool DOOR_IsOpen(void);
bool DOOR_IsLastDoorOpenFailed(void);

#endif /* INC_DOOR_H_ */
