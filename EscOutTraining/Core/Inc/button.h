/*
 * button.h
 *
 *  Created on: Aug 26, 2023
 *      Author: stasz
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define DEBOUNCE_TIME 20

typedef enum
{
	BUTTON_IDLE,
	BUTTON_DEBOUNCE,
	BUTTON_PRESSED,
	BUTTON_RELEASED
}button_state_t;

typedef enum
{
	BUTTON_LED_ON,
	BUTTON_LED_OFF
}button_led_state_t;

typedef struct
{
	GPIO_TypeDef* SW_Port;
	uint16_t SW_Pin;
	GPIO_TypeDef* LED_Port;
	uint16_t LED_Pin;
	button_state_t button_state;
	button_led_state_t button_led_state;
	uint32_t last_tick;
}button_t;


void BUTTON_Init(button_t* button, GPIO_TypeDef* SW_Port, uint16_t SW_Pin, GPIO_TypeDef* LED_Port, uint16_t LED_Pin);
void BUTTON_Process(button_t* button);

#endif /* INC_BUTTON_H_ */
