/**
 * @file        main.c
 * @description Scan for connected I2C devices and log device address
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

#include <stdio.h>

#include "stm32f4xx.h"
#include "gpio.h"
#include "timer.h"

const char *str = "I2C Scanner\r\n"; /**< Initial string */
char        buffer[128];             /**< Buffer for storing msg */

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    GPIOA->MODER &= ~(GPIO_MODER_MODER0);
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_0;

    EXTI->IMR |= EXTI_IMR_IM0;
    EXTI->EMR |= EXTI_EMR_MR0;

    EXTI->FTSR |= EXTI_FTSR_TR0;
    NVIC_EnableIRQ(EXTI0_IRQn);
    
    // InitTimer();

    SysTick_Config(16000);

    while (1)
    {
        // GPIOToggle(GPIOC, GPIO_ODR_OD13);
        // DelayMs(500);
    }
}

void TIM1_Break_TIM9_Handler()
{
    if(TIM9->SR & TIM_SR_UIF)
    {
        // GPIOToggle(GPIOC, GPIO_ODR_OD13);
    }
}

void EXTI1_IRQHandler()
{
    /* Acknowledge inetrrupt */
    EXTI->PR |= EXTI_PR_PR0;
    GPIOToggle(GPIOC, GPIO_ODR_OD13);
    EXTI->PR |= EXTI_PR_PR0;
}

