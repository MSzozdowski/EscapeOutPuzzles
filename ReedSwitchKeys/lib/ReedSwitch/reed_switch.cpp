#include "Arduino.h"
#include "reed_switch.h"


static uint8_t REED_SW_GetState(reed_sw* reed_sw);

ReedSwitchActive reed_callback = NULL;

void REED_SW_Init(reed_sw* reed_sw, uint8_t GpioPin, uint8_t reed_id)
{
    //pinMode(reed_sw->GpioPin, INPUT_PULLUP);
	reed_sw->reed_sw_state = REED_SW_IDLE;
	reed_sw->GpioPin = GpioPin;
	reed_sw->reed_sw_tick = 0;
	reed_sw->reed_sw_id = reed_id;
}

void REED_SW_Process(reed_sw* reed_sw)
{
	switch (reed_sw->reed_sw_state) {
		case REED_SW_IDLE:
			if(REED_SW_GetState(reed_sw) == LOW)
			{
				reed_sw->reed_sw_state = REED_SW_DEBOUNCE;
				reed_sw->reed_sw_tick = millis();
			}
			break;

		case REED_SW_DEBOUNCE:
			if(millis() - reed_sw->reed_sw_tick > REED_SW_DEBOUNCE_TIME)
			{
				if(REED_SW_GetState(reed_sw) == LOW)
				{
					reed_sw->reed_sw_state = REED_SW_WAIT;
					reed_sw->reed_sw_tick = millis();

					if (reed_callback != NULL)
					{
						reed_callback(reed_sw);
					}
				}
				else
				{
					reed_sw->reed_sw_state = REED_SW_IDLE;
				}
			}
			break;

		case REED_SW_WAIT:
			if(REED_SW_GetState(reed_sw) == HIGH && millis() - reed_sw->reed_sw_tick > REED_SW_WAIT_TIME)
			{
				reed_sw->reed_sw_state = REED_SW_IDLE;
			}
			break;
	}
}

void ReedSwitchCallBack(ReedSwitchActive callback)
{
	reed_callback = callback;
}

static uint8_t REED_SW_GetState(reed_sw* reed_sw)
{
	return digitalRead(reed_sw->GpioPin);
}