/*
 * led.c
 *
 *  Created on: Nov 11, 2023
 *      Author: stasz
 */

#include "main.h"
#include "app/led.h"

void LED_On(void)
{
	HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_SET);
}

void LED_Off(void)
{
	HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET);
}

void LED_Toggle(void)
{
	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
}
