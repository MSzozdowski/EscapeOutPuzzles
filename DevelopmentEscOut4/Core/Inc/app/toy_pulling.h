/*
 * toy_pulling.h
 *
 *  Created on: Dec 10, 2023
 *      Author: stasz
 */

#ifndef INC_APP_TOY_PULLING_H_
#define INC_APP_TOY_PULLING_H_

#define TOY_PULLING_OPEN_DELAY 1500

typedef enum
{
	TOY_PULLING_IDLE,
	TOY_PULLING_SENS_DETECTED,
	TOY_PULLING_WAIT
}toy_pulling_state_t;

void TOY_PULLING_Init(void);
void TOY_PULLING_Process(void);

#endif /* INC_APP_TOY_PULLING_H_ */
