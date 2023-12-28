/*
 * cap_sense_player.h
 *
 *  Created on: 2 gru 2023
 *      Author: stasz
 */

#ifndef INC_APP_CAP_SENSE_PLAYER_H_
#define INC_APP_CAP_SENSE_PLAYER_H_

#define STAGE_1_DURATION 3500
#define STAGE_2_DURATION 6500
#define MAX_TOUCH_INTERVAL 1500
#define DOOR_OPEN_DELAY 1000

typedef enum
{
	CAP_SENSE_PLAYER_INIT,
	CAP_SENSE_PLAYER_STAGE_1,
	CAP_SENSE_PLAYER_STAGE_2,
	CAP_SENSE_PLAYER_OPEN_DOOR
}cap_sense_player_state_t;

void CAP_SENSE_PLAYER_Init(void);
void CAP_SENSE_PLAYER_Process(void);

#endif /* INC_APP_CAP_SENSE_PLAYER_H_ */
