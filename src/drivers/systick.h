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

// System Tick base address.
#define SYSTICK ((systick_t * const)0xE000E010)

void systick_init(uint32_t ticks);

#ifdef __cplusplus
}
#endif

#endif  // __KL46Z_SYSTICK__
