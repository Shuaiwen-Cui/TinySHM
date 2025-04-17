/**
 * @file tiny_math.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the header file for the tiny_math middleware.
 * @version 1.0
 * @date 2025-03-26
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TINY_MATH__
#define __TINY_MATH__

#ifdef __cplusplus
extern "C"
{
#endif

/* DEPENDENCIES */

// this layer
#include "tiny_math_config.h"

/* SUBMODULES */

// vector operations
#include "tiny_vec.h"

// matrix operations
#include "tiny_mat.h" // basic matrix operations

#ifdef __cplusplus
// #include "tiny_mat_ex.hpp" // advanced matrix operations
#endif

/* TEST */ // NOTE: test files are platform specific and should not be included in the library

// vector operations
#include "tiny_vec_test.h"

// matrix operations
#include "tiny_mat_test.h"


#ifdef __cplusplus
}
#endif

#endif /* __TINY_TOOLBOX__ */