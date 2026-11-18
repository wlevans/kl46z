#include "systick.h"

volatile uint32_t systick_count = 0;

void systick_init(uint32_t ticks)
{
  // Set reload value.
  SYSTICK->SYST_RVR = ticks;
  // Clear current count.
  SYSTICK->SYST_CVR = 0x00000000;
  // Select processor clock.
  // Enable interrupt.
  // Enable counter.
  SYSTICK->SYST_CSR = 0x00000007;
  return;
}

void SysTick_Handler(void)
{
  ++systick_count;
}
