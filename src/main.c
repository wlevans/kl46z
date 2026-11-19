#include <frdm_kl46z.h>
#include <stdint.h>
#include "bsp/led.h"
#include "systick.h"
#include <stdbool.h>

uint32_t systick_count = 0;

void delay(uint32_t count);

int main(void)
{
  // Initialize system tick.
  systick_init(48000000 / 1000);

  // Initialize LEDs.
  led_init(LED_RED);
  led_init(LED_GREEN);
  led_on(LED_GREEN);

  while(1)
  {
    delay(500);
    // Toggle LEDs.
    led_toggle(LED_RED);
    led_toggle(LED_GREEN);
  }

  // Should never get here.
  return 0;
}

void delay(uint32_t count)
{
  uint32_t then = count + systick_count;
  while(then > systick_count )
  {
    __asm__("nop");
  }
  return;
}

void SysTick_Handler(void)
{
  ++systick_count;
}
