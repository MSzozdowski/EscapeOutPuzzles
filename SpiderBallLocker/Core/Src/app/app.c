/*
 * app.c
 *
 *  Created on: Oct 14, 2026
 *      Author: stasz
 */
#include "gpio.h"
#include "door.h"
#include "lock_input.h"

door_t door;
lock_input_t lock_input;

void APP_Init(void)
{
	DOOR_Init(&door, RELAY_GPIO_Port, RELAY_Pin);
	LOCK_INPUT_Init(&lock_input, LOCK_INPUT_GPIO_Port, LOCK_INPUT_Pin);
}

void APP_Loop(void)
{
	DOOR_Process(&door);
	LOCK_INPUT_Process(&lock_input);
}
