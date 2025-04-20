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

void print_matrix(const tiny::Mat &mat, const std::string &label)
{
    std::cout << label << "\n";
    std::cout << "rows: " << mat.rows << ", cols: " << mat.cols << "\n";
    std::cout << "stride: " << mat.stride << ", length: " << mat.length << "\n";
    std::cout << "ext_buff: " << mat.ext_buff << ", sub_matrix: " << mat.sub_matrix << "\n";
    std::cout << "data pointer: " << static_cast<void *>(mat.data) << "\n";
    std::cout << "data (row-major):\n";

    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {
            std::cout << std::setw(8) << mat.data[i * mat.stride + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void tiny_matrix_test() {
    std::cout << "============ [tiny_matrix_test] ============\n";

    // Test 1: Internal constructor
    tiny::Mat mat1(3, 4);
    std::cout << "[Test 1] Internal 3x4 matrix (default initialized):\n";
    mat1.PrintHead();

    // Test 2: External buffer constructor
    float data2[6] = {1, 2, 3, 4, 5, 6};
    tiny::Mat mat2(data2, 2, 3);
    std::cout << "[Test 2] External 2x3 matrix (no stride):\n";
    mat2.PrintHead();

    // Test 3: External buffer with stride
    float data3[8] = {1, 2, 3, 0, 4, 5, 6, 0};
    tiny::Mat mat3(data3, 2, 3, 4);
    std::cout << "[Test 3] External 2x3 matrix (stride = 4):\n";
    mat3.PrintHead();

    // Test 4: Default constructor
    tiny::Mat mat4;
    std::cout << "[Test 4] Default constructor (1x1):\n";
    mat4.PrintHead();

    // Test 5: Copy constructor
    tiny::Mat mat5(mat1);
    std::cout << "[Test 5] Copy constructor from mat1:\n";
    mat5.PrintHead();

    // Test 6: getROI using coordinates
    tiny::Mat roi1 = mat1.getROI(1, 1, 2, 2);
    std::cout << "[Test 6] ROI (1,1,2,2) from mat1:\n";
    roi1.PrintHead();

    // Test 7: getROI using Rect
    tiny::Mat::Rect r(0, 0, 2, 2);
    tiny::Mat roi2 = mat1.getROI(r);
    std::cout << "[Test 7] ROI using Rect(0,0,2,2):\n";
    roi2.PrintHead();

    // Test 8: CopyHead
    tiny::Mat mat8;
    mat8.CopyHead(mat3);
    std::cout << "[Test 8] CopyHead from mat3:\n";
    mat8.PrintHead();

    // Test 9: Copy content into offset
    tiny::Mat mat9(5, 5);
    mat9.Copy(mat1, 2, 1);
    std::cout << "[Test 9] mat1 copied into mat9 at (2,1):\n";
    mat9.PrintHead();

    std::cout << "============ [test complete] ============\n";
}
