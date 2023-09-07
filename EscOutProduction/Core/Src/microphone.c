/*
 * microphone.c
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */

#include "main.h"
#include "microphone.h"

static ADC_HandleTypeDef* micro_adc;
static uint32_t microphone_channel;

static void MICROPHONE_SetChannel(uint32_t Channel);

void MICROPHONE_Init(ADC_HandleTypeDef* hadc, uint32_t channel)
{
	micro_adc = hadc;
	microphone_channel = channel;
}

static void MICROPHONE_SetChannel(uint32_t Channel)
{
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = Channel;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	  if (HAL_ADC_ConfigChannel(micro_adc, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

uint16_t MICROPHONE_GetMillivolts(void)
{
	uint16_t adc_value;
	MICROPHONE_SetChannel(microphone_channel);
	HAL_ADC_Start(micro_adc);
	if(HAL_ADC_PollForConversion(micro_adc, 1000) == HAL_OK)
	{
		adc_value = HAL_ADC_GetValue(micro_adc);
		return ((adc_value*REFERENCE_VOLTAGE)/4095);
	}
	return 0;
}
