# 代码

!!! warning "注意"
    以下代码应以发布代码中的代码为准，可能会有更新。

## CMakeLists.txt

```cmake
set(src_dirs
    .
)

set(include_dirs
    include
)

set(requires
    esp_timer
    espressif__esp-dsp
    espressif__esp_jpeg
    espressif__esp-dl
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})
```

## TinyToolbox.h

```c
/**
 * @file TinyToolbox.h
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the header file for the TinyToolbox middleware.
 * @version 1.0
 * @date 2025-03-26
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TINYTOOLBOX__
#define __TINYTOOLBOX__

/* CONFIGURATIONS */

/* DEPENDENCIES */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_dsp.h"
// #include "esp_dl.h"

/* DEFINITIONS */
typedef TickType_t TinyTimeMark_t;

/* FUNCTIONS */
TinyTimeMark_t tiny_get_running_time(void);

#endif /* __TINYTOOLBOX__ */
```

## TinyToolbox.c

```c
/**
 * @file TinyToolbox.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief This file is the source file for the TinyToolbox middleware.
 * @version 1.0
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

/* DEPENDENCIES */
#include "TinyToolbox.h"

/* DEFINITIONS */

/* FUNCTIONS */
TinyTimeMark_t tiny_get_running_time(void)
{
    return esp_timer_get_time();
}

```