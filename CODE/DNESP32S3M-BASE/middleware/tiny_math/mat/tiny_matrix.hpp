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
         * ^= xor with constant operator
         * The operator use DSP optimized implementation of multiplication.
         * @param[in] C: constant value
         *
         * @return
         *      - result matrix: result ^= C
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