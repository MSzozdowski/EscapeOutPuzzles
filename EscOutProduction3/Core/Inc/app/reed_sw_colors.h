/*
 * reed_sw_colors.h
 *
 *  Created on: Nov 13, 2023
 *      Author: stasz
 */

#ifndef INC_APP_REED_SW_COLORS_H_
#define INC_APP_REED_SW_COLORS_H_

#define INIT_NEXT_COLOR_DELAY 500
#define DOOR_OPEN_DELAY_1 1000
#define NEXT_GAME_DELAY 5000

#define NUMBER_OF_REED_SW 4
#define SEGMENT_SIZE (WS2812_LED_NUMBER/NUMBER_OF_REED_SW)

#define SEGMENT_START(REED_ID) ((REED_ID*SEGMENT_SIZE)-SEGMENT_SIZE)
#define SEGMENT_END(REED_ID) ((REED_ID*SEGMENT_SIZE)-1)

#define COLORS_NUMBER 4

#define RED 	0xFF0000
#define GREEN 	0x00FF00
#define BLUE 	0x0000FF
#define YELLOW 	0xFFD700
#define WHITE	0xFFFFFF
#define PINK 	0xFC0FC0
#define BRONZE	0x6C3C0C
#define PURPLE 	0xB803FF

typedef enum
{
	INIT_STAGE_1,
	INIT_STAGE_2,
	INIT_STAGE_3,
	INIT_STAGE_4
}reed_sw_colors_init_stage_t;

typedef enum
{
	REED_SW_COLORS_INIT,
	REED_SW_COLORS_GAME,
	REED_SW_COLORS_WAIT_TO_OPEN,
	REED_SW_COLORS_FINISH
}reed_sw_colors_state_t;

void REED_SW_COLORS_Init(void);
void REED_SW_COLORS_Process(void);

#endif /* INC_APP_REED_SW_COLORS_H_ */
