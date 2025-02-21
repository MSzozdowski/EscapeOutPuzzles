/*
 * relay_buzzer.h
 *
 *  Created on: Feb 21, 2025
 *      Author: stasz
 */

#ifndef INC_APP_RELAY_BUZZER_H_
#define INC_APP_RELAY_BUZZER_H_

typedef enum {
	RELAY_BUZZER_IDLE,
	RELAY_BUZZER_OFF,
	RELAY_BUZZER_ON
}relay_buzzer_state_t;

typedef struct
{
	relay_buzzer_state_t relay_buzzer_state;
	GPIO_TypeDef 	*GpioPort;
	uint16_t 		GpioPin;
	uint32_t 		last_tick;
	uint16_t 		time_on;
	uint16_t 		time_off;
	uint8_t 		buzz_times;
}relay_buzzer_t;

void RELAY_BUZZER_Init(relay_buzzer_t* relay_buzzer, GPIO_TypeDef *GpioPort, uint16_t GpioPin);
void RELAY_BUZZER_Process(relay_buzzer_t* relay_buzzer);
void RELAY_BUZZER_Start(relay_buzzer_t* relay_buzzer, uint16_t time_on, uint16_t time_off, uint8_t buzz_times);

#endif /* INC_APP_RELAY_BUZZER_H_ */
