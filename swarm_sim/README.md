# Swarm Simulation Package

This `ament_python` package handles the physical simulation of the UAV swarm within the Gazebo environment. It integrates the 3D models of the drones with the ROS 2 framework, providing a realistic physics engine to validate the control algorithms developed in `swarm_control`.

## Directory Structure
*   `/launch`: Python-based ROS 2 launch files to spawn the multi-agent system and initialize the environment.
*   `/models`: URDF/SDF descriptions of the UAVs, including mass, inertia, and aerodynamic properties.
*   `/worlds`: Gazebo world files defining the simulation environment (e.g., empty space, obstacle courses).

## Simulation Engine
*   **Target Simulator:** Gazebo (Classic/Ignition)
*   **Physics:** Real-time rigid body dynamics.
