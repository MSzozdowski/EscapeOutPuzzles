/*
 * button.c
 *
 *  Created on: Aug 26, 2023
 *      Author: stasz
 */

#include "main.h"
#include "gpio.h"
#include "application/button.h"
#include "application/buzzer.h"

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
	button->button_accept_press = false;
	button->button_led_blink_stage = 0;
	button->button_blink_counter = 0;
}

void BUTTON_RegisterPositivePressCallBack(button_t *button, void *callback)
{
	button->ButtonPositivePressed = callback;
}

void BUTTON_RegisterNegativePressCallBack(button_t *button, void *callback)
{
	button->ButtonNegativePressed = callback;
}

static void BUTTON_LEDBlink(button_t* button)
{
	switch (button->button_led_blink_stage) {
		case 0: //Set LED on and register time
			BUTTON_LED_SetPinState(button, LED_ON);
			button->button_press_flag = BUTTON_WAS_NOT_PRESSED;
			button->led_last_tick = HAL_GetTick();
			button->button_accept_press = true;
			button->button_led_blink_stage = 1;
			break;

		case 1: //Set LED off after button blink time, if button will be pressed before LED is off then register a callback
			if((HAL_GetTick() - button->led_last_tick) > BUTTON_BLINK_TIME)
			{
				BUTTON_LED_SetPinState(button, LED_OFF);
				button->led_last_tick = HAL_GetTick();
				button->button_accept_press = false;
				button->button_led_blink_stage = 2;
			}
			break;

		case 2: //Wait some time to next blink
			if((HAL_GetTick() - button->led_last_tick) > BUTTON_BLINK_TIME)
			{
				BUTTON_LED_SetState(button, BUTTON_LED_IDLE);
				button->button_led_blink_stage = 0;
			}
			break;
	}
}

static void BUTTON_LEDThreeFastBlinks(button_t* button)
{
	switch (button->button_led_blink_stage) {
		case 0:
			BUTTON_LED_SetPinState(button, BUTTON_LED_ON);
			button->led_last_tick = HAL_GetTick();
			button->button_led_blink_stage = 1;
			break;

		case 1:
			if(((HAL_GetTick() - button->led_last_tick) > BUTTON_FAST_BLINK_TIME))
			{
				BUTTON_LED_SetPinState(button, BUTTON_LED_TOGGLE);
				if(button->button_blink_counter++ > 5)
				{
					button->button_led_blink_stage = 2;
					BUTTON_LED_SetPinState(button, LED_OFF);
				}

				button->led_last_tick = HAL_GetTick();
			}
			break;

		case 2:
			BUTTON_LED_SetState(button, BUTTON_LED_IDLE);
			button->button_led_blink_stage = 0;
			button->button_blink_counter = 0;
			break;
	}
}

void BUTTON_LED_SetState(button_t* button, button_led_state_t button_led_state)
{
		button->button_led_state = button_led_state;
}

static void BUTTON_LED_Process(button_t* button)
{
	switch (button->button_led_state)
	{
		case BUTTON_LED_IDLE:

		break;

		case BUTTON_LED_ON:
			BUTTON_LED_SetPinState(button, LED_ON);
			button->button_led_state = BUTTON_LED_IDLE;
			break;

		case BUTTON_LED_TOGGLE:
			BUTTON_LED_SetPinState(button, LED_TOGGLE);
			button->button_led_state = BUTTON_LED_IDLE;
			break;

		case BUTTON_LED_BLINK:
			BUTTON_LEDBlink(button);
			break;

		case BUTTON_LED_THREE_FAST_BLINKS:
			BUTTON_LEDThreeFastBlinks(button);
			break;

		case BUTTON_LED_OFF:
				BUTTON_LED_SetPinState(button, LED_OFF);
				button->button_led_state = BUTTON_LED_IDLE;
			break;

		default:
			break;
	}
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
				{
					if(button->button_accept_press == true)
					{

						if(button->ButtonPositivePressed != NULL)
						{
							button->ButtonPositivePressed();
						}
					}
					else
					{

						if(button->ButtonNegativePressed != NULL)
						{
							button->ButtonNegativePressed();
						}
					}
					button->button_state = BUTTON_PRESSED;
					button->button_last_tick = HAL_GetTick();
				}
				else
				{
					button->button_state = BUTTON_IDLE;
				}

			}
			break;

		case BUTTON_PRESSED:
			if(HAL_GetTick() - button->button_last_tick > NEXT_PRESS_TIME)
			{
				if(BUTTON_GetSWState(button) == GPIO_PIN_SET)
				{
					button->button_state = BUTTON_IDLE;
				}
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
