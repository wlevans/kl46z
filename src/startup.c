#include <stdint.h>

// Forward define main.
int main(void);

// Reset Handler prototype.
__attribute__((naked, noreturn)) void Reset_Handler(void);

// Startup code.
void Reset_Handler(void)
{
  // Get section start and end points from linker directive.
  extern uint32_t _sbss;
  extern uint32_t _ebss;
  extern uint32_t _sdata;
  extern uint32_t _edata;
  extern uint32_t _sidata;

  // Initialize .bss to zeros.
  for(uint32_t *dst = &_sbss; dst < &_ebss;)
  {
    *dst++ = 0;
  }
  // Copy .data to RAM.
  for(uint32_t *dst = &_sdata, *src = &_sidata; dst < &_edata;)
  {
    *dst++ = *src++;
  }
  // Call main.
  main();
  // Infinite loop in the case if main() returns
  while(1)
  {
    (void) 0;
  }
}

extern void _estack(void);

// 16 standard plus 33 KL46Z specific handlers.
__attribute__((section(".vectors"))) void (*const tab[16 + 33])(void) =
{
  _estack, Reset_Handler
};
