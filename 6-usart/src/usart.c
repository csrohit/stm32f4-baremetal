#include "usart.h"

void usart_init(uint32_t baud){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~ (GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
    GPIOA->MODER |= GPIO_MODER_MODE9_1 | GPIO_MODER_MODER10_1;
    GPIOA->OSPEEDR = 0U;
    /* Set alternate functions */  
    // GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10);
    // GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2;
    GPIOA->AFR[1] = 0x00000770;
    USART1->BRR = 0x8b;
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
}