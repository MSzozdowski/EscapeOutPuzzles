/*
 * distance_sens.c
 *
 *  Created on: Dec 10, 2023
 *      Author: stasz
 */

#include "main.h"
#include "app/distance_sens.h"

static GPIO_PinState DISTANCE_SENS_GetState(distance_sens_t* distance_sens);

DistanceSensActive distance_sens_detected_callback = NULL;
DistanceSensActive distance_sens_released_callback = NULL;

void DISTANCE_SENS_Init(distance_sens_t* distance_sens, GPIO_TypeDef* GpioPort, uint16_t GpioPin, uint8_t sens_id)
{
	distance_sens->distance_sens_state = DISTANCE_SENS_IDLE;
	distance_sens->GpioPort = GpioPort;
	distance_sens->GpioPin = GpioPin;
	distance_sens->distance_sens_tick = 0;
	distance_sens->distance_sens_id = sens_id;
}

void DISTANCE_SENS_Process(distance_sens_t* distance_sens)
{
	switch (distance_sens->distance_sens_state) {
		case DISTANCE_SENS_IDLE:
			if(DISTANCE_SENS_GetState(distance_sens) == GPIO_PIN_RESET)
			{
				distance_sens->distance_sens_state = DISTANCE_SENS_DEBOUNCE;
				distance_sens->distance_sens_tick = HAL_GetTick();
			}
			break;

		case DISTANCE_SENS_DEBOUNCE:
			if(HAL_GetTick() - distance_sens->distance_sens_tick > DISTANCE_SENS_DEBOUNCE_TIME)
			{
				if(DISTANCE_SENS_GetState(distance_sens) == GPIO_PIN_RESET)
				{
					distance_sens->distance_sens_state = DISTANCE_SENS_WAIT;
					distance_sens->distance_sens_tick = HAL_GetTick();

					if (distance_sens_detected_callback != NULL)
					{
						distance_sens_detected_callback(distance_sens);
					}
				}
				else
				{
					distance_sens->distance_sens_state = DISTANCE_SENS_IDLE;
				}
			}
			break;

		case DISTANCE_SENS_WAIT:
			if(DISTANCE_SENS_GetState(distance_sens) == GPIO_PIN_SET && HAL_GetTick() - distance_sens->distance_sens_tick > DISTANCE_SENS_WAIT_TIME)
			{
				distance_sens->distance_sens_state = DISTANCE_SENS_IDLE;
				if (distance_sens_released_callback != NULL)
				{
					distance_sens_released_callback(distance_sens);
				}
			}
			break;
	}
}

void DistanceSensDetectedCallback(DistanceSensActive callback)
{
	distance_sens_detected_callback = callback;
}

void DistanceSensReleasedCallback(DistanceSensActive callback)
{
	distance_sens_released_callback = callback;
}

static GPIO_PinState DISTANCE_SENS_GetState(distance_sens_t* distance_sens)
{
	return HAL_GPIO_ReadPin(distance_sens->GpioPort, distance_sens->GpioPin);
}
