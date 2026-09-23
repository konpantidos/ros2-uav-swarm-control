# Autonomous UAV Swarm Control & Trajectory Tracking

![ROS 2](https://img.shields.io/badge/ROS_2-Humble-blue)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Gazebo](https://img.shields.io/badge/Simulation-Gazebo-orange)
![License](https://img.shields.io/badge/License-MIT-green)

A mathematically rigorous, decentralized ROS 2 / C++ simulation framework for autonomous UAV swarm control, dynamic trajectory tracking, and obstacle avoidance.

---

## Project Overview

This project provides a highly modular, multi-agent simulation framework for Unmanned Aerial Vehicles (UAVs). Designed with academic rigor in mind, it focuses on the application of advanced control theory—specifically **Artificial Potential Fields (APF)** and **Consensus Algorithms**—to achieve stable, deterministic, and collision-free spatial coordination among multiple aerial agents.

Unlike black-box AI approaches, this framework guarantees mathematically provable stability, making it ideal for safety-critical aerospace applications. The architecture explicitly decouples the mathematical control logic from the simulation engine, ensuring a seamless transition path from software simulation to Hardware-In-The-Loop (HITL) testing.

<p align="center">
  <!-- TODO: προσθήκη ενός GIF εδώ όταν τρέξει η προσομοίωση -->
  <i>[Placeholder: A GIF demonstrating the swarm successfully navigating through obstacles in Gazebo will be placed here.]</i>
</p>

## System Architecture

The repository is structured following standard ROS 2 best practices, divided into three core packages:

*   **`swarm_control`**: The C++ "brain" of the operation. Contains the decentralized algorithms using `Eigen3` for real-time matrix operations and state-space calculations.
*   **`swarm_sim`**: The Python-based physical simulation package linking the control inputs to the Gazebo physics engine via custom URDF/SDF models.
*   **`swarm_interfaces`**: A standalone `ament_cmake` package defining the custom `.msg` structures used for inter-UAV telemetry and state sharing.

For a detailed view of the system's architecture and the mathematical proofs governing the swarm dynamics, please refer to the documents in the `/docs` directory.

## Mathematical Foundation

At the core of the navigation logic is a decentralized Artificial Potential Field controller. Each UAV continuously computes its local velocity vector $\vec{v}_i$ based on:
1.  An attractive force towards the global target.
2.  Repulsive forces from static/dynamic obstacles.
3.  Consensus-based repulsive/attractive forces to maintain formation with neighboring UAVs.

The complete mathematical derivations, including stability analysis, are available in [`docs/mathematical_model.pdf`](./docs/mathematical_model.pdf).

## Prerequisites & Dependencies

To build and run this framework, your system must meet the following requirements:

*   **OS:** Ubuntu 22.04 LTS (Native or via WSL2)
*   **Middleware:** ROS 2 Humble Hawksbill
*   **Simulation:** Gazebo Ignition / Classic
*   **Libraries:** `Eigen3` (C++ Linear Algebra Library)
*   **Build System:** `colcon`

## Installation & Quick Start

**1. Clone the repository into a ROS 2 workspace:**
```bash
mkdir -p ~/uav_swarm_ws/src
cd ~/uav_swarm_ws/src
git clone [https://github.com/konpantidos/uav_swarm_control.git](https://github.com/konpantidos/uav_swarm_control.git) .
