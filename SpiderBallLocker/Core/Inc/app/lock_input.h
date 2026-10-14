/*
 * lock_input.h
 *
 *  Created on: Oct 14, 2026
 *      Author: stasz
 */

#ifndef INC_APP_LOCK_INPUT_H_
#define INC_APP_LOCK_INPUT_H_

#include "gpio.h"
#include "stdbool.h"

typedef enum
{
	LOCK_INPUT_IDLE,
	LOCK_INPUT_LOCKED,
	LOCK_INPUT_DEBOUNCE,
	LOCK_INPUT_UNLOCKED
}lock_input_state_t;

typedef struct
{
	lock_input_state_t lock_input_state;
	GPIO_TypeDef 	*GpioPort;
	uint16_t 		GpioPin;
	uint32_t 		last_tick;
	bool requested_to_open;
}lock_input_t;

void LOCK_INPUT_Init(lock_input_t* lock_input, GPIO_TypeDef *GpioPort, uint16_t GpioPin);
void LOCK_INPUT_Process(lock_input_t* lock_input);
lock_input_state_t LOCK_Input_GetState(lock_input_t* lock_input);

#endif /* INC_APP_LOCK_INPUT_H_ */
