/*
 * door.h
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

#define DOOR_OPEN_TIME 200
#define DOOR_RETRY_DELAY 750
#define DOOR_NEXT_TRY_TIME 2000
#define DOOR_DEBOUNCE_TIME 100

#include "stdbool.h"

typedef enum{
	DOOR_IDLE,
	START_OPENING,
	CHECK_OPEN_STATUS,
	WAIT_FOR_NEXT_OPEN,
	STOP_OPENING
}door_state_t;

void DOOR_Process(void);
void DOOR_Open(void);
bool DOOR_IsOpen(void);
bool DOOR_IsLastDoorOpenFailed(void);

#endif /* INC_DOOR_H_ */
