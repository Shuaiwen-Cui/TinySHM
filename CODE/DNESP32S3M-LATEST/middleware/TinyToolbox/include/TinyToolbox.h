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
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"

// customized drivers
#include "esp_rtc.h"

/* DEFINITIONS */
typedef TickType_t TinyTimeMark_t;

/**
 * @brief Structure to hold date and time
 */
typedef struct DateTime_t
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    long microsecond;
} DateTime_t;

/* FUNCTIONS */
/**
 * @brief Get the running time in microseconds
 * @return TinyTimeMark_t
 */
TinyTimeMark_t tiny_get_running_time(void);

/**
 * @brief Initialize SNTP
 * @return None
 */
void initialize_sntp(void);

/**
 * @brief Obtain the current time with timezone
 * @param timezone_str Timezone string (e.g., "CST-8")
 * @note The timezone string should be in the format "TZ=GMT+/-HH:MM"
 * @note To use this function, in application, insert "sync_time_with_timezone("CST-8");" will do
 * @return None
 */
void sync_time_with_timezone(const char *timezone_str);

/**
 * @name tiny_get_current_time
 * @brief Get the current time as a DateTime_t struct
 * @param print_flag Flag to indicate whether to print the time
 * @return DateTime_t structure containing the current date and time
 */
DateTime_t tiny_get_current_time(bool print_flag);


#endif /* __TINYTOOLBOX__ */