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

/* LIBRARIE CONTENTS */
namespace tiny
{
    /* === Rectangular ROI Structure === */

    Mat::ROI::ROI(int pos_x, int pos_y, int width, int height)
    {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
    }

    void Mat::ROI::resize_roi(int pos_x, int pos_y, int width, int height)
    {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
    }

    int Mat::ROI::area_roi(void) const
    {
        return this->width * this->height;
    }

    /* === Printing Functions === */
    /**
     * @name Mat::PrintHead()
     * @brief Print the header of the matrix.
     */
    void Mat::print_info(void)
    {
        std::cout << "Matrix Info >>>\n";
        std::cout << "rows            " << this->row << std::endl;
        std::cout << "cols            " << this->col << std::endl;
        std::cout << "elements        " << this->element << std::endl;
        std::cout << "paddings        " << this->pad << std::endl;
        std::cout << "stride          " << this->stride << std::endl;
        std::cout << "memory          " << this->memory << std::endl;
        if (this->data != nullptr)
        {
            std::cout << "data pointer    " << static_cast<void *>(data) << std::endl;
        }
        else
        {
            std::cout << "data pointer    nullptr" << std::endl;
        }
        if (this->temp != nullptr)
        {
            std::cout << "temp pointer    " << static_cast<void *>(temp) << std::endl;
        }
        else
        {
            std::cout << "temp pointer    nullptr" << std::endl;
        }
        std::cout << "ext_buff        " << this->ext_buff << std::endl;
        std::cout << "sub_matrix      " << this->sub_matrix << std::endl;
        std::cout << "<<< Matrix Info\n";
        std::cout << std::endl;
    }

    /**
     * @name Mat::print_matrix()
     * @brief Print the matrix elements.
     *
     * @param show_padding If true, print the padding elements as well.
     */
    void Mat::print_matrix(bool show_padding)
    {
        std::cout << "Matrix Elements >>>\n";
        for (int i = 0; i < this->row; ++i)
        {
            // print the non-padding elements
            for (int j = 0; j < this->col; ++j)
            {
                std::cout << std::setw(12) << this->data[i * this->stride + j] << " ";
            }

            // if padding is enabled, print the padding elements
            if (show_padding)
            {
                // print a separator first
                std::cout << "      |";

                // print the padding elements
                for (int j = this->col; j < this->stride; ++j)
                {
                    if (j == this->col)
                    {
                        std::cout << std::setw(7) << this->data[i * this->stride + j] << " ";
                    }
                    else
                    {
                        // print the padding elements
                        std::cout << std::setw(12) << this->data[i * this->stride + j] << " ";
                    }
                }
            }

            // print a new line after each row
            std::cout << "\n";
        }

        std::cout << "<<< Matrix Elements\n";
        std::cout << std::endl;
    }

    /* === Constructors & Destructor === */
    // memory allocation
    /**
     * @name Mat::allocate()
     * @brief Allocate memory for the matrix according to the memory required.
     */
    void Mat::alloc_mem()
    {
        this->ext_buff = false;
        this->memory = this->row * this->stride;
        this->data = new float[this->memory];
    }

    /**
     * @name Mat::Mat()
     * @brief Constructor - default constructor: create a 1x1 matrix with only a zero element.
     */
    Mat::Mat()
    {
        this->row = 1;
        this->col = 1;
        this->pad = 0;
        this->stride = 1;
        this->element = 1;
        this->memory = 1;
        this->data = nullptr;
        this->temp = nullptr;
        this->ext_buff = false;
        this->sub_matrix = false;
        alloc_mem();
        if (this->data == nullptr)
        {
            std::cerr << "[Error] Memory allocation failed in alloc_mem()\n";
        }
        std::memset(this->data, 0, this->memory * sizeof(float));
    }

    /**
     * @name Mat::Mat(int rows, int cols)
     * @brief Constructor - create a matrix with the specified number of rows and columns.
     *
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Mat::Mat(int rows, int cols)
    {
        this->row = rows;
        this->col = cols;
        this->pad = 0;
        this->stride = cols;
        this->element = rows * cols;
        this->memory = rows * cols;
        this->data = nullptr;
        this->temp = nullptr;
        this->ext_buff = false;
        this->sub_matrix = false;
        alloc_mem();
        if (this->data == nullptr)
        {
            std::cerr << "[Error] Memory allocation failed in alloc_mem()\n";
        }
        std::memset(this->data, 0, this->memory * sizeof(float));
    }
    /**
     * @name Mat::Mat(int rows, int cols, int stride)
     * @brief Constructor - create a matrix with the specified number of rows, columns and stride.
     *
     * @param rows Number of rows
     * @param cols Number of columns
     * @param stride Stride (number of elements in a row)
     */
    Mat::Mat(int rows, int cols, int stride)
    {
        this->row = rows;
        this->col = cols;
        this->pad = stride - cols;
        this->stride = stride;
        this->element = rows * cols;
        this->memory = rows * stride;
        this->data = nullptr;
        this->temp = nullptr;
        this->ext_buff = false;
        this->sub_matrix = false;
        alloc_mem();
        if (this->data == nullptr)
        {
            std::cerr << "[Error] Memory allocation failed in alloc_mem()\n";
        }
        std::memset(this->data, 0, this->memory * sizeof(float));
    }

    /**
     * @name Mat::Mat(float *data, int rows, int cols)
     * @brief Constructor - create a matrix with the specified number of rows, columns and external data.
     *
     * @param data Pointer to external data buffer
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Mat::Mat(float *data, int rows, int cols)
    {
        this->row = rows;
        this->col = cols;
        this->pad = 0;
        this->stride = cols;
        this->element = rows * cols;
        this->memory = rows * cols; // for external data, this item is actually not used
        this->data = data;
        this->temp = nullptr;
        this->ext_buff = true;
        this->sub_matrix = false;
    }

    /**
     * @name Mat::Mat(float *data, int rows, int cols, int stride)
     * @brief Constructor - create a matrix with the specified number of rows, columns and external data.
     *
     * @param data Pointer to external data buffer
     * @param rows Number of rows
     * @param cols Number of columns
     * @param stride Stride (number of elements in a row)
     */
    Mat::Mat(float *data, int rows, int cols, int stride)
    {
        this->row = rows;
        this->col = cols;
        this->pad = stride - cols;
        this->stride = stride;
        this->element = rows * cols;
        this->memory = rows * stride; // for external data, this item is actually not used
        this->data = data;
        this->temp = nullptr;
        this->ext_buff = true;
        this->sub_matrix = false;
    }

    /**
     * @name Mat::Mat(const Mat &src)
     * @brief Copy constructor - create a matrix with the same properties as the source matrix.
     *
     * @param src Source matrix
     */
    Mat::Mat(const Mat &src)
    {
        this->row = src.row;
        this->col = src.col;
        this->pad = src.pad;
        this->stride = src.stride;
        this->element = src.element;
        this->memory = src.memory;
        this->data = nullptr;
        this->temp = nullptr;
        this->ext_buff = false;
        this->sub_matrix = false;

        if (src.data != nullptr)
        {
            alloc_mem();
            if (this->data == nullptr)
            {
                std::cerr << "[Error] Memory allocation failed in alloc_mem()\n";
            }
            std::memcpy(this->data, src.data, this->memory * sizeof(float));
        }
    }

    /**
     * @name ~Mat()
     * @brief Destructor - free the memory allocated for the matrix.
     */
    Mat::~Mat()
    {
        if (!this->ext_buff && this->data)
        {
            delete[] this->data;
        }
        if (this->temp)
        {
            delete[] this->temp;
        }
    }

    /* === Element Access === */
    // Already defined by inline functions in the header file

    /* === Data Manipulation === */

    /**
     * @name Mat::copy_paste(const Mat &src, int row_pos, int col_pos)
     * @brief Copy the elements of the source matrix into the destination matrix. The dimension of the current matrix must be larger than the source matrix.
     * @brief This one does not share memory with the source matrix.
     *
     * @param src Source matrix
     * @param row_pos Start row position of the destination matrix
     * @param col_pos Start column position of the destination matrix
     */
    tiny_error_t Mat::copy_paste(const Mat &src, int row_pos, int col_pos)
    {
        if ((row_pos + src.row) > this->row)
        {
            std::cerr << "[Error] Invalid row position " << std::endl;
            return TINY_ERR_INVALID_ARG;
        }
        if ((col_pos + src.col) > this->col)
        {
            std::cerr << "[Error] Invalid column position " << std::endl;
            return TINY_ERR_INVALID_ARG;
        }
        for (size_t r = 0; r < src.row; r++)
        {
            memcpy(&this->data[(r + row_pos) * this->stride + col_pos], &src.data[r * src.col], src.col * sizeof(float));
        }

        return TINY_OK;
    }

    /**
     * @name Mat::copy_head(const Mat &src)
     * @brief Copy the header of the source matrix into the destination matrix. The data pointer is shared.
     *
     * @param src Source matrix
     */
    tiny_error_t Mat::copy_head(const Mat &src)
    {
        if (!this->ext_buff)
        {
            delete[] this->data;
        }
        this->row = src.row;
        this->col = src.col;
        this->element = src.element;
        this->pad = src.pad;
        this->stride = src.stride;
        this->memory = src.memory;
        this->data = src.data;
        this->temp = src.temp;
        this->ext_buff = src.ext_buff;
        this->sub_matrix = src.sub_matrix;

        return TINY_OK;
    }

    /**
     * @name Mat::get_roi(int start_row, int start_col, int roi_rows, int roi_cols, int stride)
     * @brief Make a shallow copy of ROI matrix. | Make a view of the ROI matrix. Low level function.
     *
     * @param start_row Start row position of source matrix to copy
     * @param start_col Start column position of source matrix to copy
     * @param roi_rows Size of row elements of source matrix to copy
     * @param roi_cols Size of column elements of source matrix to copy
     * @param stride Number of cols + padding between 2 rows
     *
     * @return result matrix size row_size x col_size
     */
    Mat Mat::get_roi(int start_row, int start_col, int roi_rows, int roi_cols, int stride)
    {
        Mat result(this->data, roi_rows, roi_cols, 0);

        if ((start_row + roi_rows) > this->row)
        {
            return result;
        }

        if ((start_col + roi_cols) > this->col)
        {
            return result;
        }

        const int ptr_move = start_row * this->col + start_col;
        float *new_data_ptr = this->data + ptr_move;

        result.data = new_data_ptr;
        result.stride = stride;
        result.pad = result.stride - result.col;

        return result;
    }

    /**
     * @name Mat::get_roi(int start_row, int start_col, int roi_rows, int roi_cols)
     * @brief Make a shallow copy of ROI matrix. | Make a view of the ROI matrix. Without stride.
     *
     * @param start_row Start row position of source matrix to copy
     * @param start_col Start column position of source matrix to copy
     * @param roi_rows Size of row elements of source matrix to copy
     * @param roi_cols Size of column elements of source matrix to copy
     *
     * @return result matrix size row_size x col_size
     */
    Mat Mat::get_roi(int start_row, int start_col, int roi_rows, int roi_cols)
    {
        return (get_roi(start_row, start_col, roi_rows, roi_cols, this->col));
    }

    /**
     * @name Mat::get_roi(const Mat::ROI &roi)
     * @brief Make a shallow copy of ROI matrix. | Make a view of the ROI matrix. Using ROI structure.
     *
     * @param roi Rectangular area of interest
     *
     * @return result matrix size row_size x col_size
     */
    Mat Mat::get_roi(const Mat::ROI &roi)
    {
        return (get_roi(roi.pos_y, roi.pos_x, roi.height, roi.width));
    }

    /**
     * @name Mat::copy_roi(int start_row, int start_col, int height, int width)
     * @brief Make a deep copy of matrix.
     *
     * @param start_row Start row position of source matrix to copy
     * @param start_col Start column position of source matrix to copy
     * @param height Size of row elements of source matrix to copy
     * @param width Size of column elements of source matrix to copy
     *
     * @return result matrix size row_size x col_size
     */
    Mat Mat::copy_roi(int start_row, int start_col, int height, int width)
    {
        Mat result(height, width);

        if ((start_row + height) > this->row)
        {
            return result;
        }
        if ((start_col + width) > this->col)
        {
            return result;
        }

        for (size_t r = 0; r < result.row; r++)
        {
            memcpy(&result.data[r * result.col], &this->data[(r + start_row) * this->stride + start_col], result.col * sizeof(float));
        }
        return result;
    }

    /**
     * @name Mat::copy_roi(const Mat::ROI &roi)
     * @brief Make a deep copy of matrix. Using ROI structure.
     *
     * @param roi Rectangular area of interest
     *
     * @return result matrix size row_size x col_size
     */
    Mat Mat::copy_roi(const Mat::ROI &roi)
    {
        return (copy_roi(roi.pos_y, roi.pos_x, roi.height, roi.width));
    }

    /**
     * @name Mat::block(int start_row, int start_col, int block_rows, int block_cols)
     * @brief Get a block of matrix.
     *
     * @param start_row
     * @param start_col
     * @param block_rows
     * @param block_cols
     * @return Mat
     */
    Mat Mat::block(int start_row, int start_col, int block_rows, int block_cols)
    {
        Mat result(block_rows, block_cols);
        for (int i = 0; i < block_rows; ++i)
        {
            for (int j = 0; j < block_cols; ++j)
            {
                result(i, j) = (*this)(start_row + i, start_col + j);
            }
        }
        return result;
    }

    /**
     * @name Mat::swap_rows(int row1, int row2)
     * @brief Swap two rows of the matrix.
     *
     * @param row1 The index of the first row to swap
     * @param row2 The index of the second row to swap
     */
    void Mat::swap_rows(int row1, int row2)
    {
        if ((this->row <= row1) || (this->row <= row2))
        {
            std::cerr << "Error: row index out of range" << std::endl;
        }
        else
        {
            float *temp_row = new float[this->col];
            memcpy(temp_row, &this->data[row1 * this->stride], this->col * sizeof(float));
            memcpy(&this->data[row1 * this->stride], &this->data[row2 * this->stride], this->col * sizeof(float));
            memcpy(&this->data[row2 * this->stride], temp_row, this->col * sizeof(float));
            delete[] temp_row;
        }
    }

    /**
     * @name Mat::clear()
     * @brief Clear the matrix by setting all elements to zero.
     */
    void Mat::clear(void)
    {
        for (int row = 0; row < this->row; row++)
        {
            memset(this->data + (row * this->stride), 0, this->col * sizeof(float));
        }
    }

}