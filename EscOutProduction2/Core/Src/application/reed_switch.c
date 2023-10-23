/*
 * reed_switch.c
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/reed_switch.h"

static GPIO_PinState REED_SW_GetState(reed_sw* reed_sw);

ReedSwitchActive reed_callback = NULL;

void REED_SW_Init(reed_sw* reed_sw, GPIO_TypeDef* GpioPort, uint16_t GpioPin, uint8_t reed_id)
{
	reed_sw->reed_sw_state = REED_SW_IDLE;
	reed_sw->GpioPort = GpioPort;
	reed_sw->GpioPin = GpioPin;
	reed_sw->reed_sw_tick = 0;
	reed_sw->reed_sw_id = reed_id;
}

void REED_SW_Process(reed_sw* reed_sw)
{
	switch (reed_sw->reed_sw_state) {
		case REED_SW_IDLE:
			if(REED_SW_GetState(reed_sw) == GPIO_PIN_RESET)
			{
				reed_sw->reed_sw_state = REED_SW_DEBOUNCE;
				reed_sw->reed_sw_tick = HAL_GetTick();
			}
			break;

		case REED_SW_DEBOUNCE:
			if(HAL_GetTick() - reed_sw->reed_sw_tick > REED_SW_DEBOUNCE_TIME)
			{
				if(REED_SW_GetState(reed_sw) == GPIO_PIN_RESET)
				{
					reed_sw->reed_sw_state = REED_SW_WAIT;
					reed_sw->reed_sw_tick = HAL_GetTick();

					if (reed_callback != NULL)
					{
						reed_callback(reed_sw);
					}
				}
				else
				{
					reed_sw->reed_sw_state = REED_SW_IDLE;
				}
			}
			break;

		case REED_SW_WAIT:
			if(REED_SW_GetState(reed_sw) == GPIO_PIN_SET && HAL_GetTick()-reed_sw->reed_sw_tick > REED_SW_WAIT_TIME)
			{
				reed_sw->reed_sw_state = REED_SW_IDLE;
			}
			break;
	}
}

void ReedSwitchCallBack(ReedSwitchActive callback)
{
	reed_callback = callback;
}

static GPIO_PinState REED_SW_GetState(reed_sw* reed_sw)
{
	return HAL_GPIO_ReadPin(reed_sw->GpioPort, reed_sw->GpioPin);
}
