#ifndef led_h
#define led_h

#define LED_SHORT_BLINK_TIME 500

typedef enum
{
    LED_IDLE,
    LED_SHORT_BLINK,
}led_state_t;

void LED_Init(uint8_t pin);
void LED_Process(void);
void LED_SetState(led_state_t led_st);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);

#endif
