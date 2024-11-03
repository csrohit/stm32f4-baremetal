/**
 * @file        gpio.h
 * @description GPIO related function declarations
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

#include "stm32f4xx.h"

/**
 * @brief
 *   Toggle state of GPIO pin
 *
 * @param [in] port
 *   Address of port
 *
 * @param pin
 *   Pin to be toggled
 */
static inline void GPIOToggle(GPIO_TypeDef *port, uint32_t pin)
{
    port->ODR ^= pin;
}
