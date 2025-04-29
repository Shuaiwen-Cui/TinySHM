/**
 * @file tiny_resample.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_resample | code | source
 * @version 1.0
 * @date 2025-04-29
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
#include "tiny_resample.h" // tiny_resample header

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
                               int factor)
{
    if (!input || !output || !output_len)
        return TINY_ERR_DSP_NULL_POINTER;

    if (input_len <= 0 || factor <= 0)
        return TINY_ERR_DSP_INVALID_PARAM;

    int out_len = input_len / factor;
    *output_len = out_len;

    for (int i = 0; i < out_len; i++)
    {
        output[i] = input[i * factor];
    }

    return TINY_OK;
}

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
                               int target_len)
{
    if (!input || !output)
        return TINY_ERR_DSP_NULL_POINTER;

    if (input_len <= 0 || target_len <= 0)
        return TINY_ERR_DSP_INVALID_PARAM;

    float ratio = (float)(target_len) / (float)(input_len);

    for (int i = 0; i < target_len; i++)
    {
        float pos = i / ratio;
        int index = (int)floorf(pos);
        float frac = pos - index;

        if (index >= input_len - 1)
            output[i] = input[input_len - 1]; // Clamp at end
        else
            output[i] = input[index] * (1.0f - frac) + input[index + 1] * frac;
    }

    return TINY_OK;
}
