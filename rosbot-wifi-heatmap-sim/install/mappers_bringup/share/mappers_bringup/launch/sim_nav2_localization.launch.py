"""
Launch Nav2 in localization mode (AMCL) using a saved map.

USAGE:
  ros2 launch mappers_bringup sim_nav2_localization.launch.py \
    map:=$HOME/rosbot-wifi-heatmap-sim/maps/map.yaml
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

    nav2_params_file = os.path.join(bringup_dir, 'config', 'nav2_params.yaml')

    use_sim_time = LaunchConfiguration('use_sim_time')
    map_yaml_file = LaunchConfiguration('map')

    return LaunchDescription([
        # ── Arguments ──
        DeclareLaunchArgument(
            'use_sim_time', default_value='true',
            description='Use simulation clock from Gazebo'),
        DeclareLaunchArgument(
            'map',
            default_value=os.path.expanduser('~/rosbot-wifi-heatmap-sim/maps/map.yaml'),
            description='Full path to the saved map YAML file'),
        DeclareLaunchArgument(
            'nav2_params_file', default_value=nav2_params_file,
            description='Full path to the Nav2 parameters YAML'),
        DeclareLaunchArgument(
            'autostart', default_value='true',
            description='Automatically start Nav2 lifecycle nodes'),

        # ── Nav2 Localization (map_server + AMCL) ──
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(nav2_bringup_dir, 'launch', 'localization_launch.py')
            ),
            launch_arguments={
                'use_sim_time': use_sim_time,
                'map': map_yaml_file,
                'params_file': LaunchConfiguration('nav2_params_file'),
                'autostart': LaunchConfiguration('autostart'),
            }.items(),
        ),

        # ── Nav2 Navigation Stack ──
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