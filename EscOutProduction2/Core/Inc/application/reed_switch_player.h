/*
 * reed_sw_player.h
 *
 *  Created on: Oct 21, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_REED_SWITCH_PLAYER_H_
#define INC_APPLICATION_REED_SWITCH_PLAYER_H_

#define LAST_MUSIC_DELAY 500
#define DOOR_OPEN_DELAY 1000

typedef enum
{
	REED_SWITCH_PLAYER_WAIT,
	REED_SWITCH_PLAYER_SOLVED,
	REED_SWITCH_PLAYER_OPEN_DOOR
}reed_switch_player_state_t;

void REED_SW_PLAYER_Init(void);
void REED_SW_PLAYER_Process(void);

#endif /* INC_APPLICATION_REED_SWITCH_PLAYER_H_ */
