# 说明

## 依赖

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

## 运行时间查询

首先基于ESP32平台的数据类型定义了新的数据类型

```c
typedef TickType_t TinyTimeMark_t;
```

然后在适配层中定义了一个函数用于获取当前的系统自启动后的运行时间戳，单位为微秒

```c
TinyTimeMark_t tiny_get_running_time(void)
{
    return esp_timer_get_time();
}
```