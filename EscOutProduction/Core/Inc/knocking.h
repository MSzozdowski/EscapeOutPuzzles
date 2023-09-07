/*
 * knocking.h
 *
 *  Created on: Aug 24, 2023
 *      Author: stasz
 */

#ifndef INC_KNOCKING_H_
#define INC_KNOCKING_H_

#define PIEZO_THRESHOLD 450
#define KNOCK_INTERVAL 200
#define KNOCK_MAX_SEQUENCE_TIME 3000
#define FAIL_DELAY 1000
#define KNOCK_SOLVE_VALUE 4
#define NEXT_ROUND_DELAY 5000
typedef enum
{
	KNOCKING_IDLE,
	START_KNOCKING,
	KNOCKING_FAILED,
	FINISH_KNOCKING
}knocking_state_t;

void KNOCKING_Init(void);
void KNOCKING_Process(void);

#endif /* INC_KNOCKING_H_ */
