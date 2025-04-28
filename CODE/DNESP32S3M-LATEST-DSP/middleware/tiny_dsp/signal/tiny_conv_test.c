/**
 * @file tiny_conv_test.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_conv | test | header
 * @version 1.0
 * @date 2025-04-28
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
// tiny_conv
#include "tiny_conv_test.h"

void tiny_signal_conv_test(void)
{
    // 1. definition
    const float test_signal[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    const int siglen = sizeof(test_signal) / sizeof(test_signal[0]);

    const float test_kernel[] = {0.5f, 1.0f};
    const int kernlen = sizeof(test_kernel) / sizeof(test_kernel[0]);

    // 2. compute output length
    const int conv_len = siglen + kernlen - 1;
    float conv_output[conv_len];

    // 3. call the convolution function
    tiny_error_t status = tiny_conv_f32(test_signal, siglen, test_kernel, kernlen, conv_output);

    // 4. return status;
    if (status != TINY_OK) {
        printf("[Test Failed] tiny_conv_f32 returned error code: %d\n", status);
        return;
    }

    // 5. printf("Convolution Test:\n");
    printf("Convolution Output:\n");
    for (int i = 0; i < conv_len; i++) {
        printf("  conv_output[%d] = %.3f\n", i, conv_output[i]);
    }

    // 6. verify the output
    const float expected_output[] = {0.5f, 2.0f, 3.5f, 5.0f, 6.5f, 5.0f};
    int pass = 1;
    for (int i = 0; i < conv_len; i++) {
        if ( (conv_output[i] - expected_output[i]) > 1e-5f || (conv_output[i] - expected_output[i]) < -1e-5f ) {
            pass = 0;
            break;
        }
    }

    if (pass) {
        printf("[Test Passed] tiny_conv_f32 output matches expected results.\n");
    } else {
        printf("[Test Failed] tiny_conv_f32 output mismatch.\n");
    }
}