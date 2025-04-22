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
    Mat::Rect::Rect(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    void Mat::Rect::resizeRect(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    int Mat::Rect::areaRect(void) const
    {
        return width * height;
    }

    // Constructor with initialization to 0
    Mat::Mat(int rows, int cols)
        : rows(rows), cols(cols), stride(cols), padding(0), length(rows * cols),
          data(nullptr), ext_buff(false), sub_matrix(false)
    {
        allocate();
        std::memset(this->data, 0, this->length * sizeof(float));
    }

    // Constructor with external buffer
    Mat::Mat(float *data, int rows, int cols)
        : rows(rows), cols(cols), stride(cols), padding(0), length(rows * cols),
          data(data), ext_buff(true), sub_matrix(false) {}

    // Constructor with external buffer and stride
    Mat::Mat(float *data, int rows, int cols, int stride)
        : rows(rows), cols(cols), stride(stride), padding(stride - cols), length(rows * cols),
          data(data), ext_buff(true), sub_matrix(false) {}

    // Default constructor
    Mat::Mat()
        : rows(1), cols(1), stride(1), padding(0), length(1),
          data(nullptr), ext_buff(false), sub_matrix(false)
    {
        allocate();
        std::memset(this->data, 0, this->length * sizeof(float));
    }

    // Destructor
    Mat::~Mat()
    {
        if (!this->ext_buff && this->data)
        {
            delete[] this->data;
        }
    }

    // Memory allocation for the matrix
    void Mat::allocate()
    {
        this->ext_buff = false;
        this->length = this->rows * this->cols;
        this->data = new float[this->length];
    }

    // Copy constructor - if it is a sub-matrix, only the header is copied, else both header and data are copied
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

    // Get a sub-matrix (ROI) from the original matrix
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

    // Get a sub-matrix (ROI) from the original matrix, compact version
    Mat Mat::getROI(int startRow, int startCol, int roiRows, int roiCols)
    {
        return (getROI(startRow, startCol, roiRows, roiCols, this->cols));
    }

    // Get a sub-matrix (ROI) from the original matrix using Rect structure
    Mat Mat::getROI(const Mat::Rect &rect)
    {
        return (getROI(rect.y, rect.x, rect.height, rect.width, this->cols));
    }

    // Make copy of matrix.
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

    // Copy header of matrix
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

    // Print matrix header information
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

    // Print Matrix
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

    // Get a sub-matrix (ROI) from the original matrix
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

    // Get a sub-matrix (ROI) from the original matrix using Rect structure
    Mat Mat::Get(const Mat::Rect &rect)
    {
        return (Get(rect.y, rect.height, rect.x, rect.width));
    }

    // Copy operator
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

}

Mat Mat::expHelper(const Mat &m, int num)
{
    if (num == 0) {
        return Mat::eye(m.rows);
    } else if (num == 1) {
        return m;
    } else if (num % 2 == 0) {  // num is even
        return expHelper(m * m, num / 2);
    } else {                    // num is odd
        return m * expHelper(m * m, (num - 1) / 2);
    }
}

Mat Mat::operator^(int num)
{
    Mat temp(*this);
    return expHelper(temp, num);
}

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

Mat Mat::ones(int size)
{
    return (ones(size, size));
}

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

void Mat::clear()
{
    for (int row = 0; row < this->rows; row++)
    {
        memset(this->data + (row * this->stride), 0, this->cols * sizeof(float));
    }
}

// Duplicate to Get method
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