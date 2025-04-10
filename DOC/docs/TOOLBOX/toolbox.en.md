# TOOLBOX

!!! note "TinyToolbox"
    TinyToolbox is a library designed for **platform adaptation and optimization**, providing **various practical tools** to serve edge computing and application development. **Note that the adaptation and tools are included in the same library because many tools utilize the functions provided by the platform at a lower level. Therefore, placing platform adaptation and various tools together facilitates usage and maintenance.**

!!! warning
    Currently, development is based on ESP32, and migration to platforms like STM32 requires some modifications to the adaptation layer.

## FEATURE OVERVIEW

### [TIME](./TIME/time.en.md)

- Get Running Time: `tiny_get_running_time()`
- SNTP Time Synchronization: `sync_time_with_timezone("CST-8")`
- Get World Time: `tiny_get_current_time(1)`
  
TODO:

- Local Time Synchronization for Wireless Sensor Networks - Microsecond Level