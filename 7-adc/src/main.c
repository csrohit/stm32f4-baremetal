#include "stm32f4xx.h"
#include <stdint.h>
#include "usart.h"

volatile uint32_t  jiffies = 0U;
static inline void gpio_toggle(GPIO_TypeDef* port, uint32_t pin);

void ms_delay(uint32_t ms);

const char* str = "hello rohit\r\n";

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Set OUTPUT mode

    usart_init(115200U);

    SysTick_Config(16000);


    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    
    /* Set PA0 to analog mode */
    GPIOA->MODER |= GPIO_MODER_MODE1;

    ADC1->SQR3 = ADC_SQR1_L_2;

    while (1)
    {
        gpio_toggle(GPIOC, GPIO_ODR_OD13);
        ms_delay(1000);
        usart_txbuf(str);
    }
}

void SysTick_Handler(void)
{
    jiffies++;
}

void ms_delay(uint32_t ms)
{
    uint32_t expected_ticks = jiffies + ms;
    while (jiffies < expected_ticks)
    {
        __asm("nop");
    }
}

static inline void gpio_toggle(GPIO_TypeDef* port, uint32_t pin)
{
    port->ODR ^= pin;
}
