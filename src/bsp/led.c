#include "led.h"
#include <assert.h>
#include <stdlib.h>

leds_t leds[LED_COUNT] = {NULL};

void led_init(led_t led)
{
	assert(led < LED_COUNT);
	assert(NULL == &leds[led]);

	switch(led)
	{
		case LED_RED:
			leds[led].gpio_port = LED_RED_GPIO_PORT;
			leds[led].pin_mask = LED_RED_PIN_MASK;
			break;
		case LED_GREEN:
			leds[led].gpio_port = LED_GREEN_GPIO_PORT;
			leds[led].pin_mask = LED_GREEN_PIN_MASK;
			break;
		default:
			break;
	}

	gpio_set_mode(leds[led].gpio_port, leds[led].pin_mask, GPIO_MODE_OUTPUT);
	gpio_output_clear(leds[led].gpio_port, leds[led].pin_mask);
	return;
}

void led_on(led_t led)
{
	assert(led < LED_COUNT);
	assert(NULL != &leds[led]);

	gpio_output_set(leds[led].gpio_port, leds[led].pin_mask);
	return;
}

void led_off(led_t led)
{
	assert(led < LED_COUNT);
	assert(NULL != &leds[led]);

	gpio_output_clear(leds[led].gpio_port, leds[led].pin_mask);
	return;
}

void led_toggle(led_t led)
{
	assert(led < LED_COUNT);
	assert(NULL != &leds[led]);

	gpio_output_toggle(leds[led].gpio_port, leds[led].pin_mask);
	return;
}
