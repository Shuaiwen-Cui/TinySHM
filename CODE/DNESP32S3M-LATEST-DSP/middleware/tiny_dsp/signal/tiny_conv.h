/**
 * @file tiny_conv.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_conv | code | header 
 * @version 1.0
 * @date 2025-04-27
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

/* DEPENDENCIES */
// tiny_dsp configuration file
#include "tiny_dsp_config.h"

// ESP32 DSP Library for Acceleration
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32 // ESP32 DSP library

#include "dsps_conv.h"
#include "dspi_conv.h"

#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name: tiny_conv_f32
 * @brief Convolution function
 * 
 * @param Signal The input signal array
 * @param siglen The length of the input signal array
 * @param Kernel The input kernel array
 * @param kernlen The length of the input kernel array
 * @param convout The output array for the convolution result
 * 
 * @return tiny_error_t 
 */
tiny_error_t tiny_conv_f32(const float *Signal, const int siglen, const float *Kernel, const int kernlen, float *convout);

#ifdef __cplusplus
}
#endif
