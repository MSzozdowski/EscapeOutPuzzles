/*
 * comms.h
 *
 *  Created on: Sep 29, 2024
 *      Author: AG
 */

#ifndef INC_DRIVER_COMMS_H_
#define INC_DRIVER_COMMS_H_

#include "app/board_id.h"

#define MASTER_TRANSMIT_INTERVAL	2000
#define SLAVE_1_STATE_REQUEST		0x31 //'1'
#define SLAVE_2_STATE_REQUEST		0x32 //'2'
#define SLAVE_3_STATE_REQUEST		0x33 //'3'
#define SLAVE_RESET_REQUEST			0x52 //'R'

#define EYES_ARE_CENTER				0x41 //'A'
#define EYES_ARE_UP					0x42 //'B'
#define EYES_ARE_RIGHT				0x43 //'C'
#define EYES_ARE_DOWN				0x44 //'D'
#define EYES_ARE_LEFT				0x45 //'E'

#define RECEIVE_BUFFER_SIZE			8

void COMMS_Init(UART_HandleTypeDef* uart, board_id_e board_id, GPIO_TypeDef *GPIO_Port_En, uint16_t GPIO_Pin_En);
void COMMS_Process(void);

#endif /* INC_DRIVER_COMMS_H_ */
