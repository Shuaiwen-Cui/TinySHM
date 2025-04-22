/**
 * @file tiny_matrix.hpp
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the header file for the submodule matrix (advanced matrix operations) of the tiny_math middleware.
 * @version 1.0
 * @date 2025-04-17
 * @copyright Copyright (c) 2025
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
        // Matrix metadata
        int rows;    /*!< Amount of rows*/
        int cols;    /*!< Amount of columns*/
        int stride;  /*!< Stride = (number of elements in a row) + padding*/
        int padding; /*!< Padding between 2 rows*/
        int length;  /*!< Total amount of data in data array*/

        // Matrix data pointer and flags
        float *data;     /*!< Buffer with matrix data*/
        bool ext_buff;   /*!< Flag indicates that matrix use external buffer*/
        bool sub_matrix; /*!< Flag indicates that matrix is a subset of another matrix*/

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
         * Allocate matrix with undefined size.
         */
        Mat();

        /**
         * @brief Destroy the Mat object, freeing internal memory
         */
        ~Mat();

        /**
         * @brief Allocate internal memory buffer
         */
        void allocate();

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
        Mat getROI(const Mat::Rect &rect);

        /**
         * Make copy of matrix.
         * @param[in] src: source matrix
         * @param[in] row_pos: start row position of destination matrix
         * @param[in] col_pos: start col position of destination matrix
         */
        void Copy(const Mat &src, int row_pos, int col_pos);

        /**
         * @brief copy header of matrix
         *
         * Make a shallow copy of matrix (no data copy)
         * @param[in] src: source matrix
         */
        void CopyHead(const Mat &src);

        /**
         * @brief print matrix header
         *
         * Print all information about matrix to the terminal
         * @param[in] src: source matrix
         */
        void PrintHead(void);
        /**
         * @brief print matrix header and data
         *
         * Print all information about matrix to the terminal
         * @param[in] show_padding: show padding information
         * @param[in] label: label for the matrix
         */
        void PrintMatrix(bool show_padding, const std::string &label);

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
        Mat Get(const Mat::Rect &rect);

        /**
         * Copy operator
         *
         * @param[in] src: source matrix
         *
         * @return
         *      - matrix copy
         */
        Mat &operator=(const Mat &src);

        /**
         * Access to the matrix elements.
         * @param[in] row: row position
         * @param[in] col: column position
         *
         * @return
         *      - element of matrix M[row][col]
         */
        inline float &operator()(int row, int col)
        {
            return data[row * this->stride + col];
        }
        /**
         * Access to the matrix elements.
         * @param[in] row: row position
         * @param[in] col: column position
         *
         * @return
         *      - element of matrix M[row][col]
         */
        inline const float &operator()(int row, int col) const
        {
            return data[row * this->stride + col];
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
    Mat  operator^(int C);        

    /**
     * Swap two rows between each other.
     * @param[in] row1: position of first row
     * @param[in] row2: position of second row
     */
    void swapRows(int row1, int row2);
    };

    /**
     * Matrix transpose.
     * Change rows and columns between each other.
     *
     * @return
     *      - transposed matrix
     */
    Mat t();

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
     * The method fill 0 to the matrix structure.
     *
     */
    void clear(void);

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
     * Normalizes the vector, i.e. divides it by its own norm.
     * If it's matrix, calculate matrix norm
     *
     */
    void normalize(void);

    /**
     * Return  norm of the vector.
     * If it's matrix, calculate matrix norm
     *
     * @return
     *      - matrix norm
     */
    float norm(void);
}