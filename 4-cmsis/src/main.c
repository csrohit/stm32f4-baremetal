#include <stdint.h>
#include "stm32f401xe.h"
#include "stm32f4xx.h"

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

/* Function declaration */
extern void _estack(void);

static inline void gpio_set(GPIO_TypeDef *port, uint32_t pin);
static inline void gpio_reset(GPIO_TypeDef * port, uint32_t pin);

void ms_delay(int ms);


int main(void)
{
	RCC->AHB1ENR |= 1 << 2;

	GPIOC->MODER &= ~ 3U  << (13 * 2);

    GPIOC->MODER |= (GPIO_MODE_OUTPUT & 3U) << (13 * 2);   // Set new mode

	while(1){
        gpio_set(GPIOC, 13);
		ms_delay(500);
        gpio_reset(GPIOC, 13);
		ms_delay(500);
	}
}

void ms_delay(int ms)
{
    while (ms-- > 0)
    {
        volatile int x = 1000;
        while (x-- > 0)
            __asm("nop");
    }
}

static inline void gpio_set(GPIO_TypeDef * port, uint32_t pin){
    port->BSRR |= 1 << pin;
}

static inline void gpio_reset(GPIO_TypeDef * port, uint32_t pin){
    port->BSRR |= 1 << (pin + 16);
}
