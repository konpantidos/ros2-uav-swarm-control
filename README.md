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
  <i>[Placeholder: A GIF demonstrating the swarm successfully navigating through obstacles in Gazebo will be placed here.]</i>
</p>

## System Architecture & Packages

The repository is structured following standard ROS 2 best practices, divided into three core packages that work together to simulate the swarm:

### 1. `swarm_control` (The Brain)
This package acts as the decentralized controller for the UAV swarm.
*   **Architecture:** Each UAV runs an independent instance of the control node (`swarm_controller_node`), ensuring a truly decentralized system.
*   **Implementation:** Written in C++17 for real-time performance, utilizing the `Eigen3` library for efficient matrix operations and state-space calculations.
*   **Logic:** Computes the optimal velocity vector based on local information, target attraction, and obstacle repulsion.

### 2. `swarm_interfaces` (Communication)
A standalone `ament_cmake` package defining the custom ROS 2 messages (`.msg`) used for inter-UAV telemetry and state sharing.
*   **`DroneState.msg`:** Contains essential state variables (Agent ID, Position, Velocity, Status) exchanged between neighbors to maintain swarm consensus.

### 3. `swarm_sim` (Physics & Simulation)
An `ament_python` package handling the physical simulation within the Gazebo environment.
*   **Integration:** Links the control inputs to the Gazebo physics engine via custom URDF/SDF models.
*   **Contents:** Contains Python-based launch files to spawn the multi-agent system and world files defining the obstacle courses.

## Mathematical Foundation

At the core of the navigation logic is a decentralized Artificial Potential Field controller. Each UAV continuously computes its local velocity vector based on:
1.  An attractive force towards the global target.
2.  Repulsive forces from static and dynamic obstacles.
3.  Consensus-based forces to maintain formation with neighboring UAVs.

The complete mathematical derivations, including stability analysis, are available in [`docs/mathematical_model.pdf`](./docs/mathematical_model.pdf).

## Prerequisites & Dependencies

To build and run this framework, your system must meet the following requirements:
*   **OS:** Ubuntu 22.04 LTS (Native or via WSL2)
*   **Middleware:** ROS 2 Humble Hawksbill
*   **Simulation:** Gazebo Ignition / Classic
*   **Libraries:** `Eigen3` (C++ Linear Algebra Library)
*   **Build System:** `colcon`

## Installation & Quick Start

1. Clone the repository into a ROS 2 workspace:
    mkdir -p ~/uav_swarm_ws/src
    cd ~/uav_swarm_ws/src
    git clone https://github.com/YourUsername/uav_swarm_control.git .

2. Install dependencies (rosdep):
    cd ~/uav_swarm_ws
    rosdep update
    rosdep install --from-paths src --ignore-src -r -y

3. Build the workspace:
    colcon build --symlink-install

4. Source and Launch:
    source install/setup.bash
    ros2 launch swarm_sim main_launch.py

*(Note: Launch file implementation is currently under active development).*

## Data Analysis

The repository includes Python scripts in the `/scripts` directory to parse ROS bags and visualize telemetry data. Tools like `plot_trajectories.py` can plot 3D trajectories, velocity profiles, and inter-agent distances to mathematically validate the controller's performance against theoretical expectations.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
