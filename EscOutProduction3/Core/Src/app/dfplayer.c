/*
 * dfplayer.c
 *
 *  Created on: Sep 29, 2023
 *      Author: stasz
 */

#include "main.h"
#include "gpio.h"
#include "app/dfplayer.h"

UART_HandleTypeDef *dfp_uart;

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

void DFPLAYER_Stop(void)
{
	DFPLAYER_SendCommand(0x0E, 0x00, 0x00);
}

busy_state_t DFPLAYER_GetState(void)
{
	if(HAL_GPIO_ReadPin(DFR_BUSY_GPIO_Port, DFR_BUSY_Pin) == GPIO_PIN_RESET)
		return DFP_PLAYING;
	else
		return DFP_NOT_PLAYING;
}
