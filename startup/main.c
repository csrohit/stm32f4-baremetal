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
extern void _estack(void);

__attribute__((weak)) void *memcpy(void *dest, const void *src, uint32_t n);
__attribute__((weak)) void *memset(void *dst0, int c, uint32_t length);

static inline void gpio_set(struct gpio* port, uint32_t pin);
static inline void gpio_reset(struct gpio* port, uint32_t pin);
void ms_delay(int ms);
void Reset_Handler(void);
int main();

#define RCC ((struct rcc *) 0x40023800)
#define GPIOC ((struct gpio *)0x40020800)

// Define the veector table
void (*vectors[16 + 52])(void) __attribute__((section(".isr_vector"))) = {
    _estack,
    Reset_Handler,
};


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


// Command: reset memory and restart user program
void Reset_Handler(void)
{
    extern uint32_t _sdata, _edata, _la_data, _sbss, _ebss;
    
    memcpy(&_sdata, &_la_data, &_edata - &_sdata);
    memset(&_sbss, 0, &_ebss - &_sbss);

    main();
    while(1);
}

__attribute__((weak)) void *memcpy(void *dest, const void *src, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

__attribute__((weak)) void *memset(void *dst0, int c, uint32_t length){
	char *dst = (char*)dst0;
	while (length--){
		*dst = (char) c;
		dst++;
	}
	return dst0;
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
