#include <stdint.h>

/* Function declarations */
extern void _estack(void); // initial value of stack pointer
extern int main();
__attribute__((noreturn)) void Reset_Handler(void);
__attribute__((noreturn)) void Default_Handler(void);
__attribute__((weak)) void SysTick_Handler(void);

/* Define the veector table */
void (*vectors[16 + 52])(void) __attribute__((section(".isr_vector"))) = {
    _estack,
    Reset_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    SysTick_Handler 
};

__attribute__((noreturn)) void Reset_Handler(void) {
    extern uint32_t _sdata, _edata, _la_data, _sbss, _ebss;

    uint32_t *start_sram = (uint32_t *)&_sdata;
    uint32_t *start_flash = (uint32_t *)&_la_data;
    while (start_sram < (uint32_t *)&_edata)
    {
        *start_sram++ = *start_flash++;
    }

    uint32_t *start_bss = (uint32_t *)&_sbss;
    while (start_bss < (uint32_t *)&_ebss)
    {
        *start_bss++ = 0;
    }

    // now invoke main
    main();
    while (1)
    {
        __asm("nop");
    }
}

__attribute__((noreturn)) void Default_Handler(void)
{
    while (1)
        ;
}
