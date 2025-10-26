/**
 * @file     main.cpp
 * @author   Rohit Nimkar <https://csrohit.github.io>
 * @brief    I2c Device Scanner
 * @version  1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include "stm32f4xx.h"
#include <stdint.h>


void usart_init(uint32_t baud)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~ (GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
    GPIOA->MODER |= GPIO_MODER_MODE9_1 | GPIO_MODER_MODER10_1;
    GPIOA->OSPEEDR = 0U;

    /* Set alternate functions: USART1 -> AF7 */
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10);
    GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2;

    USART1->BRR = 16000000U/baud;
    USART1->CR1 |= USART_CR1_TE | USART_CR1_UE | USART_CR1_RE;
}

void usart_txchar(char c)
{
    // wait for tx data register to be empty
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = 0x000000ff & c;
}

void usart_txbuf(const char *ch)
{
    while (*ch)
    {
        usart_txchar(*ch);
        ch++;
    }

    // __disable_irq();
}


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

static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin);


const char* str = "hello\r\n";
int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Set OUTPUT mode
    
    usart_init(115200U);
    SysTick_Config(16000);

    while (1) {
        gpio_toggle(GPIOC, GPIO_ODR_OD13);
        ms_delay(1000);
        usart_txbuf(str);
    }
}


static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin) {
    port->ODR ^= pin;
}
