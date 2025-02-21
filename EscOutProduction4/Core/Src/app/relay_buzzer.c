/*
 * relay_buzzer.c
 *
 *  Created on: Feb 21, 2025
 *      Author: stasz
 */
#include "main.h"
#include "app/relay_buzzer.h"

static void RELAY_BUZZER_On(relay_buzzer_t* relay_buzzer);
static void RELAY_BUZZER_Off(relay_buzzer_t* relay_buzzer);

void RELAY_BUZZER_Init(relay_buzzer_t* relay_buzzer, GPIO_TypeDef *GpioPort, uint16_t GpioPin)
{
	relay_buzzer->relay_buzzer_state = RELAY_BUZZER_IDLE;
	relay_buzzer->GpioPort = GpioPort;
	relay_buzzer->GpioPin = GpioPin;
}

void RELAY_BUZZER_Process(relay_buzzer_t* relay_buzzer)
{
	switch (relay_buzzer->relay_buzzer_state) {
		case RELAY_BUZZER_IDLE:
			if(relay_buzzer->buzz_times > 0)
			{
				relay_buzzer->relay_buzzer_state = RELAY_BUZZER_ON;
				relay_buzzer->last_tick = HAL_GetTick();
				RELAY_BUZZER_On(relay_buzzer);
			}
		break;

		case RELAY_BUZZER_OFF:
			if(relay_buzzer->buzz_times == 0)
			{
				relay_buzzer->relay_buzzer_state = RELAY_BUZZER_IDLE;
				RELAY_BUZZER_Off(relay_buzzer);
			}
			if(HAL_GetTick() - relay_buzzer->last_tick > relay_buzzer->time_off)
			{
				RELAY_BUZZER_On(relay_buzzer);
				relay_buzzer->relay_buzzer_state = RELAY_BUZZER_ON;
				relay_buzzer->last_tick = HAL_GetTick();
			}
			break;

		case RELAY_BUZZER_ON:
			if(HAL_GetTick() - relay_buzzer->last_tick > relay_buzzer->time_on)
			{
				RELAY_BUZZER_Off(relay_buzzer);
				relay_buzzer->relay_buzzer_state = RELAY_BUZZER_OFF;
				relay_buzzer->buzz_times--;
				relay_buzzer->last_tick = HAL_GetTick();
			}
			break;
	}
}

void RELAY_BUZZER_Start(relay_buzzer_t* relay_buzzer, uint16_t time_on, uint16_t time_off, uint8_t buzz_times)
{
	relay_buzzer->time_on = time_on;
	relay_buzzer->time_off = time_off;
	relay_buzzer->buzz_times = buzz_times;
}

static void RELAY_BUZZER_On(relay_buzzer_t* relay_buzzer)
{
	HAL_GPIO_WritePin(relay_buzzer->GpioPort, relay_buzzer->GpioPin, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, GPIO_PIN_SET);
}

static void RELAY_BUZZER_Off(relay_buzzer_t* relay_buzzer)
{
	HAL_GPIO_WritePin(relay_buzzer->GpioPort, relay_buzzer->GpioPin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, GPIO_PIN_RESET);
}
