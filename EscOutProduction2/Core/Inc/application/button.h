/*
 * button.h
 *
 *  Created on: Oct 16, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_BUTTON_H_
#define INC_APPLICATION_BUTTON_H_

#define SHORT_BLINK_TIME_ON 200
#define SHORT_BLINK_TIME_OFF 2000

#define THREE_BLINK_TIME 300

#define DEBOUNCE_TIME 20

typedef enum
{
	LED_OFF,
	LED_ON,
	LED_CONT_SHORT_BLINK,
	LED_THREE_BLINKS
}led_state_t;

typedef enum
{
	BUTTON_IDLE,
	BUTTON_DEBOUNCE,
	BUTTON_PRESSED
}button_state_t;

typedef void (*PressedCallback)(void);

void BUTTON_LED_Init(void);
void BUTTON_LED_Process(void);
void BUTTON_LED_SetState(led_state_t led_st);
led_state_t BUTTON_LED_GetLEDState(void);
button_state_t BUTTON_LED_GetButtonState(void);
void BUTTON_PressCallback(PressedCallback callback);

#endif /* INC_APPLICATION_BUTTON_H_ */
