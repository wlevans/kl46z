#include <stdint.h>
#include "gpio.h"

void delay(void);

void main(void)
{
  *((uint32_t *)0x40048038) |= (1 << 13);
  *((uint32_t *)0x4004D074) |= (1 <<  8);
  GPIOE->PDDR |= (1 << 29);
  GPIOE->PCOR |= (1 << 29);

  *((uint32_t *)0x40048038) |= (1 << 12);
  *((uint32_t *)0x4004C014) |= (1 <<  8);
  GPIOD->PDDR |= (1 << 5);
  GPIOD->PSOR |= (1 << 5);

  while(1)
  {
    delay();
    GPIOE->PTOR |= (1 << 29);
    GPIOD->PTOR |= (1 <<  5);
  }
}

void delay(void)
{
  uint32_t i;
  for(i = 0; i < 1000000; ++i)
    {
      __asm__("nop");
    }
}
