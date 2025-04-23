# 代码

## tiny_matrix.h

```cpp
/**
 * @file tiny_matrix.hpp
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the header file for the submodule matrix (advanced matrix operations) of the tiny_math middleware.
 * @version 1.0
 * @date 2025-04-17
 * @note This file is built on top of the mat.h file from the ESP-DSP library.
 *
 */

#pragma once

/* DEPENDENCIES */
// TinyMath
#include "tiny_math_config.h"
#include "tiny_vec.h"
#include "tiny_mat.h"

// Standard Libraries
#include <iostream>
#include <stdint.h>

#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
// ESP32 DSP C++ Matrix library
#include "mat.h"
#endif

/* STATEMENTS */
namespace tiny
{
    class Mat
    {
    public:
        /* === Matrix Metadata === */
        int rows;        /*!< Amount of rows*/
        int cols;        /*!< Amount of columns*/
        int stride;      /*!< Stride = (number of elements in a row) + padding*/
        int padding;     /*!< Padding between 2 rows*/
        int length;      /*!< Total amount of data in data array*/
        float *data;     /*!< Buffer with matrix data*/
        bool ext_buff;   /*!< Flag indicates that matrix use external buffer*/
        bool sub_matrix; /*!< Flag indicates that matrix is a subset of another matrix*/

        /* === Rectangular ROI Structure === */
        /**
         * @brief Rectangular area
         *
         * The Rect is used for creating regions of interest ROI(s). The ROI is then used as a sub-matrix
         */
        struct Rect
        {
            int x;      ///< starting column index
            int y;      ///< starting row index
            int width;  ///< width of ROI (columns)
            int height; ///< height of ROI (rows)

            /**
             * @brief Constructor with initialization to 0
             *
             * @param[in] x: x starting position (start col) of the rectangular area
             * @param[in] y: y starting position (start row) of the rectangular area
             * @param[in] width: width (number of cols) of the rectangular area
             * @param[in] height: height (number of rows) of the rectangular area
             */
            Rect(int x = 0, int y = 0, int width = 0, int height = 0);

            /**
             * @brief Resize rect area
             *
             * @param[in] x: x starting position (start col) of the new rectangular area
             * @param[in] y: y starting position (start row) of the new rectangular area
             * @param[in] width: width (number of cols) of the new rectangular area
             * @param[in] height: height (number of rows) of the new rectangular area
             */
            void resizeRect(int x, int y, int width, int height);

            /**
             * @brief Get amount of elements in the rect area
             */
            int areaRect(void) const;
        };

        /* === Constructors & Destructor === */
        /**
         * Allocate matrix with undefined size.
         */
        Mat();
        /**
         * @brief Construct a new Mat object (internal allocation)
         *
         * @param rows Number of rows
         * @param cols Number of columns
         */
        Mat(int rows, int cols);
        /**
         * @brief Construct a new Mat object (external allocation)
         *
         * @param data Pointer to external data buffer
         * @param rows Number of rows
         * @param cols Number of columns
         */
        Mat(float *data, int rows, int cols);
        /**
         * @brief Construct a new Mat object (external allocation with stride)
         *
         * @param data Pointer to external data buffer
         * @param rows Number of rows
         * @param cols Number of columns
         * @param stride Stride (number of elements in a row)
         */
        Mat(float *data, int rows, int cols, int stride);
        /**
         * @brief Make copy of matrix.
         *
         * if src matrix is sub matrix, only the header is copied
         * if src matrix is matrix, header and data are copied
         *
         * @param[in] src: source matrix
         */
        Mat(const Mat &src);
        /**
         * @brief Destroy the Mat object, freeing internal memory
         */
        ~Mat();
        /**
         * @brief Allocate internal memory buffer
         */
        void allocate(); // Allocate internal memory

        /* === Element Access === */
        inline float &operator()(int row, int col) { return data[row * stride + col]; }             // for non-const
        inline const float &operator()(int row, int col) const { return data[row * stride + col]; } // for const

        /* === Data Manipulation === */
        /**
         * Make copy of matrix. Memory not shared.
         * @param[in] src: source matrix
         * @param[in] row_pos: start row position of destination matrix
         * @param[in] col_pos: start col position of destination matrix
         */
        void Copy(const Mat &src, int row_pos, int col_pos);
        /**
         * @brief Copy header of matrix. Memory shared.
         *
         * Make a shallow copy of matrix (no data copy)
         * @param[in] src: source matrix
         */
        void CopyHead(const Mat &src);
        /**
         * @brief Create a subset of matrix as ROI (Region of Interest)
         *
         * @param[in] startRow: start row position of source matrix to get the subset matrix from
         * @param[in] startCol: start col position of source matrix to get the subset matrix from
         * @param[in] roiRows: size of row elements of source matrix to get the subset matrix from
         * @param[in] roiCols: size of col elements of source matrix to get the subset matrix from
         * @param[in] stride: number of cols + padding between 2 rows
         *
         * @return
         *      - result matrix size roiRows x roiCols
         */
        Mat getROI(int startRow, int startCol, int roiRows, int roiCols, int stride);
        /**
         * @brief Create a subset of matrix as ROI (Region of Interest)
         *
         * @param[in] startRow: start row position of source matrix to get the subset matrix from
         * @param[in] startCol: start col position of source matrix to get the subset matrix from
         * @param[in] roiRows: size of row elements of source matrix to get the subset matrix from
         * @param[in] roiCols: size of col elements of source matrix to get the subset matrix from
         *
         * @return
         *      - result matrix size roiRows x roiCols
         */
        Mat getROI(int startRow, int startCol, int roiRows, int roiCols);
        /**
         * @brief Create a subset of matrix as ROI (Region of Interest)
         *
         * @param[in] rect: rectangular area of interest
         *
         * @return
         *      - result matrix size rect.rectRows x rect.rectCols
         */
        Mat getROI(const Rect &rect);
        /**
         * Make copy of matrix.
         * @param[in] row_start: start row position of source matrix to copy
         * @param[in] row_size: size of wor elements of source matrix to copy
         * @param[in] col_start: start col position of source matrix to copy
         * @param[in] col_size: size of wor elements of source matrix to copy
         *
         * @return
         *      - result matrix size row_size x col_size
         */
        Mat Get(int row_start, int row_size, int col_start, int col_size);
        /**
         * Make copy of matrix.
         * @param[in] rect: rectangular area of interest
         * @return
         *      - result matrix size row_size x col_size
         */
        Mat Get(const Rect &rect);
        /**
         * Return part of matrix from defined position (startRow, startCol) as a matrix[blockRows x blockCols].
         *
         * @param[in] startRow: start row position
         * @param[in] startCol: start column position
         * @param[in] blockRows: amount of rows in result matrix
         * @param[in] blockCols: amount of columns in the result matrix
         *
         * @return
         *      - matrix [blockRows]x[blockCols]
         */
        Mat block(int startRow, int startCol, int blockRows, int blockCols);
        /**
         * Swap two rows between each other.
         * @param[in] row1: position of first row
         * @param[in] row2: position of second row
         */
        void swapRows(int row1, int row2);
        /**
         * The method fill 0 to the matrix structure.
         *
         */
        void clear();

        /* === Print & Debug === */
        /**
         * @brief print matrix header
         *
         * Print all information about matrix to the terminal
         * @param[in] src: source matrix
         */
        void PrintHead();
        /**
         * @brief print matrix header and data
         *
         * Print all information about matrix to the terminal
         * @param[in] show_padding: show padding information
         * @param[in] label: label for the matrix
         */
        void PrintMatrix(bool show_padding, const std::string &label);

        /* === Arithmetic Operators === */
        /**
         * Copy operator
         *
         * @param[in] src: source matrix
         *
         * @return
         *      - matrix copy
         */
        Mat &operator=(const Mat &src); // Copy assignment
        /**
         * += operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] A: source matrix
         *
         * @return
         *      - result matrix: result += A
         */
        Mat &operator+=(const Mat &A);
        /**
         * += operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] C: constant
         *
         * @return
         *      - result matrix: result += C
         */
        Mat &operator+=(float C);
        /**
         * -= operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] A: source matrix
         *
         * @return
         *      - result matrix: result -= A
         */
        Mat &operator-=(const Mat &A);
        /**
         * -= operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] C: constant
         *
         * @return
         *      - result matrix: result -= C
         */
        Mat &operator-=(float C);
        /**
         * *= operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] A: source matrix
         *
         * @return
         *      - result matrix: result -= A
         */
        Mat &operator*=(const Mat &A);
        /**
         * += with constant operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] C: constant value
         *
         * @return
         *      - result matrix: result *= C
         */
        Mat &operator*=(float C);
        /**
         * /= operator
         *
         * @param[in] B: source matrix
         *
         * @return
         *      - result matrix: result[i,j] = result[i,j]/B[i,j]
         */
        Mat &operator/=(const Mat &B);
        /**
         * /= with constant operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] C: constant value
         *
         * @return
         *      - result matrix: result /= C
         */
        Mat &operator/=(float C);
        /**
         * ^= exponentiation operator
         * The operator use DSP optimized implementation of multiplication.
         *
         * @param[in] num: exponent
         *
         * @return
         *      - result matrix: result = result^num
         */
        Mat operator^(int C);

        /* === Linear Algebra === */
        /**
         * @brief Normalize the matrix
         *
         * The method normalize the matrix to unit length.
         */
        void normalize();
        /**
         * @brief Calculate the matrix norm
         *
         * The method calculate the matrix norm.
         *
         * @return
         *      - result matrix norm
         */
        float norm();
        /**
         * @brief Calculate the determinant of the matrix
         *
         * The method calculate the determinant of the matrix.
         *
         * @param n: size of the matrix
         *
         * @return
         *      - result matrix determinant
         */
        float det(int n);
        /**
         * Matrix transpose.
         * Change rows and columns between each other.
         *
         * @return
         *      - transposed matrix
         */
        Mat t();
        /**
         * Find the inverse matrix
         *
         * @return
         *      - inverse matrix
         */
        Mat inverse();
        /**
         * Find pseudo inverse matrix
         *
         * @return
         *      - inverse matrix
         */
        Mat pinv();
        /**
         * @brief   Gaussian Elimination
         *
         * Gaussian Elimination of matrix
         *
         * @return
         *      - result matrix
         */
        Mat gaussianEliminate();
        /**
         * Row reduction for Gaussian elimination
         *
         * @return
         *      - result matrix
         */
        Mat rowReduceFromGaussian();

        /* === Static Utility Functions === */
        /**
         * Create identity matrix.
         * Create a square matrix and fill diagonal with 1.
         *
         * @param[in] size: matrix size
         *
         * @return
         *      - matrix [N]x[N] with 1 in diagonal
         */
        static Mat eye(int size);
        /**
         * Create matrix with all elements 1.
         * Create a square matrix and fill all elements with 1.
         *
         * @param[in] size: matrix size
         *
         * @return
         *      - matrix [N]x[N] with 1 in all elements
         */
        static Mat ones(int size);
        /**
         * Create matrix with all elements 1.
         * Create a matrix and fill all elements with 1.
         *
         * @param[in] rows: matrix rows
         * @param[in] cols: matrix cols
         *
         * @return
         *      - matrix [N]x[N] with 1 in all elements
         */
        static Mat ones(int rows, int cols);
        /**
         * @brief   Solve the matrix
         *
         * Solve matrix. Find roots for the matrix A*x = b
         *
         * @param[in] A: matrix [N]x[N] with input coefficients
         * @param[in] b: vector [N]x[1] with result values
         *
         * @return
         *      - matrix [N]x[1] with roots
         */
        static Mat solve(Mat A, Mat b);
        /**
         * @brief   Band solve the matrix
         *
         * Solve band matrix. Find roots for the matrix A*x = b with bandwidth k.
         *
         * @param[in] A: matrix [N]x[N] with input coefficients
         * @param[in] b: vector [N]x[1] with result values
         * @param[in] k: upper bandwidth value
         *
         * @return
         *      - matrix [N]x[1] with roots
         */
        static Mat bandSolve(Mat A, Mat b, int k);
        /**
         * @brief   Solve the matrix
         *
         * Different way to solve the matrix. Find roots for the matrix A*x = y
         *
         * @param[in] A: matrix [N]x[N] with input coefficients
         * @param[in] y: vector [N]x[1] with result values
         *
         * @return
         *      - matrix [N]x[1] with roots
         */
        static Mat roots(Mat A, Mat y);
        /**
         * @brief   Dotproduct of two vectors
         *
         * The method returns dotproduct of two vectors
         *
         * @param[in] A: Input vector A Nx1
         * @param[in] B: Input vector B Nx1
         *
         * @return
         *      - dotproduct value
         */
        static float dotProduct(Mat A, Mat B);
        /**
         * @brief   Augmented matrices (concatenate two matrices horizontally)
         *
         * Augmented matrices
         *
         * @param[in] A: Input vector A MxN
         * @param[in] B: Input vector B MxK
         *
         * @return
         *      - Augmented matrix Mx(N+K)
         */
        static Mat augment(Mat A, Mat B);

    private:
        /* === Private Utility Functions === */
        /**
         * @brief   Calculate cofactor matrix
         *
         * Calculate cofactor matrix of the matrix
         *
         * @param[in] row: row position
         * @param[in] col: column position
         * @param[in] n: size of the matrix
         *
         * @return
         *      - cofactor matrix
         */
        Mat cofactor(int row, int col, int n);
        /**
         * @brief   Calculate adjoint matrix
         *
         * Calculate adjoint matrix of the matrix
         *
         * @return
         *      - adjoint matrix
         */
        Mat adjoint();
        /**
         * @brief   Calculate matrix exponential
         *
         * Calculate matrix exponential of the matrix
         *
         * @param[in] m: input matrix
         * @param[in] num: number of iterations
         *
         * @return
         *      - matrix exponential
         */
        Mat expHelper(const Mat &m, int num);
    };

    /* === Stream Operators === */
    /**
     * Print matrix to the standard iostream.
     * @param[in] os: output stream
     * @param[in] m: matrix to print
     *
     * @return
     *      - output stream
     */
    std::ostream &operator<<(std::ostream &os, const Mat &m);
    /**
     * Print rectangular ROI to the standard iostream.
     * @param[in] os: output stream
     * @param[in] rect: ROI
     *
     * @return
     *      - output stream
     */
    std::ostream &operator<<(std::ostream &os, const Mat::Rect &rect);
    /**
     * Fill the matrix from iostream.
     * @param[in] is: input stream
     * @param[in] m: matrix to fill
     *
     * @return
     *      - input stream
     */
    std::istream &operator>>(std::istream &is, Mat &m);

    /* === Global Arithmetic Operators === */
    /**
     * + operator, sum of two matrices
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A+B
     */
    Mat operator+(const Mat &A, const Mat &B);
    /**
     * + operator, sum of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: Input constant
     *
     * @return
     *     - result matrix A+C
     */
    Mat operator+(const Mat &A, float C);
    /**
     * - operator, subtraction of two matrices
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A-B
     */
    Mat operator-(const Mat &A, const Mat &B);
    /**
     * - operator, subtraction of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: Input constant
     *
     * @return
     *     - result matrix A-C
     */
    Mat operator-(const Mat &A, float C);
    /**
     * * operator, multiplication of two matrices.
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A*B
     */
    Mat operator*(const Mat &A, const Mat &B);
    /**
     * * operator, multiplication of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: floating point value
     *
     * @return
     *     - result matrix A*B
     */
    Mat operator*(const Mat &A, float C);
    /**
     * * operator, multiplication of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: floating point value
     * @param[in] A: Input matrix A
     *
     * @return
     *     - result matrix C*A
     */
    Mat operator*(float C, const Mat &A);
    /**
     * / operator, divide of matrix by constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: floating point value
     *
     * @return
     *     - result matrix A/C
     */
    Mat operator/(const Mat &A, float C);
    /**
     * / operator, divide matrix A by matrix B (element-wise)
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix C, where C[i,j] = A[i,j]/B[i,j]
     */
    Mat operator/(const Mat &A, const Mat &B);
    /**
     * == operator, compare two matrices
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *      - true if matrices are the same
     *      - false if matrices are different
     */
    bool operator==(const Mat &A, const Mat &B);

}
```

## tiny_matrix.c

```cpp
/**
 * @file tiny_matrix.cpp
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the source file for the submodule matrix (advanced matrix operations) of the tiny_math middleware.
 * @version 1.0
 * @date 2025-04-17
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
// TinyMath
#include "tiny_matrix.hpp"

// Standard Libraries
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <math.h>
#include <cmath>
#include <inttypes.h>
#include <iomanip>

// Namespace
using std::endl;
using std::istream;
using std::ostream;

/* LIBRARIE CONTENTS */
namespace tiny
{
    /* === Rectangular ROI Structure === */

    /**
     * @brief Constructor with initialization to 0
     *
     * @param[in] x: x starting position (start col) of the rectangular area
     * @param[in] y: y starting position (start row) of the rectangular area
     * @param[in] width: width (number of cols) of the rectangular area
     * @param[in] height: height (number of rows) of the rectangular area
     */
    Mat::Rect::Rect(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    /**
     * @brief Resize rect area
     *
     * @param[in] x: x starting position (start col) of the new rectangular area
     * @param[in] y: y starting position (start row) of the new rectangular area
     * @param[in] width: width (number of cols) of the new rectangular area
     * @param[in] height: height (number of rows) of the new rectangular area
     */
    void Mat::Rect::resizeRect(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    /**
     * @brief Get amount of elements in the rect area
     */
    int Mat::Rect::areaRect(void) const
    {
        return width * height;
    }

    /* === Constructors & Destructor === */
    /**
     * Allocate matrix with undefined size.
     */
    Mat::Mat()
        : rows(1), cols(1), stride(1), padding(0), length(1),
          data(nullptr), ext_buff(false), sub_matrix(false)
    {
        allocate();
        std::memset(this->data, 0, this->length * sizeof(float));
    }

    /**
     * @brief Construct a new Mat object (internal allocation)
     *
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Mat::Mat(int rows, int cols)
        : rows(rows), cols(cols), stride(cols), padding(0), length(rows * cols),
          data(nullptr), ext_buff(false), sub_matrix(false)
    {
        allocate();
        std::memset(this->data, 0, this->length * sizeof(float));
    }

    /**
     * @brief Construct a new Mat object (external allocation)
     *
     * @param data Pointer to external data buffer
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Mat::Mat(float *data, int rows, int cols)
        : rows(rows), cols(cols), stride(cols), padding(0), length(rows * cols),
          data(data), ext_buff(true), sub_matrix(false) {}

    /**
     * @brief Construct a new Mat object (external allocation with stride)
     *
     * @param data Pointer to external data buffer
     * @param rows Number of rows
     * @param cols Number of columns
     * @param stride Stride (number of elements in a row)
     */
    Mat::Mat(float *data, int rows, int cols, int stride)
        : rows(rows), cols(cols), stride(stride), padding(stride - cols), length(rows * cols),
          data(data), ext_buff(true), sub_matrix(false) {}

    /**
     * @brief Make copy of matrix.
     *
     * if src matrix is sub matrix, only the header is copied
     * if src matrix is matrix, header and data are copied
     *
     * @param[in] src: source matrix
     */
    Mat::Mat(const Mat &m)
        : rows(m.rows), cols(m.cols), stride(m.stride), padding(m.padding), length(m.length),
          data(nullptr), ext_buff(false), sub_matrix(m.sub_matrix)
    {
        if (m.sub_matrix)
        {
            this->data = m.data;
            this->ext_buff = true;
        }
        else
        {
            allocate();
            std::memcpy(this->data, m.data, this->length * sizeof(float));
        }
    }

    /**
     * @brief Destroy the Mat object, freeing internal memory
     */
    Mat::~Mat()
    {
        if (!this->ext_buff && this->data)
        {
            delete[] this->data;
        }
    }

    /**
     * @brief Allocate internal memory buffer
     */
    void Mat::allocate()
    {
        this->ext_buff = false;
        this->length = this->rows * this->cols;
        this->data = new float[this->length];
    }
    /* === Element Access === */
    // Already defined by inline functions in the header file

    /* === Data Manipulation === */
    /**
     * Make copy of matrix. Memory not shared.
     * @param[in] src: source matrix
     * @param[in] row_pos: start row position of destination matrix
     * @param[in] col_pos: start col position of destination matrix
     */
    void Mat::Copy(const Mat &src, int row_pos, int col_pos)
    {
        if ((row_pos + src.rows) > this->rows)
        {
            return;
        }
        if ((col_pos + src.cols) > this->cols)
        {
            return;
        }

        for (size_t r = 0; r < src.rows; r++)
        {
            memcpy(&this->data[(r + row_pos) * this->stride + col_pos], &src.data[r * src.cols], src.cols * sizeof(float));
        }
    }

    /**
     * @brief Copy header of matrix. Memory shared.
     *
     * Make a shallow copy of matrix (no data copy)
     * @param[in] src: source matrix
     */
    void Mat::CopyHead(const Mat &src)
    {
        if (!this->ext_buff)
        {
            delete[] this->data;
        }
        this->rows = src.rows;
        this->cols = src.cols;
        this->length = src.length;
        this->padding = src.padding;
        this->stride = src.stride;
        this->data = src.data;
        this->ext_buff = src.ext_buff;
        this->sub_matrix = src.sub_matrix;
    }

    /**
     * @brief Create a subset of matrix as ROI (Region of Interest)
     *
     * @param[in] startRow: start row position of source matrix to get the subset matrix from
     * @param[in] startCol: start col position of source matrix to get the subset matrix from
     * @param[in] roiRows: size of row elements of source matrix to get the subset matrix from
     * @param[in] roiCols: size of col elements of source matrix to get the subset matrix from
     * @param[in] stride: number of cols + padding between 2 rows
     *
     * @return
     *      - result matrix size roiRows x roiCols
     */
    Mat Mat::getROI(int startRow, int startCol, int roiRows, int roiCols, int stride)
    {
        Mat result(this->data, roiRows, roiCols, 0); // this is an illegal matrix, for illegal access

        if ((startRow + roiRows) > this->rows)
        {
            return result;
        }
        if ((startCol + roiCols) > this->cols)
        {
            return result;
        }

        const int ptr_move = startRow * this->cols + startCol;
        float *new_data_ptr = this->data + ptr_move;

        result.data = new_data_ptr;
        result.stride = stride;
        result.padding = result.stride - result.cols;
        return result;
    }

    /**
     * @brief Create a subset of matrix as ROI (Region of Interest)
     *
     * @param[in] startRow: start row position of source matrix to get the subset matrix from
     * @param[in] startCol: start col position of source matrix to get the subset matrix from
     * @param[in] roiRows: size of row elements of source matrix to get the subset matrix from
     * @param[in] roiCols: size of col elements of source matrix to get the subset matrix from
     *
     * @return
     *      - result matrix size roiRows x roiCols
     */
    Mat Mat::getROI(int startRow, int startCol, int roiRows, int roiCols)
    {
        return (getROI(startRow, startCol, roiRows, roiCols, this->cols));
    }

    /**
     * @brief Create a subset of matrix as ROI (Region of Interest)
     *
     * @param[in] rect: rectangular area of interest
     *
     * @return
     *      - result matrix size rect.rectRows x rect.rectCols
     */
    Mat Mat::getROI(const Mat::Rect &rect)
    {
        return (getROI(rect.y, rect.x, rect.height, rect.width, this->cols));
    }

    /**
     * Make copy of matrix.
     * @param[in] row_start: start row position of source matrix to copy
     * @param[in] row_size: size of wor elements of source matrix to copy
     * @param[in] col_start: start col position of source matrix to copy
     * @param[in] col_size: size of wor elements of source matrix to copy
     *
     * @return
     *      - result matrix size row_size x col_size
     */
    Mat Mat::Get(int row_start, int row_size, int col_start, int col_size)
    {
        Mat result(row_size, col_size);

        if ((row_start + row_size) > this->rows)
        {
            return result;
        }
        if ((col_start + col_size) > this->cols)
        {
            return result;
        }

        for (size_t r = 0; r < result.rows; r++)
        {
            memcpy(&result.data[r * result.cols], &this->data[(r + row_start) * this->stride + col_start], result.cols * sizeof(float));
        }
        return result;
    }

    /**
     * Make copy of matrix.
     * @param[in] rect: rectangular area of interest
     * @return
     *      - result matrix size row_size x col_size
     */
    Mat Mat::Get(const Mat::Rect &rect)
    {
        return (Get(rect.y, rect.height, rect.x, rect.width));
    }

    /**
     * Return part of matrix from defined position (startRow, startCol) as a matrix[blockRows x blockCols].
     *
     * @param[in] startRow: start row position
     * @param[in] startCol: start column position
     * @param[in] blockRows: amount of rows in result matrix
     * @param[in] blockCols: amount of columns in the result matrix
     *
     * @return
     *      - matrix [blockRows]x[blockCols]
     */
    Mat Mat::block(int startRow, int startCol, int blockRows, int blockCols)
    {
        Mat result(blockRows, blockCols);
        for (int i = 0; i < blockRows; ++i)
        {
            for (int j = 0; j < blockCols; ++j)
            {
                result(i, j) = (*this)(startRow + i, startCol + j);
            }
        }
        return result;
    }

    /**
     * Swap two rows between each other.
     * @param[in] row1: position of first row
     * @param[in] row2: position of second row
     */
    void Mat::swapRows(int r1, int r2)
    {
        if ((this->rows <= r1) || (this->rows <= r2))
        {
            std::cerr << "swapRows Error: row " << r1 << " or " << r2 << " out of matrix row " << this->rows << " range" << std::endl;
        }
        else
        {
            for (int i = 0; i < this->cols; i++)
            {
                float temp = this->data[r1 * this->stride + i];
                this->data[r1 * this->stride + i] = this->data[r2 * this->stride + i];
                this->data[r2 * this->stride + i] = temp;
            }
        }
    }

    /**
     * The method fill 0 to the matrix structure.
     *
     */
    void Mat::clear()
    {
        for (int row = 0; row < this->rows; row++)
        {
            memset(this->data + (row * this->stride), 0, this->cols * sizeof(float));
        }
    }

    /* === Print & Debug === */
    /**
     * @brief print matrix header
     *
     * Print all information about matrix to the terminal
     * @param[in] src: source matrix
     */
    void Mat::PrintHead(void)
    {
        std::cout << "rows     " << this->rows << std::endl;
        std::cout << "cols     " << this->cols << std::endl;
        std::cout << "lenght   " << this->length << std::endl;
        std::cout << "data     " << this->data << std::endl;
        std::cout << "ext_buff " << this->ext_buff << std::endl;
        std::cout << "sub_mat  " << this->sub_matrix << std::endl;
        std::cout << "stride   " << this->stride << std::endl;
        std::cout << "padding  " << this->padding << std::endl
                  << std::endl;
    }

    /**
     * @brief print matrix header and data
     *
     * Print all information about matrix to the terminal
     * @param[in] show_padding: show padding information
     * @param[in] label: label for the matrix
     */
    void Mat::PrintMatrix(bool show_padding, const std::string &label)
    {
        std::cout << label << "\n";
        std::cout << "rows: " << rows << ", cols: " << cols << "\n";
        std::cout << "stride: " << stride << ", length: " << length << "\n";
        std::cout << "ext_buff: " << ext_buff << ", sub_matrix: " << sub_matrix << "\n";
        std::cout << "data pointer: " << static_cast<void *>(data) << "\n";
        std::cout << "data (row-major):\n";

        int display_cols = show_padding ? stride : cols;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < display_cols; ++j)
            {
                std::cout << std::setw(8) << data[i * stride + j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
    /* === Arithmetic Operators === */
    /**
     * Copy operator
     *
     * @param[in] src: source matrix
     *
     * @return
     *      - matrix copy
     */
    Mat &Mat::operator=(const Mat &m)
    {
        if (this == &m)
        {
            return *this;
        }

        // matrix dimensions not equal, note the dimension will be changed! (for non-sub-matrix)
        if (this->rows != m.rows || this->cols != m.cols)
        {
            // left operand is a sub-matrix - error
            if (this->sub_matrix)
            {
                std::cerr << "operator = Error for sub-matrices: operands matrices dimensions " << this->rows << "x" << this->cols << " and " << m.rows << "x" << m.cols << " do not match" << std::endl;
                return *this;
            }
            if (!this->ext_buff)
            {
                delete[] this->data;
            }
            this->ext_buff = false;
            this->rows = m.rows;
            this->cols = m.cols;
            this->stride = this->cols;
            this->padding = 0;
            this->sub_matrix = false;
            allocate();
        }

        for (int row = 0; row < this->rows; row++)
        {
            memcpy(this->data + (row * this->stride), m.data + (row * m.stride), this->cols * sizeof(float));
        }
        return *this;
    }

    /**
     * += operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: source matrix
     *
     * @return
     *      - result matrix: result += A
     */
    Mat &Mat::operator+=(const Mat &m)
    {
        if ((this->rows != m.rows) || (this->cols != m.cols))
        {
            std::cerr << "operator += Error: matrices do not have equal dimensions" << std::endl;
            return *this;
        }

        if (this->sub_matrix || m.sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_add_f32(this->data, m.data, this->data, this->rows, this->cols, this->padding, m.padding, this->padding, 1, 1, 1);
#else
            tiny_mat_add_f32(this->data, m.data, this->data, this->rows, this->cols, this->padding, m.padding, this->padding, 1, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_add_f32(this->data, m.data, this->data, this->length, 1, 1, 1);
#else
            tiny_vec_add_f32(this->data, m.data, this->data, this->length, 1, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * += operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: constant
     *
     * @return
     *      - result matrix: result += C
     */
    Mat &Mat::operator+=(float C)
    {
        if (this->sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_addc_f32(this->data, this->data, C, this->rows, this->cols, this->padding, this->padding, 1, 1);
#else
            tiny_mat_addc_f32(this->data, this->data, C, this->rows, this->cols, this->padding, this->padding, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_addc_f32_ansi(this->data, this->data, this->length, C, 1, 1);
#else
            tiny_vec_addc_f32(this->data, this->data, this->length, C, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * -= operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: source matrix
     *
     * @return
     *      - result matrix: result -= A
     */

    Mat &Mat::operator-=(const Mat &m)
    {
        if ((this->rows != m.rows) || (this->cols != m.cols))
        {
            std::cerr << "operator -= Error: matrices do not have equal dimensions" << std::endl;
            return *this;
        }

        if (this->sub_matrix || m.sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_sub_f32(this->data, m.data, this->data, this->rows, this->cols, this->padding, m.padding, this->padding, 1, 1, 1);
#else
            tiny_mat_sub_f32(this->data, m.data, this->data, this->rows, this->cols, this->padding, m.padding, this->padding, 1, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_sub_f32(this->data, m.data, this->data, this->length, 1, 1, 1);
#else
            tiny_vec_sub_f32(this->data, m.data, this->data, this->length, 1, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * -= operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: constant
     *
     * @return
     *      - result matrix: result -= C
     */
    Mat &Mat::operator-=(float C)
    {
        if (this->sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_addc_f32(this->data, this->data, -C, this->rows, this->cols, this->padding, this->padding, 1, 1);
#else
            tiny_mat_addc_f32(this->data, this->data, -C, this->rows, this->cols, this->padding, this->padding, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_addc_f32_ansi(this->data, this->data, this->length, -C, 1, 1);
#else
            tiny_vec_addc_f32(this->data, this->data, this->length, -C, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * *= operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: source matrix
     *
     * @return
     *      - result matrix: result -= A
     */
    Mat &Mat::operator*=(const Mat &m)
    {
        if (this->cols != m.rows)
        {
            std::cerr << "operator *= Error: matrices do not have equal dimensions" << std::endl;
            return *this;
        }

        if (this->sub_matrix || m.sub_matrix)
        {
            Mat temp = this->Get(0, this->rows, 0, this->cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mult_ex_f32(temp.data, m.data, this->data, temp.rows, temp.cols, m.cols, temp.padding, m.padding, this->padding);
#else
            tiny_mat_mult_ex_f32(temp.data, m.data, this->data, temp.rows, temp.cols, m.cols, temp.padding, m.padding, this->padding);
#endif
        }
        else
        {
            Mat temp = *this;
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mult_f32(temp.data, m.data, this->data, temp.rows, temp.cols, m.cols);
#else
            tiny_mat_mult_f32(temp.data, m.data, this->data, temp.rows, temp.cols, m.cols);
#endif
        }
        return (*this);
    }

    /**
     * += with constant operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: constant value
     *
     * @return
     *      - result matrix: result *= C
     */
    Mat &Mat::operator*=(float num)
    {
        if (this->sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mulc_f32(this->data, this->data, num, this->rows, this->cols, this->padding, this->padding, 1, 1);
#else
            tiny_mat_mulc_f32(this->data, this->data, num, this->rows, this->cols, this->padding, this->padding, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_mulc_f32_ansi(this->data, this->data, this->length, num, 1, 1);
#else
            tiny_vec_mulc_f32(this->data, this->data, this->length, num, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * /= operator
     *
     * @param[in] B: source matrix
     *
     * @return
     *      - result matrix: result[i,j] = result[i,j]/B[i,j]
     */
    Mat &Mat::operator/=(const Mat &B) // note this is element-wise division
    {
        // dimension check
        if ((this->rows != B.rows) || (this->cols != B.cols))
        {
            std::cerr << "operator /= Error: matrices do not have equal dimensions" << std::endl;
            return *this;
        }

        // check for zero division
        for (int row = 0; row < B.rows; row++)
        {
            for (int col = 0; col < B.cols; col++)
            {
                if (B(row, col) == 0)
                {
                    std::cerr << "operator /= Error: division by zero" << std::endl;
                    return *this;
                }
            }
        }

        for (int row = 0; row < this->rows; row++)
        {
            for (int col = 0; col < this->cols; col++)
            {
                (*this)(row, col) = (*this)(row, col) / B(row, col); // note this is element-wise division
            }
        }
        return (*this);
    }

    /**
     * /= with constant operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: constant value
     *
     * @return
     *      - result matrix: result /= C
     */
    Mat &Mat::operator/=(float num)
    {
        if (num == 0)
        {
            std::cerr << "operator /= Error: division by zero" << std::endl;
            return *this;
        }

        if (this->sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mulc_f32(this->data, this->data, 1 / num, this->rows, this->cols, this->padding, this->padding, 1, 1);
#else
            tiny_mat_multc_f32(this->data, this->data, 1 / num, this->rows, this->cols, this->padding, this->padding, 1, 1);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dsps_mulc_f32_ansi(this->data, this->data, this->length, 1 / num, 1, 1);
#else
            tiny_vec_mulc_f32(this->data, this->data, this->length, 1 / num, 1, 1);
#endif
        }
        return *this;
    }

    /**
     * ^= exponentiation operator
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] num: exponent
     *
     * @return
     *      - result matrix: result = result^num
     */
    Mat Mat::operator^(int num)
    {
        Mat temp(*this);
        return expHelper(temp, num);
    }

    /* === Linear Algebra === */
    /**
     * @brief Normalize the matrix
     *
     * The method normalize the matrix to unit length.
     */
    void Mat::normalize(void) // normalize the matrix
    {
        float sqr_norm = 0;
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                sqr_norm += (*this)(i, j) * (*this)(i, j);
            }
        }
        sqr_norm = 1 / sqrtf(sqr_norm);
        *this *= sqr_norm;
    }

    /**
     * @brief Calculate the matrix norm
     *
     * The method calculate the matrix norm.
     *
     * @return
     *      - result matrix norm
     */
    float Mat::norm(void) // calculate matrix norm
    {
        float sqr_norm = 0;
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                sqr_norm += (*this)(i, j) * (*this)(i, j);
            }
        }
        sqr_norm = sqrtf(sqr_norm);
        return sqr_norm;
    }

    /**
     * @brief Calculate the determinant of the matrix
     *
     * The method calculate the determinant of the matrix.
     *
     * @param n: size of the matrix
     *
     * @return
     *      - result matrix determinant
     */
    float Mat::det(int n)
    {
        float D = 0; // Initialize result

        //  Base case : if matrix contains single element
        if (n == 1)
        {
            return (*this)(0, 0);
        }

        Mat temp(this->rows, this->rows); // To store cofactors

        int sign = 1; // To store sign multiplier

        // Iterate for each element of first row
        for (int f = 0; f < n; f++)
        {
            // Getting Cofactor of A[0][f]
            Mat temp = this->cofactor(0, f, n);
            D += (*this)(0, f) * temp.det(n - 1) * sign;

            // terms are to be added with alternate sign
            sign = -sign;
        }

        return D;
    }

    /**
     * Matrix transpose.
     * Change rows and columns between each other.
     *
     * @return
     *      - transposed matrix
     */
    Mat Mat::t()
    {
        Mat ret(this->cols, this->rows);
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                ret(j, i) = this->data[i * this->stride + j];
            }
        }
        return ret;
    }

    /**
     * Find the inverse matrix
     *
     * @return
     *      - inverse matrix
     */
    Mat Mat::inverse()
    {
        Mat result(this->rows, this->cols);
        // Find determinant of matrix
        float det = this->det(this->rows);
        if (det == 0)
        {
            // std::cout << "Singular matrix, can't find its inverse";
            return result;
        }

        // Find adjoint
        Mat adj = this->adjoint();

        // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                result(i, j) = adj(i, j) / float(det);
            }

        return result;
    }

    /**
     * Find pseudo inverse matrix
     *
     * @return
     *      - inverse matrix
     */
    Mat Mat::pinv()
    {
        Mat I = Mat::eye(this->rows);
        Mat AI = Mat::augment(*this, I);
        Mat U = AI.gaussianEliminate();
        Mat IAInverse = U.rowReduceFromGaussian();
        Mat AInverse(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                AInverse(i, j) = IAInverse(i, j + this->cols);
            }
        }
        return AInverse;
    }

    /**
     * @brief   Gaussian Elimination
     *
     * Gaussian Elimination of matrix
     *
     * @return
     *      - result matrix
     */
    Mat Mat::gaussianEliminate()
    {
        Mat Ab(*this);
        int rows = Ab.rows;
        int cols = Ab.cols;
        int Acols = cols - 1;

        int i = 0; // row tracker
        int j = 0; // column tracker

        // iterate through the rows
        while (i < rows)
        {
            // find a pivot for the row
            bool pivot_found = false;
            while (j < Acols && !pivot_found)
            {
                if (Ab(i, j) != 0)
                { // pivot not equal to 0
                    pivot_found = true;
                }
                else
                { // check for a possible swap
                    int max_row = i;
                    float max_val = 0;
                    for (int k = i + 1; k < rows; ++k)
                    {
                        float cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
                        if (cur_abs > max_val)
                        {
                            max_row = k;
                            max_val = cur_abs;
                        }
                    }
                    if (max_row != i)
                    {
                        Ab.swapRows(max_row, i);
                        pivot_found = true;
                    }
                    else
                    {
                        j++;
                    }
                }
            }

            // perform elimination as normal if pivot was found
            if (pivot_found)
            {
                for (int t = i + 1; t < rows; ++t)
                {
                    for (int s = j + 1; s < cols; ++s)
                    {
                        Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
                        if (Ab(t, s) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && Ab(t, s) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
                        {
                            Ab(t, s) = 0;
                        }
                    }
                    Ab(t, j) = 0;
                }
            }

            i++;
            j++;
        }

        return Ab;
    }

    /**
     * Row reduction for Gaussian elimination
     *
     * @return
     *      - result matrix
     */
    Mat Mat::rowReduceFromGaussian()
    {
        Mat R(*this);
        int rows = R.rows;
        int cols = R.cols;

        int i = rows - 1; // row tracker
        int j = cols - 2; // column tracker

        // iterate through every row
        while (i >= 0)
        {
            // find the pivot column
            int k = j - 1;
            while (k >= 0)
            {
                if (R(i, k) != 0)
                {
                    j = k;
                }
                k--;
            }

            // zero out elements above pivots if pivot not 0
            if (R(i, j) != 0)
            {
                for (int t = i - 1; t >= 0; --t)
                {
                    for (int s = 0; s < cols; ++s)
                    {
                        if (s != j)
                        {
                            R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                            if (R(t, s) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && R(t, s) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
                            {
                                R(t, s) = 0;
                            }
                        }
                    }
                    R(t, j) = 0;
                }

                // divide row by pivot
                for (int k = j + 1; k < cols; ++k)
                {
                    R(i, k) = R(i, k) / R(i, j);
                    if (R(i, k) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && R(i, k) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
                    {
                        R(i, k) = 0;
                    }
                }
                R(i, j) = 1;
            }

            i--;
            j--;
        }

        return R;
    }

    /* === Static Utility Functions === */

    /**
     * Create identity matrix.
     * Create a square matrix and fill diagonal with 1.
     *
     * @param[in] size: matrix size
     *
     * @return
     *      - matrix [N]x[N] with 1 in diagonal
     */
    Mat Mat::eye(int size)
    {
        Mat temp(size, size);
        for (int i = 0; i < temp.rows; ++i)
        {
            for (int j = 0; j < temp.cols; ++j)
            {
                if (i == j)
                {
                    temp(i, j) = 1;
                }
                else
                {
                    temp(i, j) = 0;
                }
            }
        }
        return temp;
    }
    
    /**
     * Create matrix with all elements 1.
     * Create a square matrix and fill all elements with 1.
     *
     * @param[in] size: matrix size
     *
     * @return
     *      - matrix [N]x[N] with 1 in all elements
     */
    Mat Mat::ones(int size)
    {
        return (ones(size, size));
    }

    /**
     * Create matrix with all elements 1.
     * Create a matrix and fill all elements with 1.
     *
     * @param[in] rows: matrix rows
     * @param[in] cols: matrix cols
     *
     * @return
     *      - matrix [N]x[N] with 1 in all elements
     */
    Mat Mat::ones(int rows, int cols)
    {
        Mat temp(rows, cols);
        for (int row = 0; row < temp.rows; ++row)
        {
            for (int col = 0; col < temp.cols; ++col)
            {
                temp(row, col) = 1;
            }
        }
        return temp;
    }

    /**
     * @brief   Solve the matrix
     *
     * Solve matrix. Find roots for the matrix A*x = b
     *
     * @param[in] A: matrix [N]x[N] with input coefficients
     * @param[in] b: vector [N]x[1] with result values
     *
     * @return
     *      - matrix [N]x[1] with roots
     */
    Mat Mat::solve(Mat A, Mat b)
    {
        // Gaussian elimination
        for (int i = 0; i < A.rows; ++i)
        {
            if (A(i, i) == 0)
            {
                // pivot 0 - error
                std::cerr << "Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again." << std::endl;
                Mat err_result(0, 0);
                return err_result;
            }
            float a_ii = 1 / A(i, i);
            for (int j = i + 1; j < A.rows; ++j)
            {
                float a_ji = A(j, i) * a_ii;
                for (int k = i + 1; k < A.cols; ++k)
                {
                    A(j, k) -= A(i, k) * a_ji;
                    if ((A(j, k) < TINY_MATH_MIN_POSITIVE_INPUT_F32) && (A(j, k) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32))
                    {
                        A(j, k) = 0;
                    }
                }
                b(j, 0) -= b(i, 0) * a_ji;
                if (A(j, 0) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && A(j, 0) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
                {
                    A(j, 0) = 0;
                }
                A(j, i) = 0;
            }
        }

        // Back substitution
        Mat x(b.rows, 1);
        x((x.rows - 1), 0) = b((x.rows - 1), 0) / A((x.rows - 1), (x.rows - 1));
        if (x((x.rows - 1), 0) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && x((x.rows - 1), 0) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
        {
            x((x.rows - 1), 0) = 0;
        }
        for (int i = x.rows - 2; i >= 0; --i)
        {
            float sum = 0;
            for (int j = i + 1; j < x.rows; ++j)
            {
                sum += A(i, j) * x(j, 0);
            }
            x(i, 0) = (b(i, 0) - sum) / A(i, i);
            if (x(i, 0) < TINY_MATH_MIN_POSITIVE_INPUT_F32 && x(i, 0) > -1 * TINY_MATH_MIN_POSITIVE_INPUT_F32)
            {
                x(i, 0) = 0;
            }
        }
        return x;
    }

    /**
     * @brief   Band solve the matrix
     *
     * Solve band matrix. Find roots for the matrix A*x = b with bandwidth k.
     *
     * @param[in] A: matrix [N]x[N] with input coefficients
     * @param[in] b: vector [N]x[1] with result values
     * @param[in] k: upper bandwidth value
     *
     * @return
     *      - matrix [N]x[1] with roots
     */
    Mat Mat::bandSolve(Mat A, Mat b, int k)
    {
        // optimized Gaussian elimination
        int bandsBelow = (k - 1) / 2;
        for (int i = 0; i < A.rows; ++i)
        {
            if (A(i, i) == 0)
            {
                // pivot 0 - error
                std::cerr << "Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again." << std::endl;
                Mat err_result(b.rows, 1);
                memset(err_result.data, 0, b.rows * sizeof(float));
                return err_result;
            }
            float a_ii = 1 / A(i, i);
            for (int j = i + 1; j < A.rows && j <= i + bandsBelow; ++j)
            {
                int k = i + 1;
                while ((k < A.cols) && (fabs(A(j, k)) > TINY_MATH_MIN_POSITIVE_INPUT_F32))
                {
                    A(j, k) -= A(i, k) * (A(j, i) * a_ii);
                    k++;
                }
                b(j, 0) -= b(i, 0) * (A(j, i) * a_ii);
                A(j, i) = 0;
            }
        }

        // Back substitution
        Mat x(b.rows, 1);
        x((x.rows - 1), 0) = b((x.rows - 1), 0) / A((x.rows - 1), (x.rows - 1));
        for (int i = x.rows - 2; i >= 0; --i)
        {
            float sum = 0;
            for (int j = i + 1; j < x.rows; ++j)
            {
                sum += A(i, j) * x(j, 0);
            }
            x(i, 0) = (b(i, 0) - sum) / A(i, i);
        }

        return x;
    }

    /**
     * @brief   Solve the matrix
     *
     * Different way to solve the matrix. Find roots for the matrix A*x = y
     *
     * @param[in] A: matrix [N]x[N] with input coefficients
     * @param[in] y: vector [N]x[1] with result values
     *
     * @return
     *      - matrix [N]x[1] with roots
     */
    Mat Mat::roots(Mat A, Mat y)
    {
        int n = A.cols + 1;

        Mat result(y.rows, 1);

        Mat g_m = Mat::augment(A, y);
        for (int j = 0; j < A.cols; j++)
        {
            float g_jj = 1 / g_m(j, j);
            for (int i = 0; i < A.cols; i++)
            {
                if (i != j)
                {
                    float c = g_m(i, j) * g_jj;
                    for (int k = 0; k < n; k++)
                    {
                        g_m(i, k) = g_m(i, k) - c * g_m(j, k);
                    }
                }
            }
        }
        for (int i = 0; i < A.rows; i++)
        {
            result(i, 0) = g_m(i, A.cols) / g_m(i, i);
        }
        return result;
    }

    /**
     * @brief   Dotproduct of two vectors
     *
     * The method returns dotproduct of two vectors
     *
     * @param[in] A: Input vector A Nx1
     * @param[in] B: Input vector B Nx1
     *
     * @return
     *      - dotproduct value
     */
    float Mat::dotProduct(Mat a, Mat b)
    {
        float sum = 0;
        for (int i = 0; i < a.rows; ++i)
        {
            sum += (a(i, 0) * b(i, 0));
        }
        return sum;
    }

    /**
     * @brief   Augmented matrices (concatenate two matrices horizontally)
     *
     * Augmented matrices
     *
     * @param[in] A: Input vector A MxN
     * @param[in] B: Input vector B MxK
     *
     * @return
     *      - Augmented matrix Mx(N+K)
     */
    Mat Mat::augment(Mat A, Mat B)
    {
        Mat AB(A.rows, A.cols + B.cols);
        for (int i = 0; i < AB.rows; ++i)
        {
            for (int j = 0; j < AB.cols; ++j)
            {
                if (j < A.cols)
                {
                    AB(i, j) = A(i, j);
                }
                else
                {
                    AB(i, j) = B(i, j - A.cols);
                }
            }
        }
        return AB;
    }

    /* === Private Utility Functions === */
    /**
     * @brief   Calculate cofactor matrix
     *
     * Calculate cofactor matrix of the matrix
     *
     * @param[in] row: row position
     * @param[in] col: column position
     * @param[in] n: size of the matrix
     *
     * @return
     *      - cofactor matrix
     */
    Mat Mat::cofactor(int row, int col, int n)
    {
        int i = 0, j = 0;
        Mat result(n, n);
        // Looping for each element of the matrix
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                //  Copying into temporary matrix only those element
                //  which are not in given row and column
                if (r != row && c != col)
                {
                    result(i, j++) = (*this)(r, c);

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == this->rows - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return result;
    }

    /**
     * @brief   Calculate adjoint matrix
     *
     * Calculate adjoint matrix of the matrix
     *
     * @return
     *      - adjoint matrix
     */
    Mat Mat::adjoint()
    {
        Mat adj(this->rows, this->cols);
        if (this->rows == 1)
        {
            adj(0, 0) = 1;
            return adj;
        }

        // temp is used to store cofactors of A(,)
        int sign = 1;
        Mat temp(this->rows, this->cols);

        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                // Get cofactor of A(i,j)
                temp = this->cofactor(i, j, this->rows);

                // sign of adj(j,i) positive if sum of row
                // and column indexes is even.
                sign = ((i + j) % 2 == 0) ? 1 : -1;

                // Interchanging rows and columns to get the
                // transpose of the cofactor matrix
                adj(j, i) = (sign) * (temp.det(this->rows - 1));
            }
        }
        return adj;
    }

    /**
     * @brief   Calculate matrix exponential
     *
     * Calculate matrix exponential of the matrix
     *
     * @param[in] m: input matrix
     * @param[in] num: number of iterations
     *
     * @return
     *      - matrix exponential
     */
    Mat Mat::expHelper(const Mat &m, int num)
    {
        if (num == 0)
        {
            return Mat::eye(m.rows);
        }
        else if (num == 1)
        {
            return m;
        }
        else if (num % 2 == 0)
        { // num is even
            return expHelper(m * m, num / 2);
        }
        else
        { // num is odd
            return m * expHelper(m * m, (num - 1) / 2);
        }
    }
    /* === Stream Operators === */

    /* === Stream Operators === */
    /**
     * Print matrix to the standard iostream.
     * @param[in] os: output stream
     * @param[in] m: matrix to print
     *
     * @return
     *      - output stream
     */
    ostream &operator<<(ostream &os, const Mat &m)
    {
        for (int i = 0; i < m.rows; ++i)
        {
            os << m(i, 0);
            for (int j = 1; j < m.cols; ++j)
            {
                os << " " << m(i, j);
            }
            os << endl;
        }
        return os;
    }

    /**
     * Print rectangular ROI to the standard iostream.
     * @param[in] os: output stream
     * @param[in] rect: ROI
     *
     * @return
     *      - output stream
     */
    ostream &operator<<(ostream &os, const Mat::Rect &rect)
    {
        os << "row start " << rect.y << endl;
        os << "col start " << rect.x << endl;
        os << "row count " << rect.height << endl;
        os << "col count " << rect.width << endl;

        return os;
    }
    
    /**
     * Fill the matrix from iostream.
     * @param[in] is: input stream
     * @param[in] m: matrix to fill
     *
     * @return
     *      - input stream
     */
    istream &operator>>(istream &is, Mat &m)
    {
        for (int i = 0; i < m.rows; ++i)
        {
            for (int j = 0; j < m.cols; ++j)
            {
                is >> m(i, j);
            }
        }
        return is;
    }

    /* === Global Arithmetic Operators === */
    /**
     * + operator, sum of two matrices
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A+B
     */
    Mat operator+(const Mat &m1, const Mat &m2)
    {
        if ((m1.rows != m2.rows) || (m1.cols != m2.cols))
        {
            std::cerr << "operator + Error: matrices do not have equal dimensions" << std::endl;
            Mat err_ret;
            return err_ret;
        }

        if (m1.sub_matrix || m2.sub_matrix)
        {
            Mat temp(m1.rows, m2.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_add_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m1.padding, m2.padding, temp.padding, 1, 1, 1);
#else
            tiny_mat_add_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m1.padding, m2.padding, temp.padding, 1, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m1);
            return (temp += m2);
        }
    }

    /**
     * + operator, sum of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: Input constant
     *
     * @return
     *     - result matrix A+C
     */
    Mat operator+(const Mat &m, float C)
    {
        if (m.sub_matrix)
        {
            Mat temp(m.rows, m.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_addc_f32(m.data, temp.data, C, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#else
            tiny_mat_addc_f32(m.data, temp.data, C, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m);
            return (temp += C);
        }
    }

    /**
     * - operator, subtraction of two matrices
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A-B
     */
    Mat operator-(const Mat &m1, const Mat &m2)
    {
        if ((m1.rows != m2.rows) || (m1.cols != m2.cols))
        {
            std::cerr << "operator - Error: matrices do not have equal dimensions" << std::endl;
            Mat err_ret;
            return err_ret;
        }

        if (m1.sub_matrix || m2.sub_matrix)
        {
            Mat temp(m1.rows, m1.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_sub_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m1.padding, m2.padding, temp.padding, 1, 1, 1);
#else
            tiny_mat_sub_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m1.padding, m2.padding, temp.padding, 1, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m1);
            return (temp -= m2);
        }
    }

    /**
     * - operator, subtraction of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: Input constant
     *
     * @return
     *     - result matrix A-C
     */
    Mat operator-(const Mat &m, float C)
    {
        if (m.sub_matrix)
        {
            Mat temp(m.rows, m.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_addc_f32(m.data, temp.data, -C, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#else
            tiny_mat_addc_f32(m.data, temp.data, -C, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m);
            return (temp -= C);
        }
    }

    /**
     * * operator, multiplication of two matrices.
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix A*B
     */
    Mat operator*(const Mat &m1, const Mat &m2)
    {
        if (m1.cols != m2.rows)
        {
            std::cerr << "operator * Error: matrices do not have correct dimensions" << std::endl;
            Mat err_ret;
            return err_ret;
        }
        Mat temp(m1.rows, m2.cols);

        if (m1.sub_matrix || m2.sub_matrix)
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mult_ex_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m2.cols, m1.padding, m2.padding, temp.padding);
#else
            tiny_mat_mult_ex_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m2.cols, m1.padding, m2.padding, temp.padding);
#endif
        }
        else
        {
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mult_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m2.cols);
#else
            tiny_mat_mult_f32(m1.data, m2.data, temp.data, m1.rows, m1.cols, m2.cols);
#endif
        }

        return temp;
    }

    /**
     * * operator, multiplication of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: floating point value
     *
     * @return
     *     - result matrix A*B
     */
    Mat operator*(const Mat &m, float num)
    {
        if (m.sub_matrix)
        {
            Mat temp(m.rows, m.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mulc_f32(m.data, temp.data, num, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#else
            tiny_mat_mulc_f32(m.data, temp.data, num, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m);
            return (temp *= num);
        }
    }
    
    /**
     * * operator, multiplication of matrix with constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] C: floating point value
     * @param[in] A: Input matrix A
     *
     * @return
     *     - result matrix C*A
     */
    Mat operator*(float num, const Mat &m)
    {
        return (m * num);
    }

    /**
     * / operator, divide of matrix by constant
     * The operator use DSP optimized implementation of multiplication.
     *
     * @param[in] A: Input matrix A
     * @param[in] C: floating point value
     *
     * @return
     *     - result matrix A/C
     */
    Mat operator/(const Mat &m, float num)
    {
        if (m.sub_matrix)
        {
            Mat temp(m.rows, m.cols);
#if MCU_PLATFORM_SELECTED == MCU_PLATFORM_ESP32
            dspm_mulc_f32(m.data, temp.data, 1 / num, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#else
            tiny_mat_multc_f32(m.data, temp.data, 1 / num, m.rows, m.cols, m.padding, temp.padding, 1, 1);
#endif
            return temp;
        }
        else
        {
            Mat temp(m);
            return (temp /= num);
        }
    }

    /**
     * / operator, divide matrix A by matrix B (element-wise)
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *     - result matrix C, where C[i,j] = A[i,j]/B[i,j]
     */
    Mat operator/(const Mat &A, const Mat &B)
    {
        if ((A.rows != B.rows) || (A.cols != B.cols))
        {
            std::cerr << "operator / Error: matrices do not have equal dimensions" << std::endl;
            Mat err_ret;
            return err_ret;
        }

        Mat temp(A.rows, A.cols);
        for (int row = 0; row < A.rows; row++)
        {
            for (int col = 0; col < A.cols; col++)
            {
                temp(row, col) = A(row, col) / B(row, col);
            }
        }
        return temp;
    }

    /**
     * == operator, compare two matrices
     *
     * @param[in] A: Input matrix A
     * @param[in] B: Input matrix B
     *
     * @return
     *      - true if matrices are the same
     *      - false if matrices are different
     */
    bool operator==(const Mat &m1, const Mat &m2)
    {
        if ((m1.cols != m2.cols) || (m1.rows != m2.rows))
        {
            return false;
        }

        for (int row = 0; row < m1.rows; row++)
        {
            for (int col = 0; col < m1.cols; col++)
            {
                if (m1(row, col) != m2(row, col))
                {
                    std::cout << "operator == Error: " << row << " " << col << ", m1.data=" << m1(row, col) << ", m2.data=" << m2(row, col) << std::endl;
                    return false;
                }
            }
        }

        return true;
    }



}
```