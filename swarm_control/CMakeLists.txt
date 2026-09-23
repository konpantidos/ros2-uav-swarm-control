cmake_minimum_required(VERSION 3.8)
project(swarm_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(swarm_interfaces REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(swarm_controller_node src/swarm_controller.cpp)

target_include_directories(swarm_controller_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
)

ament_target_dependencies(swarm_controller_node
  rclcpp
  geometry_msgs
  std_msgs
  swarm_interfaces
)

install(TARGETS
  swarm_controller_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

ament_package()
