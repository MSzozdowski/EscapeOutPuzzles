/*
 * door.c
 *
 *  Created on: 23 sie 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/door.h"
#include "stdbool.h"

static void RELAY_On(void);
static void RELAY_Off(void);
static void DOOR_ElectromagnetProcess(void);
static void DOOR_LockProcess(void);

static electromagnet_state_t electromagnet_state = ELECTROMAGNET_IDLE;
static lock_state_t lock_state = LOCK_IDLE;
static bool request_to_open = false;
static bool last_open_failed = false;
static uint32_t last_tick;

void DOOR_Process(door_type_t door_type)
{
	switch (door_type) {
		case ELECTROMAGNET:
			DOOR_ElectromagnetProcess();
			break;

		case LOCK:
			DOOR_LockProcess();
			break;
	}
}

static void DOOR_ElectromagnetProcess(void)
{
	switch (electromagnet_state) {
		case ELECTROMAGNET_IDLE:
			if(request_to_open == true)
			{
				RELAY_On();
				electromagnet_state = ELECTROMAGNET_OPEN;
				last_tick = HAL_GetTick();
			}
			break;

		case ELECTROMAGNET_OPEN:
			if(HAL_GetTick() - last_tick > ELETROMAGNET_OPEN_TIME)
			{
				RELAY_Off();
				electromagnet_state = ELECTROMAGNET_WAIT_FOR_NEXT_OPEN;
				last_tick = HAL_GetTick();
			}
		break;

		case ELECTROMAGNET_WAIT_FOR_NEXT_OPEN:
			if(HAL_GetTick() - last_tick > ELECTROMAGNET_NEXT_DOOR_OPEN_TIME)
			{
				request_to_open = false;
				electromagnet_state = ELECTROMAGNET_IDLE;
			}
		break;
	}
}

static void DOOR_LockProcess(void)
{
	static uint8_t retry_counter = 0;
	switch (lock_state) {
		case LOCK_IDLE:
			if(request_to_open)
			{
				lock_state = LOCK_START_OPENING;
				RELAY_On();
				last_tick = HAL_GetTick();
			}
			break;

		case LOCK_START_OPENING:
			if(HAL_GetTick() - last_tick > LOCK_OPEN_TIME)
			{
				lock_state = LOCK_CHECK_OPEN_STATUS;
				RELAY_Off();
				last_tick = HAL_GetTick();
			}
		break;

		case LOCK_CHECK_OPEN_STATUS:
			if(HAL_GetTick() - last_tick > LOCK_DEBOUNCE_TIME)
			{
				if(DOOR_IsOpen() == true)
				{
					lock_state = LOCK_STOP_OPENING;
				}
				else
				{
					if(retry_counter++ < 3)
						lock_state = LOCK_WAIT_FOR_NEXT_OPEN;
					else
					{
						lock_state = LOCK_STOP_OPENING;
						last_open_failed = true;
					}

				}
				last_tick = HAL_GetTick();
			}
			break;

		case LOCK_WAIT_FOR_NEXT_OPEN:
			if(HAL_GetTick() - last_tick > LOCK_RETRY_DELAY)
			{
				lock_state = LOCK_IDLE;
			}
			break;

		case LOCK_STOP_OPENING:
			if(HAL_GetTick() - last_tick > LOCK_NEXT_TRY_TIME)
			{
				lock_state = LOCK_IDLE;
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
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}

static void RELAY_Off(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
}
