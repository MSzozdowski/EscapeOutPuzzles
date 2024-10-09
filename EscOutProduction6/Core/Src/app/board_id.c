/*
 * board_id.c
 *
 *  Created on: 7 paź 2024
 *      Author: stasz
 */
#include "main.h"
#include "gpio.h"
#include "app/board_id.h"

static board_id_ports_t board_id_ports[4] = {
		{MCU_SEL1_GPIO_Port,MCU_SEL1_Pin},
		{MCU_SEL2_GPIO_Port,MCU_SEL2_Pin},
		{MCU_SEL3_GPIO_Port,MCU_SEL3_Pin},
		{MCU_SEL4_GPIO_Port,MCU_SEL4_Pin},
};

board_id_e BOARD_ID_GetBoardID(void)
{
	uint8_t board_id = 0;
	uint8_t two_keys_switched_flag = 0;

	GPIO_PinState pin_state;

	for(uint8_t i=0; i < MCU_SEL_PINS; i++)
	{
		pin_state = HAL_GPIO_ReadPin(board_id_ports[i].port, board_id_ports[i].pin);
		if(pin_state == GPIO_PIN_RESET)
		{
			if(two_keys_switched_flag)
			{
				return BOARD_ID_WRONG;
			}
			else
			{
				board_id = i;
				two_keys_switched_flag = 1;
			}
		}
	}

	if(board_id == BOARD_ID_MASTER)
		return BOARD_ID_MASTER;
	else if(board_id == BOARD_ID_SLAVE_1)
		return BOARD_ID_SLAVE_1;
	else if(board_id == BOARD_ID_SLAVE_2)
		return BOARD_ID_SLAVE_2;
	else if(board_id == BOARD_ID_SLAVE_3)
		return BOARD_ID_SLAVE_3;
	else
		return BOARD_ID_WRONG;

}
