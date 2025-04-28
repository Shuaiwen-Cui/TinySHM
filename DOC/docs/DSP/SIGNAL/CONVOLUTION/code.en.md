# CODE

## tiny_conv.h

```c
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

```

## tiny_conv.c

```c
/**
 * @file tiny_conv.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_conv | code | source
 * @version 1.0
 * @date 2025-04-27
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
#include "tiny_conv.h"

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
tiny_error_t tiny_conv_f32(const float *Signal, const int siglen, const float *Kernel, const int kernlen, float *convout)
{
    if (NULL == Signal || NULL == Kernel || NULL == convout)
    {
        return TINY_ERR_DSP_NULL_POINTER;
    }

#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
    // ESP32 DSP library
    dsps_conv_f32(Signal, siglen, Kernel, kernlen, convout);
#else
    float *sig = (float *)Signal;
    float *kern = (float *)Kernel;
    int lsig = siglen;
    int lkern = kernlen;

    // swap the signal and kernel to ensure the signal is longer than the kernel
    if (siglen < kernlen)
    {
        sig = (float *)Kernel;
        kern = (float *)Signal;
        lsig = kernlen;
        lkern = siglen;
    }

    // stage I
    for (int n = 0; n < lkern; n++)
    {
        size_t k;

        convout[n] = 0;

        for (k = 0; k <= n; k++)
        {
            convout[n] += sig[k] * kern[n - k];
        }
    }

    // stage II
    for (int n = lkern; n < lsig; n++)
    {
        size_t kmin, kmax, k;

        convout[n] = 0;

        kmin = n - lkern + 1;
        kmax = n;
        for (k = kmin; k <= kmax; k++)
        {
            convout[n] += sig[k] * kern[n - k];
        }
    }

    // stage III
    for (int n = lsig; n < lsig + lkern - 1; n++)
    {
        size_t kmin, kmax, k;

        convout[n] = 0;

        kmin = n - lkern + 1;
        kmax = lsig - 1;
        for (k = kmin; k <= kmax; k++)
        {
            convout[n] += sig[k] * kern[n - k];
        }
    }
#endif

    return TINY_OK;
}
```