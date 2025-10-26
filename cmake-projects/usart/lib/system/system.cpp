/**
 * @file     system.cpp
 * @author   Rohit Nimkar <https://csrohit.github.io>
 * @brief    Definitions of functions related to CMSIS and timing related peripherals
 * @version  1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include "system.h"

uint32_t          Core::clock    = 16000000U;
volatile uint32_t Core::ms_ticks = 0;

void SysTick_Handler(void)
{
    Core::ms_ticks = Core::ms_ticks + 1;
}
