/**
 * @file        main.c
 * @brief       Timer3 configuration with 4 output compare channels on STM32F4
 * @details     Demonstrates configuration of TIM3 with 4 output compare channels and toggles an LED using a timer interrupt.
 * @author      Rohit Nimkar
 * @version     1.0
 * @date        2025-05-12
 * @copyright   Copyright 2025 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include "stm32f4xx.h"
#include "gpio.h"

/**
 * @brief   Timer interrupt flag. Set in TIM3_IRQHandler, cleared in delay_ms().
 */
volatile int flag = 0;

/**
 * @brief   Initializes Timer 3 (TIM3) with 4 output compare channels.
 * @details
 *  - Enables clocks for GPIOA, GPIOB, and TIM3.
 *  - Configures PA6, PA7, PB0, PB1 as alternate function (AF2) for TIM3 CH1-CH4.
 *  - Sets prescaler and auto-reload for 1ms period.
 *  - Configures output compare for all 4 channels.
 *  - Enables TIM3 interrupt in NVIC.
 *  - Starts the timer.
 *
 * @note
 *  - Output compare values set for demonstration (200, 400, 600, 800).
 *  - GPIO configuration assumes default push-pull output.
 */
void Timer3_Init(void)
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

    /* Enable clock for TIM3 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    /* Timer clock frequency = SystemCoreClock / (PSC + 1)
     * Assuming SystemCoreClock is 16 MHz,
     * To get a timer clock of 1 KHz (1 ms per tick): (16 MHz / 1 KHz) - 1 = 15999
     */
    TIM3->PSC = 15999;

    /* For a 1s timer period with 1ms ticks: 1s / 1ms = 1000 counts
     * Since counting starts from 0, ARR should be set to 999.
     */
    TIM3->ARR = 1000 - 1;

    /* Enable update interrupt */
    TIM3->DIER |= TIM_DIER_UIE;

    /* Enable NVIC for TIM3 update interrupt */
    NVIC_EnableIRQ(TIM3_IRQn);

    /* Set output compare values for all 4 channels */
    TIM3->CCR1 = 200 - 1;
    TIM3->CCR2 = 400 - 1;
    TIM3->CCR3 = 600 - 1;
    TIM3->CCR4 = 800 - 1;

    /* Configure output compare toggle mode for CH1 and CH2 */
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0;

    /* Enable preload for CH1 and CH2, set as output */
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC1PE;
    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);

    /* Configure output compare toggle mode for CH3 and CH4 */
    TIM3->CCMR2 &= ~(TIM_CCMR2_OC3M | TIM_CCMR2_OC4M);
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0;

    /* Enable preload for CH3 and CH4, set as output */
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;
    TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S | TIM_CCMR2_CC4S);

    /* Enable all 4 channels */
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

    /* Enable timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief   TIM3 interrupt handler.
 * @details Clears the update interrupt flag and sets the global flag.
 */
void TIM3_IRQHandler(void)
{
    /* Check if update interrupt flag is set */
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF; /* Clear the interrupt flag */
        flag = 1;
    }
}

/**
 * @brief   Millisecond delay using TIM3 update interrupt.
 * @param   ms [in]
 *          Number of milliseconds to delay.
 * 
 * @details Waits for the timer interrupt flag for each ms.
 */
void delay_ms(uint32_t ms)
{
    /* Wait for the update interrupt */
    while (!flag)
        __WFI();
    flag = 0;
}

/**
 * @brief   Main program entry point.
 * @details Configures PC13 as output, initializes TIM3, and toggles PC13 every 500 ms.
 * @return  int Always returns 0.
 */
int main(void)
{
    /* Enable clock for GPIOC */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* Set PC13 as output */
    GPIOC->MODER &= ~GPIO_MODER_MODER13;
    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    /* Initialize Timer3 */
    Timer3_Init();

    while (1)
    {
        GPIOToggle(GPIOC, GPIO_ODR_OD13);
        delay_ms(1000);
    }
}
