#include "systick.h"

void systick_init(uint32_t ticks)
{
  // Set reload value.
  SYSTICK->SYST_RVR = ticks - 1;
  // Clear current count.
  SYSTICK->SYST_CVR = 0x00000000;
  // Select processor clock.
  // Enable interrupt.
  // Enable counter.
  SYSTICK->SYST_CSR = 0x00000007;
  return;
}
