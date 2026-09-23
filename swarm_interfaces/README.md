# Swarm Interfaces Package

This package defines the custom ROS 2 messages (`.msg`) used for inter-UAV communication and telemetry. 

By isolating the message definitions into a standalone `ament_cmake` package, we ensure clean dependency management across the workspace and allow external modules (e.g., Python plotting scripts) to easily utilize the defined data structures.

## Custom Messages
*   `DroneState.msg`: Contains the essential state variables of a single UAV, including:
    *   Unique Agent ID
    *   Position (x, y, z)
    *   Velocity vectors (vx, vy, vz)
    *   Current operational mode/status
