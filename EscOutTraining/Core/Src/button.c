/*
 * button.c
 *
 *  Created on: Aug 26, 2023
 *      Author: stasz
 */

#include "main.h"
#include "button.h"
#include "gpio.h"
#include "buzzer.h"

static GPIO_PinState BUTTON_GetSWState(button_t* button);
static void BUTTON_LED_SetPinState(button_t* button, led_state_t pin_state);
static void BUTTON_LED_Process(button_t* button);

void BUTTON_Init(button_t* button, GPIO_TypeDef* SW_Port, uint16_t SW_Pin, GPIO_TypeDef* LED_Port, uint16_t LED_Pin)
{
	button->button_state = BUTTON_IDLE;
	button->button_led_state = BUTTON_LED_OFF;
	button->button_press_flag = BUTTON_WAS_NOT_PRESSED;
	button->SW_Port = SW_Port;
	button->SW_Pin = SW_Pin;
	button->LED_Port = LED_Port;
	button->LED_Pin = LED_Pin;
}

void BUTTON_Process(button_t* button)
{
	BUTTON_LED_Process(button);
	switch (button->button_state) {
		case BUTTON_IDLE:
			if(BUTTON_GetSWState(button) == GPIO_PIN_RESET)
			{
				button->button_state = BUTTON_DEBOUNCE;
				button->button_last_tick = HAL_GetTick();
			}
			break;

		case BUTTON_DEBOUNCE:
			if(HAL_GetTick() - button->button_last_tick > DEBOUNCE_TIME)
			{
				if(BUTTON_GetSWState(button) == GPIO_PIN_RESET)
					button->button_state = BUTTON_PRESSED;
				else
					button->button_state = BUTTON_IDLE;
			}
			break;

		case BUTTON_PRESSED:
			//BUTTON_LED_SetState(button, BUTTON_LED_BLINK);
			if(BUTTON_GetSWState(button) == GPIO_PIN_SET )
			{
				button->button_state = BUTTON_IDLE;
			}
			break;

		default:
			break;
	}
}



void BUTTON_LED_SetState(button_t* button, button_led_state_t button_led_state)
{
	button->button_led_state = button_led_state;

	if(button->button_led_state == BUTTON_LED_BLINK)
	{
		BUTTON_LED_SetPinState(button, LED_ON);
		button->led_last_tick = HAL_GetTick();
	}
}

static void BUTTON_LED_Process(button_t* button)
{
	switch (button->button_led_state)
	{
		case BUTTON_LED_IDLE:

		break;

		case BUTTON_LED_BLINK:
			if((HAL_GetTick() - button->led_last_tick) > BUTTON_BLINK_TIME)
			{
				button->button_led_state = BUTTON_LED_OFF;
				BUTTON_LED_SetPinState(button, LED_OFF);
				button->button_last_tick = HAL_GetTick();
			}
			else
			{
				if(button->button_state == BUTTON_PRESSED && button->button_press_flag == BUTTON_WAS_NOT_PRESSED)
				{
					BUZZER_Go(TBUZ_20, TICK_1);
					button->button_press_flag = BUTTON_WAS_PRESSED;
				}
			}
			break;

		case BUTTON_LED_OFF:
			if(HAL_GetTick() - button->button_last_tick > BUTTON_BLINK_NEXT_BLINK)
			{
				button->button_led_state = BUTTON_LED_IDLE;
				button->button_press_flag = BUTTON_WAS_NOT_PRESSED;
			}
			break;

		default:
			break;
	}
}

static GPIO_PinState BUTTON_GetSWState(button_t* button)
{
	return HAL_GPIO_ReadPin(button->SW_Port, button->SW_Pin);
}

static void BUTTON_LED_SetPinState(button_t* button, led_state_t pin_state)
{
	if(pin_state == LED_ON)
		HAL_GPIO_WritePin(button->LED_Port, button->LED_Pin, GPIO_PIN_SET);
	else if(pin_state == LED_OFF)
		HAL_GPIO_WritePin(button->LED_Port, button->LED_Pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_TogglePin(button->LED_Port, button->LED_Pin);
}
