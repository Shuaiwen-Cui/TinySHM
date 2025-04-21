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

void tiny_matrix_test() {
    std::cout << "============ [tiny_matrix_test] ============\n";

    // Test 1: Internal constructor
    tiny::Mat mat1(3, 4);
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

    std::cout << "============ [test complete] ============\n";
}