#include "led.h"

leds_t leds[LED_COUNT];

void led_init(led_t led)
{
  assert(led < LED_COUNT);
  assert(0 == leds[led].gpio_port);

  switch(led)
  {
    case LED_RED:
      *((uint32_t *)0x40048038) |= (1 << 13);
      *((uint32_t *)0x4004D074) |= (1 <<  8);
      leds[led].gpio_port = LED_RED_GPIO_PORT;
      leds[led].pin_mask = LED_RED_PIN_MASK;
      break;
    case LED_GREEN:
      *((uint32_t *)0x40048038) |= (1 << 12);
      *((uint32_t *)0x4004C014) |= (1 <<  8);
      leds[led].gpio_port = LED_GREEN_GPIO_PORT;
      leds[led].pin_mask = LED_GREEN_PIN_MASK;
      break;
    default:
      break;
  }

  gpio_set_mode(leds[led].gpio_port, leds[led].pin_mask, GPIO_MODE_OUTPUT);
  gpio_output_clear(leds[led].gpio_port, leds[led].pin_mask);
  gpio_output_set(leds[led].gpio_port, leds[led].pin_mask);
  return;
}

extern inline void led_on(led_t led);
extern inline void led_off(led_t led);
extern inline void led_toggle(led_t led);
