/*
 * reed_sw_colors.h
 *
 *  Created on: Nov 13, 2023
 *      Author: stasz
 */

#ifndef INC_APP_REED_SW_COLORS_H_
#define INC_APP_REED_SW_COLORS_H_

#define INIT_NEXT_COLOR_DELAY 500

#define NUMBER_OF_REED_SW 4
#define SEGMENT_SIZE (WS2812_LED_NUMBER/NUMBER_OF_REED_SW)

#define SEGMENT_START(REED_ID) ((REED_ID*SEGMENT_SIZE)-SEGMENT_SIZE)
#define SEGMENT_END(REED_ID) ((REED_ID*SEGMENT_SIZE)-1)

#define COLORS_NUMBER 4

#define RED 0x02F0000
#define GREEN 0x000F00
#define BLUE 0x00000F
#define YELLOW 0x3F0A00

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
	REED_SW_COLORS_FINISH
}reed_sw_colors_state_t;

void REED_SW_COLORS_Init(void);
void REED_SW_COLORS_Process(void);

#endif /* INC_APP_REED_SW_COLORS_H_ */
