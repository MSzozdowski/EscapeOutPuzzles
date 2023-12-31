/*
 * board_id.h
 *
 *  Created on: Sep 6, 2023
 *      Author: stasz
 */

#ifndef INC_BOARD_ID_H_
#define INC_BOARD_ID_H_

#define REFERENCE_VOLTAGE 3300

#define REED_SWITCH_MILLIVOLTS_THRESHOLD 300
#define CAP_SENSE_PLAYER_MILLLIVOLTS_THRESHOLD 3000

typedef enum
{
	BOARD_IS_REED_SWITCH_COLORS = 0,
	BOARD_IS_CAP_SENSE_PLAYER = 1,
	BOARD_NOT_DEFINED = 3
}board_id_t;

void BOARD_ID_Init(ADC_HandleTypeDef* hadc, uint32_t channel);
board_id_t BOARD_ID_GetBoardID(void);

#endif /* INC_BOARD_ID_H_ */
