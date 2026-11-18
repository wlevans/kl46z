#include "vector.h"
#include "frdm_kl46z.h"
#include <stdint.h>

extern void _estack(void);

// 1 stack pointer + 16 standard plus 32 KL46Z specific handlers.
__attribute__((section(".vectors"))) void (*const tab[1 + 16 + 32])(void) =
{
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
  SysTick_Handler,
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
  Default_Handler,
  Default_Handler,
  Default_Handler,
  Default_Handler,
  Default_Handler,
  Default_Handler,
  Default_Handler
};

// System default handler.
void Default_Handler(void)
{
  while(1);
}

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

  board_init();

  // Call main.
  main();
  // Infinite loop in the case if main() returns
  while(1)
  {
    (void) 0;
  }
}
