#ifndef TIMER_H
#define TIMER_H
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

#include <stdint.h>

/**
 * @brief 
 *   Generate delay in milliseconds
 *
 * @param [in] ms 
 *   Delay in milliseconds
 */
void DelayMs(uint32_t ms);

/**
 * @brief 
 *   Initialize timer 1
 */
void InitTimer();

#endif // !TIMER_H
