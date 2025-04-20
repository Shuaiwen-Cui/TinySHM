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

void tiny_matrix_test()
{
    std::cout << "============ [tiny_matrix_test] ============\n";

    // Test 1: Internal memory constructor
    tiny::Mat mat_internal(2, 3);
    print_matrix(mat_internal, "[Test 1] Internal Constructor");

    // Test 2: External buffer constructor (default stride)
    float buffer1[6] = {1, 2, 3, 4, 5, 6};
    tiny::Mat mat_external(buffer1, 2, 3);
    print_matrix(mat_external, "[Test 2] External Constructor (stride = cols)");

    // Test 3: External buffer with custom stride
    float buffer2[8] = {1, 2, 3, 0, 4, 5, 6, 0}; // 2 rows, stride = 4
    tiny::Mat mat_strided(buffer2, 2, 3, 4);
    print_matrix(mat_strided, "[Test 3] External Constructor (stride = 4)");

    // Test 4: Rect structure testing
    tiny::Mat::Rect roi(1, 1, 2, 2);
    std::cout << "[Test 4] Rect structure:\n";
    std::cout << "x: " << roi.x << ", y: " << roi.y
              << ", width: " << roi.width << ", height: " << roi.height << "\n";
    std::cout << "area: " << roi.areaRect() << "\n\n";

    roi.resizeRect(0, 0, 1, 3);
    std::cout << "Resized ROI:\n";
    std::cout << "x: " << roi.x << ", y: " << roi.y
              << ", width: " << roi.width << ", height: " << roi.height << "\n";
    std::cout << "area: " << roi.areaRect() << "\n";

    std::cout << "============ [test complete] ============\n";
}
