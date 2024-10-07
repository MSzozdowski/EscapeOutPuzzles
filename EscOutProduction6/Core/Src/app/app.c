/*
 * app.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AG
 */

#include "app.h"
#include "comms.h"

uint32_t prev_tick;

uint8_t g_mcu_id;

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;

}mcu_sel_t;

mcu_sel_t mcu_selection[4] = {
		{MCU_SEL1_GPIO_Port,MCU_SEL1_Pin},
		{MCU_SEL2_GPIO_Port,MCU_SEL2_Pin},
		{MCU_SEL3_GPIO_Port,MCU_SEL3_Pin},
		{MCU_SEL4_GPIO_Port,MCU_SEL4_Pin},
};

static void set_mcu_id();

void set_mcu_id()
{
	GPIO_PinState pin_state;
	for(uint8_t i=0; i < MCU_SEL_MAX; i++)
	{
		pin_state = HAL_GPIO_ReadPin(mcu_selection[i].port, mcu_selection[i].pin);
		if(GPIO_PIN_RESET == pin_state){
			g_mcu_id = (i+1);
		}
	}
}

void APP_Init(){
	set_mcu_id();

	ST7735_Init();
	ST7735_FillScreen(ST7735_BLUE);


}

void APP_Main(){
	if((HAL_GetTick() - prev_tick) >= MAIN_LOOP_TIME){
		prev_tick = HAL_GetTick();
		LED_Toggle();

		Process_comms();



	}

}
