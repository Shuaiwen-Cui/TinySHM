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

    std::cout << "============ [tiny_matrix_test end] ============\n";
}