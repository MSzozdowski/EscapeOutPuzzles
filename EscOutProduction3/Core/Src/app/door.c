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
static bool last_open_failed = false;
static uint32_t last_tick;

void DOOR_Process(void)
{
	static uint8_t retry_counter = 0;
	switch (door_state) {
		case DOOR_IDLE:
			if(request_to_open)
			{
				door_state = START_OPENING;
				RELAY_On();
				last_tick = HAL_GetTick();
			}
			break;

		case START_OPENING:
			if(HAL_GetTick() - last_tick > DOOR_OPEN_TIME)
			{
				door_state = CHECK_OPEN_STATUS;
				RELAY_Off();
				last_tick = HAL_GetTick();
			}
		break;

		case CHECK_OPEN_STATUS:
			if(HAL_GetTick() - last_tick > DOOR_DEBOUNCE_TIME)
			{
				if(DOOR_IsOpen() == true)
				{
					door_state = STOP_OPENING;
				}
				else
				{
					if(retry_counter++ < 3)
						door_state = WAIT_FOR_NEXT_OPEN;
					else
					{
						door_state = STOP_OPENING;
						last_open_failed = true;
					}

				}
				last_tick = HAL_GetTick();
			}
			break;

		case WAIT_FOR_NEXT_OPEN:
			if(HAL_GetTick() - last_tick > DOOR_RETRY_DELAY)
			{
				door_state = DOOR_IDLE;
			}
			break;

		case STOP_OPENING:
			if(HAL_GetTick() - last_tick > DOOR_NEXT_TRY_TIME)
			{
				door_state = DOOR_IDLE;
				retry_counter = 0;
				request_to_open = false;
				last_open_failed = false;
			}
			break;

		default:
			break;
	}
}

bool DOOR_IsOpen(void)
{
	// 1 - doors are opened
	// 0 - doors are closed
	if(HAL_GPIO_ReadPin(LOCK_STATE_GPIO_Port, LOCK_STATE_Pin) == GPIO_PIN_SET)
		return true;
	else
		return false;
}

bool DOOR_IsLastDoorOpenFailed(void)
{
	return last_open_failed;
}

void DOOR_Open(void)
{
	request_to_open = true;
}

static void RELAY_On(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY2_Pin, GPIO_PIN_SET);
}

static void RELAY_Off(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY2_Pin, GPIO_PIN_RESET);
}
