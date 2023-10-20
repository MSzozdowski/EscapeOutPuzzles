/*
 * door.h
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

#define DOOR_OPEN_TIME 500
#define NEXT_DOOR_OPEN_TIME 500

#include "stdbool.h"

typedef enum{
	DOOR_IDLE,
	OPEN,
	WAIT_FOR_NEXT_OPEN,
}door_state_t;

void DOOR_Process(void);
void DOOR_Open(void);

#endif /* INC_DOOR_H_ */
