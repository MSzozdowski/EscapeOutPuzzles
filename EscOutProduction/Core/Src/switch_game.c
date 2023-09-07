/*
 * switch_game.c
 *
 *  Created on: Sep 4, 2023
 *      Author: stasz
 */

#include "main.h"
#include "switch_game.h"
#include "button.h"
#include "buzzer.h"
#include "door.h"
//Callbacks
static void AddToCounter(void);
static void ResetCounter(void);

button_t button_red;
button_t button_green;
button_t button_blue;
button_t button_yellow;

static switch_game_state_t switch_game_state = SWITCH_GAME_INIT;

static volatile uint8_t positive_press_counter = 0;

//uint8_t const rand_array[RAND_ARRAY_SIZE] = {0, 1, 2, 3, 0, 1, 2, 3 , 0, 1, 2, 3};
uint8_t const rand_array[RAND_ARRAY_SIZE] = {0, 3, 0, 1, 3, 2, 0, 2, 3, 2, 1, 0};
static uint8_t rand_index = 0;
static uint32_t last_tick = 0;

static volatile uint32_t solve_tick = 0;

void SWITCH_GAME_Init(void)
{
	BUTTON_Init(&button_red, SW_RED_GPIO_Port, SW_RED_Pin, RED_LED_GPIO_Port, RED_LED_Pin);
	BUTTON_Init(&button_green, SW_GREEN_GPIO_Port, SW_GREEN_Pin, GREEN_LED_GPIO_Port, GREEN_LED_Pin);
	BUTTON_Init(&button_blue, SW_BLUE_GPIO_Port, SW_BLUE_Pin, BLUE_LED_GPIO_Port, BLUE_LED_Pin);
	BUTTON_Init(&button_yellow, SW_YELLOW_GPIO_Port, SW_YELLOW_Pin, YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);

	BUTTON_RegisterPositivePressCallBack(&button_red, AddToCounter);
	BUTTON_RegisterPositivePressCallBack(&button_green, AddToCounter);
	BUTTON_RegisterPositivePressCallBack(&button_blue, AddToCounter);
	BUTTON_RegisterPositivePressCallBack(&button_yellow, AddToCounter);

	BUTTON_RegisterNegativePressCallBack(&button_red, ResetCounter);
	BUTTON_RegisterNegativePressCallBack(&button_green, ResetCounter);
	BUTTON_RegisterNegativePressCallBack(&button_blue, ResetCounter);
	BUTTON_RegisterNegativePressCallBack(&button_yellow, ResetCounter);
}

static void SWITCH_GAME_Initialization(void)
{
	static uint8_t stage = 0;
	switch (stage) {
		case 0:
			BUTTON_LED_SetState(&button_red, BUTTON_LED_THREE_FAST_BLINKS);
			BUTTON_LED_SetState(&button_green, BUTTON_LED_THREE_FAST_BLINKS);
			BUTTON_LED_SetState(&button_blue, BUTTON_LED_THREE_FAST_BLINKS);
			BUTTON_LED_SetState(&button_yellow, BUTTON_LED_THREE_FAST_BLINKS);
			stage = 1;
			break;

		case 1:
			if(button_red.button_led_state == BUTTON_LED_IDLE
					&& button_green.button_led_state == BUTTON_LED_IDLE
					&& button_blue.button_led_state == BUTTON_LED_IDLE
					&& button_yellow.button_led_state == BUTTON_LED_IDLE)
			{
				stage = 0;
				last_tick = HAL_GetTick();
				switch_game_state = SWITCH_GAME_PROCESS;
			}
			break;
	}
}

static void SWITCH_GAME_Finish(void)
{
	static uint8_t stage = 0;
	switch (stage) {
			case 0:
				if(button_red.button_led_state == BUTTON_LED_IDLE
						&& button_green.button_led_state == BUTTON_LED_IDLE
						&& button_blue.button_led_state == BUTTON_LED_IDLE
						&& button_yellow.button_led_state == BUTTON_LED_IDLE)
				{
					BUTTON_LED_SetState(&button_red, BUTTON_LED_BLINK);
					BUTTON_LED_SetState(&button_green, BUTTON_LED_BLINK);
					BUTTON_LED_SetState(&button_blue, BUTTON_LED_BLINK);
					BUTTON_LED_SetState(&button_yellow, BUTTON_LED_BLINK);
					BUZZER_Go(TBUZ_500, TICK_5, BUZZ_DEL_500, BUZZER_FREQ_HIGH);
					stage = 1;
				}
				break;

			case 1:
				if(button_red.button_led_state == BUTTON_LED_IDLE
						&& button_green.button_led_state == BUTTON_LED_IDLE
						&& button_blue.button_led_state == BUTTON_LED_IDLE
						&& button_yellow.button_led_state == BUTTON_LED_IDLE)
				{
					BUTTON_LED_SetState(&button_red, BUTTON_LED_ON);
					BUTTON_LED_SetState(&button_green, BUTTON_LED_ON);
					BUTTON_LED_SetState(&button_blue, BUTTON_LED_ON);
					BUTTON_LED_SetState(&button_yellow, BUTTON_LED_ON);
					stage = 2;
					last_tick = HAL_GetTick();
					DOOR_Open();
				}
				break;

			case 2:
				if(HAL_GetTick() - last_tick > CHECK_DOOR_STATUS_DELAY)
				{
					if(DOOR_IsOpen() == false)
					{
						stage = 0;
						switch_game_state = SWITCH_GAME_INIT;
					}
				}
				break;
	}
}

void SWITCH_GAME_Process(void)
{
	BUTTON_Process(&button_red);
	BUTTON_Process(&button_green);
	BUTTON_Process(&button_blue);
	BUTTON_Process(&button_yellow);

	switch (switch_game_state) {
		case SWITCH_GAME_INIT:
			SWITCH_GAME_Initialization();
			break;

		case SWITCH_GAME_PROCESS:
			if(button_red.button_led_state == BUTTON_LED_IDLE
					&& button_green.button_led_state == BUTTON_LED_IDLE
					&& button_blue.button_led_state == BUTTON_LED_IDLE
					&& button_yellow.button_led_state == BUTTON_LED_IDLE)
			{
			  if(rand_array[rand_index] == 0)
				  BUTTON_LED_SetState(&button_red, BUTTON_LED_BLINK);
			  else if(rand_array[rand_index] == 1)
				  BUTTON_LED_SetState(&button_green, BUTTON_LED_BLINK);
			  else if(rand_array[rand_index] == 2)
				  BUTTON_LED_SetState(&button_blue, BUTTON_LED_BLINK);
			  else if(rand_array[rand_index] == 3)
				  BUTTON_LED_SetState(&button_yellow, BUTTON_LED_BLINK);
			  rand_index++;
			  rand_index=rand_index%RAND_ARRAY_SIZE;
			}
			break;

		case SWITCH_GAME_FINISH:
				SWITCH_GAME_Finish();
			break;
	}
}

void AddToCounter(void)
{
	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	if(switch_game_state == SWITCH_GAME_PROCESS)
	{
		BUZZER_Go(TBUZ_200, TICK_0, BUZZ_DEL_0, BUZZER_FREQ_HIGH);
		if(positive_press_counter++ >= 3)
		{
			switch_game_state = SWITCH_GAME_FINISH;
			positive_press_counter = 0;
			solve_tick = HAL_GetTick();
		}
	}
}

void ResetCounter(void)
{

	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	if(switch_game_state == SWITCH_GAME_PROCESS)
	{
		BUZZER_Go(TBUZ_500, TICK_0, BUZZ_DEL_0, BUZZER_FREQ_LOW);
		positive_press_counter = 0;
	}
}
