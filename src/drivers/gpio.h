#ifndef __KL46Z_GPIO__
#define __KL46Z_GPIO__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

// GPIO ports register definition.
typedef volatile struct
{
        uint32_t PDOR;  // Port Data Output Register
        uint32_t PSOR;  // Port Set Output Register
        uint32_t PCOR;  // Port Clear Output Register
        uint32_t PTOR;  // Port Toggle Output Register
  const uint32_t PDIR;  // Port Data Input Register
        uint32_t PDDR;  // Port Data Direction Register
} gpio_t;

// General Purpose Input/Output Ports base addresses.
#define GPIOA ((gpio_t * const)0x400FF000)
#define GPIOB ((gpio_t * const)0x400FF040)
#define GPIOC ((gpio_t * const)0x400FF080)
#define GPIOD ((gpio_t * const)0x400FF0C0)
#define GPIOE ((gpio_t * const)0x400FF100)

// GPIO operational modes.
typedef enum
{
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_COUNT
} gpio_mode_t;

// GPIO commands.
void gpio_set_mode(gpio_t * gpio_port, uint32_t mask, gpio_mode_t mode);
void gpio_output_set(gpio_t * gpio_port, uint32_t mask);
void gpio_output_clear(gpio_t * gpio_port, uint32_t mask);
void gpio_output_write(gpio_t * gpio_port, uint32_t mask);
void gpio_output_toggle(gpio_t * gpio_port, uint32_t mask);
uint32_t gpio_input_read(gpio_t * gpio_port);

#ifdef __cplusplus
}
#endif

#endif  // __KL46Z_GPIO__
