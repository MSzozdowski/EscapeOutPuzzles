/*
 * dfplayer.c
 *
 *  Created on: Sep 29, 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/dfplayer.h"

UART_HandleTypeDef *dfp_uart;
//dfplayer_state_t dfplayer_state;

//uint8_t dfplayer_buffer[MAX_COM_PARAM_QUE][3] = {0};

//static void DFPLAYER_Busy(busy_state_t busy_state)
//{
//	if(busy_state == DFP_ON)
//		HAL_GPIO_WritePin(DFP_BUSY_GPIO_Port, DFP_BUSY_Pin, GPIO_PIN_RESET);
//	else
//		HAL_GPIO_WritePin(DFP_BUSY_GPIO_Port, DFP_BUSY_Pin, GPIO_PIN_SET);
//}

static void DFPLAYER_SendCommand(uint8_t command, uint8_t param1, uint8_t param2)
{
	uint16_t checksum = VERSION + CMD_LENGTH + command + FEEDBACK + param1 + param2;
	checksum = 0-checksum;

	uint8_t command_frame[FRAME_LENGTH] = {START_BIT, VERSION, CMD_LENGTH, command, FEEDBACK, param1, param2, (checksum>>8)&0x00FF, (checksum&0x00FF), END_BIT};

	HAL_UART_Transmit(dfp_uart, command_frame, FRAME_LENGTH, HAL_MAX_DELAY);
}

void DFPLAYER_Init(UART_HandleTypeDef* uart)
{
	dfp_uart = uart;
//	DFPLAYER_Busy(DFP_ON);

//	DFPLAYER_SendCommand(QRY_CUR_STAT, 0x00, 0x00);

	DFPLAYER_SendCommand(RST_MOD, 0x00, 0x00);
	HAL_Delay(1500);

	DFPLAYER_SendCommand(INIT_PARAMS, 0x00, SD_CARD);
	HAL_Delay(50);

	DFPLAYER_SendCommand(SPEC_EQ, 0x00, 0x00);
	HAL_Delay(50);

	DFPLAYER_SendCommand(SPEC_VOL, 0x00, 0x1E); //Volume 1E max
	HAL_Delay(50);
}

void DFPLAYER_Play(uint8_t audio_number)
{
	DFPLAYER_SendCommand(SEL_TRACK, 0x00, audio_number);
}
