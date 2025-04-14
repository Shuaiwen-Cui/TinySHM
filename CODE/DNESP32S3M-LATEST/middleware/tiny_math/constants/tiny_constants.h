#ifndef __TINY_CONSTANTS_H__
#define __TINY_CONSTANTS_H__

/* DEPENDENCIES */
#include "tiny_math_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// =======================================
// Logical Constants
// =======================================
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

// =======================================
// Math Constants (float/double safe)
// =======================================
#define TINY_PI         3.14159265358979323846f
#define TINY_TWO_PI     6.28318530717958647692f
#define TINY_HALF_PI    1.57079632679489661923f
#define TINY_E          2.71828182845904523536f
#define TINY_SQRT2      1.41421356237309504880f
#define TINY_INV_SQRT2  0.70710678118654752440f

#define TINY_DEG2RAD(x) ((x) * TINY_PI / 180.0f)
#define TINY_RAD2DEG(x) ((x) * 180.0f / TINY_PI)

// =======================================
// Bitmask & Bit Manipulation
// =======================================

// Bit Manipulation
#define BIT(n)              (1U << (n))         // e.g. BIT(3) = 0b00001000
#define BIT_SET(x, n)       ((x) |= BIT(n))
#define BIT_CLEAR(x, n)     ((x) &= ~BIT(n))
#define BIT_TOGGLE(x, n)    ((x) ^= BIT(n))
#define BIT_CHECK(x, n)     (((x) >> (n)) & 0x1)

// Common Masks
#define MASK_4BIT           0x0F    // 00001111
#define MASK_8BIT           0xFF    // 11111111
#define MASK_16BIT          0xFFFF
#define MASK_32BIT          0xFFFFFFFF

// =======================================
// Fixed Point Scaling
// =======================================
#define Q7_SCALE   128      // For fixed-point representation
#define Q15_SCALE  32768
#define Q31_SCALE  2147483648    

#ifdef __cplusplus
}
#endif

#endif /* __TINY_CONSTANTS_H__ */
