/*
 * app.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AG
 */

#include "app.h"
#include "app/board_id.h"
#include "driver/led.h"
#include "st7735.h"
#include "usart.h"
#include "comms.h"

board_id_e g_board_id = BOARD_ID_WRONG;
lcd_t lcd_left, lcd_right;

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

	ST7735_Init(&lcd_left, LCD_RST_LEFT_GPIO_Port, LCD_RST_LEFT_Pin, LCD_CS_LEFT_GPIO_Port, LCD_CS_LEFT_Pin, LCD_A0_LEFT_GPIO_Port, LCD_A0_LEFT_Pin);

	//ST7735_Init(&lcd_right, LCD_RST_RIGHT_GPIO_Port, LCD_RST_RIGHT_Pin, LCD_CS_RIGHT_GPIO_Port, LCD_CS_RIGHT_Pin, LCD_A0_RIGHT_GPIO_Port, LCD_A0_RIGHT_Pin);

	ST7735_FillScreen(&lcd_left, ST7735_BLUE);

	//ST7735_FillScreen(&lcd_right, ST7735_RED);

//	for(uint8_t i = 0; i < 10; i++)
//	{
//		if(i%2)
//		{
//			ST7735_FillScreen(&lcd_left, ST7735_BLUE);
//		}
//		else
//		{
//			ST7735_FillScreen(&lcd_left, ST7735_RED);
//		}
//	}
}

void APP_Main(void)
{
	COMMS_Process();
//	if(g_board_id == BOARD_ID_MASTER)
//	{
//		//LED_On();
//	}
//	else if(g_board_id != BOARD_ID_WRONG) //SLAVE 1/2/3
//	{
//		//LED_Off();
//	}
}
