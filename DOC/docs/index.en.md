# TinySHM: Microcontroller-oriented Distributed Intelligence Enabling Framework for Structural Health Monitoring

![cover](cover.jpg)

## PROJECT OVERVIEW

This project aims to develop an empowering framework that equips MCU-level IoT devices with distributed computing and intelligence capabilities to facilitate structural health monitoring applications. If you think this project is interesting, please give it a star and stay tuned.

!!! info "TinySHM"
    "TinySHM" is a combination of "Tiny" and "SHM". "Tiny" means the codes are designed to run on MCU devices, while "SHM" stands for "Structural Health Monitoring".

## TARGET HARDWARE

- MCU devices (currently targeting ESP32 as the main platform)

## SCOPE

- Platform adaptation and various tools (time, communication, etc.)
- Basic Math Operations
- Digital Signal Processing
- TinyML / Edge AI
- Measurement
- System Identification
- Damage Monitoring, Localization, and Assessment

## HOST DEVKITS

!!! TIP 
    The following hardwares are for demonstration purposes only. This project is not limited to these and can be ported to other types of hardwares.

- DNESP32S3M from Alientek (ESP32-S3)

<!-- ![DNESP32S3M](DNESP32S3M.png){width=800px}

![DNESP32S3M-BACK](DNESP32S3M-BACK.png){width=800px} -->

<div class="grid cards" markdown>

-   :simple-github:{ .lg .middle } __NexNode__

    ---

    [:octicons-arrow-right-24: <a href="https://github.com/Shuaiwen-Cui/NexNode.git" target="_blank"> Repo </a>](#)

    [:octicons-arrow-right-24: <a href="https://shuaiwen-cui.github.io/NexNode/" target="_blank"> Online Doc </a>](#)


</div>

## PROJECT ARCHITECTURE

```txt
+------------------------------+
|   - damage_detection         | <-- damage detection, localization, and assessment
|   - system_identification    | <-- system identification
|   - measurement              | <-- measurement / sensing
| APPLICATION                  |
+------------------------------+
|   - TinyAI                   | <-- AI Functions
|   - TinyDSP                  | <-- DSP Functions
|   - TinyMath                 | <-- Common Math Functions
|   - TinyToolbox              | <-- Platform-specific Low-level Optimization + Various Utilities
| MIDDLEWARE                   |
+------------------------------+
| DRIVERS                      |
+------------------------------+
| HARDWARE                     |
+------------------------------+

```