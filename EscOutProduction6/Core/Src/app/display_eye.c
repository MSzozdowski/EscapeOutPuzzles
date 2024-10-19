/*
 * display_eye.c
 *
 *  Created on: Oct 13, 2024
 *      Author: Artur
 */

#include "main.h"
#include "display_eye.h"
#include "driver/lcd/st7735.h"
#include "driver/lcd/bitmap.h"

uint8_t pos_x;
uint8_t pos_y;
uint8_t last_x;
uint8_t last_y;

void DrawEyeInit(void)
{
	ST7735_Init();
	ST7735_FillScreenFast(ST7735_EYE_BKG);
	DrawEye(EYES_ARE_CENTER);
}


void DrawEye(eyes_state_e eye_state)
{
	switch (eye_state)
	{
		case EYES_ARE_CENTER:
			pos_x = 32;
			pos_y = 32;
		break;
		case EYES_ARE_UP:
			pos_x = 32;
		    pos_y = 15;
		break;
		case EYES_ARE_RIGHT:
			pos_x = 63;
			pos_y = 32;
		break;
		case EYES_ARE_DOWN:
			pos_x = 32;
			pos_y = 48;
		break;
		case EYES_ARE_LEFT:
			pos_x = 0;
			pos_y = 32;
		break;
	}

	ST7735_FillRectangleFast(last_x,last_y,IMG_WIDTH,IMG_HEIGHT,ST7735_EYE_BKG);
	ST7735_DrawImage(pos_x,pos_y, IMG_WIDTH,IMG_HEIGHT, eye_img_64x64);
	last_x = pos_x;
	last_y = pos_y;
}

void DrawEyeTest(void)
{
	HAL_Delay(2000);
	DrawEye(EYES_ARE_UP);

	HAL_Delay(2000);
	DrawEye(EYES_ARE_RIGHT);

	HAL_Delay(2000);
	DrawEye(EYES_ARE_DOWN);

	HAL_Delay(2000);
	DrawEye(EYES_ARE_LEFT);

	HAL_Delay(2000);
	DrawEye(EYES_ARE_CENTER);
}
