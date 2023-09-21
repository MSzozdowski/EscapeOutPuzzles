/*
 * knocking.c
 *
 *  Created on: Aug 24, 2023
 *      Author: stasz
 */

#include "main.h"
#include "adc.h"
#include "application/knocking.h"
#include "application/piezo.h"
#include "application/door.h"

static knocking_state_t knocking_state;
static uint16_t piezo_value = 0;
static uint8_t knock_counter = 1;
static uint32_t last_tick;
static uint32_t start_tick_time;

void KNOCKING_Init(void)
{
	 PIEZO_Init(&hadc1, ADC_CHANNEL_0);
	 knocking_state = KNOCKING_IDLE;
	 last_tick = HAL_GetTick();
}

void KNOCKING_Process(void)
{
	switch (knocking_state) {
		case KNOCKING_IDLE:
			piezo_value = PIEZO_GetMillivolts();
			if(piezo_value > PIEZO_THRESHOLD)
			{
				knocking_state = START_KNOCKING;
				knock_counter++;
				last_tick = HAL_GetTick();
				start_tick_time = HAL_GetTick();
			}
			break;

		case START_KNOCKING:
			piezo_value = PIEZO_GetMillivolts();
			if(HAL_GetTick() - start_tick_time < KNOCK_MAX_SEQUENCE_TIME)
			{
				if(piezo_value > PIEZO_THRESHOLD && ((HAL_GetTick() - last_tick) > KNOCK_INTERVAL))
				{
					HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
					if(knock_counter >= KNOCK_SOLVE_VALUE)
					{
						knocking_state = FINISH_KNOCKING;
						DOOR_Open();
					}
					knock_counter++;
					last_tick = HAL_GetTick();
				}
			}
			else
			{
				knocking_state = KNOCKING_FAILED;
				last_tick = HAL_GetTick();
			}
			break;

		case KNOCKING_FAILED:
			if(HAL_GetTick() - last_tick > FAIL_DELAY)
			{
				knocking_state = KNOCKING_IDLE;
				knock_counter = 1;
			}
			break;

		case FINISH_KNOCKING:
			//if(HAL_GetTick() - last_tick > NEXT_ROUND_DELAY)
			if(HAL_GetTick() - last_tick > CHECK_DOOR_STATUS_DELAY)
			{
				if(DOOR_IsOpen() == false)
				{
					knocking_state = KNOCKING_IDLE;
					knock_counter = 1;
				}
			}
			break;
	}
}
