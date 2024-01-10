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

static void ButtonPressed(void);

static void SensDetected(distance_sens_t* distance_sens);
//static void SensReleased(distance_sens_t* distance_sens);

static toy_pulling_state_t toy_pulling_state = TOY_PULLING_IDLE;

static door_t toy;
static door_t door_puzzle;

static distance_sens_t distance_sens;

static volatile bool distance_sens_detected_flag = false;
static volatile bool distance_sens_released_flag = false;
static volatile bool button_pressed_flag = false;

void TOY_PULLING_Init(void)
{
	BUTTON_LED_Init();
	BUTTON_PressCallback(ButtonPressed);

	DOOR_Init(&toy, RELAY2_GPIO_Port, RELAY2_Pin);
	DOOR_Init(&door_puzzle, RELAY1_GPIO_Port, RELAY1_Pin);

	DISTANCE_SENS_Init(&distance_sens, DISTANCE_SENS_GPIO_Port, DISTANCE_SENS_Pin, 1);
	DistanceSensDetectedCallback(SensDetected);
//	DistanceSensReleasedCallback(SensReleased);

	if(reset_cause_get() == RESET_CAUSE_EXTERNAL_RESET_PIN_RESET)
	{
		DOOR_Open(&toy);
		DOOR_Open(&door_puzzle);
	}
}

void TOY_PULLING_Process(void)
{
	BUTTON_LED_Process();
	DOOR_Process(&toy);
	DOOR_Process(&door_puzzle);
	DISTANCE_SENS_Process(&distance_sens);

	static uint32_t tick;
	switch (toy_pulling_state) {
		case TOY_PULLING_IDLE:
			if(distance_sens_detected_flag == true)
			{
				button_pressed_flag = false;
				distance_sens_detected_flag = false;
				tick = HAL_GetTick();
				toy_pulling_state = TOY_PULLING_SENS_DETECTED;
			}
			break;
		case TOY_PULLING_SENS_DETECTED:
			if(HAL_GetTick() - tick > TOY_PULLING_OPEN_DELAY)
			{
				//DOOR_Open(&door_puzzle);
				DOOR_OpenPernament(&door_puzzle);
				toy_pulling_state = TOY_PULLING_WAIT;
			}
			break;

		case TOY_PULLING_WAIT:
			if(button_pressed_flag == true)
			{
				DOOR_ClosePernament(&door_puzzle);
				//distance_sens_released_flag = false;
				toy_pulling_state = TOY_PULLING_IDLE;
			}
			break;
	}
}

static void ButtonPressed(void)
{
	DOOR_Open(&toy);
	DOOR_Open(&door_puzzle);
	BUTTON_LED_SetState(LED_THREE_BLINKS);
	button_pressed_flag = true;
}

static void SensDetected(distance_sens_t* distance_sens)
{
	distance_sens_detected_flag = true;
}

//static void SensReleased(distance_sens_t* distance_sens)
//{
//	distance_sens_released_flag = true;
//}
