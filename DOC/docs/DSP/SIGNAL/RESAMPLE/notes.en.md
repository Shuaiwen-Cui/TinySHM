# NOTES

!!! note "Note"
    Resampling is an important step in signal processing, typically used to change the sampling rate of a signal. It can be used in audio, video, and other types of signal processing.

## Signal Decimation - Integer Factor

    Signal decimation refers to selecting samples from the original signal at certain intervals. It is typically used to reduce the sampling rate of a signal.

    Theoretically, it should first filter out high-frequency components to prevent aliasing and then decimate. Currently, for simplification, we directly decimate, which may introduce aliasing.

```c
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

```

**Description**:

Signal resampling refers to converting the sampling rate of a signal from one value to another. It is commonly used in audio and video processing to adapt to different playback devices or network bandwidth.

**Features**:

- Integer Factor

**Parameters**:

- `input`: Pointer to the input signal array

- `input_len`: Length of the input signal array

- `output`: Pointer to the output signal array

- `output_len`: **Pointer** to the length of the output signal array

- `factor`: Decimation factor

## Signal Resampling - Non-integer Factor

    Signal resampling is the process of changing the sampling rate of a signal. We need to first calculate the proportional factor and then use interpolation to fill in the gaps.


```c
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

```

***Description**:

Signal resampling is the process of changing the sampling rate of a signal. Here, we use the most straightforward linear interpolation method. First, we calculate the approximate position of the new signal in the old signal, and then balance the left and right values to generate the new signal.

**Features**:

- Non-integer Factor

- Linear Interpolation

**Parameters**:

- `input`: Pointer to the input signal array

- `input_len`: Length of the input signal array

- `output`: Pointer to the output signal array

- `target_len`: Target length for the output signal array



