/*
 * buzzer.c
 *
 *  Created on: Oct 15, 2026
 *      Author: stasz
 */

#include "buzzer.h"
#include "gpio.h"

static void BUZZER_On(buzzer_t *buzzer);
static void BUZZER_Off(buzzer_t *buzzer);

void BUZZER_Init(buzzer_t *buzzer, GPIO_TypeDef *GpioPort, uint16_t GpioPin)
{
	if (buzzer == NULL)
		return;

	buzzer->GpioPort = GpioPort;
	buzzer->GpioPin = GpioPin;
	buzzer->buzzer_state = BUZZER_IDLE;

	BUZZER_Off(buzzer);
}

void BUZZER_Start(buzzer_t *buzzer, uint32_t on_time_ms, uint32_t off_time_ms, uint8_t beep_count)
{
	if (buzzer == NULL)
		return;

	if (beep_count == 0 || on_time_ms == 0)
		return;

	if (beep_count > 1 && off_time_ms == 0)
		return;

	if (buzzer->buzzer_state != BUZZER_IDLE)
	    return;

	buzzer->on_time_ms = on_time_ms;
	buzzer->off_time_ms = off_time_ms;
	buzzer->beeps_remaining = beep_count;

	buzzer->buzzer_state = BUZZER_START;
}

void BUZZER_Process(buzzer_t *buzzer)
{
	if (buzzer == NULL)
		return;

	switch (buzzer->buzzer_state)
	{
		case BUZZER_IDLE:
			//wait for start
			break;

		case BUZZER_START:
			BUZZER_On(buzzer);
			buzzer->last_tick = HAL_GetTick();
			buzzer->buzzer_state = BUZZER_ON;
			break;

		case BUZZER_ON:
			if(HAL_GetTick() - buzzer->last_tick >= buzzer->on_time_ms)
			{
				BUZZER_Off(buzzer);
				buzzer->beeps_remaining -= 1;

				if(buzzer->beeps_remaining == 0)
				{
					BUZZER_Off(buzzer);
					buzzer->buzzer_state = BUZZER_IDLE;
				}
				else
				{
					buzzer->last_tick = HAL_GetTick();
					buzzer->buzzer_state = BUZZER_OFF;
				}
			}
			break;

		case BUZZER_OFF:
			if(HAL_GetTick() - buzzer->last_tick >= buzzer->off_time_ms)
			{
				BUZZER_On(buzzer);
				buzzer->last_tick = HAL_GetTick();
				buzzer->buzzer_state = BUZZER_ON;
			}

			break;
	}
}

static void BUZZER_On(buzzer_t *buzzer)
{
	if(buzzer == NULL)
		return;

	HAL_GPIO_WritePin(buzzer->GpioPort, buzzer->GpioPin, GPIO_PIN_SET);
}

static void BUZZER_Off(buzzer_t *buzzer)
{
	if(buzzer == NULL)
		return;

	HAL_GPIO_WritePin(buzzer->GpioPort, buzzer->GpioPin, GPIO_PIN_RESET);
}

