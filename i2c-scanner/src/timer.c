/**
 * @file        timer.c
 * @description Timing and Delay related function definitions
 * @author      Rohit Nimkar
 * @version     1.0
 * @date        2024-07-07
 * @copyright   Copyright 2024 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include "timer.h"

/**
 * @brief
 *   Systick timer ticks
 */
static volatile uint32_t jiffies = 0U;

/**
 * @brief
 *   Interrupt Handler for Systick timer overflow interrupt
 */
void SysTick_Handler(void)
{
    jiffies++;
}

/**
 * @brief
 *   Generate delay in milliseconds
 *
 * @param [in] ms
 *   Delay in milliseconds
 */
void DelayMs(uint32_t ms)
{
    uint32_t expected_ticks = jiffies + ms;
    while (jiffies < expected_ticks)
    {
        __asm("nop");
    }
}
