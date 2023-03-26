#include "stm32f4xx.h"
#include <stdint.h>

volatile uint32_t jiffies = 0;
static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin);

void ms_delay(uint32_t ms);

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Set OUTPUT mode
    
    SysTick_Config(8000);

    while (1) {
        gpio_toggle(GPIOC, GPIO_ODR_OD13);
        ms_delay(900);
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

static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin) {
    port->ODR ^= pin;
}
