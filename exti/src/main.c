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

#include "stm32f4xx.h"
#include "gpio.h"

/**
 * @brief 
 *   Initialize Switch for falling edge triggered interrupt
 */
void initSwitch()
{
    /* Set PA0 as input */
    GPIOA->MODER &= ~(GPIO_MODER_MODER0);

    /* Set Pull Up */
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_0;

    /* Unmask EXTI0 interrupt and event */
    EXTI->IMR |= EXTI_IMR_IM0;
    EXTI->EMR |= EXTI_EMR_MR0;

    /* Trigger when falling edge is detecte */
    EXTI->FTSR |= EXTI_FTSR_TR0;

    /* Enable interrupt */
    NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
 * @brief 
 *   Initialize LED
 */
void initLed()
{
    /* Set PC13 as output */
    GPIOC->MODER &= ~GPIO_MODER_MODER13;
    GPIOC->MODER |= GPIO_MODER_MODER13_0;
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN;

    initLed();
    initSwitch();

    while (1)
    {
        // GPIOToggle(GPIOC, GPIO_ODR_OD13);
        // DelayMs(500);
    }
}

void EXTI0_IRQHandler()
{
    /* Acknowledge inetrrupt */
    EXTI->PR |= EXTI_PR_PR0;

    GPIOToggle(GPIOC, GPIO_ODR_OD13);
}

