/*
 * buzzer.h
 *
 *  Created on: Oct 15, 2026
 *      Author: stasz
 */

#ifndef INC_APP_BUZZER_H_
#define INC_APP_BUZZER_H_

#include "gpio.h"

typedef enum
{
	BUZZER_IDLE,
	BUZZER_START,
	BUZZER_ON,
	BUZZER_OFF
}buzzer_state_t;

typedef struct
{
	buzzer_state_t buzzer_state;
    GPIO_TypeDef* GpioPort;
    uint16_t GpioPin;

    uint32_t on_time_ms;
    uint32_t off_time_ms;
    uint32_t last_tick;

    uint8_t beeps_remaining;
}buzzer_t;

void BUZZER_Init(buzzer_t *buzzer, GPIO_TypeDef *GpioPort, uint16_t GpioPin);
void BUZZER_Start(buzzer_t *buzzer, uint32_t on_time_ms, uint32_t off_time_ms, uint8_t beep_count);
void BUZZER_Process(buzzer_t *buzzer);

#endif /* INC_APP_BUZZER_H_ */
