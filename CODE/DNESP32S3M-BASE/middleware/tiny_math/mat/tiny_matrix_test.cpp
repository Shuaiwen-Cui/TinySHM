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
    float data[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    tiny::Mat mat4(data, 3, 4);
    mat4.print_info();
    mat4.print_matrix(true);

    // test5: constructor with external data and stride
    std::cout << "[Test5: Constructor with External Data and Stride]\n";
    float data_stride[15] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0};
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

// Group 3: data manipulation
void test_roi_operations()
{
    std::cout << "\n--- Test: Data Manipulation ---\n";

    // Material Matrices
    tiny::Mat matA(2, 3);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            matA(i, j) = i * 3 + j + 1;
            matA(i, j) = matA(i, j) / 10;
        }
    }

    float data[15] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0};
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
    std::cout << "nothing changed.\n";

    std::cout << "[Test1: Copy ROI - suitable range case]\n";
    matB.copy_paste(matA, 1, 1);
    std::cout << "matB after copy_paste matA at (1, 1):\n";
    matB.print_info();
    matB.print_matrix(true);
    std::cout << "successfully copied.\n";

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

    // Test 3: Get a View of ROI - low level function
    std::cout << "[Test3: Get a View of ROI - low level function]\n";
    std::cout << "get a view of ROI with overrange dimensions - rows:\n";
    tiny::Mat roi1 = matB.view_roi(1, 1, 3, 2); // note here, C++ will use the copy constructor, which will copy according to the case (submatrix - shallow copy | normal - deep copy)
    std::cout << "get a view of ROI with overrange dimensions - cols:\n";
    tiny::Mat roi2 = matB.view_roi(1, 1, 2, 4); // note here, C++ will use the copy constructor, which will copy according to the case (submatrix - shallow copy | normal - deep copy)
    std::cout << "get a view of ROI with suitable dimensions:\n";
    tiny::Mat roi3 = matB.view_roi(1, 1, 2, 2); // note here, C++ will use the copy constructor, which will copy according to the case (submatrix - shallow copy | normal - deep copy)
    std::cout << "roi3:\n";
    roi3.print_info();
    roi3.print_matrix(true);

    // Test 4: Get a View of ROI - using ROI structure
    std::cout << "[Test4: Get a View of ROI - using ROI structure]\n";
    tiny::Mat::ROI roi_struct(1, 1, 2, 2);
    tiny::Mat roi4 = matB.view_roi(roi_struct);
    roi4.print_info();
    roi4.print_matrix(true);

    // Test 5: Copy ROI - low level function
    std::cout << "[Test5: Copy ROI - low level function]\n";
    tiny::Mat mat_deep_copy = matB.copy_roi(1, 1, 2, 2);
    mat_deep_copy.print_info();
    mat_deep_copy.print_matrix(true);

    // Test 6: Copy ROI - using ROI structure
    std::cout << "[Test6: Copy ROI - using ROI structure]\n";
    TinyTimeMark_t tic1 = tiny_get_running_time();
    tiny::Mat::ROI roi_struct2(1, 1, 2, 2);
    tiny::Mat mat_deep_copy2 = matB.copy_roi(roi_struct2);
    TinyTimeMark_t toc1 = tiny_get_running_time();
    TinyTimeMark_t copy_roi_time = toc1 - tic1;
    std::cout << "time for copy_roi using ROI structure: " << copy_roi_time << " ms\n";
    mat_deep_copy2.print_info();
    mat_deep_copy2.print_matrix(true);

    // Test 7: Block
    std::cout << "[Test7: Block]\n";
    TinyTimeMark_t tic2 = tiny_get_running_time();
    tiny::Mat mat_block = matB.block(1, 1, 2, 2);
    TinyTimeMark_t toc2 = tiny_get_running_time();
    TinyTimeMark_t block_roi_time = toc2 - tic2;
    std::cout << "time for block: " << block_roi_time << " ms\n";
    mat_block.print_info();
    mat_block.print_matrix(true);

    // swap rows
    std::cout << "[Test7: Swap Rows]\n";
    std::cout << "matB before swap:\n";
    matB.print_info();
    matB.print_matrix(true);
    std::cout << "matB after swap:\n";
    matB.swap_rows(0, 2);
    matB.print_info();
    matB.print_matrix(true);

    // clear function
    std::cout << "[Test8: Clear]\n";
    std::cout << "matB before clear:\n";
    matB.print_info();
    matB.print_matrix(true);
    std::cout << "matB after clear:\n";
    matB.clear();
    matB.print_info();
    matB.print_matrix(true);
}

// Group 4: arithmetic operators
// void test_arithmetic_operators()
// {
//     std::cout << "\n[Arithmetic Operators Test Start]\n";

//     /*** Test1: Assignment Operator ***/
//     std::cout << "\n[Test 1.1] Assignment (Same Dimensions)\n";
//     tiny::Mat assignMat_1_1_dst(2, 3);
//     tiny::Mat assignMat_1_1_src(2, 3);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 3; ++j)
//             assignMat_1_1_src(i, j) = static_cast<float>(i * 3 + j + 1);
//     assignMat_1_1_dst = assignMat_1_1_src;
//     assignMat_1_1_dst.print_matrix(true);

//     std::cout << "\n[Test 1.2] Assignment (Different Dimensions)\n";
//     tiny::Mat assignMat_1_2_dst(4, 2);
//     assignMat_1_2_dst = assignMat_1_1_src;
//     assignMat_1_2_dst.print_matrix(true);

//     std::cout << "\n[Test 1.3] Assignment to Sub-Matrix (Expect Error)\n";
//     float data_1_3[15] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0};
//     tiny::Mat baseMat_1_3(data_1_3, 3, 4, 5);
//     tiny::Mat subView_1_3 = baseMat_1_3.view_roi(1, 1, 2, 2);
//     subView_1_3 = assignMat_1_1_src;
//     subView_1_3.print_matrix(true);

//     std::cout << "\n[Test 1.4] Self-Assignment\n";
//     assignMat_1_1_src = assignMat_1_1_src;
//     assignMat_1_1_src.print_matrix(true);

//     /*** Test2: Matrix Addition ***/
//     std::cout << "\n[Test 2.1] Matrix Addition (Same Dimensions)\n";
//     tiny::Mat addMat_2_1_A(2, 3);
//     tiny::Mat addMat_2_1_B(2, 3);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 3; ++j)
//         {
//             addMat_2_1_A(i, j) = static_cast<float>(i * 3 + j + 1);
//             addMat_2_1_B(i, j) = 1.0f;
//         }
//     addMat_2_1_A += addMat_2_1_B;
//     addMat_2_1_A.print_matrix(true);

//     std::cout << "\n[Test 2.2] Sub-Matrix Addition\n";
//     float data_2_2[20] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0, 12, 13, 14, 15, 0};
//     tiny::Mat baseMat_2_2(data_2_2, 4, 4, 5);
//     tiny::Mat subView_2_2_A = baseMat_2_2.view_roi(1, 1, 2, 2);
//     tiny::Mat subView_2_2_B = baseMat_2_2.view_roi(1, 1, 2, 2);
//     subView_2_2_A += subView_2_2_B;
//     subView_2_2_A.print_matrix(true);

//     std::cout << "\n[Test 2.3] Full Matrix + Sub-Matrix Addition\n";
//     tiny::Mat addMat_2_3(2, 2);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 2; ++j)
//             addMat_2_3(i, j) = 2.0f;
//     addMat_2_3 += subView_2_2_B;
//     addMat_2_3.print_matrix(true);

//     std::cout << "\n[Test 2.4] Addition Dimension Mismatch (Expect Error)\n";
//     tiny::Mat addMat_2_4_wrongDim(3, 3);
//     addMat_2_3 += addMat_2_4_wrongDim;

//     /*** Test3: Constant Addition ***/
//     std::cout << "\n[Test 3.1] Full Matrix + Constant\n";
//     tiny::Mat addConstMat_3_1(2, 3);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 3; ++j)
//             addConstMat_3_1(i, j) = static_cast<float>(i * 3 + j);
//     addConstMat_3_1 += 5.0f;
//     addConstMat_3_1.print_matrix(true);

//     std::cout << "\n[Test 3.2] Sub-Matrix + Constant\n";
//     float data_3_2[20] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0, 12, 13, 14, 15, 0};
//     tiny::Mat baseMat_3_2(data_3_2, 4, 4, 5);
//     tiny::Mat subView_3_2 = baseMat_3_2.view_roi(1, 1, 2, 2);
//     subView_3_2 += 3.0f;
//     subView_3_2.print_matrix(true);

//     std::cout << "\n[Test 3.3] Add Zero to Matrix\n";
//     tiny::Mat addConstMat_3_3(2, 2);
//     addConstMat_3_3(0, 0) = 1;
//     addConstMat_3_3(0, 1) = 2;
//     addConstMat_3_3(1, 0) = 3;
//     addConstMat_3_3(1, 1) = 4;
//     addConstMat_3_3 += 0.0f;
//     addConstMat_3_3.print_matrix(true);

//     std::cout << "\n[Test 3.4] Add Negative Constant\n";
//     tiny::Mat addConstMat_3_4(2, 2);
//     addConstMat_3_4(0, 0) = 10;
//     addConstMat_3_4(0, 1) = 20;
//     addConstMat_3_4(1, 0) = 30;
//     addConstMat_3_4(1, 1) = 40;
//     addConstMat_3_4 += -15.0f;
//     addConstMat_3_4.print_matrix(true);

//     /*** Test4: Matrix Subtraction ***/
//     std::cout << "\n[Test 4.1] Matrix Subtraction\n";
//     tiny::Mat subMat_4_1_A(2, 2);
//     tiny::Mat subMat_4_1_B(2, 2);
//     subMat_4_1_A(0, 0) = 5;
//     subMat_4_1_A(0, 1) = 7;
//     subMat_4_1_A(1, 0) = 9;
//     subMat_4_1_A(1, 1) = 11;
//     subMat_4_1_B(0, 0) = 1;
//     subMat_4_1_B(0, 1) = 2;
//     subMat_4_1_B(1, 0) = 3;
//     subMat_4_1_B(1, 1) = 4;
//     subMat_4_1_A -= subMat_4_1_B;
//     subMat_4_1_A.print_matrix(true);

//     std::cout << "\n[Test 4.2] Subtraction Dimension Mismatch (Expect Error)\n";
//     tiny::Mat subMat_4_2_wrong(3, 3);
//     subMat_4_1_A -= subMat_4_2_wrong;

//     /*** Test5: Constant Subtraction ***/
//     std::cout << "\n[Test 5.1] Full Matrix - Constant\n";
//     tiny::Mat subConstMat_5_1(2, 3);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 3; ++j)
//             subConstMat_5_1(i, j) = static_cast<float>(i * 3 + j + 1);
//     subConstMat_5_1 -= 2.0f;
//     subConstMat_5_1.print_matrix(true);

//     std::cout << "\n[Test 5.2] Sub-Matrix - Constant\n";
//     float data_5_2[15] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0};
//     tiny::Mat baseMat_5_2(data_5_2, 3, 4, 5);
//     tiny::Mat subView_5_2 = baseMat_5_2.view_roi(1, 1, 2, 2);
//     subView_5_2 -= 1.5f;
//     subView_5_2.print_matrix(true);

//     /*** Test6: Matrix Element-wise Division ***/
//     std::cout << "\n[Test6: Operator /= (Matrix)]\n";

//     // Test 6.1: Standard element-wise division
//     std::cout << "\n[Test 6.1] Element-wise division (no zero, same dimensions)\n";
//     tiny::Mat divMat_6_1_A(2, 2);
//     tiny::Mat divMat_6_1_B(2, 2);

//     // Initialize matrices
//     divMat_6_1_A(0, 0) = 10;
//     divMat_6_1_A(0, 1) = 20;
//     divMat_6_1_A(1, 0) = 30;
//     divMat_6_1_A(1, 1) = 40;

//     divMat_6_1_B(0, 0) = 2;
//     divMat_6_1_B(0, 1) = 4;
//     divMat_6_1_B(1, 0) = 5;
//     divMat_6_1_B(1, 1) = 8;

//     divMat_6_1_A /= divMat_6_1_B;
//     divMat_6_1_A.print_matrix(true);

//     // Test 6.2: Dimension mismatch
//     std::cout << "\n[Test 6.2] Division with dimension mismatch (expect error)\n";
//     tiny::Mat divMat_6_2_wrong(3, 3);
//     divMat_6_1_A /= divMat_6_2_wrong;

//     // Test 6.3: Division by zero detection
//     std::cout << "\n[Test 6.3] Division by matrix containing zero (expect error)\n";
//     tiny::Mat divMat_6_3_A(2, 2);
//     tiny::Mat divMat_6_3_B(2, 2);

//     divMat_6_3_A(0, 0) = 5;
//     divMat_6_3_A(0, 1) = 10;
//     divMat_6_3_A(1, 0) = 15;
//     divMat_6_3_A(1, 1) = 20;

//     divMat_6_3_B(0, 0) = 1;
//     divMat_6_3_B(0, 1) = 0; // Contains zero
//     divMat_6_3_B(1, 0) = 3;
//     divMat_6_3_B(1, 1) = 4;

//     divMat_6_3_A /= divMat_6_3_B;
//     divMat_6_3_A.print_matrix(true); // Should remain unchanged

//     /*** Test7: Matrix Division by Constant ***/
//     std::cout << "\n[Test7: Operator /= (Constant)]\n";

//     // Test 7.1: Standard division by positive constant
//     std::cout << "\n[Test 7.1] Divide full matrix by positive constant\n";
//     tiny::Mat divConstMat_7_1(2, 3);
//     for (int i = 0; i < 2; ++i)
//         for (int j = 0; j < 3; ++j)
//             divConstMat_7_1(i, j) = static_cast<float>((i * 3 + j + 2)); // Avoid zero

//     divConstMat_7_1 /= 2.0f;
//     divConstMat_7_1.print_matrix(true);

//     // Test 7.2: Division by negative constant
//     std::cout << "\n[Test 7.2] Divide matrix by negative constant\n";
//     tiny::Mat divConstMat_7_2(2, 2);
//     divConstMat_7_2(0, 0) = 6;
//     divConstMat_7_2(0, 1) = 12;
//     divConstMat_7_2(1, 0) = 18;
//     divConstMat_7_2(1, 1) = 24;

//     divConstMat_7_2 /= -3.0f;
//     divConstMat_7_2.print_matrix(true);

//     // Test 7.3: Division by zero (expect error)
//     std::cout << "\n[Test 7.3] Division by zero constant (expect error)\n";
//     tiny::Mat divConstMat_7_3(2, 2);
//     divConstMat_7_3(0, 0) = 1;
//     divConstMat_7_3(0, 1) = 2;
//     divConstMat_7_3(1, 0) = 3;
//     divConstMat_7_3(1, 1) = 4;

//     divConstMat_7_3 /= 0.0f;
//     divConstMat_7_3.print_matrix(true); // Should remain unchanged

//     /*** Test8: Matrix Element-wise Exponentiation ***/
//     std::cout << "\n[Test8: Operator ^ (Element-wise Exponentiation)]\n";

//     // Test 8.1: Positive exponent (Square)
//     std::cout << "\n[Test 8.1] Raise each element to power of 2\n";
//     tiny::Mat expMat_8_1(2, 2);
//     expMat_8_1(0, 0) = 2;
//     expMat_8_1(0, 1) = 3;
//     expMat_8_1(1, 0) = 4;
//     expMat_8_1(1, 1) = 5;

//     tiny::Mat result_8_1 = expMat_8_1 ^ 2;
//     result_8_1.print_matrix(true);

//     // Test 8.2: Exponent = 0
//     std::cout << "\n[Test 8.2] Raise each element to power of 0\n";
//     tiny::Mat expMat_8_2(2, 2);
//     expMat_8_2(0, 0) = 7;
//     expMat_8_2(0, 1) = -3;
//     expMat_8_2(1, 0) = 0.5f;
//     expMat_8_2(1, 1) = 10;

//     tiny::Mat result_8_2 = expMat_8_2 ^ 0;
//     result_8_2.print_matrix(true); // Expected: all 1

//     // Test 8.3: Exponent = 1
//     std::cout << "\n[Test 8.3] Raise each element to power of 1\n";
//     tiny::Mat expMat_8_3(2, 2);
//     expMat_8_3(0, 0) = 9;
//     expMat_8_3(0, 1) = 8;
//     expMat_8_3(1, 0) = 7;
//     expMat_8_3(1, 1) = 6;

//     tiny::Mat result_8_3 = expMat_8_3 ^ 1;
//     result_8_3.print_matrix(true); // Expected: same as original

//     // Test 8.4: Negative exponent (if supported)
//     std::cout << "\n[Test 8.4] Raise each element to power of -1 (Expect reciprocal if supported)\n";
//     tiny::Mat expMat_8_4(2, 2);
//     expMat_8_4(0, 0) = 1;
//     expMat_8_4(0, 1) = 2;
//     expMat_8_4(1, 0) = 4;
//     expMat_8_4(1, 1) = 5;

//     tiny::Mat result_8_4 = expMat_8_4 ^ -1;
//     result_8_4.print_matrix(true); // Depends on expHelper behavior

//     // Test 8.5: Matrix contains zero, exponent = 3
//     std::cout << "\n[Test 8.5] Raise matrix containing zero to power of 3\n";
//     tiny::Mat expMat_8_5(2, 2);
//     expMat_8_5(0, 0) = 0;
//     expMat_8_5(0, 1) = 2;
//     expMat_8_5(1, 0) = -1;
//     expMat_8_5(1, 1) = 3;

//     tiny::Mat result_8_5 = expMat_8_5 ^ 3;
//     result_8_5.print_matrix(true); // Expected: 0^3=0, others normal

//     std::cout << "\n[Arithmetic Operators Test End]\n";
// }

// Test 4.1
void test_assignment_operator()
{
    std::cout << "\n[Assignment Operator Tests]\n";

    std::cout << "\n[Test 1.1] Assignment (Same Dimensions)\n";
    tiny::Mat dst(2, 3), src(2, 3);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            src(i, j) = static_cast<float>(i * 3 + j + 1);
    dst = src;
    dst.print_matrix(true);

    std::cout << "\n[Test 1.2] Assignment (Different Dimensions)\n";
    tiny::Mat dst2(4, 2);
    dst2 = src;
    dst2.print_matrix(true);

    std::cout << "\n[Test 1.3] Assignment to Sub-Matrix (Expect Error)\n";
    float data[15] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0, 8, 9, 10, 11, 0};
    tiny::Mat base(data, 3, 4, 5);
    tiny::Mat subView = base.view_roi(1, 1, 2, 2);
    subView = src;
    subView.print_matrix(true);

    std::cout << "\n[Test 1.4] Self-Assignment\n";
    src = src;
    src.print_matrix(true);
}

// Test 4.2
void test_matrix_addition()
{
    std::cout << "\n[Matrix Addition Tests]\n";

    std::cout << "\n[Test 2.1] Matrix Addition (Same Dimensions)\n";
    tiny::Mat A(2, 3), B(2, 3);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
        {
            A(i, j) = static_cast<float>(i * 3 + j + 1);
            B(i, j) = 1.0f;
        }
    A += B;
    A.print_matrix(true);

    std::cout << "\n[Test 2.2] Sub-Matrix Addition\n";
    float data[20] = {0,1,2,3,0,4,5,6,7,0,8,9,10,11,0,12,13,14,15,0};
    tiny::Mat base(data, 4, 4, 5);
    tiny::Mat subA = base.view_roi(1,1,2,2);
    tiny::Mat subB = base.view_roi(1,1,2,2);
    subA += subB;
    subA.print_matrix(true);

    std::cout << "\n[Test 2.3] Full Matrix + Sub-Matrix Addition\n";
    tiny::Mat full(2,2);
    for(int i=0;i<2;++i) for(int j=0;j<2;++j) full(i,j)=2.0f;
    full += subB;
    full.print_matrix(true);

    std::cout << "\n[Test 2.4] Addition Dimension Mismatch (Expect Error)\n";
    tiny::Mat wrongDim(3,3);
    full += wrongDim;
}

// Test 4.3
void test_constant_addition()
{
    std::cout << "\n[Constant Addition Tests]\n";

    std::cout << "\n[Test 3.1] Full Matrix + Constant\n";
    tiny::Mat mat1(2,3);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            mat1(i,j) = static_cast<float>(i*3 + j);
    mat1 += 5.0f;
    mat1.print_matrix(true);

    std::cout << "\n[Test 3.2] Sub-Matrix + Constant\n";
    float data[20] = {0,1,2,3,0,4,5,6,7,0,8,9,10,11,0,12,13,14,15,0};
    tiny::Mat base(data,4,4,5);
    tiny::Mat sub = base.view_roi(1,1,2,2);
    sub += 3.0f;
    sub.print_matrix(true);

    std::cout << "\n[Test 3.3] Add Zero\n";
    tiny::Mat mat2(2,2);
    mat2(0,0)=1; mat2(0,1)=2; mat2(1,0)=3; mat2(1,1)=4;
    mat2 += 0.0f;
    mat2.print_matrix(true);

    std::cout << "\n[Test 3.4] Add Negative Constant\n";
    tiny::Mat mat3(2,2);
    mat3(0,0)=10; mat3(0,1)=20; mat3(1,0)=30; mat3(1,1)=40;
    mat3 += -15.0f;
    mat3.print_matrix(true);
}

// Test 4.4
void test_matrix_subtraction()
{
    std::cout << "\n[Matrix Subtraction Tests]\n";

    std::cout << "\n[Test 4.1] Matrix Subtraction\n";
    tiny::Mat A(2,2), B(2,2);
    A(0,0)=5; A(0,1)=7; A(1,0)=9; A(1,1)=11;
    B(0,0)=1; B(0,1)=2; B(1,0)=3; B(1,1)=4;
    A -= B;
    A.print_matrix(true);

    std::cout << "\n[Test 4.2] Subtraction Dimension Mismatch\n";
    tiny::Mat wrong(3,3);
    A -= wrong;
}

// Test 4.5
void test_constant_subtraction()
{
    std::cout << "\n[Constant Subtraction Tests]\n";

    std::cout << "\n[Test 5.1] Full Matrix - Constant\n";
    tiny::Mat mat(2,3);
    for (int i=0;i<2;++i) for(int j=0;j<3;++j) mat(i,j) = i*3+j+1;
    mat -= 2.0f;
    mat.print_matrix(true);

    std::cout << "\n[Test 5.2] Sub-Matrix - Constant\n";
    float data[15] = {0,1,2,3,0,4,5,6,7,0,8,9,10,11,0};
    tiny::Mat base(data,3,4,5);
    tiny::Mat sub = base.view_roi(1,1,2,2);
    sub -= 1.5f;
    sub.print_matrix(true);
}

// Test 4.6
void test_matrix_division()
{
    std::cout << "\n[Matrix Element-wise Division Tests]\n";

    std::cout << "\n[Test 6.1] Element-wise division (same dimensions, no zero)\n";
    tiny::Mat A(2, 2), B(2, 2);
    A(0,0) = 10; A(0,1) = 20; A(1,0) = 30; A(1,1) = 40;
    B(0,0) = 2;  B(0,1) = 4;  B(1,0) = 5;  B(1,1) = 8;
    A /= B;
    A.print_matrix(true);

    std::cout << "\n[Test 6.2] Dimension mismatch (expect error)\n";
    tiny::Mat wrongDim(3, 3);
    A /= wrongDim;

    std::cout << "\n[Test 6.3] Division by matrix containing zero (expect error)\n";
    tiny::Mat C(2, 2), D(2, 2);
    C(0,0)=5; C(0,1)=10; C(1,0)=15; C(1,1)=20;
    D(0,0)=1; D(0,1)=0;  D(1,0)=3;  D(1,1)=4;  // Contains zero
    C /= D;
    C.print_matrix(true);  // Should remain unchanged
}

// Test 4.7
void test_constant_division()
{
    std::cout << "\n[Matrix Division by Constant Tests]\n";

    std::cout << "\n[Test 7.1] Divide full matrix by positive constant\n";
    tiny::Mat mat1(2, 3);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            mat1(i, j) = static_cast<float>(i * 3 + j + 2);  // Avoid zero
    mat1 /= 2.0f;
    mat1.print_matrix(true);

    std::cout << "\n[Test 7.2] Divide matrix by negative constant\n";
    tiny::Mat mat2(2, 2);
    mat2(0,0)=6; mat2(0,1)=12; mat2(1,0)=18; mat2(1,1)=24;
    mat2 /= -3.0f;
    mat2.print_matrix(true);

    std::cout << "\n[Test 7.3] Division by zero constant (expect error)\n";
    tiny::Mat mat3(2, 2);
    mat3(0,0)=1; mat3(0,1)=2; mat3(1,0)=3; mat3(1,1)=4;
    mat3 /= 0.0f;
    mat3.print_matrix(true);  // Should remain unchanged
}

// Test 4.8
void test_matrix_exponentiation()
{
    std::cout << "\n[Matrix Exponentiation Tests]\n";

    std::cout << "\n[Test 8.1] Raise each element to power of 2\n";
    tiny::Mat mat1(2, 2);
    mat1(0,0)=2; mat1(0,1)=3; mat1(1,0)=4; mat1(1,1)=5;
    tiny::Mat result1 = mat1 ^ 2;
    result1.print_matrix(true);

    std::cout << "\n[Test 8.2] Raise each element to power of 0\n";
    tiny::Mat mat2(2, 2);
    mat2(0,0)=7; mat2(0,1)=-3; mat2(1,0)=0.5f; mat2(1,1)=10;
    tiny::Mat result2 = mat2 ^ 0;
    result2.print_matrix(true);  // Expect all 1

    std::cout << "\n[Test 8.3] Raise each element to power of 1\n";
    tiny::Mat mat3(2, 2);
    mat3(0,0)=9; mat3(0,1)=8; mat3(1,0)=7; mat3(1,1)=6;
    tiny::Mat result3 = mat3 ^ 1;
    result3.print_matrix(true);  // Expect same as original

    std::cout << "\n[Test 8.4] Raise each element to power of -1 (expect error or warning)\n";
    tiny::Mat mat4(2, 2);
    mat4(0,0)=1; mat4(0,1)=2; mat4(1,0)=4; mat4(1,1)=5;
    tiny::Mat result4 = mat4 ^ -1;
    result4.print_matrix(true);

    std::cout << "\n[Test 8.5] Raise matrix containing zero to power of 3\n";
    tiny::Mat mat5(2, 2);
    mat5(0,0)=0; mat5(0,1)=2; mat5(1,0)=-1; mat5(1,1)=3;
    tiny::Mat result5 = mat5 ^ 3;
    result5.print_matrix(true);
}

// Group 5: Linear Algebra
// Test 5.1 Transpose
void test_matrix_transpose()
{
    std::cout << "\n[Matrix Transpose Test]\n";

    // Test 1: Basic 2x3 matrix transpose
    std::cout << "\n[Test 1] Transpose of 2x3 Matrix\n";
    tiny::Mat mat1(2, 3);
    int val = 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            mat1(i, j) = val++;

    std::cout << "Original 2x3 Matrix:\n";
    mat1.print_matrix(true);

    tiny::Mat transposed1 = mat1.transpose();
    std::cout << "Transposed 3x2 Matrix:\n";
    transposed1.print_matrix(true);

    // Test 2: Square matrix transpose (3x3)
    std::cout << "\n[Test 2] Transpose of 3x3 Square Matrix\n";
    tiny::Mat mat2(3, 3);
    val = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat2(i, j) = val++;

    std::cout << "Original 3x3 Matrix:\n";
    mat2.print_matrix(true);

    tiny::Mat transposed2 = mat2.transpose();
    std::cout << "Transposed 3x3 Matrix:\n";
    transposed2.print_matrix(true);

    // Test 3: Matrix with padding (4x2, stride=3)
    std::cout << "\n[Test 3] Transpose of Matrix with Padding\n";
    float data[12] = {1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8, 0};  // stride=3, 4 rows
    tiny::Mat mat3(data, 4, 2, 3);
    std::cout << "Original 4x2 Matrix (with padding):\n";
    mat3.print_matrix(true);

    tiny::Mat transposed3 = mat3.transpose();
    std::cout << "Transposed 2x4 Matrix:\n";
    transposed3.print_matrix(true);

    // Test 4: Transpose of empty matrix
    std::cout << "\n[Test 4] Transpose of Empty Matrix\n";
    tiny::Mat mat4;
    mat4.print_matrix(true);

    tiny::Mat transposed4 = mat4.transpose();
    transposed4.print_matrix(true);
}

// Test 5.2 cofactor calculation - prepare the matrix for cofactor calculation
void test_matrix_cofactor()
{
    std::cout << "\n[Matrix Cofactor Test]\n";

    // Test 1: 3x3 Matrix - Standard Case
    std::cout << "\n[Test 1] Cofactor of 3x3 Matrix (remove row 1, col 1)\n";
    tiny::Mat mat1(3, 3);
    int val = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat1(i, j) = val++;

    std::cout << "Original 3x3 Matrix:\n";
    mat1.print_matrix(true);

    tiny::Mat cof1 = mat1.cofactor(1, 1);
    std::cout << "Cofactor Matrix (remove row 1, col 1):\n";
    cof1.print_matrix(true);  // Expected: [[1,3],[7,9]]

    // Test 2: Remove first row and first column
    std::cout << "\n[Test 2] Remove row 0, col 0\n";
    tiny::Mat cof2 = mat1.cofactor(0, 0);
    cof2.print_matrix(true);  // Expected: [[5,6],[8,9]]

    // Test 3: Remove last row and last column
    std::cout << "\n[Test 3] Remove row 2, col 2\n";
    tiny::Mat cof3 = mat1.cofactor(2, 2);
    cof3.print_matrix(true);  // Expected: [[1,2],[4,5]]

    // Test 4: 4x4 Matrix Example
    std::cout << "\n[Test 4] Cofactor of 4x4 Matrix (remove row 2, col 1)\n";
    tiny::Mat mat4(4, 4);
    val = 1;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat4(i, j) = val++;

    mat4.print_matrix(true);
    tiny::Mat cof4 = mat4.cofactor(2, 1);
    std::cout << "Cofactor Matrix:\n";
    cof4.print_matrix(true);

    // Test 5: Non-square Matrix (Expect Error)
    std::cout << "\n[Test 5] Non-square Matrix (Expect Error)\n";
    tiny::Mat rectMat(3, 4);
    rectMat.cofactor(1, 1).print_matrix(true);  // Should trigger error and return empty matrix
}

// Test 5.3 determinant calculation
void test_matrix_determinant()
{
    std::cout << "\n[Matrix Determinant Test Start]\n";

    /*** Test 1: 1x1 Matrix ***/
    std::cout << "\n[Test 1] 1x1 Matrix Determinant\n";
    tiny::Mat mat1(1, 1);
    mat1(0, 0) = 7;
    std::cout << "Determinant: " << mat1.determinant() << "  (Expected: 7)\n";

    /*** Test 2: 2x2 Matrix ***/
    std::cout << "\n[Test 2] 2x2 Matrix Determinant\n";
    tiny::Mat mat2(2, 2);
    mat2(0, 0) = 3; mat2(0, 1) = 8;
    mat2(1, 0) = 4; mat2(1, 1) = 6;
    std::cout << "Determinant: " << mat2.determinant() << "  (Expected: -14)\n";

    /*** Test 3: 3x3 Matrix ***/
    std::cout << "\n[Test 3] 3x3 Matrix Determinant\n";
    tiny::Mat mat3(3, 3);
    mat3(0,0) = 1; mat3(0,1) = 2; mat3(0,2) = 3;
    mat3(1,0) = 0; mat3(1,1) = 4; mat3(1,2) = 5;
    mat3(2,0) = 1; mat3(2,1) = 0; mat3(2,2) = 6;
    std::cout << "Determinant: " << mat3.determinant() << "  (Expected: 22)\n";

    /*** Test 4: 4x4 Matrix ***/
    std::cout << "\n[Test 4] 4x4 Matrix Determinant\n";
    tiny::Mat mat4(4, 4);
    int val = 1;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat4(i, j) = val++;
    std::cout << "Determinant: " << mat4.determinant() << "  (Expected: 0)\n";  

    /*** Test 5: Non-square Matrix (Expect Error) ***/
    std::cout << "\n[Test 5] Non-square Matrix (Expect Error)\n";
    tiny::Mat rectMat(3, 4);
    float det_rect = rectMat.determinant();  // should trigger error
    std::cout << "Determinant: " << det_rect << "  (Expected: 0 with error message)\n";

    std::cout << "\n[Matrix Determinant Test End]\n";
}

// Test 5.4 adjoint calculation
void test_matrix_adjoint()
{
    std::cout << "\n[Matrix Adjoint Test Start]\n";

    /*** Test 1: 1x1 Matrix ***/
    std::cout << "\n[Test 1] Adjoint of 1x1 Matrix\n";
    tiny::Mat mat1(1, 1);
    mat1(0, 0) = 5;
    tiny::Mat adj1 = mat1.adjoint();
    adj1.print_matrix(true);  // Expected: [1]

    /*** Test 2: 2x2 Matrix ***/
    std::cout << "\n[Test 2] Adjoint of 2x2 Matrix\n";
    tiny::Mat mat2(2, 2);
    mat2(0, 0) = 1; mat2(0, 1) = 2;
    mat2(1, 0) = 3; mat2(1, 1) = 4;
    tiny::Mat adj2 = mat2.adjoint();
    adj2.print_matrix(true);  // Expected: [4, -2; -3, 1]

    /*** Test 3: 3x3 Matrix ***/
    std::cout << "\n[Test 3] Adjoint of 3x3 Matrix\n";
    tiny::Mat mat3(3, 3);
    mat3(0,0) = 1; mat3(0,1) = 2; mat3(0,2) = 3;
    mat3(1,0) = 0; mat3(1,1) = 4; mat3(1,2) = 5;
    mat3(2,0) = 1; mat3(2,1) = 0; mat3(2,2) = 6;
    tiny::Mat adj3 = mat3.adjoint();
    adj3.print_matrix(true);
    // No simple expected value, but should compute correctly

    /*** Test 4: Non-Square Matrix (Expect Error) ***/
    std::cout << "\n[Test 4] Adjoint of Non-Square Matrix (Expect Error)\n";
    tiny::Mat rectMat(2, 3);
    tiny::Mat adjRect = rectMat.adjoint();
    adjRect.print_matrix(true);  // Should be empty or default matrix

    std::cout << "\n[Matrix Adjoint Test End]\n";
}

// Test 5.5 normalization function
void test_matrix_normalize()
{
    std::cout << "\n[Test: Matrix Normalization]\n";

    /*** Test 1: Standard normalization ***/
    std::cout << "\n[Test 1] Normalize a standard 2x2 matrix\n";
    tiny::Mat mat1(2, 2);
    mat1(0, 0) = 3.0f; mat1(0, 1) = 4.0f;
    mat1(1, 0) = 3.0f; mat1(1, 1) = 4.0f;

    std::cout << "Before normalization:\n";
    mat1.print_matrix(true);

    mat1.normalize();

    std::cout << "After normalization (Expected L2 norm = 1):\n";
    mat1.print_matrix(true);

    /*** Test 2: Matrix with padding ***/
    std::cout << "\n[Test 2] Normalize a 2x2 matrix with stride=4 (Padding Test)\n";
    float data_with_padding[8] = {3.0f, 4.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f, 0.0f};
    tiny::Mat mat2(data_with_padding, 2, 2, 4);  // 2x2 matrix, stride 4

    std::cout << "Before normalization:\n";
    mat2.print_matrix(true);

    mat2.normalize();

    std::cout << "After normalization:\n";
    mat2.print_matrix(true);

    /*** Test 3: Zero matrix normalization ***/
    std::cout << "\n[Test 3] Normalize a zero matrix (Expect warning)\n";
    tiny::Mat mat3(2, 2);
    mat3.clear();  // Assuming clear() sets all elements to zero

    mat3.print_matrix(true);
    mat3.normalize();  // Should trigger warning
}

// Test 5.6: Matrix Norm Calculation
void test_matrix_norm()
{
    std::cout << "\n[Test: Matrix Norm Calculation]\n";

    /*** Test 1: Simple 2x2 Matrix ***/
    std::cout << "\n[Test 1] 2x2 Matrix Norm (Expect 5.0)\n";
    tiny::Mat mat1(2, 2);
    mat1(0, 0) = 3.0f; mat1(0, 1) = 4.0f;
    mat1(1, 0) = 0.0f; mat1(1, 1) = 0.0f;
    float norm1 = mat1.norm();
    std::cout << "Calculated Norm: " << norm1 << "\n";

    /*** Test 2: Zero Matrix ***/
    std::cout << "\n[Test 2] Zero Matrix Norm (Expect 0.0)\n";
    tiny::Mat mat2(3, 3);
    mat2.clear();  // Assuming clear() sets all elements to zero
    float norm2 = mat2.norm();
    std::cout << "Calculated Norm: " << norm2 << "\n";

    /*** Test 3: Matrix with Negative Values ***/
    std::cout << "\n[Test 3] Matrix with Negative Values\n";
    tiny::Mat mat3(2, 2);
    mat3(0, 0) = -1.0f; mat3(0, 1) = -2.0f;
    mat3(1, 0) = -3.0f; mat3(1, 1) = -4.0f;
    float norm3 = mat3.norm();
    std::cout << "Calculated Norm: " << norm3 << "  (Expect sqrt(30) ≈ 5.477)\n";

    /*** Test 4: Matrix with Padding ***/
    std::cout << "\n[Test 4] 2x2 Matrix with Stride=4 (Padding Test)\n";
    float data4[8] = {1.0f, 2.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f, 0.0f};
    tiny::Mat mat4(data4, 2, 2, 4);  // 2x2 matrix, stride 4
    float norm4 = mat4.norm();
    std::cout << "Calculated Norm: " << norm4 << "  (Expect sqrt(30) ≈ 5.477)\n";
}

// Test 5.7: Matrix Inversion
void test_matrix_inverse()
{
    std::cout << "\n[Test: Matrix Inverse Calculation]\n";

    /*** Test 1: 2x2 Regular Matrix ***/
    std::cout << "\n[Test 1] Inverse of 2x2 Matrix\n";
    tiny::Mat mat1(2, 2);
    mat1(0, 0) = 4;  mat1(0, 1) = 7;
    mat1(1, 0) = 2;  mat1(1, 1) = 6;

    mat1.print_matrix(true);
    tiny::Mat inv1 = mat1.inverse();
    std::cout << "Inverse Matrix:\n";
    inv1.print_matrix(true);
    std::cout << "Expected Approx:\n[ 0.6  -0.7 ]\n[ -0.2  0.4 ]\n";

    /*** Test 2: Singular Matrix (Determinant = 0) ***/
    std::cout << "\n[Test 2] Singular Matrix (Expect Error)\n";
    tiny::Mat mat2(2, 2);
    mat2(0, 0) = 1;  mat2(0, 1) = 2;
    mat2(1, 0) = 2;  mat2(1, 1) = 4;   // Rank-deficient, det = 0

    mat2.print_matrix(true);
    tiny::Mat inv2 = mat2.inverse();
    std::cout << "Inverse Matrix (Should be zero matrix):\n";
    inv2.print_matrix(true);

    /*** Test 3: 3x3 Regular Matrix ***/
    std::cout << "\n[Test 3] Inverse of 3x3 Matrix\n";
    tiny::Mat mat3(3, 3);
    mat3(0,0) = 3; mat3(0,1) = 0; mat3(0,2) = 2;
    mat3(1,0) = 2; mat3(1,1) = 0; mat3(1,2) = -2;
    mat3(2,0) = 0; mat3(2,1) = 1; mat3(2,2) = 1;

    mat3.print_matrix(true);
    tiny::Mat inv3 = mat3.inverse();
    std::cout << "Inverse Matrix:\n";
    inv3.print_matrix(true);

    /*** Test 4: Non-Square Matrix (Expect Error) ***/
    std::cout << "\n[Test 4] Non-Square Matrix (Expect Error)\n";
    tiny::Mat mat4(2, 3);
    tiny::Mat inv4 = mat4.inverse();
    inv4.print_matrix(true);
}

// Test 5.8: Matrix Utilities
void test_matrix_utilities()
{
    std::cout << "\n[Matrix Utilities Test Start]\n";

    /*** Test 1: Identity Matrix (eye) ***/
    std::cout << "\n[Test 1] Generate Identity Matrix (eye)\n";
    tiny::Mat I3 = tiny::Mat::eye(3);
    std::cout << "3x3 Identity Matrix:\n";
    I3.print_matrix(true);

    tiny::Mat I5 = tiny::Mat::eye(5);
    std::cout << "5x5 Identity Matrix:\n";
    I5.print_matrix(true);

    /*** Test 2: Ones Matrix ***/
    std::cout << "\n[Test 2] Generate Ones Matrix\n";
    tiny::Mat ones_3x4 = tiny::Mat::ones(3, 4);
    std::cout << "3x4 Ones Matrix:\n";
    ones_3x4.print_matrix(true);

    tiny::Mat ones_4x4 = tiny::Mat::ones(4);
    std::cout << "4x4 Ones Matrix (Square):\n";
    ones_4x4.print_matrix(true);

    /*** Test 3: Matrix Augmentation ***/
    std::cout << "\n[Test 3] Augment Two Matrices Horizontally [A | B]\n";

    // Prepare matrices A (2x2) and B (2x3)
    tiny::Mat A(2, 2);
    A(0,0) = 1;  A(0,1) = 2;
    A(1,0) = 3;  A(1,1) = 4;

    tiny::Mat B(2, 3);
    B(0,0) = 5;  B(0,1) = 6;  B(0,2) = 7;
    B(1,0) = 8;  B(1,1) = 9;  B(1,2) = 10;

    std::cout << "Matrix A:\n";
    A.print_matrix(true);
    std::cout << "Matrix B:\n";
    B.print_matrix(true);

    tiny::Mat AB = tiny::Mat::augment(A, B);
    std::cout << "Augmented Matrix [A | B]:\n";
    AB.print_matrix(true);

    // Test 3.2: Row mismatch case
    std::cout << "\n[Test 3.2] Augment with Row Mismatch (Expect Error)\n";
    tiny::Mat C(3, 2);  // 3x2 matrix
    tiny::Mat invalidAug = tiny::Mat::augment(A, C);
    invalidAug.print_info();  // Should show empty matrix due to error

    std::cout << "\n[Matrix Utilities Test End]\n";
}

// Test 5.9: Gaussian Elimination
void test_gaussian_eliminate()
{
    std::cout << "\n[Gaussian Elimination Test]\n";

    /*** Test 1: Simple 3x3 System ***/
    std::cout << "\n[Test 1] 3x3 Matrix (Simple Upper Triangular)\n";
    tiny::Mat mat1(3, 3);
    mat1(0,0) = 2; mat1(0,1) = 1; mat1(0,2) = -1;
    mat1(1,0) = -3; mat1(1,1) = -1; mat1(1,2) = 2;
    mat1(2,0) = -2; mat1(2,1) = 1; mat1(2,2) = 2;

    std::cout << "Original Matrix:\n";
    mat1.print_matrix(true);

    tiny::Mat result1 = mat1.gaussian_eliminate();

    std::cout << "After Gaussian Elimination:\n";
    result1.print_matrix(true);

    /*** Test 2: 3x4 Augmented Matrix ***/
    std::cout << "\n[Test 2] 3x4 Augmented Matrix (Linear System Ax = b)\n";
    tiny::Mat mat2(3, 4);
    mat2(0,0) = 1; mat2(0,1) = 2; mat2(0,2) = -1; mat2(0,3) =  8;
    mat2(1,0) = -3; mat2(1,1) = -1; mat2(1,2) = 2; mat2(1,3) = -11;
    mat2(2,0) = -2; mat2(2,1) = 1; mat2(2,2) = 2; mat2(2,3) = -3;

    std::cout << "Original Augmented Matrix:\n";
    mat2.print_matrix(true);

    tiny::Mat result2 = mat2.gaussian_eliminate();

    std::cout << "Row Echelon Form:\n";
    result2.print_matrix(true);

    /*** Test 3: Singular Matrix ***/
    std::cout << "\n[Test 3] Singular Matrix (No unique solution)\n";
    tiny::Mat mat3(2, 2);
    mat3(0,0) = 1; mat3(0,1) = 2;
    mat3(1,0) = 2; mat3(1,1) = 4;  // Linearly dependent rows

    mat3.print_matrix(true);
    tiny::Mat result3 = mat3.gaussian_eliminate();
    std::cout << "After Gaussian Elimination:\n";
    result3.print_matrix(true);

    /*** Test 4: Zero Matrix ***/
    std::cout << "\n[Test 4] Zero Matrix\n";
    tiny::Mat mat4(3, 3);
    mat4.clear();  // Assuming clear() sets all elements to zero
    mat4.print_matrix(true);

    tiny::Mat result4 = mat4.gaussian_eliminate();
    std::cout << "After Gaussian Elimination:\n";
    result4.print_matrix(true);
}

// Test 5.10: Row Reduce from Gaussian (RREF Calculation)
void test_row_reduce_from_gaussian()
{
    std::cout << "\n[Test] Row Reduce From Gaussian (RREF Calculation)\n";

    // Example 1: Simple 3x4 augmented matrix (representing a system of equations)
    std::cout << "\n[Test 1] 3x4 Augmented Matrix\n";
    tiny::Mat mat1(3, 4);

    // Matrix:
    // [ 1  2 -1  -4 ]
    // [ 2  3 -1 -11 ]
    // [-2  0 -3  22 ]
    mat1(0,0) = 1;  mat1(0,1) = 2;  mat1(0,2) = -1; mat1(0,3) = -4;
    mat1(1,0) = 2;  mat1(1,1) = 3;  mat1(1,2) = -1; mat1(1,3) = -11;
    mat1(2,0) = -2; mat1(2,1) = 0;  mat1(2,2) = -3; mat1(2,3) = 22;

    std::cout << "Original Matrix:\n";
    mat1.print_matrix(true);

    tiny::Mat rref1 = mat1.gaussian_eliminate().row_reduce_from_gaussian();
    std::cout << "RREF Result:\n";
    rref1.print_matrix(true);

    // Example 2: 2x3 Matrix
    std::cout << "\n[Test 2] 2x3 Matrix\n";
    tiny::Mat mat2(2, 3);
    mat2(0,0) = 1; mat2(0,1) = 2;  mat2(0,2) = 3;
    mat2(1,0) = 4; mat2(1,1) = 5;  mat2(1,2) = 6;

    std::cout << "Original Matrix:\n";
    mat2.print_matrix(true);

    tiny::Mat rref2 = mat2.gaussian_eliminate().row_reduce_from_gaussian();
    std::cout << "RREF Result:\n";
    rref2.print_matrix(true);

    // Example 3: Already reduced matrix (should remain the same)
    std::cout << "\n[Test 3] Already Reduced Matrix\n";
    tiny::Mat mat3(2, 3);
    mat3(0,0) = 1; mat3(0,1) = 0; mat3(0,2) = 2;
    mat3(1,0) = 0; mat3(1,1) = 1; mat3(1,2) = 3;

    std::cout << "Original Matrix:\n";
    mat3.print_matrix(true);

    tiny::Mat rref3 = mat3.row_reduce_from_gaussian();
    std::cout << "RREF Result:\n";
    rref3.print_matrix(true);
}

// Test 5.11 gaussian inverse
void test_gaussian_inverse()
{
    std::cout << "\n--- Test: Gaussian Inverse ---\n";

    /*** Test1: Regular 2x2 Matrix ***/
    std::cout << "[Test 1: 2x2 Matrix Inverse]\n";
    tiny::Mat mat1(2, 2);
    mat1(0, 0) = 4; mat1(0, 1) = 7;
    mat1(1, 0) = 2; mat1(1, 1) = 6;
    std::cout << "Original matrix (mat1):\n";
    mat1.print_matrix(true);
    
    tiny::Mat invMat1 = mat1.gaussian_inverse();
    std::cout << "Inverse matrix (mat1):\n";
    invMat1.print_matrix(true);

    /*** Test2: Identity Matrix (should return identity matrix) ***/
    std::cout << "[Test 2: Identity Matrix Inverse]\n";
    tiny::Mat mat2 = tiny::Mat::eye(3);
    std::cout << "Original matrix (Identity):\n";
    mat2.print_matrix(true);
    
    tiny::Mat invMat2 = mat2.gaussian_inverse();
    std::cout << "Inverse matrix (Identity):\n";
    invMat2.print_matrix(true); // Expected: Identity matrix

    /*** Test3: Singular Matrix (should return empty matrix or indicate error) ***/
    std::cout << "[Test 3: Singular Matrix (Expected: No Inverse)]\n";
    tiny::Mat mat3(3, 3);
    mat3(0, 0) = 1; mat3(0, 1) = 2; mat3(0, 2) = 3;
    mat3(1, 0) = 4; mat3(1, 1) = 5; mat3(1, 2) = 6;
    mat3(2, 0) = 7; mat3(2, 1) = 8; mat3(2, 2) = 9;  // Determinant is 0
    std::cout << "Original matrix (singular):\n";
    mat3.print_matrix(true);
    
    tiny::Mat invMat3 = mat3.gaussian_inverse();
    std::cout << "Inverse matrix (singular):\n";
    invMat3.print_matrix(true); // Expected: empty matrix or error message

    /*** Test4: 3x3 Matrix with a valid inverse ***/
    std::cout << "[Test 4: 3x3 Matrix Inverse]\n";
    tiny::Mat mat4(3, 3);
    mat4(0, 0) = 4; mat4(0, 1) = 7; mat4(0, 2) = 2;
    mat4(1, 0) = 3; mat4(1, 1) = 5; mat4(1, 2) = 1;
    mat4(2, 0) = 8; mat4(2, 1) = 6; mat4(2, 2) = 9;
    std::cout << "Original matrix (mat4):\n";
    mat4.print_matrix(true);
    
    tiny::Mat invMat4 = mat4.gaussian_inverse();
    std::cout << "Inverse matrix (mat4):\n";
    invMat4.print_matrix(true); // Check that the inverse is calculated correctly

    /*** Test5: Non-square Matrix (should return error or empty matrix) ***/
    std::cout << "[Test 5: Non-square Matrix Inverse (Expected Error)]\n";
    tiny::Mat mat5(2, 3);
    mat5(0, 0) = 1; mat5(0, 1) = 2; mat5(0, 2) = 3;
    mat5(1, 0) = 4; mat5(1, 1) = 5; mat5(1, 2) = 6;
    std::cout << "Original matrix (non-square):\n";
    mat5.print_matrix(true);
    
    tiny::Mat invMat5 = mat5.gaussian_inverse();
    std::cout << "Inverse matrix (non-square):\n";
    invMat5.print_matrix(true); // Expected: Error message or empty matrix
}



void tiny_matrix_test()
{
    std::cout << "============ [tiny_matrix_test start] ============\n";

    // Group 1: constructor & destructor
    // test_constructor_destructor();

    // Group 2: element access
    // test_element_access();

    // Group 3: ROI operations
    // test_roi_operations();

    // Group 4: arithmetic operators
    // test_assignment_operator();
    // test_matrix_addition();
    // test_constant_addition();
    // test_matrix_subtraction();
    // test_constant_subtraction();
    // test_matrix_division();
    // test_constant_division();
    // test_matrix_exponentiation();

    // Group 5: Linear algebra tests
    // test_matrix_transpose();
    // test_matrix_cofactor();
    // test_matrix_determinant();
    // test_matrix_adjoint();
    // test_matrix_normalize();
    // test_matrix_norm();
    // test_matrix_inverse();
    // test_matrix_utilities();
    // test_gaussian_eliminate();
    // test_row_reduce_from_gaussian();
    test_gaussian_inverse();

    std::cout << "============ [tiny_matrix_test end] ============\n";
}