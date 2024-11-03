/*
 * metal_ball.c
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/metal_ball.h"
#include "application/cap_sensor.h"
#include "application/door.h"
#include "stdbool.h"

static void SensorCallback(void);

static metal_ball_state_t metal_ball_state;
static bool sensor_detected_flag;
static uint32_t metal_ball_tick;

void METAL_BALL_Init(void)
{
	CAP_SENSOR_Init();
	metal_ball_state = METAL_BALL_IDLE;
	CAP_SENSOR_DetectedCallback(SensorCallback);
	sensor_detected_flag = false;
}

void METAL_BALL_Process(void)
{
	CAP_SENSOR_Process();
	switch (metal_ball_state) {
		case METAL_BALL_IDLE:
			if(sensor_detected_flag == true)
			{
				metal_ball_state = METAL_BALL_DETECTED;
				metal_ball_tick = HAL_GetTick();
			}
			break;

		case METAL_BALL_DETECTED:
			if(HAL_GetTick() - metal_ball_tick > METAL_BALL_DELAY_REACTION)
			{
				DOOR_Open();
				metal_ball_state = METAL_BALL_WAIT;
				metal_ball_tick = HAL_GetTick();
			}
			break;
		case METAL_BALL_WAIT:
			if(HAL_GetTick() - metal_ball_tick > METAL_BALL_NEXT_ROUND_TIME && CAP_SENSOR_GetState() == CAP_SENS_NOT_DETECTED)
			{
				sensor_detected_flag = false;
				metal_ball_state = METAL_BALL_IDLE;
			}
			break;
	}
}

static void SensorCallback(void)
{
	if(sensor_detected_flag == false)
	{
		sensor_detected_flag = true;
		HAL_GPIO_TogglePin(DBG_LED_GPIO_Port, DBG_LED_Pin);
	}

}
