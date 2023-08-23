/*
 * putchar.c
 *
 *  Created on: Aug 20, 2023
 *      Author: stasz
 */

#include "main.h"
#include "putchar.h"
#include "usart.h"

int __io_putchar(int ch)
{
    if (ch == '\n') {
        uint8_t ch2 = '\r';
        HAL_UART_Transmit(&huart2, &ch2, 1, 1000);
    }

    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1000);
    return 1;
}
