/*

https://support.arm.com/documentation/dui0662/b/Cortex-M0--Peripherals/System-timer--SysTick?lang=en

https://www.embeddedsoft.net/cortex-m-systick-timer-configuration-and-usage/

(48000000 / 1000) - 1;

*/


#ifndef __KL46Z_SYSTICK__
#define __KL46Z_SYSTICK__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef volatile struct
{
        uint32_t SYST_CSR;    // Control and Status Register.
        uint32_t SYST_RVR;    // Reload Value Register.
        uint32_t SYST_CVR;    // Current Value Register.
  const uint32_t SYST_CALIB;  // Calibration Value Register.
} systick_t;

#define SYSTICK ((systick_t * const)0xE000E010)

void systick_init(uint32_t ticks);
void SysTick_Handler(void);
/*
uint32_t systick_get_countflag(void);
void systick_clock_source(uint32_t source);
void systick_enable_exception(void);
void systick_disable_exception(void);
void systick_enable(void);
void systick_disable(void);
void systick_reload_value(uint32_t value);
uint32_t systick_current_value(void);
*/

#ifdef __cplusplus
}
#endif

#endif  // __KL46Z_SYSTICK__
