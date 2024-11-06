#ifndef reed_switch_h
#define reed_switch_h

#include <stdint.h>

#define REED_SW_DEBOUNCE_TIME 100
#define REED_SW_WAIT_TIME 500

typedef enum
{
	REED_SW_IDLE,
	REED_SW_DEBOUNCE,
	REED_SW_WAIT
}reed_sw_state_t;

typedef struct
{
	reed_sw_state_t reed_sw_state;
    uint8_t GpioPin;
    uint32_t reed_sw_tick;
	uint8_t reed_sw_id;
}reed_sw;

typedef void (*ReedSwitchActive)(reed_sw* reed_sw);

void REED_SW_Init(reed_sw* reed_sw, uint8_t GpioPin, uint8_t reed_id);
void REED_SW_Process(reed_sw* reed_sw);
void REED_SW_Toggle(void);

void ReedSwitchCallBack(ReedSwitchActive callback);

#endif