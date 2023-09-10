/*
 * piezo.c
 *
 *  Created on: Aug 24, 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/piezo.h"

static ADC_HandleTypeDef* piezo_adc;
static uint32_t piezo_channel;

static void PIEZO_SetChannel(uint32_t Channel);

void PIEZO_Init(ADC_HandleTypeDef* hadc, uint32_t channel)
{
	piezo_adc = hadc;
	piezo_channel = channel;
	HAL_ADCEx_Calibration_Start(piezo_adc);
}

static void PIEZO_SetChannel(uint32_t Channel)
{
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = Channel;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	  if (HAL_ADC_ConfigChannel(piezo_adc, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

uint16_t PIEZO_GetMillivolts(void)
{
	uint16_t adc_value;
	PIEZO_SetChannel(piezo_channel);
	HAL_ADC_Start(piezo_adc);
	if(HAL_ADC_PollForConversion(piezo_adc, 1000) == HAL_OK)
	{
		adc_value = HAL_ADC_GetValue(piezo_adc);
		return ((adc_value*REFERENCE_VOLTAGE)/4095);
	}
	return 0;
}

