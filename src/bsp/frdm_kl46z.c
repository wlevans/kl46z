#include "frdm_kl46z.h"

void board_init(void)
{
	// Disable COP watchdog.
	*((uint32_t *)0x40048100) &= ~(0x0C);

	// Transition from FEI to FBE.

	// High frequency range.
	// High gain operation.
	// External crystal.
	MCG->C2 = 0x1C; // 0x2C?
	// External reference clock as system clock.
	// Divide by 256 (8 Mhz / 256 = 31.25 kHz).
	// External reference clock is selected.
	MCG->C1 = 0x98;
	// Loop until crystal oscillator has been initialized.
	while(!(MCG->S & 0x02));
	// Loop until external reference is the current source for reference clock.
	while(MCG->S & 0x10);
	// Loop until external reference clock is selected for MCGOUTCLK.
	while(!(MCG->S & 0x08));
	// Divide by 4 (8 Mhz / 4 = 2 MHz).
	MCG->C5 = 0x03;

	// Transition from FBE to PBE.

	// Select PLL.
	// Multiply by 24 (2 MHz * 24 = 48 MHz).
	MCG->C6 = 0x40;
	// Loop until source of PLLS clock is PLL output clock.
	while(!(MCG->S & 0x20));
	// Loop until PLL is locked.
	while(!(MCG->S & 0x40));

	// Transition from PBE to PEE.
	// Select PLL as the system clock.
	MCG->C1 = 0x18;
	// Loop until PLL outpus is selected to feed MCGOUTCLK.
	while(!(MCG->S & 0x0C));

	return;
}
