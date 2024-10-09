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

#define RECEIVE_BUFFER_SIZE			8

typedef enum
{
	SLAVE_1_STATE_REQUEST 	= 0x31,//'1'
	SLAVE_2_STATE_REQUEST 	= 0x32,//'2'
	SLAVE_3_STATE_REQUEST 	= 0x33,//'3'
	SLAVE_RESET_REQUEST	 	= 0x52 //'R'
}master_request_command_e;

typedef enum
{
	EYES_ARE_CENTER = 0x41, //'A'
	EYES_ARE_UP 	= 0x42, //'B'
	EYES_ARE_RIGHT 	= 0x43, //'C'
	EYES_ARE_DOWN 	= 0x44, //'D'
	EYES_ARE_LEFT 	= 0x45 	//'E'
}eyes_state_e;

typedef enum
{
	MASTER_TO_SLAVE = 0x3E, // '>'
	SLAVE_TO_MASTER = 0x3C, // '<'
}frame_type_e;

typedef struct
{
	frame_type_e frame_type;
	master_request_command_e master_request_command;
}master_frame_t;

typedef struct
{
	frame_type_e frame_type;
	board_id_e board_type;
	eyes_state_e state;
}slave_frame_t;

void COMMS_Init(UART_HandleTypeDef* uart, board_id_e board_id, GPIO_TypeDef *GPIO_Port_En, uint16_t GPIO_Pin_En);
void COMMS_Process(void);

#endif /* INC_DRIVER_COMMS_H_ */
