/*
 * shout_led.h
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */
#ifndef INC_SHOUT_LED_H_
#define INC_SHOUT_LED_H_

#define INIT_DELAY 50

#define INIT_TIME_MIN 1500
#define INIT_TIME_MAX 1700

#define PROGRESS_TIME 100
#define REGRESS_TIME 5

#define PROGRESS_TO_REGRESS_TIME 150
#define REGRESS_TO_PROGRESS_TIME 150

#define ZERO_PERCENT 0
#define ONE_HUNDRED_PERCENT 350

#define SHOUT_THRESHOLD 300

#define RED 0xFF
#define GREEN 0x00
#define BLUE 0x00

#define RED_FINISH 0xFF
#define GREEN_FINISH 0xFF
#define BLUE_FINISH 0x00

#define BLINK_TIME_INITIAL 1000
#define BLINK_COUNTER_INITIAL 15

#define BLINK_TIME_STEP 100

#define NEXT_ROUND_DELAY 5000


typedef enum
{
	INIT,
	LED_IDLE,
	START_SHOUTING,
	PROGRESS,
	REGRESS,
	FINISH_BLINK,
	FINISH
}shout_led_state_t;

void ShoutLED_Init(void);
void ShoutLED_Process(void);

#endif /* INC_SHOUT_LED_H_ */
