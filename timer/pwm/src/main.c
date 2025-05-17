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
#include <stdint.h>

volatile int      flag    = 0;
volatile uint32_t msTicks = 0U;

/**
 * @brief Interrupt handler function
 *
 */
void SysTick_Handler(void)
{
    msTicks++;
}

/**
 * @brief Add blocking delay
 *
 * @param ms delay in milliseconds
 */
void ms_delay(uint32_t ms)
{
    uint32_t expected_ticks = msTicks + ms;
    while (msTicks < expected_ticks)
    {
        __asm("nop");
    }
}

void Timer1_Init(void)
{
    /* Enable Clock for GPIOA and GPIOB */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    /* Set PA6, PA7 to alternate function */
    GPIOA->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
    GPIOA->MODER |= GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1;

    /* Set PB0, PB1 to alternate function */
    GPIOB->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1);
    GPIOB->MODER |= GPIO_MODER_MODE0_1 | GPIO_MODER_MODE1_1;

    /* Set PA6, PA7 to Push-Pull (Default) */
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);

    /* Set PB0, PB1 to Push-Pull (Default) */
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);

    /* Set PA6, PA7 to AF2 */
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL6 | GPIO_AFRL_AFRL7);
    GPIOA->AFR[0] |= GPIO_AFRL_AFRL6_1 | GPIO_AFRL_AFRL7_1;

    /* Set PB0, PB1 to AF2 */
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL0 | GPIO_AFRL_AFRL1);
    GPIOB->AFR[0] |= GPIO_AFRL_AFRL0_1 | GPIO_AFRL_AFRL1_1;

    /*---- Enable clock for TIM3 ----*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    /*----
        Set prescaler value
        Timer clock = SystemCoreClock / (prescaler + 1)
        Assuming SystemCoreClock is 16 MHz, for 1 ms => 16 - 1 = 15
    ----*/
    TIM3->PSC = 15; // Prescaler to get 1 MHz (1 µs tick)

    // Set auto-reload register (ARR) for 1 ms
    TIM3->ARR = 1000 - 1; // 1 ms

    /* Enable update interrupt */
    TIM3->DIER |= TIM_DIER_UIE;

    // Enable NVIC for TIM1 update interrupt
    NVIC_EnableIRQ(TIM3_IRQn);

    /* Write compare values */
    TIM3->CCR1 = 200 - 1;
    TIM3->CCR2 = 400 - 1;
    TIM3->CCR3 = 600 - 1;
    TIM3->CCR4 = 800 - 1;

    /* Toggle CH1 and CH2 on Match */
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;

    /* Enable TIM3 CHannel 1, 2, 3, 4 */
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC1PE;
    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);

    TIM3->CCMR2 &= ~(TIM_CCMR2_OC3M | TIM_CCMR2_OC4M);
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;

    TIM3->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;
    TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S | TIM_CCMR2_CC4S);

    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

    /* Enable timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler(void)
{
    // Check if update interrupt flag is set
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF; // Clear the interrupt flag
        flag = 1;
    }
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    Timer1_Init();

    SysTick_Config(16000);

    uint32_t duty      = 0;
    uint32_t increment = +2;

    uint32_t duty1 = 250;
    uint32_t increment1 = 2;

    uint32_t duty2 = 500;
    uint32_t increment2 = 2;

    uint32_t duty3 = 550;
    uint32_t increment3 = 2;

    while (1)
    {

        TIM3->CCR1 = duty;
        TIM3->CCR2 = duty1;
        TIM3->CCR3 = duty2;
        TIM3->CCR4 = duty3;

        duty = duty + increment;
        if(duty > 1000 || duty < 20)
        {
            increment = -increment;
        }

        duty1 = duty1 + increment1;
        if(duty1 > 1000 || duty1 < 20)
        {
            increment1 = -increment1;
        }

        duty2 = duty2 + increment2;
        if(duty2 > 1000 || duty2 < 20)
        {
            increment2 = -increment2;
        }

        duty3 = duty3 + increment3;
        if(duty3 > 1000 || duty3 < 20)
        {
            increment3 = -increment3;
        }

        ms_delay(2);
    }
}
