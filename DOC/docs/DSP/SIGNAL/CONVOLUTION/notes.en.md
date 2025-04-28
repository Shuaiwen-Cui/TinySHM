# NOTES

## Mathematical Principle of Convolution

Convolution is an important operation in signal processing, which is used to describe the relationship between two signals. It can be regarded as the weighted average of one signal and another signal. The mathematical definition of convolution is as follows:

$$y(t) = \int_{-\infty}^{\infty} x(\tau) h(t - \tau) d\tau$$

Where $x(t)$ is the input signal, $h(t)$ is the impulse response of the system, and $y(t)$ is the output signal. The result of convolution is a new signal that contains all the information between the input signal and the impulse response of the system.

![](https://www.brandonrohrer.com/images/conv1d/aa_copy.gif)

## Programming Philosophy

The convolution operation in this library actually reverses the direction of the convolution kernel and then multiplies it point by point with the input signal and sums it.

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

**Description**:  
This function performs the convolution operation between the input signal and the kernel. It first checks whether the input parameters are `NULL`, and then selects either the ESP32 DSP library or a standard C implementation for the convolution calculation based on the platform. The function returns the convolution result.

**Features**:

- Supports acceleration with the ESP32 DSP library.
- Supports swapping the signal and kernel to ensure the signal length is greater than the kernel length.

**Parameters**:

- `Signal`: Input signal array.
- `siglen`: Length of the input signal array.
- `Kernel`: Input kernel array.
- `kernlen`: Length of the input kernel array.
- `convout`: Output array to store the convolution result.

**Return Value**:

- `TINY_OK`: Convolution completed successfully.
- `TINY_ERR_DSP_NULL_POINTER`: One or more input parameters are `NULL`.
