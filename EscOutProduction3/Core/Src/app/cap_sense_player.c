/*
 * cap_sense_player.c
 *
 *  Created on: 2 gru 2023
 *      Author: stasz
 */

#include "main.h"
#include "usart.h"
#include "app/cap_sense_player.h"
#include "app/cap_sensor.h"
#include "app/dfplayer.h"
#include "app/door.h"
#include "stdbool.h"

static void SensorCallback(void);
static void LightOn(void);

static cap_sense_player_state_t cap_sense_player_state = CAP_SENSE_PLAYER_INIT;

static volatile bool cap_sense_touched = false;


void CAP_SENSE_PLAYER_Init(void)
{
	CAP_SENSOR_Init();
	CAP_SENSOR_DetectedCallback(SensorCallback);
	DFPLAYER_Init(&huart2);
	LightOn();
}

void CAP_SENSE_PLAYER_Process(void)
{
	CAP_SENSOR_Process();

	static uint32_t stage_tick = 0;
	static uint32_t last_touch_tick = 0;

	switch (cap_sense_player_state) {
		case CAP_SENSE_PLAYER_INIT:
			if(cap_sense_touched)
			{
				cap_sense_touched = false;
				cap_sense_player_state = CAP_SENSE_PLAYER_STAGE_1;
				DFPLAYER_Play(0x01);
				last_touch_tick = HAL_GetTick();
				stage_tick = HAL_GetTick();
			}
			break;

		case CAP_SENSE_PLAYER_STAGE_1:
			if(cap_sense_touched)
			{
				cap_sense_touched = false;
				last_touch_tick = HAL_GetTick();
			}

			if(HAL_GetTick() - last_touch_tick > MAX_TOUCH_INTERVAL)
			{
				DFPLAYER_Stop();
				cap_sense_player_state = CAP_SENSE_PLAYER_INIT;
			}

			if(HAL_GetTick() - stage_tick > STAGE_1_DURATION)
			{
				DFPLAYER_Play(0x02);
				cap_sense_player_state = CAP_SENSE_PLAYER_STAGE_2;
			}
			break;

		case CAP_SENSE_PLAYER_STAGE_2:
			if(cap_sense_touched)
			{
				cap_sense_touched = false;
				last_touch_tick = HAL_GetTick();
			}

			if(HAL_GetTick() - last_touch_tick > MAX_TOUCH_INTERVAL)
			{
				DFPLAYER_Stop();
				cap_sense_player_state = CAP_SENSE_PLAYER_INIT;
			}

			if(HAL_GetTick() - stage_tick > STAGE_2_DURATION)
			{
				DFPLAYER_Stop();
				cap_sense_player_state = CAP_SENSE_PLAYER_OPEN_DOOR;
				stage_tick = HAL_GetTick();
			}
			break;
		case CAP_SENSE_PLAYER_OPEN_DOOR:
			if(HAL_GetTick() - stage_tick > DOOR_OPEN_DELAY)
			{
				DOOR_Open();
				cap_sense_player_state = CAP_SENS_WAIT_NEXT_GAME;
				stage_tick = HAL_GetTick();
			}
			break;
		case CAP_SENS_WAIT_NEXT_GAME:
			if(HAL_GetTick() - stage_tick > NEXT_GAME_DELAY)
			{
				cap_sense_touched = false;
				cap_sense_player_state = CAP_SENSE_PLAYER_INIT;
			}
			break;
	}
}

static void SensorCallback(void)
{
	cap_sense_touched = true;
	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
}

static void LightOn(void)
{
	HAL_GPIO_WritePin(LIGHT_GPIO_Port, LIGHT_Pin, GPIO_PIN_SET);
}
