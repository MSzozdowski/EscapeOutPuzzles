/*
 * board_id.h
 *
 *  Created on: 7 paź 2024
 *      Author: stasz
 */

#ifndef INC_APP_BOARD_ID_H_
#define INC_APP_BOARD_ID_H_

#define MCU_SEL_PINS 4

typedef enum
{
	BOARD_ID_MASTER = 1,
	BOARD_ID_SLAVE_1 = 2,
	BOARD_ID_SLAVE_2 = 3,
	BOARD_ID_SLAVE_3 = 4,
	BOARD_ID_WRONG
}board_id_e;

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
}board_id_ports_t;

board_id_e BOARD_ID_GetBoardID(void);

#endif /* INC_APP_BOARD_ID_H_ */
