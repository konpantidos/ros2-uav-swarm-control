#include "swarm_control/swarm_controller.hpp"
#include <cmath>

using std::placeholders::_1;

SwarmController::SwarmController() : Node("swarm_controller_node") {
    // 1. Initialize Control Parameters
    k_attractive_ = 1.5; 
    max_velocity_ = 2.0; 
    
    // Repulsive Parameters
    k_repulsive_ = 5.0;       
    influence_radius_ = 3.0;  
    
    // Dummy obstacle for initial testing
    obstacles_.push_back(Eigen::Vector3d(5.0, 5.0, 2.5)); 

    target_position_ << 10.0, 10.0, 5.0;
    current_position_ << 0.0, 0.0, 0.0;

    // 2. Initialize Publishers and Subscribers
    velocity_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    
    state_sub_ = this->create_subscription<swarm_interfaces::msg::DroneState>(
        "drone_state", 10, std::bind(&SwarmController::state_callback, this, _1));

    // 3. Control Loop Timer (50Hz)
    control_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(20),
        std::bind(&SwarmController::compute_and_publish_velocity, this));

    RCLCPP_INFO(this->get_logger(), "Swarm Controller Node Initialized with APF Avoidance.");
}

void SwarmController::state_callback(const swarm_interfaces::msg::DroneState::SharedPtr msg) {
    current_position_ << msg->x, msg->y, msg->z;
    current_velocity_ << msg->vx, msg->vy, msg->vz;
}

Eigen::Vector3d SwarmController::calculate_attractive_force() {
    Eigen::Vector3d error = target_position_ - current_position_;
    return k_attractive_ * error;
}

Eigen::Vector3d SwarmController::calculate_repulsive_force() {
    Eigen::Vector3d f_rep(0.0, 0.0, 0.0);

    for (const auto& obs : obstacles_) {
        Eigen::Vector3d diff = current_position_ - obs;
        double distance = diff.norm();

        if (distance < influence_radius_ && distance > 0.01) {
            double magnitude = k_repulsive_ * 
                               (1.0 / distance - 1.0 / influence_radius_) * 
                               (1.0 / std::pow(distance, 2));
            
            f_rep += magnitude * diff.normalized();
        }
    }
    return f_rep;
}

void SwarmController::compute_and_publish_velocity() {
    // 1. Calculate Control Forces
    Eigen::Vector3d f_attractive = calculate_attractive_force();
    Eigen::Vector3d f_repulsive = calculate_repulsive_force();
    
    // Superposition of forces
    Eigen::Vector3d total_desired_velocity = f_attractive + f_repulsive;

    // 2. Velocity Saturation
    if (total_desired_velocity.norm() > max_velocity_) {
        total_desired_velocity = total_desired_velocity.normalized() * max_velocity_;
    }

    // 3. Convert to Twist Message
    geometry_msgs::msg::Twist cmd_vel;
    cmd_vel.linear.x = total_desired_velocity.x();
    cmd_vel.linear.y = total_desired_velocity.y();
    cmd_vel.linear.z = total_desired_velocity.z();

    velocity_pub_->publish(cmd_vel);
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SwarmController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
