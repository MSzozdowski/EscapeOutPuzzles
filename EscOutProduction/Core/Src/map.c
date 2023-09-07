/*
 * map.c
 *
 *  Created on: Aug 23, 2023
 *      Author: stasz
 */

#include "main.h"
#include "map.h"

uint16_t map(uint16_t input, uint16_t input_min, uint16_t input_max, uint16_t output_min, uint16_t output_max)
{
    return ((((input - input_min)*(output_max - output_min))/(input_max - input_min)) + output_min);
}
