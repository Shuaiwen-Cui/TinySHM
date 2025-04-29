/**
 * @file tiny_resample_test.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief tiny_resample | test | source
 * @version 1.0
 * @date 2025-04-29
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
#include "tiny_resample_test.h" // tiny_resample test header

#define EPSILON 1e-1f  // Tolerance for float comparison

// Utility to print float array
void print_array(const char *label, const float *array, int len) {
    printf("%s [", label);
    for (int i = 0; i < len; i++) {
        printf("%.2f", array[i]);
        if (i != len - 1) printf(", ");
    }
    printf("]\n");
}

// Simple float array comparison
int compare_float_array(const float *a, const float *b, int len) {
    for (int i = 0; i < len; i++) {
        if (fabs(a[i] - b[i]) > EPSILON) {
            return 0;
        }
    }
    return 1;
}

void tiny_signal_resample_decimate_test(void)
{
    printf("\n========== TinyDSP Resample & Decimate Test ==========\n");

    /*** Test 1: Decimate by factor 2 ***/
    const float input1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    const int input1_len = sizeof(input1) / sizeof(input1[0]);
    const int factor = 2;
    float dec_output[8] = {0};
    int dec_output_len = 0;

    const float expected_dec[] = {1.0f, 3.0f, 5.0f};

    tiny_error_t status_dec = tiny_decimate_f32(input1, input1_len, dec_output, &dec_output_len, factor);

    printf("\n--- Test 1: tiny_decimate_f32 (factor = %d) ---\n", factor);
    print_array("Input     :", input1, input1_len);
    print_array("Expected  :", expected_dec, dec_output_len);
    print_array("Output    :", dec_output, dec_output_len);
    printf("Result    : [%s]\n", (status_dec == TINY_OK && compare_float_array(dec_output, expected_dec, dec_output_len)) ? "PASS" : "FAIL");

    /*** Test 2: Resample to length 7 ***/
    const float input2[] = {10.0f, 20.0f, 30.0f, 40.0f};
    const int input2_len = sizeof(input2) / sizeof(input2[0]);
    const int target_len = 7;
    float res_output[16] = {0};

    // Approximate expected values by visual inspection (not exact)
    const float expected_res[] = {10.0f, 15.7f, 21.4f, 27.1f, 32.9f, 38.6f, 40.0f};

    tiny_error_t status_res = tiny_resample_f32(input2, input2_len, res_output, target_len);

    printf("\n--- Test 2: tiny_resample_f32 (target_len = %d) ---\n", target_len);
    print_array("Input     :", input2, input2_len);
    print_array("Expected  :", expected_res, target_len);
    print_array("Output    :", res_output, target_len);
    printf("Result    : [%s]\n", (status_res == TINY_OK && compare_float_array(res_output, expected_res, target_len)) ? "PASS" : "FAIL");

    printf("========================================================\n");
}
