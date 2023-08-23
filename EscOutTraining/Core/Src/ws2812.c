/*
 * ws2812.c
 *
 *  Created on: Aug 14, 2023
 *      Author: szozdowskim
 */
//#ifdef MY_MACRO
#include "main.h"
#include "ws2812.h"
#include "spi.h"
#include "dma.h"
#include "gpio.h"

#include <stdio.h>
#include <string.h>

SPI_HandleTypeDef *ws2812_spi;

static uint8_t buffer[BUFFER_SIZE] = {0};

static void WS2812_ClearDataBuffer(void);

void WS2812_Init(SPI_HandleTypeDef* hspi)
{
	ws2812_spi = hspi;


	HAL_SPI_Transmit_DMA(ws2812_spi, buffer, WS2812_RESET_BYTES);
	while(HAL_DMA_STATE_READY != HAL_DMA_GetState(ws2812_spi->hdmatx)){};

	WS2812_ClearDataBuffer();
	//Refresh LEDs
	//WS2812_SetAllOff();
}

void WS2812_SetColor(uint16_t diode_number, uint8_t r, uint8_t g, uint8_t b)
{
	/*	8 bits 		| 8bits			| 8bits
	 * 	MSB	...	LSB	| MSB	...	LSB | MSB	...	LSB
	 * 	G			| R				| B
	 */
	if(diode_number > WS2812_LED_NUMBER)
		return;

	uint8_t buff[3] = {g,r,b};
	for(uint8_t j=0; j < 3; j++)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
			if(((buff[j] >> i) & 0xFF))
			{
				buffer[8*(j+1)-i-1+diode_number*WS2812_BYTES_PER_LED] = ONE;
			}
		}
	}
}

void WS2812_SetLineColors(uint16_t diode_stop, uint8_t r, uint8_t g, uint8_t b)
{
	if(diode_stop > WS2812_LED_NUMBER)
		return;

	for(uint16_t i = 0; i <= diode_stop; i++)
	{
		WS2812_SetColor(i, r, g, b);
	}

}

void WS2812_Update(void)
{
	//Transmit the buffer
	HAL_SPI_Transmit_DMA(ws2812_spi, buffer, BUFFER_SIZE);
	while(HAL_DMA_STATE_READY != HAL_DMA_GetState(ws2812_spi->hdmatx)){};

	WS2812_ClearDataBuffer();
}

void WS2812_SetAllOff(void)
{
	WS2812_ClearDataBuffer();
	WS2812_Update();
}

static void WS2812_ClearDataBuffer(void)
{
	memset(buffer, ZERO, WS2812_LED_NUMBER * WS2812_BYTES_PER_LED);
}

/*void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
}*/
//#endif /*MY MACRO*/
