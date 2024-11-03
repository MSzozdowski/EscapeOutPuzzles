/*
 * metal_ball.h
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_METAL_BALL_H_
#define INC_APPLICATION_METAL_BALL_H_

#define METAL_BALL_NEXT_ROUND_TIME 1000
#define METAL_BALL_DELAY_REACTION 1000

typedef enum
{
	METAL_BALL_IDLE,
	METAL_BALL_DETECTED,
	METAL_BALL_WAIT
}metal_ball_state_t;

void METAL_BALL_Init(void);
void METAL_BALL_Process(void);

#endif /* INC_APPLICATION_METAL_BALL_H_ */
