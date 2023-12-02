/*
 * ws2812.c
 *
 *  Created on: Aug 14, 2023
 *      Author: szozdowskim
 */
#include "main.h"
#include "spi.h"
#include "dma.h"
#include "gpio.h"

#include "app/ws2812.h"

#include "stdio.h"
#include "string.h"

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
	WS2812_SetAllOff();
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
			if(((buff[j] >> i) & 0x01))
			{
				buffer[8*(j+1)-i-1+diode_number*WS2812_BYTES_PER_LED] = ONE;
			}
			else
			{
				buffer[8*(j+1)-i-1+diode_number*WS2812_BYTES_PER_LED] = ZERO;
			}
		}
	}
}

uint32_t WS2812_GetColor(uint16_t diode_number)
{
	if(diode_number > WS2812_LED_NUMBER)
		return 0;

	uint32_t color = 0;
	for(uint8_t i = 0; i < WS2812_BYTES_PER_LED; i++)
	{
		if(buffer[i+diode_number*WS2812_BYTES_PER_LED] == ONE)
		{
			color |= (1 << i);
		}
	}

	uint8_t r = (color>>8);
	uint8_t g = (color&0xFF);
	uint8_t b = (color>>16);

	//reverse bits in bytes
	r = ((r * 0x0802LU & 0x22110LU) | (r * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
	g = ((g * 0x0802LU & 0x22110LU) | (g * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
	b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

	color = 0;
	color = (r<<16)|(g<<8)|b;

	return color;
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

void WS2812_SetFragmentColor(uint16_t diode_start, uint16_t diode_stop, uint32_t color)
{
	if(diode_stop > WS2812_LED_NUMBER)
		return;

	uint8_t r = (color>>16);
	uint8_t g = (color>>8);
	uint8_t b = (color&0xFF);

	for(uint16_t i = diode_start; i <= diode_stop; i++)
	{
		WS2812_SetColor(i, r, g, b);
	}
}

void WS2812_Update(void)
{
	//Transmit the buffer
	HAL_SPI_Transmit_DMA(ws2812_spi, buffer, BUFFER_SIZE);
	while(HAL_DMA_STATE_READY != HAL_DMA_GetState(ws2812_spi->hdmatx)){};

	//WS2812_ClearDataBuffer();
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
