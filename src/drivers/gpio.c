#include "gpio.h"
#include <assert.h>

void gpio_set_mode(gpio_t * gpio_port, uint32_t mask, gpio_mode_t mode)
{
	assert(mode < GPIO_MODE_COUNT);
	if(GPIO_MODE_INPUT == mode)
	{
		gpio_port->PDDR &= ~mask;
	}
	else
	{
		gpio_port->PDDR |= mask;
	}
	return;
}

void gpio_output_set(gpio_t * gpio_port, uint32_t mask)
{
	gpio_port->PSOR |= mask;
	return;
}

void gpio_output_clear(gpio_t * gpio_port, uint32_t mask)
{
	gpio_port->PCOR |= mask;
	return;
}

void gpio_output_write(gpio_t * gpio_port, uint32_t mask)
{
	gpio_port->PDOR |= mask;
	return;
}

void gpio_output_toggle(gpio_t * gpio_port, uint32_t mask)
{
	gpio_port->PTOR |= mask;
	return;
}

uint32_t gpio_input_read(gpio_t * gpio_port)
{
	return gpio_port->PDIR;
}
