# 说明

!!! note "说明"
    重采样是信号处理中的一个重要步骤，通常用于改变信号的采样率。它可以用于音频、视频和其他类型的信号处理。

## 信号抽取 - 整数倍    

信号抽取是指从原始信号中以一定的间隔选择样本。它通常用于降低信号的采样率。

从原理上来说，应当是先滤波去除高频分量抗混叠，然后再抽取，目前出于简单化，直接抽取，可能会引入混叠。

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

**描述**：

信号重采样是指将信号的采样率从一个值转换为另一个值。它通常用于音频和视频处理，以适应不同的播放设备或网络带宽。

**特点**：

- 整数倍

**参数**：

- `input`: 输入信号数组的指针

- `input_len`: 输入信号数组的长度

- `output`: 输出信号数组的指针

- `output_len`: 输出信号数组的长度

- `factor`: 重采样因子


## 信号重采样 - 任意倍数上下采样 - 线性插值

重采样是指将信号的采样率从一个值转换为另一个值。这里我们采用最直接的线性插值法。首先计算新信号中点在老信号中的大概位置，结合起位置平衡左右点数值进行生成。

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

**描述**：

信号重采样是指将信号的采样率从一个值转换为另一个值。它通常用于音频和视频处理，以适应不同的播放设备或网络带宽。

**特点**：

- 任意倍数上下采样

- 线性插值

**参数**：

- `input`: 输入信号数组的指针

- `input_len`: 输入信号数组的长度

- `output`: 输出信号数组的指针

- `target_len`: 目标长度，用于输出信号数组的长度

