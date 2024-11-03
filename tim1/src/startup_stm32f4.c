#include <stdint.h>

/* Function declarations */
extern void _estack(void); // initial value of stack pointer
extern int main();
__attribute__((weak)) void *memcpy(void *dest, const void *src, uint32_t n);
__attribute__((weak)) void *memset(void *dst0, int c, uint32_t length);
__attribute__((noreturn)) void Reset_Handler(void);
__attribute__((weak)) void SysTick_Handler(void);
// Define the veector table
void (*vectors[16 + 52])(void) __attribute__((section(".isr_vector"))) = {
    _estack,
    Reset_Handler,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SysTick_Handler 
};

// Command: reset memory and restart user program
__attribute__((noreturn)) void Reset_Handler(void) {
  extern uint32_t _sdata, _edata, _la_data, _sbss, _ebss;

  memcpy(&_sdata, &_la_data, &_edata - &_sdata);
  memset(&_sbss, 0, &_ebss - &_sbss);

  main();

  while (1)
    ;
}

/**
 * @brief Definition for the memcpy function
 */
__attribute__((weak)) void *memcpy(void *dest, const void *src, uint32_t n) {
  for (uint32_t i = 0; i < n; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  return dest;
}

/**
 * @brief Definition for the memset function
 */ 
__attribute__((weak)) void *memset(void *dst0, int c, uint32_t length) {
  char *dst = (char *)dst0;
  while (length--) {
    *dst = (char)c;
    dst++;
  }
  return dst0;
}

