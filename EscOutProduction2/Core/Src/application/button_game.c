/*
 * button_game.c
 *
 *  Created on: Oct 16, 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/button_game.h"
#include "application/button.h"
#include "application/buzzer.h"
#include "application/door.h"
#include "stdbool.h"

static void ButtonPressed(void);

static button_game_state_t button_game_state;
static volatile bool button_press_flag;
static uint32_t button_game_tick;

void BUTTON_GAME_Init(void)
{
	BUTTON_LED_Init();
	BUTTON_PressCallback(ButtonPressed);
	button_game_state = BUTTON_IDLE;
	button_press_flag = false;
}

void BUTTON_GAME_Process(void)
{
	BUTTON_LED_Process();
	switch (button_game_state) {
		case BUTTON_GAME_IDLE:
			if(button_press_flag == true)
				button_game_state = BUTTON_GAME_PRESSED;
			break;

		case BUTTON_GAME_PRESSED:
			BUTTON_LED_SetState(LED_THREE_BLINKS);
			button_game_state = BUTTON_GAME_DOOR_OPEN;
			BUZZER_Go(TBUZ_600, TICK_6, BUZZ_DEL_600, BUZZER_FREQ_HIGH);
			button_game_tick = HAL_GetTick();
			break;

		case BUTTON_GAME_DOOR_OPEN:
			if(BUTTON_LED_GetLEDState() == LED_OFF)
			{
				button_game_state = BUTTON_GAME_WAIT;
				DOOR_Open();
				BUTTON_LED_SetState(LED_ON);
			}
			break;

		case BUTTON_GAME_WAIT:
			if(HAL_GetTick() - button_game_tick > NEXT_ROUND_TIME && BUTTON_LED_GetButtonState() == BUTTON_IDLE)
			{
				button_game_state = BUTTON_GAME_IDLE;
				BUTTON_LED_SetState(LED_CONT_SHORT_BLINK);
				button_press_flag = false;
			}
			break;
	}
}

static void ButtonPressed(void)
{
	if(button_press_flag == false)
	{
		HAL_GPIO_TogglePin(DBG_LED_GPIO_Port, DBG_LED_Pin);
		button_press_flag = true;
	}
}
