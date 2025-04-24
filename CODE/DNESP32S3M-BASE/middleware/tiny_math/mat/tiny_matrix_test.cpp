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

// Group 1: constructor & destructor
void test_constructor_destructor()
{
    std::cout << "\n--- Test: Constructor & Destructor ---\n";

    // test1: default constructor
    std::cout << "[Test1: Default Constructor]\n";
    tiny::Mat mat1;
    mat1.print_info();
    mat1.print_matrix(true);

    // test2: constructor with rows and cols, using internal allocation
    std::cout << "[Test2: Constructor with Rows and Cols]\n";
    tiny::Mat mat2(3, 4);
    mat2.print_info();
    mat2.print_matrix(true);

    // test3: constructor with rows and cols, specifying stride, using internal allocation
    std::cout << "[Test3: Constructor with Rows, Cols and Stride]\n";
    tiny::Mat mat3(3, 4, 5);
    mat3.print_info();    
    mat3.print_matrix(true);

    // test4: constructor with external data
    std::cout << "[Test4: Constructor with External Data]\n";
    float data[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    tiny::Mat mat4(data, 3, 4);
    mat4.print_info();
    mat4.print_matrix(true);

    // test5: constructor with external data and stride
    std::cout << "[Test5: Constructor with External Data and Stride]\n";
    float data_stride[15] = { 0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0 };
    tiny::Mat mat5(data_stride, 3, 4, 5);
    mat5.print_info();
    mat5.print_matrix(true);

    // test6: copy constructor
    std::cout << "[Test6: Copy Constructor]\n";
    tiny::Mat mat6(mat5);
    mat6.print_info();
    mat6.print_matrix(true);
}

// Group 2: element access
void test_element_access()
{
    std::cout << "\n--- Test: Element Access ---\n";
    tiny::Mat mat(2, 3);

    // Test 1: non-const access
    std::cout << "[Test1: Non-const Access]\n";
    mat(0, 0) = 1.1f;
    mat(0, 1) = 2.2f;
    mat(0, 2) = 3.3f;
    mat(1, 0) = 4.4f;
    mat(1, 1) = 5.5f;
    mat(1, 2) = 6.6f;
    mat.print_info();
    mat.print_matrix(true);
    
    // Test 2: const access
    std::cout << "[Test2: Const Access]\n";
    const tiny::Mat const_mat = mat;
    std::cout << "const_mat(0, 0): " << const_mat(0, 0) << "\n";

}

// Group 3: ROI operations
void test_roi_operations()
{
    std::cout << "\n--- Test: ROI Operations ---\n";
    
    // Material Matrices
    tiny::Mat matA(2,3);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            matA(i, j) = i * 3 + j + 1;
            matA(i, j) = matA(i, j)/10;
        }
    }

    float data[15] = { 0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0 };
    tiny::Mat matB(data, 3, 4, 5);

    tiny::Mat matC;

    std::cout << "[Material Matrices]\n";
    std::cout << "matA:\n";
    matA.print_info();
    matA.print_matrix(true);
    std::cout << "matB:\n";
    matB.print_info();
    matB.print_matrix(true);
    std::cout << "matC:\n";
    matC.print_info();
    matC.print_matrix(true);

    // Test 1: Copy ROI
    std::cout << "[Test1: Copy ROI - over range case]\n";
    matB.copy_paste(matA, 1, 2);
    std::cout << "matB after copy_paste matA at (1, 2):\n";
    matB.print_matrix(true);

    std::cout << "[Test1: Copy ROI - suitable range case]\n";
    matB.copy_paste(matA, 1, 1);
    std::cout << "matB after copy_paste matA at (1, 1):\n";
    matB.print_matrix(true);

    // Test 2: Copy Head
    std::cout << "[Test2: Copy Head]\n";
    matC.copy_head(matB);
    std::cout << "matC after copy_head matB:\n";
    matC.print_info();
    matC.print_matrix(true);

    std::cout << "[Test2: Copy Head - memory sharing check]\n"; // matB and matC share the same data pointer
    matB(0, 0) = 99.99f;
    std::cout << "matB(0, 0) = 99.99f\n";
    std::cout << "matC:\n";
    matC.print_info();
    matC.print_matrix(true);

    // Test 3: Get ROI - low level function
    std::cout << "[Test3: Get ROI - low level function]\n";
    std::cout << "get ROI with overrange dimensions - rows:\n";
    tiny::Mat roi1 = matB.get_roi(1, 1, 3, 2, 5);
    roi1.print_info();
    roi1.print_matrix(true);
    std::cout << "get ROI with overrange dimensions - cols:\n";
    tiny::Mat roi2 = matB.get_roi(1, 1, 2, 4, 5);
    roi2.print_info();
    roi2.print_matrix(true);
    std::cout << "get ROI with suitable dimensions:\n";
    tiny::Mat roi3 = matB.get_roi(1, 1, 2, 2, 3);
    roi3.print_info();
    roi3.print_matrix(true);

    // Test 4: Get ROI - without stride
    std::cout << "[Test4: Get ROI - without stride]\n";
    tiny::Mat roi4 = matB.get_roi(1, 1, 2, 2);
    roi4.print_info();
    roi4.print_matrix(true);

    // Test 5: Get ROI - using ROI structure
    std::cout << "[Test5: Get ROI - using ROI structure]\n";
    tiny::Mat::ROI roi_struct(1, 1, 2, 2);
    tiny::Mat roi5 = matB.get_roi(roi_struct);
    roi5.print_info();
    roi5.print_matrix(true);

}

// Group 4: data manipulation
void test_data_manipulation()
{
    std::cout << "\n--- Test: Data Manipulation ---\n";
    tiny::Mat mat1(3, 3);
    tiny::Mat mat2(2, 2);

    // 填充mat2
    mat2(0,0) = 9.9f;
    mat2(1,1) = 8.8f;

    // Copy-Paste 测试
    mat1.copy_paste(mat2, 1, 1);
    mat1.print_matrix(true);

    // Swap Rows 测试
    mat1.swap_rows(0, 2);
    std::cout << "[After Swapping Rows 0 and 2]\n";
    mat1.print_matrix(true);

    // Clear 测试
    mat1.clear();
    std::cout << "[After Clear]\n";
    mat1.print_matrix(true);
}


void tiny_matrix_test()
{
    std::cout << "============ [tiny_matrix_test start] ============\n";

    // Group 1: constructor & destructor
    // test_constructor_destructor();

    // Group 2: element access
    // test_element_access();

    // Group 3: ROI operations
    test_roi_operations();

    // Group 4: data manipulation
    // test_data_manipulation();

    std::cout << "============ [tiny_matrix_test end] ============\n";
}