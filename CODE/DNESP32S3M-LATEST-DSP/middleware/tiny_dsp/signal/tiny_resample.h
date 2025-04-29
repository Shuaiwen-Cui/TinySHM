/**
 * @file tiny_resample.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_resample | code | header
 * @version 1.0
 * @date 2025-04-29
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

/* DEPENDENCIES */
// tiny_dsp configuration file
#include "tiny_dsp_config.h"

// ESP32 DSP Library for Acceleration
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32 // ESP32 DSP library

#endif

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @name: tiny_decimate_f32
     * @brief Decimate a signal by a given factor
     *
     * @param input pointer to the input signal array
     * @param input_len length of the input signal array
     * @param output pointer to the output signal array
     * @param output_len pointer to the length of the output signal array
     * @param factor decimation factor
     * @return tiny_error_t
     */
    tiny_error_t tiny_decimate_f32(const float *input,
                                   int input_len,
                                   float *output,
                                   int *output_len,
                                   int factor);

    /**
     * @name: tiny_resample_f32
     * @brief Resample a signal to a target length
     *
     * @param input pointer to the input signal array
     * @param input_len length of the input signal array
     * @param output pointer to the output signal array
     * @param target_len target length for the output signal array
     * @return tiny_error_t
     */
    tiny_error_t tiny_resample_f32(const float *input,
                                   int input_len,
                                   float *output,
                                   int target_len);

#ifdef __cplusplus
}
#endif
