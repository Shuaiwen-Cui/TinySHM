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