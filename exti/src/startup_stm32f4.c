#include <stdint.h>

/* Function declarations */
extern void                    _estack(void); // initial value of stack pointer
extern int                     main();
__attribute__((noreturn)) void Reset_Handler(void);
void                           Default_Handler(void);
__attribute__((weak)) void     NMI_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     HardFault_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     MemManage_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     BusFault_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     UsageFault_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     SVCall_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DebugMon_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     PendSV_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     SysTick_Handler(void);
__attribute__((weak)) void     WWDG_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI16_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI21_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI22_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     Flash_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     RCC_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI0_IRQHandler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI1_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI2_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI3_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI4_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream0_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream1_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream2_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream3_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream4_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream5_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     DMA1Stream6_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     ADC1_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     EXTI9_5_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     TIM1_Break_TIM9_Handler(void) __attribute__((alias("Default_Handler")));
__attribute__((weak)) void     TIM1_Update_TIM10_Handler(void) __attribute__((alias("Default_Handler")));

/* Define the veector table */
void (*vectors[16 + 52])(void) __attribute__((section(".isr_vector"))) = {
    _estack,            /* Stack Top */
    Reset_Handler,      /* Reset Handler */
    NMI_Handler,        /* NMI Handler */
    HardFault_Handler,  /* HardFault Handler */
    MemManage_Handler,  /* Mem Manage fault handler */
    BusFault_Handler,   /* Bus Fault Handler */
    UsageFault_Handler, /* UsageFault Handler*/
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVCall_Handler,     /* SVCall Handler */
    DebugMon_Handler,   /* Debug Monitor Handler */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pend SV Handler */
    SysTick_Handler,    /* SysTick handler */

    0,                      /* Window WatchDog              */
    0,                      /* PVD through EXTI Line detection */
    0,                      /* Tamper and TimeStamps through the EXTI line */
    0,                      /* RTC Wakeup through the EXTI line */
    0,                      /* FLASH                        */
    0,                      /* RCC                          */
    EXTI0_IRQHandler,       /* EXTI Line0                   */
    0,                      /* EXTI Line1                   */
    0,                      /* EXTI Line2                   */
    0,                      /* EXTI Line3                   */
    0,                      /* EXTI Line4                   */
    0,                      /* DMA1 Stream 0                */
    0,                      /* DMA1 Stream 1                */
    0,                      /* DMA1 Stream 2                */
    0,                      /* DMA1 Stream 3                */
    0,                      /* DMA1 Stream 4                */
    0,                      /* DMA1 Stream 5                */
    0,                      /* DMA1 Stream 6                */
    0,                      /* ADC1                         */
    0,                      /* Reserved                     */
    0,                      /* Reserved                     */
    0,                      /* Reserved                     */
    0,                      /* Reserved                     */
    0,                      /* External Line[9:5]s          */
    TIM1_Break_TIM9_Handler /* TIM1 Break and TIM9          */
};

__attribute__((noreturn)) void Reset_Handler(void)
{
    extern uint32_t _sdata, _edata, _la_data, _sbss, _ebss;

    uint32_t* start_sram  = (uint32_t*)&_sdata;
    uint32_t* start_flash = (uint32_t*)&_la_data;
    while (start_sram < (uint32_t*)&_edata)
    {
        *start_sram++ = *start_flash++;
    }

    uint32_t* start_bss = (uint32_t*)&_sbss;
    while (start_bss < (uint32_t*)&_ebss)
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

void Default_Handler(void)
{
    while (1)
    {
            __asm("nop");
    };
}
