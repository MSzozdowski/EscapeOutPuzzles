/*
 * button.h
 *
 *  Created on: Aug 26, 2023
 *      Author: stasz
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdbool.h>

//Button defines
#define DEBOUNCE_TIME 20
#define NEXT_PRESS_TIME 200

//Button LEDs defines
#define BUTTON_BLINK_TIME 750
#define BUTTON_FAST_BLINK_TIME 350
#define BUTTON_BLINK_NEXT_BLINK 500

typedef enum
{
	BUTTON_IDLE,
	BUTTON_DEBOUNCE,
	BUTTON_PRESSED
}button_state_t;

typedef enum
{
	BUTTON_LED_IDLE,
	BUTTON_LED_ON,
	BUTTON_LED_TOGGLE,
	BUTTON_LED_BLINK,
	BUTTON_LED_THREE_FAST_BLINKS,
	BUTTON_LED_OFF
}button_led_state_t;

typedef enum
{
	LED_ON,
	LED_OFF,
	LED_TOGGLE
}led_state_t;

typedef enum
{
	BUTTON_WAS_PRESSED,
	BUTTON_WAS_NOT_PRESSED
}button_press_flag_t;

typedef struct
{
	GPIO_TypeDef* SW_Port;
	uint16_t SW_Pin;
	GPIO_TypeDef* LED_Port;
	uint16_t LED_Pin;
	button_state_t button_state;
	button_led_state_t button_led_state;
	button_press_flag_t button_press_flag;
	uint32_t button_last_tick;
	uint32_t led_last_tick;
	bool button_accept_press;
	uint8_t button_led_blink_stage;
	uint8_t button_blink_counter;
	void(*ButtonPositivePressed)(void);
	void(*ButtonNegativePressed)(void);
}button_t;


void BUTTON_Init(button_t* button, GPIO_TypeDef* SW_Port, uint16_t SW_Pin, GPIO_TypeDef* LED_Port, uint16_t LED_Pin);
void BUTTON_RegisterPositivePressCallBack(button_t *button, void *callback);
void BUTTON_RegisterNegativePressCallBack(button_t *button, void *callback);
void BUTTON_Process(button_t* button);

void BUTTON_LED_SetState(button_t* button, button_led_state_t button_led_state);
button_led_state_t BUTTON_LED_GetState(button_t* button);

#endif /* INC_BUTTON_H_ */
