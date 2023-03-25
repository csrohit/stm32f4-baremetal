#include <stdint.h>

/**
 * @brief Structure to represent RCC peripheral
 */
struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR,
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR,
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR,
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR,
      RESERVED6[2], SSCGR, PLLI2SCFGR;
};

/**
 * @brief Streucture to represent GPIO peripheral
 */
struct gpio {
  volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

/* Function declaration */

static inline void gpio_set(struct gpio* port, uint32_t pin);
static inline void gpio_reset(struct gpio* port, uint32_t pin);
void ms_delay(int ms);

#define RCC ((struct rcc *) 0x40023800)
#define GPIOC ((struct gpio *)0x40020800)

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

static inline void gpio_set(struct gpio* port, uint32_t pin){
    port->BSRR |= 1 << pin;
}

static inline void gpio_reset(struct gpio* port, uint32_t pin){
    port->BSRR |= 1 << (pin + 16);
}

