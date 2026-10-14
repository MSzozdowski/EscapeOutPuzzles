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
	lock_input->lock_input_state = LOCK_INPUT_IDLE;
	lock_input->GpioPort = GpioPort;
	lock_input->GpioPin = GpioPin;
	lock_input->locked_opened_succesfully = false;
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
			if(GetLockState(lock_input) == GPIO_PIN_RESET)
			{
				lock_input->last_tick = HAL_GetTick();
				lock_input->lock_input_state = LOCK_INPUT_DEBOUNCE;
			}
			break;

		case LOCK_INPUT_DEBOUNCE:
			if(GetLockState(lock_input) == GPIO_PIN_SET)
			{
				lock_input->lock_input_state = LOCK_INPUT_LOCKED;
			}
			else if(HAL_GetTick() - lock_input->last_tick >= LOCK_INPUT_OPEN_TIME) // in puzzle lock opens for 1500ms so we should react within this time
			{
				lock_input->lock_input_state = LOCK_INPUT_UNLOCKED;
				lock_input->last_tick = HAL_GetTick();
				lock_input->locked_opened_succesfully = true;
			}

			break;

		case LOCK_INPUT_UNLOCKED:
			if(HAL_GetTick() - lock_input->last_tick > LOCK_INPUT_NEXT_ITERATION_TIME)
			{
				lock_input->lock_input_state = LOCK_INPUT_IDLE;
			}
			break;
	}
}

lock_input_state_t LOCK_INPUT_GetState(lock_input_t* lock_input)
{
	if(lock_input == NULL)
	{
		return LOCK_INPUT_IDLE;
	}

	return lock_input->lock_input_state;
}

bool LOCK_INPUT_WasUnlocked(lock_input_t* lock_input)
{
	if(lock_input == NULL)
	{
		return false;
	}

	bool unlocked = lock_input->locked_opened_succesfully;

	if(unlocked)
	{
		lock_input->locked_opened_succesfully = false;
		return true;
	}
	else
	{
		return false;
	}
}

static GPIO_PinState GetLockState(lock_input_t* lock_input)
{
	return HAL_GPIO_ReadPin(lock_input->GpioPort, lock_input->GpioPin);
}
