/*
 * reed_sw_colors.c
 *
 *  Created on: Nov 13, 2023
 *      Author: stasz
 */

#include "main.h"
#include "spi.h"
#include "app/reed_sw_colors.h"
#include "app/reed_switch.h"
#include "app/led.h"
#include "app/ws2812.h"
#include "app/door.h"
#include <stdbool.h>

static void REED_SW_COLORS_InitStage(void);
static void ReedSwCallback(reed_sw* reed_sw);

static reed_sw reed_sw1;
static reed_sw reed_sw2;
static reed_sw reed_sw3;
static reed_sw reed_sw4;

static reed_sw_colors_state_t reed_sw_colors_state = REED_SW_COLORS_INIT;
static reed_sw_colors_init_stage_t reed_sw_colors_init_stage = INIT_STAGE_1;

static uint32_t tick;
bool solved_flag = false;


void REED_SW_COLORS_Init(void)
{
	WS2812_Init(&hspi1);

	REED_SW_Init(&reed_sw1, REED_SW1_GPIO_Port, REED_SW1_Pin, 1);
	REED_SW_Init(&reed_sw2, REED_SW2_GPIO_Port, REED_SW2_Pin, 2);
	REED_SW_Init(&reed_sw3, REED_SW3_GPIO_Port, REED_SW3_Pin, 3);
	REED_SW_Init(&reed_sw4, REED_SW4_GPIO_Port, REED_SW4_Pin, 4);

	ReedSwitchCallBack(ReedSwCallback);
}

static void REED_SW_COLORS_InitStage(void)
{
	switch (reed_sw_colors_init_stage) {
		case INIT_STAGE_1:
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw1.reed_sw_id), SEGMENT_END(reed_sw1.reed_sw_id), RED);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw2.reed_sw_id), SEGMENT_END(reed_sw2.reed_sw_id), GREEN);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw3.reed_sw_id), SEGMENT_END(reed_sw3.reed_sw_id), BLUE);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw4.reed_sw_id), SEGMENT_END(reed_sw4.reed_sw_id), YELLOW);
			WS2812_Update();
			tick = HAL_GetTick();
			reed_sw_colors_init_stage = INIT_STAGE_2;
			break;
		case INIT_STAGE_2:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1.reed_sw_id), SEGMENT_END(reed_sw1.reed_sw_id), BLUE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2.reed_sw_id), SEGMENT_END(reed_sw2.reed_sw_id), YELLOW);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3.reed_sw_id), SEGMENT_END(reed_sw3.reed_sw_id), RED);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4.reed_sw_id), SEGMENT_END(reed_sw4.reed_sw_id), GREEN);
				WS2812_Update();
				tick = HAL_GetTick();
				reed_sw_colors_init_stage = INIT_STAGE_3;
			}
			break;
		case INIT_STAGE_3:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1.reed_sw_id), SEGMENT_END(reed_sw1.reed_sw_id), YELLOW);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2.reed_sw_id), SEGMENT_END(reed_sw2.reed_sw_id), BLUE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3.reed_sw_id), SEGMENT_END(reed_sw3.reed_sw_id), GREEN);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4.reed_sw_id), SEGMENT_END(reed_sw4.reed_sw_id), RED);
				WS2812_Update();
				tick = HAL_GetTick();
				reed_sw_colors_init_stage = INIT_STAGE_4;
			}
			break;
		case INIT_STAGE_4:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetAllOff();
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1.reed_sw_id), SEGMENT_END(reed_sw1.reed_sw_id), GREEN);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2.reed_sw_id), SEGMENT_END(reed_sw2.reed_sw_id), RED);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3.reed_sw_id), SEGMENT_END(reed_sw3.reed_sw_id), YELLOW);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4.reed_sw_id), SEGMENT_END(reed_sw4.reed_sw_id), BLUE);
				WS2812_Update();
				reed_sw_colors_state = REED_SW_COLORS_GAME;
			}
			break;
	}
}

void REED_SW_COLORS_Process(void)
{
	REED_SW_Process(&reed_sw1);
	REED_SW_Process(&reed_sw2);
	REED_SW_Process(&reed_sw3);
	REED_SW_Process(&reed_sw4);

	switch (reed_sw_colors_state) {
		case REED_SW_COLORS_INIT:
			REED_SW_COLORS_InitStage();
			break;
		case REED_SW_COLORS_GAME:
			if(solved_flag)
			{
				tick = HAL_GetTick();
				reed_sw_colors_state = REED_SW_COLORS_FINISH;
				DOOR_Open();
			}
			break;

		case REED_SW_COLORS_FINISH:
			//if(DOOR_GetState() == DOOR_IDLE)
			//{
			//	solved_flag = false;
			//	reed_sw_colors_state = REED_SW_COLORS_INIT;
			//}
			break;
	}
}

static void ReedSwCallback(reed_sw* reed_sw)
{
	static const uint32_t colors[COLORS_NUMBER] = {RED, GREEN, BLUE, YELLOW};
	if(!solved_flag)
	{
		if(reed_sw == &reed_sw1)
			{
				static uint8_t reed1_color = 0;
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1.reed_sw_id), SEGMENT_END(reed_sw1.reed_sw_id), colors[reed1_color++]);
				reed1_color%=4;
			}
			else if(reed_sw == &reed_sw2)
			{
				static uint8_t reed2_color = 0;
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2.reed_sw_id), SEGMENT_END(reed_sw2.reed_sw_id), colors[reed2_color++]);
				reed2_color%=4;
			}
			else if(reed_sw == &reed_sw3)
			{
				static uint8_t reed3_color = 0;
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3.reed_sw_id), SEGMENT_END(reed_sw3.reed_sw_id), colors[reed3_color++]);
				reed3_color%=4;
			}
			else if(reed_sw == &reed_sw4)
			{
				static uint8_t reed4_color = 0;
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4.reed_sw_id), SEGMENT_END(reed_sw4.reed_sw_id), colors[reed4_color++]);
				reed4_color%=4;
			}
			WS2812_Update();

			if(WS2812_GetColor(SEGMENT_START(reed_sw1.reed_sw_id)) == YELLOW
					&& WS2812_GetColor(SEGMENT_START(reed_sw2.reed_sw_id)) == BLUE
					&& WS2812_GetColor(SEGMENT_START(reed_sw3.reed_sw_id)) == RED
					&& WS2812_GetColor(SEGMENT_START(reed_sw4.reed_sw_id)) == GREEN)
			{
				solved_flag = true;
			}
	}
	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
}
