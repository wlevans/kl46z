#ifndef __KL46Z_MCG__
#define __KL46Z_MCG__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef volatile struct
{
        uint8_t C1;
        uint8_t C2;
        uint8_t C3;
        uint8_t C4;
        uint8_t C5;
        uint8_t C6;
  const uint8_t S;
  const uint8_t RESERVED0;
        uint8_t SC;
  const uint8_t RESERVED1;
        uint8_t ATCVH;
        uint8_t ATCVL;
        uint8_t C7;
        uint8_t C8;
        uint8_t C9;
        uint8_t C10;
} mcg_t;

#define MCG ((mcg_t * const)0x40064000)

#ifdef __cplusplus
}
#endif

#endif // __KL46Z_MCG__
