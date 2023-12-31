/*
 * board_id.c
 *
 *  Created on: Sep 6, 2023
 *      Author: stasz
 */

#include "main.h"
#include "app/board_id.h"

static ADC_HandleTypeDef* board_id_adc;
static uint32_t board_id_channel;

static void BOARD_ID_SetChannel(uint32_t Channel);

void BOARD_ID_Init(ADC_HandleTypeDef* hadc, uint32_t channel)
{
	board_id_adc = hadc;
	board_id_channel = channel;
}

static void BOARD_ID_SetChannel(uint32_t Channel)
{
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = Channel;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	  if (HAL_ADC_ConfigChannel(board_id_adc, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

board_id_t BOARD_ID_GetBoardID(void)
{
	uint16_t adc_value;
	BOARD_ID_SetChannel(board_id_channel);
	HAL_ADC_Start(board_id_adc);
	if(HAL_ADC_PollForConversion(board_id_adc, 1000) == HAL_OK)
		adc_value = HAL_ADC_GetValue(board_id_adc);

	uint16_t board_id_millivolts = ((adc_value*REFERENCE_VOLTAGE)/4095);

	if(board_id_millivolts < REED_SWITCH_MILLIVOLTS_THRESHOLD)
	{
		return BOARD_IS_REED_SWITCH_COLORS;
	}
	else if(board_id_millivolts > CAP_SENSE_PLAYER_MILLLIVOLTS_THRESHOLD)
	{
		return BOARD_IS_CAP_SENSE_PLAYER;
	}
	else
	{
		return BOARD_NOT_DEFINED;
	}
}
