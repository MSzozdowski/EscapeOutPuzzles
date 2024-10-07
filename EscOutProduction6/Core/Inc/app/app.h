/*
 * app.h
 *
 *  Created on: Sep 27, 2024
 *      Author: AG
 */

#ifndef INC_APP_APP_H_
#define INC_APP_APP_H_

#include <string.h>

#include "main.h"
#include "led.h"
#include "st7735.h"
#include "fonts.h"

#define MAIN_LOOP_TIME (50)	//50ms
#define MCU_SEL_MAX (4)

extern uint8_t g_mcu_id;

void APP_Init(void);
void APP_Main(void);

#endif /* INC_APP_APP_H_ */
