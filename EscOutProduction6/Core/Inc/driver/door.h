/*
 * door.h
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

#define DOOR_OPEN_TIME 1000
#define NEXT_DOOR_OPEN_TIME 500

#include "stdbool.h"

typedef enum {
	DOOR_IDLE,
	OPEN,
	WAIT_FOR_NEXT_OPEN,
}door_state_t;

typedef struct
{
	door_state_t door_state;
	GPIO_TypeDef 	*GpioPort;
	uint16_t 		GpioPin;
	uint32_t 		last_tick;
	bool request_to_open;
}door_t;

extern door_t door;

void DOOR_Init(door_t* door, GPIO_TypeDef *GpioPort, uint16_t GpioPin);
void DOOR_Process(door_t* door);
void DOOR_Open(door_t* door);
void DOOR_OpenPernament(door_t* door);
void DOOR_ClosePernament(door_t* door);

#endif /* INC_DOOR_H_ */
