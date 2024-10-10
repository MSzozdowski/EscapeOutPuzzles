/*
 * door.c
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#include "main.h"
#include "driver/door.h"
#include "stdbool.h"

static void RELAY_On(door_t* door);
static void RELAY_Off(door_t* door);

void DOOR_Init(door_t* door, GPIO_TypeDef *GpioPort, uint16_t GpioPin)
{
	door->door_state = DOOR_IDLE;
	door->GpioPort = GpioPort;
	door->GpioPin = GpioPin;
	door->request_to_open = false;
}

void DOOR_Process(door_t* door)
{
	switch (door->door_state) {
		case DOOR_IDLE:
			if(door->request_to_open == true)
			{
				RELAY_On(door);
				door->door_state = OPEN;
				door->last_tick = HAL_GetTick();
			}
			break;

		case OPEN:
			if(HAL_GetTick() - door->last_tick > DOOR_OPEN_TIME)
			{
				RELAY_Off(door);
				door->door_state = WAIT_FOR_NEXT_OPEN;
				door->last_tick = HAL_GetTick();
			}
		break;

		case WAIT_FOR_NEXT_OPEN:
			if(HAL_GetTick() - door->last_tick > NEXT_DOOR_OPEN_TIME)
			{
				door->request_to_open = false;
				door->door_state = DOOR_IDLE;
			}
		break;
	}
}

void DOOR_Open(door_t* door)
{
	door->request_to_open = true;
}

void DOOR_OpenPernament(door_t* door)
{
	RELAY_On(door);
}

void DOOR_ClosePernament(door_t* door)
{
	RELAY_Off(door);
}

static void RELAY_On(door_t* door)
{
	HAL_GPIO_WritePin(door->GpioPort, door->GpioPin, GPIO_PIN_SET);
}

static void RELAY_Off(door_t* door)
{
	HAL_GPIO_WritePin(door->GpioPort, door->GpioPin, GPIO_PIN_RESET);
}
