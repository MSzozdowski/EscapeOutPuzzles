/*
 * comms.c
 *
 *  Created on: Sep 29, 2024
 *      Author: AG
 */
#include "comms.h"
#include "usart.h"


#define TX_BUF_SIZE (5)

extern uint8_t g_mcu_id;

typedef struct{
	uint8_t id;
	uint8_t cmd;
	uint8_t status;
	uint8_t crc;
}comms_data_t;

comms_data_t tx_frame;

static inline void uart_tx_en(GPIO_PinState PinState){
	HAL_GPIO_WritePin(RS_485_EN_GPIO_Port, RS_485_EN_Pin, PinState);
}

static void uart_tx(comms_data_t *data){
	uint8_t tx_buffer[TX_BUF_SIZE];
	uart_tx_en(ON);
	tx_buffer[0] = '<';
	tx_buffer[1] = data->id;
	tx_buffer[2] = data->cmd;
	tx_buffer[3] = data->status;
	tx_buffer[4] = data->crc;
	HAL_UART_Transmit(&huart1, &tx_buffer[0], TX_BUF_SIZE, 1000);
	uart_tx_en(OFF);
}

void Comms_init(){

}


void Process_comms(){

	if(g_mcu_id == MASTER_ID){

		if(++tx_frame.id > NO_OF_DEVICES)
		{
			tx_frame.id = 2;
		}


		uart_tx(&tx_frame);
	}else{
		tx_frame.id = 1;
		tx_frame.cmd = 0x01;

		uart_tx(&tx_frame);
	}


}
