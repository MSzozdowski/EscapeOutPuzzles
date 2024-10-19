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
#include "app/display_eye.h"
#include "st7735.h"
#include "usart.h"
#include "comms.h"


board_id_e g_board_id = BOARD_ID_WRONG;
door_t door;

void APP_Init(void)
{
	g_board_id = BOARD_ID_GetBoardIDUntilCorrect(); //BLOCKING FUNCTION - ID SHOULD BE != BOARD_ID_WRONG
	COMMS_Init(&huart1, g_board_id, RS_485_EN_GPIO_Port, RS_485_EN_Pin);
	CAP_SENSOR_Init();
	DOOR_Init(&door, RELAY_GPIO_Port, RELAY_Pin);
	DrawEyeInit();
	//DrawEyeTest();
}

void APP_Main(void)
{
	COMMS_Process();
	CAP_SENSOR_Process();
	DOOR_Process(&door);
}
