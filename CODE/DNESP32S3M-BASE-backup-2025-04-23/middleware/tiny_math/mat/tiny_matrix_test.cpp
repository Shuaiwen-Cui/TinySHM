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

void test_constructor_and_basic()
{
    std::cout << "\n[Constructor & Basic Test]\n";
    tiny::Mat A(3, 3);
    A.PrintMatrix(false, "3x3 Zero Matrix");

    tiny::Mat I = tiny::Mat::eye(3);
    I.PrintMatrix(false, "Identity Matrix 3x3");

    tiny::Mat O = tiny::Mat::ones(2, 4);
    O.PrintMatrix(false, "2x4 Matrix with all 1s");

    tiny::Mat B(A);
    B.PrintMatrix(false, "Copy Constructor Test");
}

void test_operator_overloads()
{
    std::cout << "\n[Operator Overloads Test]\n";
    tiny::Mat A = tiny::Mat::ones(2, 2);
    tiny::Mat B = tiny::Mat::ones(2, 2);

    tiny::Mat C = A + B;
    C.PrintMatrix(false, "A + B");

    C = A - B;
    C.PrintMatrix(false, "A - B");

    C = A * 2.0f;
    C.PrintMatrix(false, "A * 2.0");

    C = A / 2.0f;
    C.PrintMatrix(false, "A / 2.0");

    bool eq = (A == B);
    std::cout << "A == B: " << eq << "\n";
}

void test_matrix_functions()
{
    std::cout << "\n[Matrix Functions Test]\n";
    tiny::Mat A = tiny::Mat::ones(3, 2);
    A.swapRows(0, 2);
    A.PrintMatrix(false, "After swapRows(0,2)");

    tiny::Mat T = A.t();
    T.PrintMatrix(false, "Transpose");

    A.clear();
    A.PrintMatrix(false, "After clear");

    tiny::Mat block = T.block(0, 0, 2, 1);
    block.PrintMatrix(false, "Block (0,0,2,1)");
}

void test_linear_algebra()
{
    std::cout << "\n[Linear Algebra Test]\n";
    tiny::Mat A(2, 2);
    A(0, 0) = 2;
    A(0, 1) = 1;
    A(1, 0) = 5;
    A(1, 1) = 7;

    tiny::Mat b(2, 1);
    b(0, 0) = 11;
    b(1, 0) = 13;

    tiny::Mat x = tiny::Mat::solve(A, b);
    x.PrintMatrix(false, "Solve Ax = b");

    float dp = tiny::Mat::dotProduct(b, b);
    std::cout << "Dot Product b·b = " << dp << "\n";
}

void test_io_streams()
{
    std::cout << "\n[IO Stream Test]\n";
    tiny::Mat A = tiny::Mat::ones(2, 2);

    std::stringstream ss;
    ss << A;

    tiny::Mat B(2, 2);
    ss >> B;

    B.PrintMatrix(false, "Matrix loaded from stream");
}

void tiny_matrix_test()
{
    std::cout << "============ [tiny_matrix_test] ============\n";

    test_constructor_and_basic();
    test_operator_overloads();
    test_matrix_functions();
    test_linear_algebra();
    test_io_streams();

    std::cout << "============ [test complete] ============\n";
}