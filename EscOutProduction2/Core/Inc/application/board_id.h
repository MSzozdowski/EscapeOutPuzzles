/*
 * board_id.h
 *
 *  Created on: Sep 6, 2023
 *      Author: stasz
 */

#ifndef INC_BOARD_ID_H_
#define INC_BOARD_ID_H_

#define REFERENCE_VOLTAGE 3300

#define BUTTON_GAME_MILLIVOLTS_THRESHOLD 3000

#define REED_SWITCH_MILLIVOLTS_THRESHOLD_MIN 1350
#define REED_SWITCH_MILLIVOLTS_THRESHOLD_MAX 1950

#define METAL_BALL_MILLIVOLTS_THRESHOLD 300

typedef enum
{
	BOARD_IS_REED_SWITCH = 0,
	BOARD_IS_BUTTON_GAME = 1,
	BOARD_IS_METAL_BALL = 2,
	BOARD_NOT_DEFINED = 3
}board_id_t;

void BOARD_ID_Init(ADC_HandleTypeDef* hadc, uint32_t channel);
board_id_t BOARD_ID_GetBoardID(void);

#endif /* INC_BOARD_ID_H_ */
