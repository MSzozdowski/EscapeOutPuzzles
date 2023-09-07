/*
 * piezo.h
 *
 *  Created on: Aug 24, 2023
 *      Author: stasz
 */

#ifndef INC_PIEZO_H_
#define INC_PIEZO_H_

#define REFERENCE_VOLTAGE 3300

void PIEZO_Init(ADC_HandleTypeDef* hadc, uint32_t channel);
uint16_t PIEZO_GetMillivolts(void);

#endif /* INC_PIEZO_H_ */
