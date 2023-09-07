/*
 * microphone.h
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */

#ifndef INC_MICROPHONE_H_
#define INC_MICROPHONE_H_

#define REFERENCE_VOLTAGE 3300

void MICROPHONE_Init(ADC_HandleTypeDef* hadc, uint32_t channel);
uint16_t MICROPHONE_GetMillivolts(void);

#endif /* INC_MICROPHONE_H_ */
