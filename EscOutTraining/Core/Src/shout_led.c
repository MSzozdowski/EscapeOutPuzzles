/*
 * ShoutLED.c
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */
//#ifdef MY_MACRO
#include "main.h"
#include "shout_led.h"
#include "microphone.h"
#include "ws2812.h"
#include "spi.h"
#include "adc.h"
#include "putchar.h"
#include "stdio.h"

static shout_led_state_t shout_led_state = IDLE;
static uint16_t progress = 0;

static uint32_t last_tick = 0;
static uint16_t microphone_value = 0;

//static uint16_t mapped_progress = 0;
static void ShoutLED_SendToLED(void);

/*static uint32_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
	uint32_t map = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return  map;
}*/

void ShoutLED_Init(void)
{
	  WS2812_Init(&hspi1);
	  MICROPHONE_Init(&hadc1, ADC_CHANNEL_0);
	  printf("Shout LED initialization \r\n");
	  //for(uint8_t i = 0; i < WS2812_LED_NUMBER; i++)
	  //{
		// WS2812_SetColor(i, RED, GREEN, BLUE);
		// WS2812_Update();
		// HAL_Delay(500);
	 // }
	  //WS2812_SetAllOff();
}

void ShoutLED_Process(void)
{
	switch (shout_led_state) {
		case IDLE:
			microphone_value = MICROPHONE_GetMillivolts();
			if(microphone_value > SHOUT_THRESHOLD)
			{
				shout_led_state = START_SHOUTING;
				last_tick = HAL_GetTick();
			}

			break;

		case START_SHOUTING:
			microphone_value = MICROPHONE_GetMillivolts();
			if(HAL_GetTick() - last_tick > INIT_TIME)
			{
				if(microphone_value > SHOUT_THRESHOLD)
				{
					shout_led_state = PROGRESS;
					ShoutLED_SendToLED();
					last_tick = HAL_GetTick();
					printf("IDLE TO PROGRESS STATE \t microphone value = %dmV \r\n", microphone_value);
				}
				else
				{
					shout_led_state = IDLE;
				}
			}
			break;

		case PROGRESS:
			microphone_value = MICROPHONE_GetMillivolts();
			if((microphone_value > SHOUT_THRESHOLD) && (HAL_GetTick() - last_tick > PROGRESS_TIME))
			{
				if(progress >= WS2812_LED_NUMBER/*ONE_HUNDRED_PERCENT*/)
				{
					shout_led_state = FINISH;
				}
				else
				{
					//mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDRED_PERCENT, 0, WS2812_LED_NUMBER);
					ShoutLED_SendToLED();
					progress++;
					printf("PROGRESS STATE STILL SHOUTING \t microphone value = %dmV \r\n", microphone_value);
				}
				last_tick = HAL_GetTick();
			}
			else
			{
				if(HAL_GetTick() - last_tick > PROGRESS_TO_REGRESS_TIME)
				{
					shout_led_state = REGRESS;
					last_tick = HAL_GetTick();
					printf("PROGRESS TO REGRESS STATE \t microphone value = %dmV \r\n", microphone_value);
				}
			}
			break;

		case REGRESS:
			microphone_value = MICROPHONE_GetMillivolts();
			if(((HAL_GetTick() - last_tick) > REGRESS_TIME) && (microphone_value < SHOUT_THRESHOLD))
			{
				if(progress <= 0)
				{
					shout_led_state = FINISH;
				}
				else
				{
					progress--;
					//mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDRED_PERCENT, 0, WS2812_LED_NUMBER);
					ShoutLED_SendToLED();
					printf("REGRESS STATE NOT SHOUTING \t microphone value = %dmV \r\n", microphone_value);
				}
				last_tick = HAL_GetTick();
			}
			else
			{
				if(microphone_value > SHOUT_THRESHOLD)
				{
					shout_led_state = PROGRESS;
					last_tick = HAL_GetTick();
					printf("REGRESS TO PROGRESS STATE \t microphone value = %dmV \r\n", microphone_value);
				}
			}
			break;

		case FINISH:
			WS2812_SetAllOff();
			WS2812_Update();
			progress = 0;
			shout_led_state = IDLE;
			break;

		default:
			break;
	}
}

static void ShoutLED_SendToLED(void)
{
	WS2812_SetLineColors(progress, RED, GREEN, BLUE);
	WS2812_Update();
}
//#endif /* MY_MACRO */
