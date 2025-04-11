# TOOLBOX

!!! note "TinyToolbox"
    TinyToolbox is a library designed for **platform adaptation and optimization**, providing **various practical tools** to serve edge computing and application development. **Note that the adaptation and tools are included in the same library because many tools utilize the functions provided by the platform at a lower level. Therefore, placing platform adaptation and various tools together facilitates usage and maintenance.**

!!! warning
    Currently, development is based on ESP32, and migration to platforms like STM32 requires some modifications to the adaptation layer.

## COMPONENT DEPENDENCIES

```c
set(src_dirs
    .
)
set(include_dirs
    include
)
set(requires
    esp_timer
    esp_rtc
    espressif__esp-dsp
    espressif__esp_jpeg
    espressif__esp-dl
)
idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})
```

## ARCHITECTURE AND FUNCTION DIRECTORY

```txt
    TINYTOOLBOX
    ├── INCLUDE
    │   ├── TinyToolbox.h // serves as a directory, integrating all submodules
    │   ├── TinyTime.h // submodule for time management - header file
    │   └── ...
    ├── TinyToolbox.c // no specific function, serves as a directory
    ├── TinyTime.c // submodule for time management - source file
```

### [TIME](./TIME/time.en.md)

- Get Running Time: `tiny_get_running_time()`
- SNTP Time Synchronization: `sync_time_with_timezone("CST-8")`
- Get World Time: `tiny_get_current_time(1)`
  
TODO:

- Local Time Synchronization for Wireless Sensor Networks - Microsecond Level

## CODE

!!! tip
    TinyToolbox.h serves merely as a directory, integrating all submodules. The specific functionalities are implemented in each submodule. TinyToolbox.c is just a formal source file without specific functionality.

### TinyToolbox.h

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

#ifdef __cplusplus
extern "C"
{
#endif

/* DEPENDENCIES */
// system
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_dsp.h"

// customized drivers
#include "esp_rtc.h"

// submodules
#include "TinyTime.h" // Time

#ifdef __cplusplus
}
#endif

#endif /* __TINYTOOLBOX__ */
```

### TinyToolbox.c

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
```