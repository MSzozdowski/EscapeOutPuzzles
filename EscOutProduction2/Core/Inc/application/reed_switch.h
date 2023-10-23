/*
 * reed_switch.h
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_REED_SWITCH_H_
#define INC_APPLICATION_REED_SWITCH_H_

#define REED_SW_DEBOUNCE_TIME 20
#define REED_SW_WAIT_TIME 1000

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
	uint8_t 		reed_sw_id;
}reed_sw;

typedef void (*ReedSwitchActive)(reed_sw* reed_sw);

void REED_SW_Init(reed_sw* reed_sw, GPIO_TypeDef* GpioPort, uint16_t GpioPin, uint8_t reed_id);
void REED_SW_Process(reed_sw* reed_sw);

void ReedSwitchCallBack(ReedSwitchActive callback);

#endif /* INC_APPLICATION_REED_SWITCH_H_ */
