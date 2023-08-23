/*
 * door.h
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

#define DOOR_OPEN_TIME 1000
#define DOOR_NEXT_TRY_TIME 1000

typedef enum{
	DOOR_IDLE,
	START_OPENING,
	STOP_OPENING
}door_state_t;

void DOOR_Process(void);
void DOOR_Open(void);

#endif /* INC_DOOR_H_ */
