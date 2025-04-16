# TinyMath头文件

!!! INFO
    这是TinyMath库的主头文件。它包含所有必要的头文件，并提供了一个统一的接口来使用库的功能。在项目中完成该库的移植后，在需要使用相关函数的地方插入该头文件即可使用库内的所有函数。文档更新速度较慢，可能与实际代码不一致，请以实际代码为准。

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
