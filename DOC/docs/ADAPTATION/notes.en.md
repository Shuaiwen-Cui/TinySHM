# NOTES

## DEPENDENCIES

> FreeRTOS

```c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
```

> log

```c
#include "esp_log.h"
```

> timer

```c
#include "esp_timer.h"
```

## RUNNING TIME QUERY

We first define a new data type based on ESP32 built-in data type

```c
typedef TickType_t TinyTimeMark_t;
```

Then we define a function in the adaptation layer to get the current system running time since startup, in microseconds

```c
TinyTimeMark_t tiny_get_running_time(void)
{
    return esp_timer_get_time();
}
```