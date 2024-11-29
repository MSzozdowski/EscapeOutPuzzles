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

static reed_sw reed_sw1_yellow;
static reed_sw reed_sw2_blue;
static reed_sw reed_sw3_green;
static reed_sw reed_sw4_red;

static reed_sw_colors_state_t reed_sw_colors_state = REED_SW_COLORS_INIT;
static reed_sw_colors_init_stage_t reed_sw_colors_init_stage = INIT_STAGE_1;


static uint32_t tick;
bool solved_flag = false;


void REED_SW_COLORS_Init(void)
{
	WS2812_Init(&hspi1);

	REED_SW_Init(&reed_sw1_yellow, REED_SW1_GPIO_Port, REED_SW1_Pin, 1);
	REED_SW_Init(&reed_sw2_blue, REED_SW2_GPIO_Port, REED_SW2_Pin, 2);
	REED_SW_Init(&reed_sw3_green, REED_SW3_GPIO_Port, REED_SW3_Pin, 3);
	REED_SW_Init(&reed_sw4_red, REED_SW4_GPIO_Port, REED_SW4_Pin, 4);

	ReedSwitchCallBack(ReedSwCallback);
}

static void REED_SW_COLORS_InitStage(void)
{
	switch (reed_sw_colors_init_stage) {
		case INIT_STAGE_1:
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id), SEGMENT_END(reed_sw1_yellow.reed_sw_id), RED);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw2_blue.reed_sw_id), SEGMENT_END(reed_sw2_blue.reed_sw_id), WHITE);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw3_green.reed_sw_id), SEGMENT_END(reed_sw3_green.reed_sw_id), BLUE);
			WS2812_SetFragmentColor(SEGMENT_START(reed_sw4_red.reed_sw_id), SEGMENT_END(reed_sw4_red.reed_sw_id), BRONZE);
			WS2812_Update();
			tick = HAL_GetTick();
			reed_sw_colors_init_stage = INIT_STAGE_2;
			break;
		case INIT_STAGE_2:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id), SEGMENT_END(reed_sw1_yellow.reed_sw_id), PURPLE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2_blue.reed_sw_id), SEGMENT_END(reed_sw2_blue.reed_sw_id), YELLOW);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3_green.reed_sw_id), SEGMENT_END(reed_sw3_green.reed_sw_id), PINK);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4_red.reed_sw_id), SEGMENT_END(reed_sw4_red.reed_sw_id), GREEN);
				WS2812_Update();
				tick = HAL_GetTick();
				reed_sw_colors_init_stage = INIT_STAGE_3;
			}
			break;
		case INIT_STAGE_3:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id), SEGMENT_END(reed_sw1_yellow.reed_sw_id), PURPLE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2_blue.reed_sw_id), SEGMENT_END(reed_sw2_blue.reed_sw_id), RED);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3_green.reed_sw_id), SEGMENT_END(reed_sw3_green.reed_sw_id), GREEN);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4_red.reed_sw_id), SEGMENT_END(reed_sw4_red.reed_sw_id), WHITE);
				WS2812_Update();
				tick = HAL_GetTick();
				reed_sw_colors_init_stage = INIT_STAGE_4;
			}
			break;
		case INIT_STAGE_4:
			if(HAL_GetTick() - tick > INIT_NEXT_COLOR_DELAY)
			{
				WS2812_SetAllOff();
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id), SEGMENT_END(reed_sw1_yellow.reed_sw_id), WHITE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2_blue.reed_sw_id), SEGMENT_END(reed_sw2_blue.reed_sw_id), PINK);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3_green.reed_sw_id), SEGMENT_END(reed_sw3_green.reed_sw_id), BRONZE);
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4_red.reed_sw_id), SEGMENT_END(reed_sw4_red.reed_sw_id), PURPLE);
				WS2812_Update();
				reed_sw_colors_state = REED_SW_COLORS_GAME;
			}
			break;
	}
}

void REED_SW_COLORS_Process(void)
{
	REED_SW_Process(&reed_sw1_yellow);
	REED_SW_Process(&reed_sw2_blue);
	REED_SW_Process(&reed_sw3_green);
	REED_SW_Process(&reed_sw4_red);

	switch (reed_sw_colors_state) {
		case REED_SW_COLORS_INIT:
			REED_SW_COLORS_InitStage();
			break;
		case REED_SW_COLORS_GAME:
			if(solved_flag)
			{
				solved_flag = false;
				tick = HAL_GetTick();
				reed_sw_colors_state = REED_SW_COLORS_WAIT_TO_OPEN;
			}
			break;
		case REED_SW_COLORS_WAIT_TO_OPEN:
			if(HAL_GetTick() - tick > DOOR_OPEN_DELAY_1)
			{
				DOOR_Open();
				tick = HAL_GetTick();
				reed_sw_colors_state = REED_SW_COLORS_FINISH;
			}
			break;

		case REED_SW_COLORS_FINISH:
			if(HAL_GetTick() - tick > NEXT_GAME_DELAY)
			{
				reed_sw_colors_state = REED_SW_COLORS_INIT;
			}
			break;
	}
}

uint32_t prev_colors_array[4] = {0, 0, 0, 0}; //Declared over function for debug purpose
uint32_t current_colors_array[4] = {0, 0, 0, 0};

static void ReedSwCallback(reed_sw* reed_sw)
{
	if(reed_sw_colors_state == REED_SW_COLORS_WAIT_TO_OPEN)
		return;

	prev_colors_array[0] = WS2812_GetColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id));
	prev_colors_array[1] = WS2812_GetColor(SEGMENT_START(reed_sw2_blue.reed_sw_id));
	prev_colors_array[2] = WS2812_GetColor(SEGMENT_START(reed_sw3_green.reed_sw_id));
	prev_colors_array[3] = WS2812_GetColor(SEGMENT_START(reed_sw4_red.reed_sw_id));

	if(!solved_flag)
	{
		if(reed_sw == &reed_sw1_yellow)
			{
				uint32_t color = 0x00;

				if(prev_colors_array[0] == RED)
					color = WHITE;
				else if(prev_colors_array[0] == WHITE)
					color = GREEN;
				else if(prev_colors_array[0] == GREEN)
					color = PINK;
				else if(prev_colors_array[0] == PINK)
					color = BLUE;
				else if(prev_colors_array[0] == BLUE)
					color = BRONZE;
				else if(prev_colors_array[0] == BRONZE)
					color = YELLOW;
				else if(prev_colors_array[0] == YELLOW)
					color = PURPLE;
				else if(prev_colors_array[0] == PURPLE)
					color = RED;

				WS2812_SetFragmentColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id), SEGMENT_END(reed_sw1_yellow.reed_sw_id), color);
			}
			else if(reed_sw == &reed_sw2_blue)
			{
				uint32_t color = 0x00;

				if(prev_colors_array[1] == RED)
					color = WHITE;
				else if(prev_colors_array[1] == WHITE)
					color = GREEN;
				else if(prev_colors_array[1] == GREEN)
					color = PINK;
				else if(prev_colors_array[1] == PINK)
					color = BLUE;
				else if(prev_colors_array[1] == BLUE)
					color = BRONZE;
				else if(prev_colors_array[1] == BRONZE)
					color = YELLOW;
				else if(prev_colors_array[1] == YELLOW)
					color = PURPLE;
				else if(prev_colors_array[1] == PURPLE)
					color = RED;
				WS2812_SetFragmentColor(SEGMENT_START(reed_sw2_blue.reed_sw_id), SEGMENT_END(reed_sw2_blue.reed_sw_id), color);
			}
			else if(reed_sw == &reed_sw3_green)
			{
				uint32_t color = 0x00;

				if(prev_colors_array[2] == RED)
					color = WHITE;
				else if(prev_colors_array[2] == WHITE)
					color = GREEN;
				else if(prev_colors_array[2] == GREEN)
					color = PINK;
				else if(prev_colors_array[2] == PINK)
					color = BLUE;
				else if(prev_colors_array[2] == BLUE)
					color = BRONZE;
				else if(prev_colors_array[2] == BRONZE)
					color = YELLOW;
				else if(prev_colors_array[2] == YELLOW)
					color = PURPLE;
				else if(prev_colors_array[2] == PURPLE)
					color = RED;

				WS2812_SetFragmentColor(SEGMENT_START(reed_sw3_green.reed_sw_id), SEGMENT_END(reed_sw3_green.reed_sw_id), color);
			}
			else if(reed_sw == &reed_sw4_red)
			{
				uint32_t color = 0x00;

				if(prev_colors_array[3] == RED)
					color = WHITE;
				else if(prev_colors_array[3] == WHITE)
					color = GREEN;
				else if(prev_colors_array[3] == GREEN)
					color = PINK;
				else if(prev_colors_array[3] == PINK)
					color = BLUE;
				else if(prev_colors_array[3] == BLUE)
					color = BRONZE;
				else if(prev_colors_array[3] == BRONZE)
					color = YELLOW;
				else if(prev_colors_array[3] == YELLOW)
					color = PURPLE;
				else if(prev_colors_array[3] == PURPLE)
					color = RED;

				WS2812_SetFragmentColor(SEGMENT_START(reed_sw4_red.reed_sw_id), SEGMENT_END(reed_sw4_red.reed_sw_id), color);
			}

			WS2812_Update();

			current_colors_array[0] = WS2812_GetColor(SEGMENT_START(reed_sw1_yellow.reed_sw_id));
			current_colors_array[1] = WS2812_GetColor(SEGMENT_START(reed_sw2_blue.reed_sw_id));
			current_colors_array[2] = WS2812_GetColor(SEGMENT_START(reed_sw3_green.reed_sw_id));
			current_colors_array[3] = WS2812_GetColor(SEGMENT_START(reed_sw4_red.reed_sw_id));

			uint8_t red_used = 0;
			uint8_t blue_used = 0;
			uint8_t green_used = 0;
			uint8_t yellow_used = 0;

			uint32_t win_colors[4] = {RED, BLUE, GREEN, YELLOW};

			for(uint8_t i = 0; i < 4; i++)
			{
				for(uint8_t j = 0; j < 4; j++)
				{
					if(current_colors_array[i] == win_colors[j])
					{
						if(win_colors[j] == RED)
						{
							red_used++;
						}
						else if(win_colors[j] == BLUE)
						{
							blue_used++;
						}
						else if(win_colors[j] == GREEN)
						{
							green_used++;
						}
						else if(win_colors[j] == YELLOW)
						{
							yellow_used++;
						}
					}

				}
			}
			if(red_used == 1 && blue_used == 1 && green_used == 1 && yellow_used == 1)
			{
				solved_flag = true;
			}
	}
	HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
}
