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
}