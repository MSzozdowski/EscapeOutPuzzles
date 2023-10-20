/*
 * button_game.h
 *
 *  Created on: Oct 16, 2023
 *      Author: stasz
 */

#ifndef INC_BUTTON_GAME_H_
#define INC_BUTTON_GAME_H_

#define NEXT_ROUND_TIME 4000

void BUTTON_GAME_Init(void);
void BUTTON_GAME_Process(void);

typedef enum
{
	BUTTON_GAME_IDLE,
	BUTTON_GAME_PRESSED,
	BUTTON_GAME_DOOR_OPEN,
	BUTTON_GAME_WAIT
}button_game_state_t;

#endif /* INC_BUTTON_GAME_H_ */
