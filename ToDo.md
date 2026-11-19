# To Do:

* [ ] Set up MCG
  * Chapter 24 RM
  * FIE to PEE
  * External Osc = 8 Mhz
  * MCGOUTCLK = 48 Mhz

* [ ] Enable GPIOE(D) clocks.

```
  // Transition from FEI to FBE.

  // High frequency range.
  // High gain operation.
  // External crystal.
  *((uint8_t *)0x40064001) = 0x0E; // 0x2C?

  // External reference clock as system clock.
  // Divide by 256 (8 Mhz / 256 = 31.25 kHz).
  // External reference clock is selected.
  *((uint8_t *)0x40064000) = 0x98;

  // Loop until crystal oscillator has been initialized.
  while(*((uint8_t *)0x40064006) & 0x02);

  // Loop until external reference is the current source for reference clock.
  while(*((uint8_t *)0x40064006) & 0x10);

  // Loop until external reference clock is selected for MCGOUTCLK.
  while(*((uint8_t *)0x40064006) & 0x04);

  // Divide by 4 (8 Mhz / 4 = 2 MHz).
  *((uint8_t *)0x40064004) = 0x03;

  // Transition from FBE to PBE.

  // Select PLL.
  // Multiply by 24 (2 MHz * 24 = 48 MHz).
  *((uint8_t *)0x40064005) = 0x40;

  // Loop until source of PLLS clock is PLL output clock.
  while(*((uint8_t *)0x40064006) & 0x20);

  // Loop until PLL is locked.
  while(*((uint8_t *)0x40064006) & 0x40);

  // Transition from PBE to PEE.

  // Select PLL as the system clock.
  *((uint8_t *)0x40064000) = 0x10;
```
