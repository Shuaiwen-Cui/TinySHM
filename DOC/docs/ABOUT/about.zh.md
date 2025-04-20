
# TinySHM：面向微控制器的结构健康监测分布式智能赋能框架

![封面](cover.jpg)

## 项目概述

该项目旨在开发一个赋能框架，使MCU级别的物联网设备具备分布式计算和智能能力，从而提升结构健康监测应用的效果。如果你对这个项目感兴趣，请给个星并保持关注。

!!! info "TinySHM"
    "TinySHM" 是 "Tiny" 和 "SHM" 的组合。"Tiny" 意味着代码被设计为运行在 MCU 设备上，而 "SHM" 是 "Structural Health Monitoring" 的缩写。

## 目标硬件

- MCU 设备（目前以 ESP32 为主要目标）

## 覆盖范围

- 平台适配与各类各类工具（时间、通讯等）
- 基本数学运算
- 数字信号处理
- TinyML / 边缘人工智能
- 测量
- 系统识别
- 损伤监测、定位、评估

## 开发载体

!!! TIP 
    以下硬件仅做展示用途，本项目并不局限于此，可以移植到其他类型的硬件上。

- Alientek 的 DNESP32S3M（ESP32-S3）

![DNESP32S3M](DNESP32S3M.png){width=800px}

![DNESP32S3M-BACK](DNESP32S3M-BACK.png){width=800px}

<div class="grid cards" markdown>

-   :simple-github:{ .lg .middle } __NexNode__

    ---

    [:octicons-arrow-right-24: <a href="https://github.com/Shuaiwen-Cui/NexNode.git" target="_blank"> 代码 </a>](#)

    [:octicons-arrow-right-24: <a href="https://shuaiwen-cui.github.io/NexNode/" target="_blank"> 文档 </a>](#)


</div>

## 项目架构

```txt
+------------------------------+
| 应用层                        |
|   - measurement              | <-- 测量
|   - system_identification    | <-- 系统识别
|   - damage_detection         | <-- 损伤检测,定位和评估
+------------------------------+
| 中间件                        |
|   - TinyToolbox              | <-- 平台底层优化 + 各种工具
|   - TinyMath                 | <-- 常用数学函数
|   - TinyDSP                  | <-- DSP 函数
|   - TinyAI                   | <-- AI 函数
+------------------------------+
| 驱动层                        |
+------------------------------+
| 硬件层                        |
+------------------------------+

```