/*
 * door.c
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#include "main.h"
#include "app/door.h"
#include "stdbool.h"

static void RELAY_On(void);
static void RELAY_Off(void);

static door_state_t door_state = DOOR_IDLE;
static bool request_to_open = false;
static uint32_t last_tick;

void DOOR_Process(void)
{
	switch (door_state) {
		case DOOR_IDLE:
			if(request_to_open == true)
			{
				RELAY_On();
				door_state = OPEN;
				last_tick = HAL_GetTick();
			}
			break;

		case OPEN:
			if(HAL_GetTick() - last_tick > DOOR_OPEN_TIME)
			{
				RELAY_Off();
				door_state = WAIT_FOR_NEXT_OPEN;
				last_tick = HAL_GetTick();
			}
		break;

		case WAIT_FOR_NEXT_OPEN:
			if(HAL_GetTick() - last_tick > NEXT_DOOR_OPEN_TIME)
			{
				request_to_open = false;
				door_state = DOOR_IDLE;
			}
		break;
	}
}

void DOOR_Open(void)
{
		request_to_open = true;
}

door_state_t DOOR_GetState(void)
{
	return door_state;
}

static void RELAY_On(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}

static void RELAY_Off(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
}
