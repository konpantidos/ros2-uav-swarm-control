import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node

def generate_launch_description():
    urdf_file = os.path.join(
        get_package_share_directory('swarm_sim'),
        'models',
        'drone.urdf'
    )

    gazebo = ExecuteProcess(
        cmd=['gazebo', '--verbose', '-s', 'libgazebo_ros_factory.so'],
        output='screen'
    )

    spawn_drone_1 = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'drone_1', '-file', urdf_file, '-x', '0', '-y', '0', '-z', '1'],
        output='screen'
    )

    spawn_drone_2 = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'drone_2', '-file', urdf_file, '-x', '2', '-y', '0', '-z', '1'],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        spawn_drone_1,
        spawn_drone_2
    ])
