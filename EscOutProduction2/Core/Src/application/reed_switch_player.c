/*
 * reed_switch_player.c
 *
 *  Created on: 22 paź 2023
 *      Author: stasz
 */

#include "main.h"
#include "application/reed_switch_player.h"
#include "application/reed_switch.h"
#include "application/dfplayer.h"
#include "application/door.h"
#include "usart.h"
#include "string.h"
#include "stdbool.h"

static void ReedSwCallback(reed_sw* reed_sw);

static reed_sw reed_sw1;
static reed_sw reed_sw2;
static reed_sw reed_sw3;
static reed_sw reed_sw4;
static reed_sw reed_sw5;

static bool puzzle_solved_flag;
static reed_switch_player_state_t reed_switch_player_state;
static uint32_t reed_switch_player_tick;

void REED_SW_PLAYER_Init(void)
{
	REED_SW_Init(&reed_sw1, REED_SW1_GPIO_Port, REED_SW1_Pin, 1);
	REED_SW_Init(&reed_sw2, REED_SW2_GPIO_Port, REED_SW2_Pin, 2);
	REED_SW_Init(&reed_sw3, REED_SW3_GPIO_Port, REED_SW3_Pin, 3);
	REED_SW_Init(&reed_sw4, REED_SW4_GPIO_Port, REED_SW4_Pin, 4);
	REED_SW_Init(&reed_sw5, REED_SW5_GPIO_Port, REED_SW5_Pin, 5);

	DFPLAYER_Init(&huart2);

	ReedSwitchCallBack(ReedSwCallback);
	puzzle_solved_flag = false;
	reed_switch_player_state = REED_SWITCH_PLAYER_WAIT;
}

void REED_SW_PLAYER_Process(void)
{
	REED_SW_Process(&reed_sw1);
	REED_SW_Process(&reed_sw2);
	REED_SW_Process(&reed_sw3);
	REED_SW_Process(&reed_sw4);
	REED_SW_Process(&reed_sw5);

	switch (reed_switch_player_state)
	{
		case REED_SWITCH_PLAYER_WAIT:
			if(puzzle_solved_flag == true)
			{
				reed_switch_player_tick = HAL_GetTick();
				reed_switch_player_state = REED_SWITCH_PLAYER_SOLVED;
			}
			break;
		case REED_SWITCH_PLAYER_SOLVED:
			if(HAL_GetTick() - reed_switch_player_tick > LAST_MUSIC_DELAY)
			{
				DFPLAYER_Play(6); //last song when before open doors
				reed_switch_player_tick = HAL_GetTick();
				reed_switch_player_state = REED_SWITCH_PLAYER_OPEN_DOOR;
			}
			break;
		case REED_SWITCH_PLAYER_OPEN_DOOR:
			if(HAL_GetTick() - reed_switch_player_tick > DOOR_OPEN_DELAY)
			{
				puzzle_solved_flag = false;
				DOOR_Open();
				reed_switch_player_state = REED_SWITCH_PLAYER_WAIT;
			}
			break;
	}
}

static uint8_t number = 0;
static uint32_t reed_sw_tick = 0;
static void ReedSwCallback(reed_sw* reed_sw)
{
	//1 - H
	//2 - P
	//3 - U
	//4 - J
	//5 - B
	//Solution U-B-P -> 3-5-2
	if(reed_switch_player_state == REED_SWITCH_PLAYER_WAIT && HAL_GetTick() - reed_sw_tick > NEXT_TOUCH_TIME)
	{
		reed_sw_tick = HAL_GetTick();
		if(reed_sw == &reed_sw1) //1-H
		{
			DFPLAYER_Play(reed_sw->reed_sw_id);
			number = 0;
		}
		else if(reed_sw == &reed_sw2) //2-P
		{
			DFPLAYER_Play(reed_sw->reed_sw_id);
			if(number == 2) //3rd good touch
			{
				puzzle_solved_flag = true;
				number = 0;
			}
			else
			{
				number = 0;
			}
		}
		else if(reed_sw == &reed_sw3) //3-U
		{
			DFPLAYER_Play(reed_sw->reed_sw_id);
			number = 1; //1st good touch
		}
		else if(reed_sw == &reed_sw4) //4-J
		{
			DFPLAYER_Play(reed_sw->reed_sw_id);
			number = 0;
		}
		else if(reed_sw == &reed_sw5)  //5-B
		{
			DFPLAYER_Play(reed_sw->reed_sw_id);
			if(number == 1) //2nd good touch
			{
				number = 2;
			}
			else
			{
				number =  0;
			}
		}
	}
	HAL_GPIO_TogglePin(DBG_LED_GPIO_Port, DBG_LED_Pin);
}
