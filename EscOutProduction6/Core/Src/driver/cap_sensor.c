/*
 * cap_sensor.c
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#include "main.h"
#include "cap_sensor.h"

static GPIO_PinState CAP_SENSOR_GetPinState(void);

cap_sens_state_t cap_sens_state;
uint32_t cap_sens_tick;

SensorDetectedCallback detected_callback = NULL;

void CAP_SENSOR_Init(void)
{
	cap_sens_state = CAP_SENS_NOT_DETECTED;
	cap_sens_tick = HAL_GetTick();
}

void CAP_SENSOR_Process(void)
{
	switch(cap_sens_state)
	{
		case CAP_SENS_NOT_DETECTED:
			if(CAP_SENSOR_GetPinState() == GPIO_PIN_RESET)
			{
				cap_sens_state = CAP_SENS_DEBOUNCE;
				cap_sens_tick = HAL_GetTick();
			}
			break;

		case CAP_SENS_DEBOUNCE:
			if(HAL_GetTick() - cap_sens_tick > CAP_SENS_DEBOUNCE_TIME)
			{
				if(CAP_SENSOR_GetPinState() == GPIO_PIN_RESET)
				{
					cap_sens_state = CAP_SENS_DETECTED;
					if (detected_callback != NULL)
						detected_callback();
				}
				else
				{
					cap_sens_state = CAP_SENS_NOT_DETECTED;
				}
			}
			break;

		case CAP_SENS_DETECTED:
			if(CAP_SENSOR_GetPinState() == GPIO_PIN_SET)
				cap_sens_state = CAP_SENS_NOT_DETECTED;
			break;
	}
}

static GPIO_PinState CAP_SENSOR_GetPinState(void)
{
	return HAL_GPIO_ReadPin(CAP_SENS_NO_GPIO_Port, CAP_SENS_NO_Pin);
}

cap_sens_state_t CAP_SENSOR_GetState(void)
{
	return cap_sens_state;
}

void CAP_SENSOR_DetectedCallback(SensorDetectedCallback callback)
{
	detected_callback = callback;
}
