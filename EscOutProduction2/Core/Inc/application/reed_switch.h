/*
 * reed_switch.h
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_REED_SWITCH_H_
#define INC_APPLICATION_REED_SWITCH_H_

typedef enum
{
	REED_SW_IDLE,
	REED_SW_DEBOUNCE,
	REED_SW_WAIT
}reed_sw_state_t;

typedef struct
{
	reed_sw_state_t reed_sw_state;
	GPIO_TypeDef 	*GpioPort;
	uint16_t 		GpioPin;
	uint32_t 		reed_sw_tick;
}reed_sw;

void REED_SW_Init(void);

void REED_SW_Process(void);

#endif /* INC_APPLICATION_REED_SWITCH_H_ */
