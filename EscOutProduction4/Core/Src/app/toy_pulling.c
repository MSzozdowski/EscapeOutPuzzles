/*
 * toy_pulling.c
 *
 *  Created on: Dec 10, 2023
 *      Author: stasz
 */

#include "main.h"
#include "app/toy_pulling.h"
#include "app/button.h"
#include "app/door.h"
#include "app/distance_sens.h"
#include "app/reset.h"

static void SensDetected(distance_sens_t* distance_sens);
static void SensReleased(distance_sens_t* distance_sens);

static toy_pulling_state_t toy_pulling_state = TOY_PULLING_IDLE;

//static door_t toy;
static door_t door_puzzle;

static distance_sens_t distance_sens;

static volatile bool distance_sens_detected_flag = false;
static volatile bool distance_sens_released_flag = false;

void TOY_PULLING_Init(void)
{
	BUTTON_LED_Init();

	DOOR_Init(&door_puzzle, RELAY1_GPIO_Port, RELAY1_Pin);

	DISTANCE_SENS_Init(&distance_sens, DISTANCE_SENS_GPIO_Port, DISTANCE_SENS_Pin, 1);
	DistanceSensDetectedCallback(SensDetected);
	DistanceSensReleasedCallback(SensReleased);
	if(reset_cause_get() == RESET_CAUSE_EXTERNAL_RESET_PIN_RESET)
	{
		DOOR_Open(&door_puzzle);
	}
}

void TOY_PULLING_Process(void)
{
	DOOR_Process(&door_puzzle);
	DISTANCE_SENS_Process(&distance_sens);

	static uint32_t tick;
	switch (toy_pulling_state) {
		case TOY_PULLING_IDLE:
			if(distance_sens_detected_flag == true)
			{
				distance_sens_detected_flag = false;
				distance_sens_released_flag = false;
				tick = HAL_GetTick();
				toy_pulling_state = TOY_PULLING_SENS_DETECTED;
			}
			break;

		case TOY_PULLING_SENS_DETECTED:
			if(HAL_GetTick() - tick > TOY_PULLING_OPEN_DELAY)
			{
				DOOR_Open(&door_puzzle);
				toy_pulling_state = TOY_PULLING_WAIT;
				tick = HAL_GetTick();
			}
			break;

		case TOY_PULLING_WAIT:
			if(HAL_GetTick() - tick > TOY_PULLING_NEXT_GAME_DELAY)
			{
				toy_pulling_state = TOY_PULLING_IDLE;
			}
			break;
	}
}

static void SensDetected(distance_sens_t* distance_sens)
{
	distance_sens_detected_flag = true;
}

static void SensReleased(distance_sens_t* distance_sens)
{
	distance_sens_released_flag = true;
}
