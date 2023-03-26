#include "stm32f4xx.h"
#include <stdint.h>

static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin);

void ms_delay(int ms);

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Set OUTPUT mode

    while (1) {
        gpio_toggle(GPIOC, GPIO_ODR_OD13);
        ms_delay(500);
    }
}

void ms_delay(int ms) {
    while (ms-- > 0) {
        volatile int x = 1000;
        while (x-- > 0)
            __asm("nop");
    }
}

static inline void gpio_toggle(GPIO_TypeDef *port, uint32_t pin) {
    port->ODR ^= pin;
}
