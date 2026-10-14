/*
 * lock_input.c
 *
 *  Created on: Oct 14, 2026
 *      Author: stasz
 */

#include "lock_input.h"
#include "gpio.h"

static GPIO_PinState GetLockState(lock_input_t* lock_input);

void LOCK_INPUT_Init(lock_input_t* lock_input, GPIO_TypeDef *GpioPort, uint16_t GpioPin)
{
	if(lock_input == NULL)
	{
		return;
	}
	lock_input->lock_input_state = LOCK_IDLE;
	lock_input->GpioPort = GpioPort;
	lock_input->GpioPin = GpioPin;
	lock_input->requested_to_open = false;
}

void LOCK_INPUT_Process(lock_input_t* lock_input)
{
	if(lock_input == NULL)
	{
		return;
	}

	switch (lock_input->lock_input_state)
	{
		case LOCK_INPUT_IDLE:
			//Wait for locking door by puzzle
			if(GetLockState(lock_input) == GPIO_PIN_SET)
			{
				lock_input->lock_input_state = LOCK_INPUT_LOCKED;
			}
			break;

		case LOCK_INPUT_LOCKED:
			break;

		case LOCK_INPUT_DEBOUNCE:
			break;

		case LOCK_INPUT_UNLOCKED:
			break;
	}
}

lock_input_state_t LOCK_Input_GetState(lock_input_t* lock_input)
{
	if(lock_input == NULL)
	{
		return LOCK_INPUT_IDLE;
	}

	return lock_input->lock_input_state;
}

static GPIO_PinState GetLockState(lock_input_t* lock_input)
{
	return HAL_GPIO_ReadPin(lock_input->GpioPort, lock_input->GpioPin);
}
