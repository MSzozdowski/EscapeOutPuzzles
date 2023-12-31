/*
 * distance_sens.h
 *
 *  Created on: Dec 10, 2023
 *      Author: stasz
 */

#ifndef INC_APP_DISTANCE_SENS_H_
#define INC_APP_DISTANCE_SENS_H_

#define DISTANCE_SENS_DEBOUNCE_TIME 100
#define DISTANCE_SENS_WAIT_TIME 3000

typedef enum
{
	DISTANCE_SENS_IDLE,
	DISTANCE_SENS_DEBOUNCE,
	DISTANCE_SENS_WAIT
}distance_sens_state_t;

typedef struct
{
	distance_sens_state_t distance_sens_state;
	GPIO_TypeDef 	*GpioPort;
	uint16_t 		GpioPin;
	uint32_t 		distance_sens_tick;
	uint8_t 		distance_sens_id;
}distance_sens_t;

typedef void (*DistanceSensActive)(distance_sens_t* distance_sens);

void DISTANCE_SENS_Init(distance_sens_t* distance_sens, GPIO_TypeDef* GpioPort, uint16_t GpioPin, uint8_t sens_id);
void DISTANCE_SENS_Process(distance_sens_t* distance_sens);

void DistanceSensDetectedCallback(DistanceSensActive callback);
void DistanceSensReleasedCallback(DistanceSensActive callback);

#endif /* INC_APP_DISTANCE_SENS_H_ */
