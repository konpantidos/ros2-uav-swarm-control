cmake_minimum_required(VERSION 3.8)
project(swarm_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Εύρεση των απαραίτητων πακέτων του ROS 2
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Δημιουργία του custom μηνύματος
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DroneState.msg"
)

ament_package()
