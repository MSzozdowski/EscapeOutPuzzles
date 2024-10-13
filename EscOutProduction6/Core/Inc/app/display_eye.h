/*
 * display_eye.h
 *
 *  Created on: Oct 13, 2024
 *      Author: Artur
 */

#ifndef INC_APP_DISPLAY_EYE_H_
#define INC_APP_DISPLAY_EYE_H_

typedef enum{
	CENTER = 0,
	UP,
	RIGHT,
	DOWN,
	LEFT
}direction_e;

void draw_eye_init(void);
void draw_eye(direction_e d);
void draw_eye_test(void);

#endif /* INC_APP_DISPLAY_EYE_H_ */
