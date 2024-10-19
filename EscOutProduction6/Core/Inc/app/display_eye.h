/*
 * display_eye.h
 *
 *  Created on: Oct 13, 2024
 *      Author: Artur
 */

#ifndef INC_APP_DISPLAY_EYE_H_
#define INC_APP_DISPLAY_EYE_H_

#include "driver/comms.h"

void DrawEyeInit(void);
void DrawEye(eyes_state_e eye_state);
void DrawEyeTest(void);

#endif /* INC_APP_DISPLAY_EYE_H_ */
