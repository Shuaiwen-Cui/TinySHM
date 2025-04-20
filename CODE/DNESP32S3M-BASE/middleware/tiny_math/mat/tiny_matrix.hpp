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
         * @brief Destroy the Mat object, freeing internal memory
         */
        ~Mat();

        /**
         * @brief Allocate internal memory buffer
         */
        void allocate();
    };
}