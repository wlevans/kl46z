#include "gpio.h"

void main(void)
{
  GPIOE->PDDR |= (1 << 29);
  GPIOE->PSOR |= (1 << 29);
  while(1);
}
