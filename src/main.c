#include <stdint.h>
#include "bsp/led.h"

#define DELAY_COUNT 1000000

void delay(void);

int main(void)
{
  // Configure red LED.
  led_init(LED_RED);
  // Configure green LED.
  led_init(LED_GREEN);
  while(1)
  {
    delay();
    // Toggle LEDs.
    led_toggle(LED_RED);
    led_toggle(LED_GREEN);
  }
}

void delay(void)
{
  volatile uint32_t i;
  for(i = 0; i < DELAY_COUNT; ++i)
    {
      __asm__("nop");
    }
}
