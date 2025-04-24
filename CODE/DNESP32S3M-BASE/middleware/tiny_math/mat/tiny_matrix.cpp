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
        std::memset(this->data, 0, this->memory * sizeof(float));
    }

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
        std::memset(this->data, 0, this->memory * sizeof(float));
    }

    // constructor - with external data
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

    // constructor - with external data and stride
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

    // destructor
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


}