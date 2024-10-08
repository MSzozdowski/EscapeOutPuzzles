/*
 * app.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AG
 */

#include "app.h"
#include "app/board_id.h"
#include "driver/led.h"
#include "usart.h"
#include "comms.h"

board_id_e g_board_id = BOARD_ID_WRONG;

void APP_Init(void)
{
	g_board_id = BOARD_ID_GetBoardID();

	while(g_board_id == BOARD_ID_WRONG)
	{
		g_board_id = BOARD_ID_GetBoardID();

		LED_Toggle();
		HAL_Delay(100);
	}

	COMMS_Init(&huart1, g_board_id, RS_485_EN_GPIO_Port, RS_485_EN_Pin);
}

void APP_Main(void)
{
	COMMS_Process();
	if(g_board_id == BOARD_ID_MASTER)
	{
		//LED_On();
	}
	else if(g_board_id != BOARD_ID_WRONG) //SLAVE 1/2/3
	{
		//LED_Off();
	}
}
