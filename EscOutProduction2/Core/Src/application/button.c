/*
 * button.c
 *
 *  Created on: Oct 16, 2023
 *      Author: stasz
 */
#include "main.h"
#include "application/button.h"

static GPIO_PinState GetButtonState(void);
static void SetLedState(GPIO_PinState PinState);

static led_state_t led_state;
static button_state_t button_state;

PressedCallback pressed_callback = NULL;

void BUTTON_LED_Init(void)
{
	led_state = LED_CONT_SHORT_BLINK;
	button_state = BUTTON_IDLE;
}

void BUTTON_LED_Process(void)
{
	static uint32_t led_tick = 0;

	switch (led_state) {
		case LED_OFF:
			SetLedState(GPIO_PIN_RESET);
			break;

		case LED_ON:
			SetLedState(GPIO_PIN_SET);
			break;

		case LED_CONT_SHORT_BLINK:;
			static uint8_t short_blink_state = 0;
			if(HAL_GetTick() - led_tick > SHORT_BLINK_TIME_OFF && short_blink_state == 0)
			{
				SetLedState(GPIO_PIN_SET);
				led_tick = HAL_GetTick();
				short_blink_state = 1;
			}
			else if(HAL_GetTick() - led_tick > SHORT_BLINK_TIME_ON && short_blink_state == 1)
			{
				SetLedState(GPIO_PIN_RESET);
				led_tick = HAL_GetTick();
				short_blink_state = 0;
			}
			break;

		case LED_THREE_BLINKS:;
			static uint8_t three_blink_state = 0;
			static uint8_t blink_counter = 0;
			if(HAL_GetTick() - led_tick > THREE_BLINK_TIME && three_blink_state == 0)
			{
				SetLedState(GPIO_PIN_SET);
				led_tick = HAL_GetTick();
				three_blink_state = 1;
			}
			else if(HAL_GetTick() - led_tick > THREE_BLINK_TIME && three_blink_state == 1)
			{
				SetLedState(GPIO_PIN_RESET);
				led_tick = HAL_GetTick();
				three_blink_state = 0;
				if(++blink_counter >= 3)
				{
					led_state = LED_OFF;
					blink_counter = 0;
					three_blink_state = 0;
				}
			}
			break;
	}

	static uint32_t button_tick = 0;
	switch (button_state) {
		case BUTTON_IDLE:
			if(GetButtonState() == GPIO_PIN_RESET)
			{
				button_state = BUTTON_DEBOUNCE;
				button_tick = HAL_GetTick();
			}
			break;

		case BUTTON_DEBOUNCE:
			if(HAL_GetTick() - button_tick > DEBOUNCE_TIME && GetButtonState() == GPIO_PIN_RESET)
			{
				if (pressed_callback != NULL)
					pressed_callback();

				button_state = BUTTON_PRESSED;
			}
			break;

		case BUTTON_PRESSED:
			if(GetButtonState() == GPIO_PIN_SET)
			{
				button_state = BUTTON_IDLE;
			}
			break;
	}
}

void BUTTON_LED_SetState(led_state_t led_st)
{
	led_state = led_st;
}

led_state_t BUTTON_LED_GetLEDState(void)
{
	return led_state;
}

button_state_t BUTTON_LED_GetButtonState(void)
{
	return button_state;
}

void BUTTON_PressCallback(PressedCallback callback)
{
	pressed_callback = callback;
}

static GPIO_PinState GetButtonState(void)
{
	return HAL_GPIO_ReadPin(BUTTON_LED_GPIO_Port, BUTTON_LED_Pin);
}

static void SetLedState(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(BTN_LED_LIGHT_GPIO_Port, BTN_LED_LIGHT_Pin, PinState);
}
