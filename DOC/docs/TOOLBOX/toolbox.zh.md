# 工具箱

!!! info "TinyToolbox"
    工具箱TinyToolbox定位是用于 **平台适配与优化** 并提供 **各种实用工具** 的库，服务于边缘计算与应用开发。**注意，之所以将适配和工具放在一个库里面，是因为很多工具底层利用的是平台提供的功能，所以将平台适配和各类工具放在同一个库里面，便于使用和维护。**

!!! warning     
    目前开发以ESP32为基础，向STM32等平台的迁移需要对适配层进行一定的修改。

## 功能目录

### [时间](./TIME/time.zh.md)

- 获取运行时间： `tiny_get_running_time()`
- SNTP对时： `sync_time_with_timezone("CST-8")`
- 获取世界时间： `tiny_get_current_time(1)`

待开发:

- 无线传感器网络本地对时-微秒级别