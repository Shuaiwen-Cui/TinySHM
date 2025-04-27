# DIGITAL SIGNAL PROCESSING

!!! note
    This component provides a set of functions designed for signal processing on edge devices, with a focus on lightweight and efficient implementations of commonly used signal processing algorithms.

!!! note
    This component is a wrapper and extension of the official ESP32 digital signal processing library [ESP-DSP](https://docs.espressif.com/projects/esp-dsp/en/latest/esp32/index.html), providing higher-level API interfaces. In simple terms, the TinyMath library corresponds to the Math, Matrix, and DotProduct modules in ESP-DSP, while the other modules in ESP-DSP correspond to the TinyDSP library. Additionally, TinyDSP provides some functionalities not available in ESP-DSP, focusing on scenarios such as structural health monitoring.

## COMPONENT DEPENDENCIES

```c
set(src_dirs
    .
)

set(include_dirs
    .
    include
)

set(requires
    tiny_toolbox
    tiny_math
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})


```

## ARCHITECTURE AND DIRECTORY

### Dependency Diagram

to be added

### Code Tree

```txt

```