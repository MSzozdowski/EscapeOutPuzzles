/*
 * door.c
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#include "main.h"
#include "door.h"
#include "stdbool.h"

static door_state_t door_state = DOOR_IDLE;
static bool request_to_open = false;
static uint32_t last_tick;

static void RELAY_On(void);
static void RELAY_Off(void);

void DOOR_Process(void)
{
	switch (door_state) {
		case DOOR_IDLE:
			if(request_to_open)
			{
				door_state = START_OPENING;
				RELAY_On();
				request_to_open = false;
				last_tick = HAL_GetTick();
			}
			break;

		case START_OPENING:
			if(HAL_GetTick() - last_tick > DOOR_OPEN_TIME)
			{
				door_state = STOP_OPENING;
				RELAY_Off();
				last_tick = HAL_GetTick();
			}
		break;

		case STOP_OPENING:
			if(HAL_GetTick() - last_tick > DOOR_NEXT_TRY_TIME)
			{
				door_state = DOOR_IDLE;
			}
			break;

		default:
			break;
	}
}

void DOOR_Open(void)
{
	request_to_open = true;
}

static void RELAY_On(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
}

static void RELAY_Off(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}
