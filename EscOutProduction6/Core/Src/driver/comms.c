/*
 * comms.c
 *
 *  Created on: Sep 29, 2024
 *      Author: AG
 */
#include "main.h"
#include "driver/comms.h"
#include "usart.h"
#include "driver/led.h"
#include "string.h"

static void COMMS_RS485_TransmitCommand(uint8_t* command);
static inline void COMMS_RS485_TransmitEnable(void);
static inline void COMMS_RS485_ReceiveEnable(void);

static UART_HandleTypeDef* comms_uart;
static board_id_e board_type;

static GPIO_TypeDef *COMMS_Port_Enable;
static uint16_t COMMS_Pin_Enable;

static uint8_t comms_receive_buffer[RECEIVE_BUFFER_SIZE] = {0};
static uint8_t return_eyes_state_flag = 0;

static slave_frame_t slave_frame;
static master_frame_t master_frame;

static eyes_state_e eyes_state_array[4] = {EYES_ARE_CENTER};

void COMMS_Init(UART_HandleTypeDef* uart, board_id_e board_id, GPIO_TypeDef *GPIO_Port_En, uint16_t GPIO_Pin_En)
{
	comms_uart = uart;
	board_type = board_id;
	COMMS_Port_Enable = GPIO_Port_En;
	COMMS_Pin_Enable = GPIO_Pin_En;

	COMMS_RS485_ReceiveEnable();
	HAL_UARTEx_ReceiveToIdle_DMA(comms_uart, comms_receive_buffer, RECEIVE_BUFFER_SIZE);

	//DEPENDS OF BOARD TYPE FILL STRUCTURES
	if(board_type == BOARD_ID_MASTER)
	{
		master_frame.frame_type = MASTER_TO_SLAVE;
		master_frame.master_request_command = SLAVE_1_STATE_REQUEST;
	}else if(board_type != BOARD_ID_WRONG) //SLAVE 1/2/3
	{
		slave_frame.frame_type = SLAVE_TO_MASTER;
		slave_frame.board_type = board_type;
		slave_frame.state = EYES_ARE_CENTER;
	}
}

void COMMS_Process(void)
{
	static uint32_t last_tick = 0;
	static board_id_e master_array_pointer = BOARD_ID_SLAVE_1;

	if(board_type == BOARD_ID_MASTER)
	{
		if(HAL_GetTick() - last_tick >= MASTER_TRANSMIT_INTERVAL)
		{
			switch (master_array_pointer)
			{
				case BOARD_ID_SLAVE_1:
					master_frame.master_request_command = SLAVE_1_STATE_REQUEST;
					COMMS_RS485_TransmitCommand((uint8_t*)&master_frame);
					break;

				case BOARD_ID_SLAVE_2:
					master_frame.master_request_command = SLAVE_2_STATE_REQUEST;
					COMMS_RS485_TransmitCommand((uint8_t*)&master_frame);
					break;

				case BOARD_ID_SLAVE_3:
					master_frame.master_request_command = SLAVE_3_STATE_REQUEST;
					COMMS_RS485_TransmitCommand((uint8_t*)&master_frame);
					break;

				default:
					break;
			}

			if(++master_array_pointer > BOARD_ID_SLAVE_3)
				master_array_pointer = BOARD_ID_SLAVE_1;

			last_tick = HAL_GetTick();
		}
	}else if(board_type != BOARD_ID_WRONG) //SLAVE 1/2/3
	{
		if(return_eyes_state_flag)
		{
			LED_Toggle();

			COMMS_RS485_TransmitCommand((uint8_t*)&slave_frame);
			return_eyes_state_flag = 0;
		}
	}
}

static inline void COMMS_RS485_TransmitEnable(void)
{
	HAL_GPIO_WritePin(COMMS_Port_Enable, COMMS_Pin_Enable, GPIO_PIN_SET);
}

static inline void COMMS_RS485_ReceiveEnable(void)
{
	HAL_GPIO_WritePin(COMMS_Port_Enable, COMMS_Pin_Enable, GPIO_PIN_RESET);
}

static void COMMS_RS485_TransmitCommand(uint8_t* command)
{
	COMMS_RS485_TransmitEnable();
	HAL_UART_Transmit(comms_uart, command, strlen((const char*)command), 1000);
	COMMS_RS485_ReceiveEnable();
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart == comms_uart)
	{
		HAL_UARTEx_ReceiveToIdle_DMA(comms_uart, comms_receive_buffer, RECEIVE_BUFFER_SIZE);

		if(board_type == BOARD_ID_WRONG)
			return;

		switch (comms_receive_buffer[0]) { //RECEIVED FRAME TYPE
			case MASTER_TO_SLAVE: //SLAVE RECEIVED COMMAND FROM MASTER
					master_frame.master_request_command = comms_receive_buffer[1];

					if(master_frame.master_request_command == SLAVE_1_STATE_REQUEST && board_type == BOARD_ID_SLAVE_1)
					{
						return_eyes_state_flag = 1;
					}
					else if(master_frame.master_request_command == SLAVE_2_STATE_REQUEST && board_type == BOARD_ID_SLAVE_2)
					{
						return_eyes_state_flag = 1;
					}
					else if(master_frame.master_request_command == SLAVE_3_STATE_REQUEST && board_type == BOARD_ID_SLAVE_3)
					{
						return_eyes_state_flag = 1;
					}
					else if(master_frame.master_request_command == SLAVE_RESET_REQUEST)
					{
						//#TODO:
					}
				}
				break;

			case SLAVE_TO_MASTER: //MASTER RECEIVED ACK FROM SLAVE
					slave_frame.board_type = comms_receive_buffer[0];
					slave_frame.state = comms_receive_buffer[1];

					//WRITE REFRESHED STATE TO THE ARRAY
					eyes_state_array[slave_frame.board_type] = slave_frame.state;
				break;
		}
	}
}
