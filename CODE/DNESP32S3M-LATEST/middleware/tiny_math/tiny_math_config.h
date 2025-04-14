/**
 * @file tiny_math_config.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief The configuration file for the tiny_math middleware.
 * @version 1.0
 * @date 2025-04-14
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TINY_MATH_CONFIG__
#define __TINY_MATH_CONFIG__

#ifdef __cplusplus
extern "C"
{
#endif

/* DEPENDENCIES */

// lower level
#include "tiny_toolbox.h"

// platform-optimization
#include "esp_dsp.h"


/* PLATFORM SELECTION */

// MCU Optimization Options: only one can be selected at a time. The first one for ANSI C for general MCUs, the rest for specific MCUs.
// #define MCU_PLATFORM_GENERIC
// #define MCU_PLATFORM_ESP32
#define MCU_PLATFORM_ESP32S3
// #define MCU_PLATFORM_STM32

#ifdef __cplusplus
}
#endif

#endif /* __TINY_MATH_CONFIG__ */