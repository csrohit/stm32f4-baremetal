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

volatile int flag = 0;

void Timer1_Init(void) {
    // Enable clock for TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // Set prescaler value
    // Timer clock = SystemCoreClock / (prescaler + 1)
    // Assuming SystemCoreClock is 84 MHz, for 1 ms => 84 - 1 = 83
    TIM1->PSC = 15; // Prescaler to get 1 MHz (1 µs tick)

    // Set auto-reload register (ARR) for 1 ms
    TIM1->ARR = 1000 - 1; // 1 ms

    // Enable update interrupt
    TIM1->DIER |= TIM_DIER_UIE;

    // Enable timer
    TIM1->CR1 |= TIM_CR1_CEN;

    // Enable NVIC for TIM1 update interrupt
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

void TIM1_UP_TIM10_IRQHandler(void) {
    // Check if update interrupt flag is set
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF; // Clear the interrupt flag
        flag= 1;
    }
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        // Wait for the update interrupt
        while (!flag);
        flag = 0;
    }
}


int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;
    
    Timer1_Init(); 

    // SysTick_Config(16000);

    while (1)
    {
        GPIOToggle(GPIOC, GPIO_ODR_OD13);
        delay_ms(1000);
    }
}
