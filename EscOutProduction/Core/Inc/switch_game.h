/*
 * switch_game.h
 *
 *  Created on: Sep 4, 2023
 *      Author: stasz
 */

#ifndef INC_SWITCH_GAME_H_
#define INC_SWITCH_GAME_H_

#define RAND_ARRAY_SIZE 12
#define CHECK_DOOR_STATUS_DELAY 500
#define NO_OPEN_DOOR_WAIT_TIME 3000
typedef enum
{
	SWITCH_GAME_INIT,
	SWITCH_GAME_PROCESS,
	SWITCH_GAME_FINISH
}switch_game_state_t;

void SWITCH_GAME_Init(void);
void SWITCH_GAME_Process(void);

#endif /* INC_SWITCH_GAME_H_ */
