/*
 * app.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AG
 */

#include "app.h"
#include "app/board_id.h"
#include "driver/led.h"
#include "driver/cap_sensor.h"
#include "driver/door.h"
#include "st7735.h"
#include "usart.h"
#include "comms.h"

board_id_e g_board_id = BOARD_ID_WRONG;
lcd_t lcd_left, lcd_right;
door_t door;

void APP_Init(void)
{
	g_board_id = BOARD_ID_GetBoardIDUntilCorrect(); //BLOCKING FUNCTION - ID SHOULD BE != BOARD_ID_WRONG
	COMMS_Init(&huart1, g_board_id, RS_485_EN_GPIO_Port, RS_485_EN_Pin);
	CAP_SENSOR_Init();
	DOOR_Init(&door, RELAY_GPIO_Port, RELAY_Pin);
//	ST7735_Init(&lcd_left, LCD_RST_LEFT_GPIO_Port, LCD_RST_LEFT_Pin, LCD_CS_LEFT_GPIO_Port, LCD_CS_LEFT_Pin, LCD_A0_LEFT_GPIO_Port, LCD_A0_LEFT_Pin);
//	ST7735_Init(&lcd_right, LCD_RST_RIGHT_GPIO_Port, LCD_RST_RIGHT_Pin, LCD_CS_RIGHT_GPIO_Port, LCD_CS_RIGHT_Pin, LCD_A0_RIGHT_GPIO_Port, LCD_A0_RIGHT_Pin);
//	ST7735_FillScreen(&lcd_left, ST7735_BLUE);
//	ST7735_FillScreen(&lcd_right, ST7735_RED);

}

void APP_Main(void)
{
	COMMS_Process();
	CAP_SENSOR_Process();
	DOOR_Process(&door);
}
