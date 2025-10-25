#include "stm32f4xx.h"
#include <stdint.h>

#include "gpio_port.h"

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

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Set OUTPUT mode
    //
    GPIO &portc = *new (GPIO::PortC) GPIO;
    
    SysTick_Config(16000);

    while (1) {
        portc.togglePin(GPIO::PIN_13);
        ms_delay(100);
    }
}

