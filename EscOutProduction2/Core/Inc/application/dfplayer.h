/*
 * dfplayer.h
 *
 *  Created on: Sep 29, 2023
 *      Author: stasz
 */

#ifndef INC_APP_DFPLAYER_H_
#define INC_APP_DFPLAYER_H_

//FRAME BITS
#define START_BIT 	0x7E
#define VERSION 	0xFF
#define CMD_LENGTH	0x06
#define FEEDBACK	0x01
#define END_BIT		0xEF

#define FRAME_LENGTH 10

//DFP CONTROL COMMANDS
#define SEL_TRACK 	0x03
#define SPEC_VOL	0x06
#define SPEC_EQ		0x07
#define RST_MOD		0x0C

//DFP QUERY COMMANDS
#define QRY_CUR_STAT	0x42
#define INIT_PARAMS		0x3F

//DFP SOURCE
#define SD_CARD 0x02

typedef enum
{
	DFP_ON,
	DFP_OFF
}busy_state_t;

void DFPLAYER_Init(UART_HandleTypeDef* uart);
void DFPLAYER_Play(uint8_t audio_number);

#endif /* INC_APP_DFPLAYER_H_ */
