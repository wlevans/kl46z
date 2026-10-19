#include <stdint.h>

typedef struct
{
        volatile uint32_t PDOR;
        volatile uint32_t PSOR;
        volatile uint32_t PCOR;
        volatile uint32_t PTOR;
  const volatile uint32_t PDIR;
        volatile uint32_t PDDR;
} gpio_t;

#define GPIOA ((gpio_t *)0x400FF000)
#define GPIOB ((gpio_t *)0x400FF080)
#define GPIOC ((gpio_t *)0x400FF080)
#define GPIOD ((gpio_t *)0x400FF0C0)
#define GPIOE ((gpio_t *)0x400FF100)
