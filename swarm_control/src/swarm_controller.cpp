#include "swarm_control/swarm_controller.hpp"

using std::placeholders::_1;

SwarmController::SwarmController() : Node("swarm_controller_node") {
    // 1. Initialize Control Parameters
    k_attractive_ = 1.5; // Gain for moving towards target
    max_velocity_ = 2.0; // m/s limit
    
    // Set a dummy target for testing (e.g., fly to x=10, y=10, z=5)
    target_position_ << 10.0, 10.0, 5.0;
    current_position_ << 0.0, 0.0, 0.0;

    // 2. Initialize Publishers and Subscribers
    velocity_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    
    state_sub_ = this->create_subscription<swarm_interfaces::msg::DroneState>(
        "drone_state", 10, std::bind(&SwarmController::state_callback, this, _1));

    // 3. Control Loop Timer (Runs at 50Hz / 20ms)
    control_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(20),
        std::bind(&SwarmController::compute_and_publish_velocity, this));

    RCLCPP_INFO(this->get_logger(), "Swarm Controller Node Initialized.");
}

void SwarmController::state_callback(const swarm_interfaces::msg::DroneState::SharedPtr msg) {
    // Update local state from telemetry
    current_position_ << msg->x, msg->y, msg->z;
    current_velocity_ << msg->vx, msg->vy, msg->vz;
}

Eigen::Vector3d SwarmController::calculate_attractive_force() {
    // F_att = k_att * (P_target - P_current)
    Eigen::Vector3d error = target_position_ - current_position_;
    return k_attractive_ * error;
}

void SwarmController::compute_and_publish_velocity() {
    // 1. Calculate Control Forces
    Eigen::Vector3d f_attractive = calculate_attractive_force();
    
    // TODO: Add f_repulsive (Collision Avoidance) here in the future
    Eigen::Vector3d total_desired_velocity = f_attractive; // + f_repulsive

    // 2. Velocity Saturation (Clamp to max_velocity_)
    if (total_desired_velocity.norm() > max_velocity_) {
        total_desired_velocity = total_desired_velocity.normalized() * max_velocity_;
    }

    // 3. Convert Eigen Vector to ROS 2 Twist Message
    geometry_msgs::msg::Twist cmd_vel;
    cmd_vel.linear.x = total_desired_velocity.x();
    cmd_vel.linear.y = total_desired_velocity.y();
    cmd_vel.linear.z = total_desired_velocity.z();

    // Publish command
    velocity_pub_->publish(cmd_vel);
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SwarmController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
