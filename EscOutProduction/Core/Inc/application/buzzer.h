#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

typedef enum BuzzerTime
{
	TBUZ_20 = 20,
	TBUZ_50 = 50,
	TBUZ_100 = 100,
	TBUZ_200 = 200,
	TBUZ_300 = 300,
	TBUZ_400 = 400,
	TBUZ_500 = 500,
	TBUZ_600 = 600,
	TBUZ_800 = 800,
	TBUZ_900 = 900,
	TBUZ_1000 = 1000
}buzz_time_t;

typedef enum BuzzerTicks
{
	TICK_0 = 0,
	TICK_2 = 2-1,
	TICK_3 = 3-1,
	TICK_4 = 4-1,
	TICK_5 = 5-1,
	TICK_6 = 6-1
}buzz_tick_t;

typedef enum BuzzerTicksDelay
{
	BUZZ_DEL_0 = 0,
	BUZZ_DEL_50 = 50,
	BUZZ_DEL_100 = 100,
	BUZZ_DEL_200 = 200,
	BUZZ_DEL_300 = 300,
	BUZZ_DEL_500 = 500
}buzz_delay_t;

typedef enum BuzzerStage
{
	BUZZER_IDLE,
	BUZZER_START,
	BUZZER_WAIT_TICK
}buzzer_stage_t;

typedef enum BuzzFrequncy
{
	BUZZER_FREQ_HIGH = 0,
	BUZZER_FREQ_LOW = 1
}buzzer_freq_t;

void BUZZER_On(void);
void BUZZER_Off(void);
void BUZZER_Go(buzz_time_t period, buzz_tick_t ticks, buzz_delay_t delay, buzzer_freq_t frequency);
void BUZZER_Handler(void);


#endif /* INC_BUZZER_H_ */
