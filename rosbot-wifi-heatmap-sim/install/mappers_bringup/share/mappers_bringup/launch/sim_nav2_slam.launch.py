"""
Launch Nav2 + SLAM Toolbox + RViz2 for the WiFi heatmap simulation.

USAGE:
  # First, launch Gazebo + ROSbot in a separate terminal:
  #   ros2 launch rosbot_gazebo simulation.launch.py
  # Or TurtleBot3:
  #   export TURTLEBOT3_MODEL=waffle
  #   ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py

  # Then launch this file:
  ros2 launch mappers_bringup sim_nav2_slam.launch.py

This file does NOT launch Gazebo — it expects a robot simulator to already be
running and publishing /scan, /odom, /cmd_vel, /tf, /tf_static.
"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    bringup_dir = get_package_share_directory('mappers_bringup')
    nav2_bringup_dir = get_package_share_directory('nav2_bringup')
    slam_toolbox_dir = get_package_share_directory('slam_toolbox')

    nav2_params_file = os.path.join(bringup_dir, 'config', 'nav2_params.yaml')
    slam_params_file = os.path.join(bringup_dir, 'config', 'slam_params.yaml')

    use_sim_time = LaunchConfiguration('use_sim_time')

    return LaunchDescription([
        # ── Arguments ──
        DeclareLaunchArgument(
            'use_sim_time', default_value='true',
            description='Use simulation clock from Gazebo'),
        DeclareLaunchArgument(
            'nav2_params_file', default_value=nav2_params_file,
            description='Full path to the Nav2 parameters YAML'),
        DeclareLaunchArgument(
            'slam_params_file', default_value=slam_params_file,
            description='Full path to the SLAM Toolbox parameters YAML'),
        DeclareLaunchArgument(
            'autostart', default_value='true',
            description='Automatically start Nav2 lifecycle nodes'),

        # ── Nav2 Navigation Stack ──
        # This brings up controller_server, planner_server, behavior_server,
        # bt_navigator, waypoint_follower (with our RSSI plugin), etc.
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(nav2_bringup_dir, 'launch', 'navigation_launch.py')
            ),
            launch_arguments={
                'use_sim_time': use_sim_time,
                'params_file': LaunchConfiguration('nav2_params_file'),
                'autostart': LaunchConfiguration('autostart'),
            }.items(),
        ),

        # ── SLAM Toolbox (online async) ──
        # Builds the map in real-time from /scan and /odom.
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(slam_toolbox_dir, 'launch', 'online_async_launch.py')
            ),
            launch_arguments={
                'use_sim_time': use_sim_time,
                'slam_params_file': LaunchConfiguration('slam_params_file'),
            }.items(),
        ),

        # ── RViz2 ──
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=[
                '-d', os.path.join(nav2_bringup_dir, 'rviz', 'nav2_default_view.rviz')
            ],
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen',
        ),
    ])
