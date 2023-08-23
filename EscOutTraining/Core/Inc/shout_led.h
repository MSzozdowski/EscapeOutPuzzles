/*
 * shout_led.h
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */
//#ifdef MY_MACRO
#ifndef INC_SHOUT_LED_H_
#define INC_SHOUT_LED_H_

#define INIT_TIME 500

#define PROGRESS_TIME 300
#define REGRESS_TIME 450

#define PROGRESS_TO_REGRESS_TIME 1000
#define REGRESS_TO_PROGRESS_TIME 500

#define ZERO_PERCENT 0
#define ONE_HUNDRED_PERCENT 100

#define SHOUT_THRESHOLD 500

#define RED 0x01
#define GREEN 0x00
#define BLUE 0x00

typedef enum
{
	IDLE,
	START_SHOUTING,
	PROGRESS,
	REGRESS,
	FINISH
}shout_led_state_t;

void ShoutLED_Init(void);
void ShoutLED_Process(void);

#endif /* INC_SHOUT_LED_H_ */
//#endif /* MY_MACRO */
