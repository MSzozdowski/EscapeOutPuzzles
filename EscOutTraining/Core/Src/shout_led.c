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
#include "door.h"
#include "spi.h"
#include "adc.h"
#include "map.h"
#include "putchar.h"
#include "stdio.h"
#include "stdbool.h"

static shout_led_state_t shout_led_state;

static uint32_t last_tick;
static uint16_t microphone_value = 0;

static uint16_t progress = 0;
static uint16_t mapped_progress = 0;

static uint16_t blink_time = BLINK_TIME_INITIAL;
static uint16_t blink_counter = BLINK_COUNTER_INITIAL;

static void ShoutLED_SendToLED(void);

void ShoutLED_Init(void)
{
	  WS2812_Init(&hspi1);
	  MICROPHONE_Init(&hadc1, ADC_CHANNEL_0);
	  printf("Shout LED initialization \r\n");
	  shout_led_state = INIT;
	  last_tick = HAL_GetTick();
}

void ShoutLED_Process(void)
{
	switch (shout_led_state) {
		case INIT:
			if(HAL_GetTick() - last_tick > INIT_DELAY)
			{
				static uint16_t i = 0;
				WS2812_SetLineColors(i, RED, GREEN, BLUE);
				WS2812_Update();
				i++;
				last_tick = HAL_GetTick();
				if(i > WS2812_LED_NUMBER)
				{
					shout_led_state = LED_IDLE;
					WS2812_SetAllOff();
				}
			}
		break;

		case LED_IDLE:
			microphone_value = MICROPHONE_GetMillivolts();
			if(microphone_value > SHOUT_THRESHOLD)
			{
				shout_led_state = START_SHOUTING;
				progress = 0;
				last_tick = HAL_GetTick();
			}
			break;

		case START_SHOUTING:
			microphone_value = MICROPHONE_GetMillivolts();
			if((HAL_GetTick() - last_tick) > INIT_TIME_MIN)
			{
				if(microphone_value > SHOUT_THRESHOLD)
				{
					shout_led_state = PROGRESS;
					mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDRED_PERCENT, 0, WS2812_LED_NUMBER);
					ShoutLED_SendToLED();
					last_tick = HAL_GetTick();
					printf("START SHOUTING TO PROGRESS STATE \t microphone value = %dmV \r\n", microphone_value);
				}
				if(microphone_value < SHOUT_THRESHOLD && (HAL_GetTick() - last_tick) > INIT_TIME_MAX)
				{
					shout_led_state = LED_IDLE;
				}
			}
			break;

		case PROGRESS:
			microphone_value = MICROPHONE_GetMillivolts();
			if((microphone_value > SHOUT_THRESHOLD) && (HAL_GetTick() - last_tick > PROGRESS_TIME))
			{
				if(progress >= ONE_HUNDRED_PERCENT)
				{
					shout_led_state = FINISH_BLINK;
				}
				else
				{
					mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDRED_PERCENT, 0, WS2812_LED_NUMBER);
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
					shout_led_state = LED_IDLE;
					WS2812_SetAllOff();
					last_tick = HAL_GetTick();
				}
				else
				{
					progress--;
					mapped_progress = map(progress, ZERO_PERCENT, ONE_HUNDRED_PERCENT, 0, WS2812_LED_NUMBER);
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

		case FINISH_BLINK:;

			if(HAL_GetTick() - last_tick > blink_time)
			{
				if(blink_counter <= 0)
				{
					shout_led_state = FINISH;
 					DOOR_Open();
					//WS2812_SetAllOff();
					blink_time = BLINK_TIME_INITIAL;
					blink_counter = BLINK_COUNTER_INITIAL;
					break;
				}
				if(blink_counter%2)
				{
					WS2812_SetLineColors(WS2812_LED_NUMBER-1, RED_FINISH, GREEN_FINISH, BLUE_FINISH);
					WS2812_Update();
					blink_time -= BLINK_TIME_STEP;
				}
				else
				{
					WS2812_SetAllOff();
				}
				blink_counter--;
				last_tick = HAL_GetTick();
			}
			break;

		case FINISH:
			if(HAL_GetTick() - last_tick > NEXT_ROUND_DELAY)
			{
				shout_led_state = LED_IDLE;
				WS2812_SetAllOff();
			}
			break;

		default:
			break;
	}
}

static void ShoutLED_SendToLED(void)
{
	WS2812_SetLineColors(mapped_progress, RED, GREEN, BLUE);
	WS2812_Update();
}
//#endif /* MY_MACRO */
