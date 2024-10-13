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

void draw_eye_init(){
	ST7735_Init();
	ST7735_FillScreenFast(ST7735_EYE_BKG);
	draw_eye(CENTER);
}


void draw_eye(direction_e dir){
	switch (dir){
		case CENTER:
			pos_x = 32;
			pos_y = 32;
		break;
		case UP:
			pos_x = 32;
		    pos_y = 15;
		break;
		case RIGHT:
			pos_x = 63;
			pos_y = 32;
		break;
		case DOWN:
			pos_x = 32;
			pos_y = 48;
		break;
		case LEFT:
			pos_x = 0;
			pos_y = 32;
		break;
	}

	ST7735_FillRectangleFast(last_x,last_y,IMG_WIDTH,IMG_HEIGHT,ST7735_EYE_BKG);
	ST7735_DrawImage(pos_x,pos_y, IMG_WIDTH,IMG_HEIGHT, eye_img_64x64);
	last_x = pos_x;
	last_y = pos_y;
}

void draw_eye_test(){
	HAL_Delay(2000);
	draw_eye(UP);

	HAL_Delay(2000);
	draw_eye(RIGHT);
	HAL_Delay(2000);
	draw_eye(DOWN);

	HAL_Delay(2000);
	draw_eye(LEFT);

	HAL_Delay(2000);
	draw_eye(CENTER);
}
