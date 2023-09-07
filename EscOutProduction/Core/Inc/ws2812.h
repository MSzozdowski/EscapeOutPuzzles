/*
 * ws2812.h
 *
 *  Created on: Aug 14, 2023
 *      Author: szozdowskim
 */

//#ifdef MY_MACRO

#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#define WS2812_LED_NUMBER 60

#define WS2812_RESET_BYTES 72
#define WS2812_BYTES_PER_LED 24
#define BUFFER_SIZE ((WS2812_LED_NUMBER * WS2812_BYTES_PER_LED) + WS2812_RESET_BYTES)

#define ZERO 0xC0
#define ONE 0xF8

void WS2812_Init(SPI_HandleTypeDef* hspi);
void WS2812_SetColor(uint16_t diode_number, uint8_t r, uint8_t g, uint8_t b);
void WS2812_SetLineColors(uint16_t diode_stop, uint8_t r, uint8_t g, uint8_t b);
void WS2812_Update(void);
void WS2812_SetAllOff(void);

#endif /* INC_WS2812_H_ */
//#endif /*MY MACRO*/
