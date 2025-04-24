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
    std::cout << "\nTest 1: Default Constructor\n";
    tiny::Mat mat_default;
    mat_default.print_info();
    mat_default.print_matrix(false);

    std::cout << "\nTest 2: Constructor with Rows and Columns\n";
    tiny::Mat mat2(3, 4);  
    mat2.print_info();
    mat2.print_matrix(false);

    std::cout << "\nTest 3: Constructor with External Data\n";
    float external_data[6] = {1, 2, 3, 4, 5, 6};
    tiny::Mat mat3(external_data, 2, 3);  
    mat3.print_info();
    mat3.print_matrix(false);

    std::cout << "\nTest 4: Constructor with External Data and Stride\n";
    float external_data_stride[12] = {1, 2, 3, 0,  4, 5, 6, 0,   7, 8, 9, 0};
    tiny::Mat mat4(external_data_stride, 3, 3, 4); 
    mat4.print_info();
    mat4.print_matrix(true);
    std::cout << "============ [test complete] ============\n";
}