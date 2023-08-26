/*
 * button.c
 *
 *  Created on: Aug 26, 2023
 *      Author: stasz
 */

#include "main.h"
#include "button.h"
#include "gpio.h"

static GPIO_PinState BUTTON_GetSWState(button_t* button);

void BUTTON_Init(button_t* button, GPIO_TypeDef* SW_Port, uint16_t SW_Pin, GPIO_TypeDef* LED_Port, uint16_t LED_Pin)
{
	button->button_state = BUTTON_IDLE;
	button->button_led_state = BUTTON_LED_OFF;
	button->SW_Port = SW_Port;
	button->SW_Pin = SW_Pin;
	button->LED_Port = LED_Port;
	button->LED_Pin = LED_Pin;
}

void BUTTON_Process(button_t* button)
{
	switch (button->button_state) {
		case BUTTON_IDLE:
			if(BUTTON_GetSWState(button) == GPIO_PIN_RESET)
			{
				button->button_state = BUTTON_DEBOUNCE;
				button->last_tick = HAL_GetTick();
			}
			break;

		case BUTTON_DEBOUNCE:
			if(HAL_GetTick() - button->last_tick > DEBOUNCE_TIME)
			{
				if(BUTTON_GetSWState(button) == GPIO_PIN_RESET)
					button->button_state = BUTTON_PRESSED;
				else
					button->button_state = BUTTON_IDLE;
			}
			break;

		case BUTTON_PRESSED:
			HAL_GPIO_TogglePin(button->LED_Port, button->LED_Pin);
			button->button_state = BUTTON_RELEASED;
			break;

		case BUTTON_RELEASED:
			if(BUTTON_GetSWState(button) == GPIO_PIN_SET)
				button->button_state = BUTTON_IDLE;
			break;

		default:
			break;
	}
}

static GPIO_PinState BUTTON_GetSWState(button_t* button)
{
	return HAL_GPIO_ReadPin(button->SW_Port, button->SW_Pin);
}

void BUTTON_LEDSetState(button_t* button, button_led_state_t led_state)
{
	if(led_state == BUTTON_LED_ON)
		HAL_GPIO_WritePin(button->LED_Port, button->LED_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(button->LED_Port, button->LED_Pin, GPIO_PIN_RESET);
}
