/**
 * @file tiny_conv.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the header file for the submodule conv of the tiny_dsp middleware.
 * @version 1.0
 * @date 2025-04-27
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

// #ifndef __TINY_CONV__
// #define __TINY_CONV__

/* DEPENDENCIES */
// tiny_dsp configuration file
#include "tiny_dsp_config.h"

// ESP32 DSP Library for Acceleration
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32 // ESP32 DSP library
#include "dsps_conv.h"
#include "dsps_corr.h"
#include "dsps_ccorr.h"
#include "dspi_conv.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

tiny_error_t tiny_conv_f32(const float *Signal, const int siglen, const float *Kernel, const int kernlen, float *convout);

#ifdef __cplusplus
}
#endif

// #endif /* __TINY_CONV__ */