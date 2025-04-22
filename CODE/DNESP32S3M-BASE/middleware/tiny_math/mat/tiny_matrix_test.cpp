/**
 * @file tiny_matrix_test.cpp
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the source file for the test of the submodule matrix (advanced matrix operations) of the tiny_math middleware.
 * @version 1.0
 * @date 2025-04-17
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
#include "tiny_matrix_test.hpp" // TinyMatrix Test Header

#include <iostream>
#include <iomanip>

void tiny_matrix_test()
{
    std::cout << "============ [tiny_matrix_test] ============\n";

    // Test 1: Internal constructor
    tiny::Mat mat1(3, 4);
    // Fill mat1 with some values
    for (int i = 0; i < mat1.rows; ++i)
    {
        for (int j = 0; j < mat1.cols; ++j)
        {
            mat1.data[i * mat1.stride + j] = static_cast<float>(i * mat1.cols + j);
        }
    }
    mat1.PrintMatrix(false, "[Test 1] Internal 3x4 matrix (default initialized):");

    // Test 2: External buffer constructor
    float data2[6] = {1, 2, 3, 4, 5, 6};
    tiny::Mat mat2(data2, 2, 3);
    mat2.PrintMatrix(false, "[Test 2] External 2x3 matrix (no stride):");

    // Test 3: External buffer with stride
    float data3[8] = {1, 2, 3, 0, 4, 5, 6, 0};
    tiny::Mat mat3(data3, 2, 3, 4);
    mat3.PrintMatrix(true, "[Test 3] External 2x3 matrix (stride = 4):");

    // Test 4: Default constructor
    tiny::Mat mat4;
    mat4.PrintMatrix(false, "[Test 4] Default constructor (1x1):");

    // Test 5: Copy constructor
    tiny::Mat mat5(mat1);
    mat5.PrintMatrix(false, "[Test 5] Copy constructor from mat1:");

    // Test 6: getROI using coordinates
    tiny::Mat roi1 = mat1.getROI(1, 1, 2, 2);
    roi1.PrintMatrix(false, "[Test 6] ROI (1,1,2,2) from mat1:");

    // Test 7: getROI using Rect
    tiny::Mat::Rect r(0, 0, 2, 2);
    tiny::Mat roi2 = mat1.getROI(r);
    roi2.PrintMatrix(false, "[Test 7] ROI using Rect(0,0,2,2):");

    // Test 8: CopyHead
    tiny::Mat mat8;
    mat8.CopyHead(mat3);
    mat8.PrintMatrix(true, "[Test 8] CopyHead from mat3:");

    // Test 9: Copy content into offset
    tiny::Mat mat9(5, 5);
    mat9.Copy(mat1, 2, 1);
    mat9.PrintMatrix(false, "[Test 9] mat1 copied into mat9 at (2,1):");

    // Test 10: Get sub-matrix by rect
    tiny::Mat get1 = mat1.Get(0, 2, 1, 2);
    get1.PrintMatrix(false, "[Test 10] Get submatrix (0,2,1,2):");

    // Test 11: Get sub-matrix by Rect
    tiny::Mat::Rect rect2(1, 0, 2, 2);
    tiny::Mat get2 = mat1.Get(rect2);
    get2.PrintMatrix(false, "[Test 11] Get submatrix by Rect(1,0,2,2):");

    // Test 12: Assignment operator
    tiny::Mat mat12(3, 4);
    mat12 = mat1;
    mat12.PrintMatrix(false, "[Test 12] Assignment operator: mat12 = mat1:");

    // Test 13: operator+= with matrix
    mat12 += mat1;
    mat12.PrintMatrix(false, "[Test 13] operator+= with matrix:");

    // Test 14: operator+= with constant
    mat12 += 10.0f;
    mat12.PrintMatrix(false, "[Test 14] operator+= with constant (+=10.0):");

    // Test 15: operator-= with matrix
    mat12 -= mat1;
    mat12.PrintMatrix(false, "[Test 15] operator-= with matrix:");

    // Test 16: operator-= with constant
    mat12 -= 5.0f;
    mat12.PrintMatrix(false, "[Test 16] operator-= with constant (-=5.0):");

    // Test 17: Matrix multiplication (3x2 * 2x4 = 3x4)
    tiny::Mat A(3, 2);
    tiny::Mat B(2, 4);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            A(i, j) = static_cast<float>(i + j + 1);  // Fill A with some values
        }
    }
    for (int i = 0; i < B.rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            B(i, j) = static_cast<float>((i + 1) * (j + 1)); // Fill B with values
        }
    }
    tiny::Mat C(3, 4);
    for (int i = 0; i < C.rows; ++i) {
        for (int j = 0; j < C.cols; ++j) {
            C(i, j) = 0.0f;
            for (int k = 0; k < A.cols; ++k) {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    A.PrintMatrix(false, "[Test 17a] Matrix A (3x2):");
    B.PrintMatrix(false, "[Test 17b] Matrix B (2x4):");
    C.PrintMatrix(false, "[Test 17] Matrix multiplication result (A * B):");

    // Test 18: operator*= with constant
    mat12 *= 2.0f;
    mat12.PrintMatrix(false, "[Test 18] operator*= with constant (*=2.0):");

    // Test 19: operator/= with constant
    mat12 /= 2.0f;
    mat12.PrintMatrix(false, "[Test 19] operator/= with constant (/=2.0):");

    // Test 20: operator/= with matrix
    tiny::Mat mat20(mat1);
    mat20 /= mat1;
    mat20.PrintMatrix(false, "[Test 20] operator/= with matrix (mat20 /= mat1):");

    std::cout << "============ [test complete] ============\n";
}
