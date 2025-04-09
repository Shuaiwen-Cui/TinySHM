# 说明

## 依赖

> SYSTEM

```c
#include "esp_system.h" // ESP32 System
#include "esp_log.h"    // ESP32 Logging
```

> RTOS

```c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
```

> BSP

```c
#include "driver/gptimer.h"
#include "led.h"
#include "lcd.h"
#include "tim.h"
#include "esp_rtc.h"
#include "spi_sdcard.h"
#include "wifi_wpa2_enterprise.h"
#include "mqtt.h"
#include "mpu6050.h"
```

> TinyAuton/TinySHM

```c
#include "TinyAdapter.h"
```

## 采样配置结构体

定义

```c
struct SenseConfig
{
    int sample_rate;
    int sample_duration;
    bool temperature_sense; // whether to sense temperature
    bool printout;          // not recommened for high sample rate as it will slow down the process
    bool mqtt_pub;          // not recommened for high sample rate as it will slow down the process
};
```

使用 - 实时

```c
// for streamline configuration
struct SenseConfig streamline_config = {
    .sample_rate = 1,          // Sample rate in Hz. For local printout + mqtt, at most 25Hz; for only mqtt, at most 200Hz.
    .temperature_sense = true, // Whether to sense temperature
    .printout = true,          // Only available for sampling rate <= 100Hz
    .mqtt_pub = true           // Only available for sampling rate <= 100Hz
};
```

使用 - 常规采样

```c
// for sensing configuration
struct SenseConfig sense_config = {
    .sample_rate = 500,   // Sample rate in Hz, only can be (1, 2, 5, 10, 20, 25, 50, 100, 200, 500) for FreeRTOS based sensing. Note can not be 1000Hz (no time to feed the watchdog).
    .sample_duration = 1, // Sample duration in seconds
    .printout = true      // Only available for sampling rate <= 100Hz
};
```

## 采样数据结构体

```c
struct DataStruct
{
    int sample_rate;
    int sample_duration;
    float sensor_temperature;
    TinyTimeMark_t start_time_stamp;
    TinyTimeMark_t *time_stamp;
    float *acc_data;
    float *temperature;
};
```

使用

```c
// for data structure
struct DataStruct data_struct = {
    .sample_rate = 0,     // Sample rate in Hz
    .sample_duration = 0, // Sample duration in seconds
    .sensor_temperature = 0.0,
    .start_time_stamp = 0,
    .acc_data = NULL}; 
```

## 采样原理

目前采样**基于FreeRTOS循环**而非基于**定时器中断**，实现简单，未来或许会添加定时器中断采样的方式。

## 采样模式与采样任务

目前共有两种采样模式：
- 实时采样
- 常规采样

### 实时采样

采样任务定义

```c
/**
 * @name acc_streamline_task
 * @brief This function is the task for streaming the accelerometer data.
 * @param pvParameters for FreeRTOS, the passed parameters are all void pointers and need to be casted to the correct type.
 * @retval None
 */
void acc_streamline_task(void *pvParameters)
{

    // streamline variables
    float acc_x, acc_y, acc_z, temperature;
    TinyTimeMark_t time_stamp;

    // MQTT publish buffer
    char streamline_buff[256];

    struct SenseConfig *config = (struct SenseConfig *)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000 / config->sample_rate);

    if (config->sample_rate > 100 && config->printout)
    {
        ESP_LOGW(TAG, "Printout is disabled for sample rate > 100Hz.");
        config->printout = false;
    }

    while (1)
    {
        // get the time stamp
        time_stamp = tiny_get_running_time();

        // get accelerometer data
        mpu6050_get_acce(mpu6050, &acce);
        acc_x = acce.acce_x;
        acc_y = acce.acce_y;
        acc_z = acce.acce_z;

        // get temperature
        mpu6050_get_temp(mpu6050, &temp);
        temperature = temp.temp;

        // sprintf
        if (config->printout || config->mqtt_pub)
        {
            snprintf(streamline_buff, sizeof(streamline_buff), "Time Stamp: %10ld, acc_x = %10.6f, acc_y = %10.6f, acc_z = %10.6f, Sensor Temperature: %4.2f °C", time_stamp, acc_x, acc_y, acc_z, temperature);
        }

        // print out the data - comment out for higher sample rate
        if (config->printout)
        {
            ESP_LOGI(TAG, "%s", streamline_buff);
        }

        // MQTT publish
        if (config->mqtt_pub)
        {
            esp_mqtt_client_publish(s_mqtt_client, MQTT_PUBLIC_TOPIC, streamline_buff, strlen(streamline_buff), 0, 0); // for streamline, data quality is not expected to be high, so QoS = 0; data retaintion is also not required, so 0.
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
    ESP_LOGI(TAG, "Streamline terminated. Task will delete itself.");
    vTaskDelete(NULL);
}
```

采样任务使用: 在应用程序部分创建任务即可

```c
xTaskCreate(acc_streamline_task, "Accel_Streamline_Task", 4096, &streamline_config, 5, NULL);
```



### 常规采样

采样任务定义

```c
/**
 * @name acc_sense_task
 * @brief This function is the task for sensing the accelerometer data according to the configuration structure.
 * @param pvParameters for FreeRTOS, the passed parameters are all void pointers and need to be casted to the correct type.
 * @retval None
 */
void acc_sense_task(void *pvParameters)
{
    struct SenseConfig *config = (struct SenseConfig *)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000 / config->sample_rate);
    int total_samples = config->sample_rate * config->sample_duration;

    // Fill global data_struct
    data_struct.sample_rate = config->sample_rate;
    data_struct.sample_duration = config->sample_duration;
    mpu6050_get_temp(mpu6050, &temp);
    data_struct.sensor_temperature = temp.temp;
    data_struct.start_time_stamp = tiny_get_running_time();

    // Allocate memory
    data_struct.acc_data = malloc(sizeof(float) * 3 * total_samples);
    data_struct.temperature = malloc(sizeof(float) * total_samples);
    data_struct.time_stamp = malloc(sizeof(TinyTimeMark_t) * total_samples);

    if (data_struct.acc_data == NULL || data_struct.temperature == NULL || data_struct.time_stamp == NULL)
    {
        ESP_LOGE(TAG, "Failed to allocate memory for sensing data.");
        if (data_struct.acc_data)
            free(data_struct.acc_data);
        if (data_struct.temperature)
            free(data_struct.temperature);
        if (data_struct.time_stamp)
            free(data_struct.time_stamp);
        vTaskDelete(NULL);
    }

    ESP_LOGI(TAG, "Sampling started: %d Hz for %d seconds (%d samples)",
             config->sample_rate, config->sample_duration, total_samples);

    for (int i = 0; i < total_samples; i++)
    {
        TinyTimeMark_t now = tiny_get_running_time();
        mpu6050_get_acce(mpu6050, &acce);
        mpu6050_get_temp(mpu6050, &temp);

        // Store data
        data_struct.time_stamp[i] = now;
        data_struct.acc_data[i * 3 + 0] = acce.acce_x;
        data_struct.acc_data[i * 3 + 1] = acce.acce_y;
        data_struct.acc_data[i * 3 + 2] = acce.acce_z;
        data_struct.temperature[i] = temp.temp;

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }

    ESP_LOGI(TAG, "Sampling complete.");

    // Print metadata
    ESP_LOGI(TAG, "-----------------------------");
    ESP_LOGI(TAG, "Sensor Temperature : %.2f °C", data_struct.sensor_temperature);
    ESP_LOGI(TAG, "Start Time Stamp   : %ld", (long)data_struct.start_time_stamp);
    ESP_LOGI(TAG, "Sample Rate        : %d Hz", data_struct.sample_rate);
    ESP_LOGI(TAG, "Sample Duration    : %d sec", data_struct.sample_duration);
    ESP_LOGI(TAG, "Total Samples      : %d", total_samples);
    ESP_LOGI(TAG, "Data Size          : %.2f KB",
             (sizeof(float) * 4 + sizeof(TinyTimeMark_t)) * total_samples / 1024.0f);
    ESP_LOGI(TAG, "-----------------------------");

    // Print collected data if enabled
    if (config->printout)
    {
        for (int i = 0; i < total_samples; i++)
        {
            ESP_LOGI(TAG, "Time Stamp: %10ld, acc_x = %10.6f, acc_y = %10.6f, acc_z = %10.6f, Temperature: %.2f °C",
                     (long)data_struct.time_stamp[i],
                     data_struct.acc_data[i * 3 + 0],
                     data_struct.acc_data[i * 3 + 1],
                     data_struct.acc_data[i * 3 + 2],
                     data_struct.temperature[i]);
    
            // Release CPU for a short time to avoid blocking
            if ((i % 10) == 0)
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }
    }

    // Free allocated memory
    if (data_struct.acc_data)
    {
        free(data_struct.acc_data);
        data_struct.acc_data = NULL;
    }
    if (data_struct.temperature)
    {
        free(data_struct.temperature);
        data_struct.temperature = NULL;
    }
    if (data_struct.time_stamp)
    {
        free(data_struct.time_stamp);
        data_struct.time_stamp = NULL;
    }

    vTaskDelete(NULL);
}

```

采样任务使用: 在应用程序部分创建任务即可

```c
xTaskCreate(acc_sense_task, "Accel_Sense_Task", 8192, &sense_config, 5, NULL);
```

## 待开发
- 标准时间戳
- 校准
- 定时器+中断
- DMA
- ADC+模拟
- 数据后处理
- 批量数据MQTT上传
- 实时处理功能开发