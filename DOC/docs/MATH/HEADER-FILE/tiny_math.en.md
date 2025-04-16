# TinyMath HEADER FILE

!!! INFO
    This is the main header file of the TinyMath library. It includes all necessary header files and provides a unified interface to use the functions of the library. After completing the porting of this library in the project, you can insert this header file where you want to use the relevant functions to use all functions in the library. The documentation update speed is slow and may not be consistent with the actual code, please refer to the actual code.

```c
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

/* TEST */ // NOTE: test files are platform specific and should not be included in the library

// vector operations
#include "tiny_vec_test.h"


#ifdef __cplusplus
}
#endif

#endif /* __TINY_TOOLBOX__ */
```