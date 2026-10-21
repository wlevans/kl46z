/*******************************************************************************
* Processor: KL46Z256VXX4
*
*/

/* Entry point. */
ENTRY(_reset);

MEMORY {
  flash(rx)  : ORIGIN = 0x00000000, LENGTH = 0x00040000 /* 256 k */
  sram(rwx)  : ORIGIN = 0x1FFFE000, LENGTH = 0x00008000 /*  32 k */
}

/* Stack points to end of SRAM. */
_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS
{
  /* Interrupt vector table. */
  .vectors :
  {
   KEEP(*(.vectors))
  } > flash

  /* Code and constants. */
  .text :
  { 
    *(.text*)
  } > flash

  /* Read only data. */
  .rodata :
  {
    *(.rodata*)
  } > flash

  /* Initialized data. */
  .data :
  {
    _sdata = .;   /* .data section start. */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = .;  /* .data section end. */
  } > sram AT > flash
  _sidata = LOADADDR(.data);

  /* Uninitialized data (set to zero). */
  .bss :
  {
    _sbss = .;              /* .bss section start. */
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;              /* .bss section end. */
  } > sram

  . = ALIGN(8);
  _end = .;     /* for cmsis_gcc.h.(?) */
}
