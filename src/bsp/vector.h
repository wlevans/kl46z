// System default handler.
void Default_Handler(void);

// Reset Handler prototype.
__attribute__((naked, noreturn)) void Reset_Handler(void);

void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
