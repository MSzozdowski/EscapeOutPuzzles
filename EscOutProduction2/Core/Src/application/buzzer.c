#include "main.h"
#include "tim.h"
#include "application/buzzer.h"

static void BUZZER_On(void);
static void BUZZER_Off(void);
static void BUZZER_StartTimer(void);
static void BUZZER_StopTimer(void);

typedef struct BuzzerDebug
{
	uint16_t period;
	uint16_t period_help;
	uint8_t ticks;
	uint16_t ticks_delay;
	uint16_t ticks_delay_help;
	uint8_t help;
	buzzer_stage_t buzzer_stage;
	buzzer_freq_t freq;
}buzdebug_t;

buzdebug_t Buzz = {0, 0, 0, 0, 0, 0, BUZZER_IDLE, BUZZER_FREQ_LOW};



static void BUZZER_On(void)
{
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
}

static void BUZZER_Off(void)
{
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}

void BUZZER_Go(buzz_time_t period, buzz_tick_t ticks, buzz_delay_t delay, buzzer_freq_t frequency)
{
	Buzz.period = period;
	Buzz.period_help = period;
	Buzz.ticks = ticks;
	Buzz.ticks_delay = delay;
	Buzz.ticks_delay_help = delay;
	Buzz.help = 0;
	Buzz.freq = frequency;
	Buzz.buzzer_stage = BUZZER_START;

	BUZZER_StartTimer();
}

void BUZZER_Handler(void)
{
	switch (Buzz.buzzer_stage) {
		case BUZZER_IDLE:
			break;

		case BUZZER_START:
			if(Buzz.period > 0)
			{
				if(Buzz.help)
					BUZZER_On();
				else
					BUZZER_Off();
				Buzz.period--;
				Buzz.help = ~Buzz.help;
			}
			else
			{
				BUZZER_Off();
				if(Buzz.ticks > 0)
				{
					Buzz.ticks--;
					Buzz.buzzer_stage = BUZZER_WAIT_TICK;
				}
				else
				{
					Buzz.buzzer_stage = BUZZER_IDLE;
					BUZZER_StopTimer();
				}
			}
			break;

		case BUZZER_WAIT_TICK:
			if(--Buzz.ticks_delay)
			{
				//wait
			}
			else
			{
				Buzz.buzzer_stage = BUZZER_START;
				Buzz.ticks_delay = Buzz.ticks_delay_help;
				Buzz.period = Buzz.period_help;
			}
			break;
	}
}

void HAL_SYSTICK_Callback(void) //Inserted into SysTick_Handler
{
	if(Buzz.freq == BUZZER_FREQ_LOW)
	{
		//HAL_GPIO_TogglePin(TIMER_OUTPUT_GPIO_Port, TIMER_OUTPUT_Pin);
		BUZZER_Handler();
	}
}

static void BUZZER_StartTimer(void)
{
	HAL_TIM_Base_Start_IT(&htim1);
}

static void BUZZER_StopTimer(void)
{
	HAL_TIM_Base_Stop_IT(&htim1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		if(Buzz.freq == BUZZER_FREQ_HIGH)
		{
			//HAL_GPIO_TogglePin(TIMER_OUTPUT_GPIO_Port, TIMER_OUTPUT_Pin);
			BUZZER_Handler();
		}
	}
}
