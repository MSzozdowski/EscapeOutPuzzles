/*
 * cap_sensor.h
 *
 *  Created on: Oct 20, 2023
 *      Author: stasz
 */

#ifndef INC_APPLICATION_CAP_SENSOR_H_
#define INC_APPLICATION_CAP_SENSOR_H_

#define CAP_SENS_DEBOUNCE_TIME 100

typedef enum
{
	CAP_SENS_NOT_DETECTED,
	CAP_SENS_DEBOUNCE,
	CAP_SENS_DETECTED
}cap_sens_state_t;

typedef void (*SensorDetectedCallback)(void);

void CAP_SENSOR_Init(void);
void CAP_SENSOR_Process(void);
void CAP_SENSOR_DetectedCallback(SensorDetectedCallback callback);
cap_sens_state_t CAP_SENSOR_GetState(void);

#endif /* INC_APPLICATION_CAP_SENSOR_H_ */
