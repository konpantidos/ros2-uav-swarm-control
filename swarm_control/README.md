# Swarm Control Package

This ROS 2 package acts as the "brain" of the UAV swarm. It contains the C++ implementation of the decentralized control algorithms responsible for trajectory tracking, spatial coordination, and obstacle avoidance.

## Architecture
The control logic is strictly decoupled from the simulation environment. Each UAV runs an independent instance of the control node, ensuring a truly decentralized architecture.

*   **Language:** C++17
*   **Math Library:** Eigen3 (for matrix operations and state-space calculations)
*   **Control Method:** Artificial Potential Fields / Consensus-based tracking (Mathematical proofs available in the `/docs` directory).

## Nodes
*   `swarm_controller_node`: Subscribes to the UAV's current state and neighboring states, computes the optimal velocity vector, and publishes command velocities.
