/*
 * app.c
 *
 *  Created on: Oct 14, 2026
 *      Author: stasz
 */
#include "gpio.h"
#include "door.h"
#include "lock_input.h"
#include "buzzer.h"

door_t door;
lock_input_t lock_input;
buzzer_t buzzer;

void APP_Init(void)
{
	DOOR_Init(&door, RELAY_GPIO_Port, RELAY_Pin);
	LOCK_INPUT_Init(&lock_input, LOCK_INPUT_GPIO_Port, LOCK_INPUT_Pin);
	BUZZER_Init(&buzzer, BUZZER_BUILD_IN_GPIO_Port, BUZZER_BUILD_IN_Pin);
}

void APP_Loop(void)
{
	DOOR_Process(&door);
	LOCK_INPUT_Process(&lock_input);
	BUZZER_Process(&buzzer);

	if(LOCK_INPUT_WasUnlocked(&lock_input) == true)
	{
		DOOR_Open(&door);
		BUZZER_Start(&buzzer, 200, 200, 10);
	}
}
