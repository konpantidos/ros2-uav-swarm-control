#ifndef SWARM_CONTROLLER_HPP
#define SWARM_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <swarm_interfaces/msg/drone_state.hpp>
#include <Eigen/Dense>
#include <vector>

class SwarmController : public rclcpp::Node {
public:
    SwarmController();

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_pub_;
    rclcpp::Subscription<swarm_interfaces::msg::DroneState>::SharedPtr state_sub_;
    rclcpp::TimerBase::SharedPtr control_timer_;

    Eigen::Vector3d current_position_;
    Eigen::Vector3d current_velocity_;
    Eigen::Vector3d target_position_;

    // APF Control Parameters
    double k_attractive_;
    double max_velocity_;
    
    // Repulsive Force Parameters
    double k_repulsive_;          
    double influence_radius_;     
    std::vector<Eigen::Vector3d> obstacles_; 

    void state_callback(const swarm_interfaces::msg::DroneState::SharedPtr msg);
    void compute_and_publish_velocity();
    
    Eigen::Vector3d calculate_attractive_force();
    Eigen::Vector3d calculate_repulsive_force(); 
};

#endif // SWARM_CONTROLLER_HPP
