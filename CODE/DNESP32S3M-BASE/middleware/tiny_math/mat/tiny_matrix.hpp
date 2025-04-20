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

    };
}