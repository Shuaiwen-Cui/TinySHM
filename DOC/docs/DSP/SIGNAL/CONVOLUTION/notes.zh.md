# 说明

## 卷积的数学原理

卷积是信号处理中的一种重要操作，用于描述两个信号之间的关系。它可以看作是一个信号与另一个信号的加权平均。卷积的数学定义如下：

$$y(t) = \int_{-\infty}^{\infty} x(\tau) h(t - \tau) d\tau$$

其中，$x(t)$ 是输入信号，$h(t)$ 是系统的脉冲响应，$y(t)$ 是输出信号。卷积的结果是一个新的信号，它包含了输入信号和系统脉冲响应之间的所有信息。

![](https://www.brandonrohrer.com/images/conv1d/aa_copy.gif)

## 编程思路

本库中的卷积操作实际上是将卷积核调转方向然后与输入信号进行逐点相乘并求和。

## tiny_conv_f32

```c
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

**描述**：该函数实现了对输入信号和卷积核的卷积操作。它首先检查输入参数是否为NULL，然后根据平台选择使用ESP32 DSP库或标准C实现进行卷积计算。函数返回卷积结果。

**特点**：

- 支持ESP32 DSP库加速

- 支持卷积核和信号互换以保证信号长度大于卷积核长度

**参数**：

- `Signal`：输入信号数组

- `siglen`：输入信号数组的长度

- `Kernel`：输入卷积核数组

- `kernlen`：输入卷积核数组的长度

- `convout`：输出数组，用于存储卷积结果

**返回值**：

- `TINY_OK`：卷积成功

- `TINY_ERR_DSP_NULL_POINTER`：输入参数为NULL