#include <stdint.h>

typedef volatile struct
{
        uint32_t PDOR;
        uint32_t PSOR;
        uint32_t PCOR;
        uint32_t PTOR;
  const uint32_t PDIR;
        uint32_t PDDR;
} gpio_t;

#define GPIOA ((gpio_t *)0x400FF000)
#define GPIOB ((gpio_t *)0x400FF080)
#define GPIOC ((gpio_t *)0x400FF080)
#define GPIOD ((gpio_t *)0x400FF0C0)
#define GPIOE ((gpio_t *)0x400FF100)
