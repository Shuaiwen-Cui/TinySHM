# ARCHITECTURE

## HARDWARE ARCHITECTURE

![Hardware Architecture](hw.png)

To demonstrate the capabilities and features, TinySHM uses LiftNode as the physical foundation. LiftNode is a MCU level low-cost, low-power-consumption, high-performance sensing node, specially designed for various SHM applications.

<div class="grid cards" markdown>

-   :fontawesome-brands-github:{ .lg .middle } __LiftNode Repo__  

    ---

    LiftNode's Github repository.


    [:octicons-arrow-right-24: <a href="https://github.com/Shuaiwen-Cui/MCU_NODE_STM32" target="_blank"> Repository </a>](#)

-   :fontawesome-brands-github:{ .lg .middle } __LiftNode__  

    ---

    LiftNode's documentation.

    [:octicons-arrow-right-24: <a href="https://shuaiwen-cui.github.io/MCU_NODE_STM32/" target="_blank"> Documentation </a>](#)

</div>

## SOFTWARE ARCHITECTURE

![Software Architecture](sw.png)

What is shown here is actually the software architecture of LiftNode. TinySHM, as a part of the middleware layer, mainly serves as an middleware, connecting the underlying driver layer and supporting the functions of the application layer. As a framework, TinySHM aims to bridge the gap between general-purposes computation and SHM specified computation, providing highly-abstracted, configurable, energy-efficient, and high-performance functions for SHM applications.
