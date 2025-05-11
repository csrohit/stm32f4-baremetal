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

/*
 * @brief
 *   Initialize Timer1 to generate an update interrupt every 1 ms.
 */
void Timer1_Init(void)
{
    // 1. Enable the peripheral clock for TIM1 by setting the TIM1EN bit in APB2ENR register.
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // 2. Set the prescaler value.
    //    Timer clock frequency = SystemCoreClock / (PSC + 1)
    //    Assuming SystemCoreClock is 16 MHz,
    //    To get a timer clock of 1 MHz (1 µs per tick): 16 MHz / (15 + 1) = 1 MHz
    TIM1->PSC = 15; // Prescaler value for 1 MHz timer clock

    // 3. Set the auto-reload register (ARR) to define the timer period.
    //    The timer will count from 0 up to ARR, then reset to 0 and generate an update event.
    //    For a 1 ms period with 1 µs ticks: 1 ms / 1 µs = 1000 counts
    //    Since counting starts from 0, ARR should be set to 999.
    TIM1->ARR = 1000 - 1; // Set ARR for 1 ms period

    // 4. Enable the update interrupt (UIE) so that an interrupt is generated on timer overflow.
    TIM1->DIER |= TIM_DIER_UIE;

    // 5. Enable the TIM1 update interrupt in the NVIC so the CPU will execute the ISR on timer overflow.
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    // 6. Start the timer by setting the CEN (counter enable) bit in the control register.
    TIM1->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief
 *   TIM1 update interrupt handler.
 *   This function is called automatically when TIM1 overflows (every 1 ms as configured).
 */
void TIM1_UP_TIM10_IRQHandler(void)
{
    // 1. Check if the update interrupt flag (UIF) is set in the status register.
    //    This indicates that the timer has reached the auto-reload value (overflowed).
    if (TIM1->SR & TIM_SR_UIF)
    {
        // 2. Clear the update interrupt flag by writing 0 to UIF.
        //    This is required to acknowledge the interrupt and allow new interrupts.
        TIM1->SR &= ~TIM_SR_UIF;

        // 3. Set the global flag to indicate that the timer period has elapsed.
        //    This flag can be used in other parts of the code (e.g., for delays).
        flag = 1;
    }
}

/**
 * @brief
 *   Blocking delay function that waits for the specified number of milliseconds.
 *   Uses the timer interrupt flag to count elapsed milliseconds.
 *
 * @param ms [in]
 *   Number of milliseconds to delay.
 */
void delay_timer(uint32_t ms)
{
    // Loop for the requested number of milliseconds
    for (uint32_t i = 0U; i < ms; i++)
    {
        // 1. Wait until the timer interrupt handler sets the flag,
        //    indicating that 1 ms has elapsed.
        while (!flag)
            __WFI();

        // 2. Clear the flag for the next iteration.
        flag = 0;
    }
}

/**
 * @brief
 *   Main program entry point.
 *   Initializes GPIOC pin 13 as output, configures Timer1, and toggles the pin every 1 second.
 */
int main(void)
{
    // 1. Enable the peripheral clock for GPIOC by setting the GPIOCEN bit in the AHB1ENR register.
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // 2. Configure GPIOC pin 13 as a general purpose output.
    //    First, clear the mode bits for pin 13 (set as input by default).
    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    //    Then, set the mode bits to '01' (output mode) for pin 13.
    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    // 3. Initialize Timer1 to generate periodic interrupts (every 1 ms as configured).
    Timer1_Init();

    // 4. Main loop: toggle GPIOC pin 13 every 1000 ms (1 second).
    while (1)
    {
        // Toggle the output state of GPIOC pin 13.
        GPIOToggle(GPIOC, GPIO_ODR_OD13);

        // Delay for 1000 ms (1 second) using the timer-based delay function.
        delay_timer(1000);
    }
}

