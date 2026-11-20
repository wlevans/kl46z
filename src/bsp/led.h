#ifndef __FRDM_KL46Z_LED__
#define __FRDM_KL46Z_LED__

#ifdef __cplusplus
extern "C"
{
#endif

#include "../drivers/gpio.h"
#include <assert.h>
#include <stdlib.h>

#define LED_RED_GPIO_PORT    GPIOE
#define LED_RED_PIN_MASK     1 << 29
#define LED_GREEN_GPIO_PORT  GPIOD
#define LED_GREEN_PIN_MASK   1 <<  5

// GPIO operational modes.
typedef enum
{
	LED_RED,
	LED_GREEN,
	LED_COUNT
} led_t;

typedef struct
{
	gpio_t * gpio_port;
	uint32_t pin_mask;
} leds_t;

extern leds_t leds[LED_COUNT];

void led_init(led_t led);
inline __attribute__((always_inline)) void led_on(led_t led)
{
  assert(led < LED_COUNT);
  assert(NULL != &leds[led]);

  gpio_output_clear(leds[led].gpio_port, leds[led].pin_mask);
  return;
}
inline __attribute__((always_inline)) void led_off(led_t led)
{
  assert(led < LED_COUNT);
  assert(NULL != &leds[led]);

  gpio_output_set(leds[led].gpio_port, leds[led].pin_mask);
  return;
}

inline __attribute__((always_inline)) void led_toggle(led_t led)
{
  assert(led < LED_COUNT);
  assert(NULL != &leds[led]);

  gpio_output_toggle(leds[led].gpio_port, leds[led].pin_mask);
  return;
}

#ifdef __cplusplus
}
#endif

#endif  // __FRDM_KL46Z_LED__
