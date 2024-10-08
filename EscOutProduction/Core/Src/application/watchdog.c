/*
 * watchdog.c
 *
 *  Created on: Sep 6, 2023
 *      Author: stasz
 */

#include "main.h"
#include "iwdg.h"
#include "application/watchdog.h"

void WATCHDOG_Refresh(void)
{
	if(HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
		Error_Handler();
}
