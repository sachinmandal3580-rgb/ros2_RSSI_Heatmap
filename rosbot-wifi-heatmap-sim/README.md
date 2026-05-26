# ROSbot WiFi Heatmap Simulator

A ROS 2 (Jazzy) simulation project that autonomously navigates a TurtleBot3 Waffle through a mapped environment, measures simulated WiFi RSSI at configurable waypoints, and generates a WiFi signal strength heatmap overlay on the map.

---

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
  - [1. ROS 2 Jazzy](#1-ros-2-jazzy)
  - [2. Nav2 and Dependencies](#2-nav2-and-dependencies)
  - [3. TurtleBot3 Packages](#3-turtlebot3-packages)
  - [4. Twist Stamper](#4-twist-stamper)
  - [5. Project Workspace](#5-project-workspace)
- [Building the Workspace](#building-the-workspace)
- [Usage](#usage)
  - [Step 1: Launch the Simulation (Gazebo)](#step-1-launch-the-simulation-gazebo)
  - [Step 2: Create and Save a Map (SLAM)](#step-2-create-and-save-a-map-slam)
  - [Step 3: Launch Nav2 Localization and Navigation](#step-3-launch-nav2-localization-and-navigation)
  - [Step 4: Launch Waypoint Publisher and Heatmap Generator](#step-4-launch-waypoint-publisher-and-heatmap-generator)
- [Configuration](#configuration)
  - [Nav2 Parameters](#nav2-parameters)
  - [WiFi Access Points](#wifi-access-points)
  - [Waypoint Generation](#waypoint-generation)
- [Troubleshooting](#troubleshooting)
- [Project Structure](#project-structure)

---

## Prerequisites

- **Ubuntu 24.04** (Noble Numbat)
- **ROS 2 Jazzy Jalisco**
- **Gazebo Harmonic** (comes with ROS 2 Jazzy)
- **Python 3.12+**
- **Git**

---

## Installation

### 1. ROS 2 Jazzy

Follow the official ROS 2 Jazzy installation guide if not already installed.

```bash
# Set locale
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

# Add ROS 2 apt repository
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install ROS 2 Jazzy Desktop
sudo apt update
sudo apt install ros-jazzy-desktop -y

# Source ROS 2
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### 2. Nav2 and Dependencies

```bash
sudo apt install -y \
  ros-jazzy-navigation2 \
  ros-jazzy-nav2-bringup \
  ros-jazzy-nav2-bt-navigator \
  ros-jazzy-nav2-controller \
  ros-jazzy-nav2-planner \
  ros-jazzy-nav2-behaviors \
  ros-jazzy-nav2-waypoint-follower \
  ros-jazzy-nav2-lifecycle-manager \
  ros-jazzy-nav2-regulated-pure-pursuit-controller \
  ros-jazzy-nav2-costmap-2d \
  ros-jazzy-nav2-smoother \
  ros-jazzy-nav2-velocity-smoother \
  ros-jazzy-slam-toolbox \
  ros-jazzy-cartographer-ros
```

### 3. TurtleBot3 Packages

```bash
sudo apt install -y \
  ros-jazzy-turtlebot3* \
  ros-jazzy-turtlebot3-gazebo \
  ros-jazzy-turtlebot3-navigation2 \
  ros-jazzy-turtlebot3-cartographer \
  ros-jazzy-turtlebot3-teleop

# Set TurtleBot3 model
echo "export TURTLEBOT3_MODEL=waffle" >> ~/.bashrc
echo "export GAZEBO_MODEL_PATH=\$GAZEBO_MODEL_PATH:/opt/ros/jazzy/share/turtlebot3_gazebo/models" >> ~/.bashrc
source ~/.bashrc
```

### 4. Twist Stamper

The TurtleBot3 Gazebo bridge expects `geometry_msgs/msg/TwistStamped` on `/cmd_vel`, but Nav2 publishes `geometry_msgs/msg/Twist`. The `twist_stamper` package converts between them.

```bash
sudo apt install ros-jazzy-twist-stamper
```

If the apt package is not available, build from source:

```bash
cd ~/rosbot-wifi-heatmap-sim/src
git clone https://github.com/ros-tooling/twist_stamper.git
cd ~/rosbot-wifi-heatmap-sim
colcon build --packages-select twist_stamper
source install/setup.bash
```

### 5. Project Workspace

```bash
# Clone the project
cd ~
git clone <your-repo-url> rosbot-wifi-heatmap-sim
cd rosbot-wifi-heatmap-sim

# Install Python dependencies
pip install numpy opencv-python matplotlib scipy pyyaml --break-system-packages

# Install ROS dependencies
sudo apt install -y \
  ros-jazzy-rviz2 \
  ros-jazzy-teleop-twist-keyboard \
  python3-colcon-common-extensions
```

---

## Building the Workspace

```bash
cd ~/rosbot-wifi-heatmap-sim
colcon build
source install/setup.bash
```

After any code changes, rebuild the affected packages:

```bash
# Rebuild specific package
colcon build --packages-select nav2_read_rssi_at_waypoint

# Rebuild everything
colcon build

# Always re-source after building
source install/setup.bash
```

---

## Usage

The project requires four steps run in separate terminals. Source your workspace in each terminal before running commands.

```bash
# Run this in EVERY new terminal
cd ~/rosbot-wifi-heatmap-sim
source install/setup.bash
```

### Step 1: Launch the Simulation (Gazebo)

Start Gazebo with the TurtleBot3 Waffle in a world.

```bash
# Terminal 1: Launch Gazebo simulation
export TURTLEBOT3_MODEL=waffle
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
```

Wait for Gazebo to fully load and display the robot in the environment.

### Step 2: Create and Save a Map (SLAM)

If you don't have a map yet, create one using SLAM and teleop.

```bash
# Terminal 2: Launch SLAM
source /opt/ros/jazzy/setup.bash

source ~/turtlebot3_ws/install/setup.bash

source ~/rosbot-wifi-heatmap-sim/install/setup.bash

ros2 launch mappers_bringup sim_nav2_slam.launch.py
```

```bash
# Terminal 3: Launch teleop to drive the robot around
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/cmd_vel_teleop
OR
use the teleop window in gazebo
```

Drive the robot around the entire environment to build a complete map.

Once the map is complete, save it:

```bash
# Terminal 4: Save the map
mkdir -p ~/rosbot-wifi-heatmap-sim/maps
ros2 run nav2_map_server map_saver_cli -f ~/rosbot-wifi-heatmap-sim/maps/map --ros-args -p use_sim_time:=true
```

This creates two files: `map.yaml` (metadata) and `map.pgm` (occupancy grid image).

Stop SLAM and teleop after saving (Ctrl+C in Terminals 2 and 3).

### Step 3: Launch Nav2 Localization and Navigation

```bash
# Terminal 2: Launch Nav2 with localization
ros2 launch mappers_bringup sim_nav2_localization.launch.py \
  map:=$HOME/rosbot-wifi-heatmap-sim/maps/map.yaml
```

This launch file automatically handles: Nav2 localization (AMCL + map_server), Nav2 navigation stack (planner, controller, behavior server, etc.), RViz2 visualization, initial pose publishing (after 3 seconds), lifecycle node activation (after 8 seconds), and the twist_stamper bridge (Twist to TwistStamped conversion).

Wait approximately 12 seconds for all nodes to initialize and activate. Verify in RViz that the robot is localized on the map (green AMCL particle cloud should be visible).

To verify all nodes are active:

```bash
ros2 lifecycle get /controller_server   # Should show: active [3]
ros2 lifecycle get /planner_server      # Should show: active [3]
ros2 lifecycle get /bt_navigator        # Should show: active [3]
ros2 lifecycle get /waypoint_follower   # Should show: active [3]
ros2 lifecycle get /velocity_smoother   # Should show: active [3]
ros2 lifecycle get /behavior_server     # Should show: active [3]
```

### Step 4: Launch Waypoint Publisher and Heatmap Generator

```bash
# Terminal 3: Launch waypoint publisher + heatmap generator
ros2 launch mappers_bringup mappers.launch.py \
  path_to_yaml:=$HOME/rosbot-wifi-heatmap-sim/maps/map.yaml
```

The robot will now autonomously visit all waypoints, collect RSSI measurements, and generate the heatmap when complete.

Monitor progress in the terminal. You should see messages like:

```
[heatmap_generator]: Received RSSI=-44 at pixel (56,9)
[heatmap_generator]: Received RSSI=-47 at pixel (64,9)
...
```

When all waypoints are visited:

```
[waypoint_publisher]: All waypoints visited — publishing trigger...
[heatmap_generator]: Generating heatmap...
[heatmap_generator]: Heatmaps saved to ~/rosbot-wifi-heatmap-sim/heatmaps
```

The generated heatmaps are saved in `~/rosbot-wifi-heatmap-sim/heatmaps/` as PNG files with timestamps: `waypoints_YYYYMMDD_HHMMSS.png`, `heatmap_abs_YYYYMMDD_HHMMSS.png`, and `heatmap_rel_YYYYMMDD_HHMMSS.png`.

---

## Configuration

### Nav2 Parameters

Located at: `src/mappers_bringup/config/nav2_params.yaml`

Key parameters to tune:

**Controller (Regulated Pure Pursuit):**

```yaml
FollowPath:
  plugin: "nav2_regulated_pure_pursuit_controller::RegulatedPurePursuitController"
  desired_linear_vel: 0.2        # Robot speed (m/s)
  lookahead_dist: 0.6            # How far ahead robot looks on path
  rotate_to_heading_angular_vel: 0.8
```

**Progress Checker** (prevents "Failed to make progress" errors):

```yaml
progress_checker:
  plugin: "nav2_controller::SimpleProgressChecker"
  required_movement_radius: 0.1    # Minimum movement required
  movement_time_allowance: 30.0    # Time allowed to make progress
```

**Goal Tolerance:**

```yaml
general_goal_checker:
  plugin: "nav2_controller::SimpleGoalChecker"
  xy_goal_tolerance: 0.3    # Position tolerance (meters)
  yaw_goal_tolerance: 0.5   # Orientation tolerance (radians)
```

**Costmap Inflation** (reduce if robot can't find paths):

```yaml
inflation_layer:
  plugin: "nav2_costmap_2d::InflationLayer"
  cost_scaling_factor: 3.0
  inflation_radius: 0.3    # Reduce from 0.55 if robot gets stuck
```

### WiFi Access Points

Located in `nav2_params.yaml` under `waypoint_follower`:

**Single AP:**

```yaml
waypoint_follower:
  ros__parameters:
    waypoint_task_executor_plugin: "nav2_read_rssi_at_waypoint"
    nav2_read_rssi_at_waypoint:
      plugin: "nav2_read_rssi_at_waypoint::ReadRssiAtWaypoint"
      enabled: True
      number_of_measurements: 5
      num_access_points: 1
      ap_1_x: 0.0
      ap_1_y: 0.0
      ap_1_tx_power: -30.0
      ap_1_path_loss_exponent: 3.0
```

**Multiple APs:**

```yaml
    nav2_read_rssi_at_waypoint:
      plugin: "nav2_read_rssi_at_waypoint::ReadRssiAtWaypoint"
      enabled: True
      number_of_measurements: 5
      num_access_points: 3
      
      # AP 1 - Center of map
      ap_1_x: 0.0
      ap_1_y: 0.0
      ap_1_tx_power: -30.0
      ap_1_path_loss_exponent: 3.0
      
      # AP 2 - Top right corner
      ap_2_x: 3.0
      ap_2_y: 3.0
      ap_2_tx_power: -30.0
      ap_2_path_loss_exponent: 3.0
      
      # AP 3 - Bottom left
      ap_3_x: -3.0
      ap_3_y: -2.0
      ap_3_tx_power: -30.0
      ap_3_path_loss_exponent: 3.0
```

The simulated RSSI value at each waypoint uses the strongest signal from all configured APs: `RSSI = tx_power - 10 * path_loss_exponent * log10(distance)`.

### Waypoint Generation

The waypoint publisher generates a grid of waypoints across the map. It reads the map YAML and places waypoints in free space only, avoiding obstacles and unknown areas.

---

## Troubleshooting

### "Frame [map] does not exist"

AMCL hasn't received an initial pose. The launch file publishes one automatically after 3 seconds. If it still fails, manually set the pose in RViz using the "2D Pose Estimate" button, or publish it manually:

```bash
ros2 topic pub -1 /initialpose geometry_msgs/msg/PoseWithCovarianceStamped \
  "{header: {frame_id: 'map'}, \
    pose: {pose: {position: {x: 0.0, y: 0.0, z: 0.0}, \
    orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}}, \
    covariance: [0.25,0,0,0,0,0, 0,0.25,0,0,0,0, 0,0,0,0,0,0, \
    0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0.068]}}"
```

### Nav2 Nodes Not Activating

If nodes remain `unconfigured` or `inactive`, activate them manually:

```bash
ros2 lifecycle set /controller_server activate
ros2 lifecycle set /planner_server activate
ros2 lifecycle set /bt_navigator activate
ros2 lifecycle set /waypoint_follower activate
ros2 lifecycle set /velocity_smoother activate
ros2 lifecycle set /behavior_server activate
```

### Robot Not Moving (Publisher count: 0 on /cmd_vel)

This is a Twist vs TwistStamped mismatch. Ensure the `twist_stamper` node is running:

```bash
ros2 node list | grep twist
```

If not running, start it manually:

```bash
ros2 run twist_stamper twist_stamper --ros-args \
  -r cmd_vel_in:=cmd_vel_smoothed \
  -r cmd_vel_out:=cmd_vel
```

### "Failed to make progress"

The robot is moving too slowly for the progress checker. Edit `nav2_params.yaml`:

```yaml
progress_checker:
  required_movement_radius: 0.1    # Reduce from 0.5
  movement_time_allowance: 30.0    # Increase from 10.0
```

### "Failed to create plan with tolerance"

The goal is inside or too close to an obstacle. Options: increase planner tolerance to 2.0 in `nav2_params.yaml`, reduce `inflation_radius` from 0.55 to 0.3, or ensure your waypoints are generated in free space.

### Robot Dancing/Oscillating

Switch from DWB to Regulated Pure Pursuit controller in `nav2_params.yaml` (see Configuration section above). This provides much smoother motion.

### bt_navigator Crashes with "ComputePathToPose already registered"

You have two `bt_navigator` instances running. Ensure it's only launched once (either in `navigation_launch.py` or manually, never both).

### Duplicate Waypoint Follower Warning

Check that `waypoint_follower` is not launched both by `navigation_launch.py` and your custom launch file. Only one instance should run.

### 0 RSSI Data Points at End

The waypoint_follower wasn't active when waypoints were sent. Ensure all Nav2 nodes are active before launching the waypoint publisher.

---

## Project Structure

```
rosbot-wifi-heatmap-sim/
├── maps/                              # Saved maps
│   ├── map.yaml
│   └── map.pgm
├── heatmaps/                          # Generated heatmaps (output)
├── src/
│   ├── mappers_bringup/               # Launch files and config
│   │   ├── config/
│   │   │   └── nav2_params.yaml       # Nav2 configuration
|   |   |   └── slam_params.yaml 
│   │   └── launch/
│   │       ├── mappers.launch.py
|   |       ├── sim_nav2_localization.launch.py
|   |       └── sim_nav2_slam.launch.py
|   |
│   ├── waypoint_publisher_package/     # Waypoint grid generator
│   ├── rssi_heatmap_generator_package/ # Heatmap visualization
│   ├── nav2_read_rssi_at_waypoint_plugin/     # RSSI measurement plugin
│   └── rosbot_interfaces/             # Custom ROS messages
│       └── msg/
│           └── RssiAtWaypoint.msg
└── README.md
```

---

## License

This project is provided for educational and research purposes.