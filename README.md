# SignalScout — Autonomous Spatial Signal Mapper

## Problem Statement

Wireless connectivity is essential in modern homes, offices, warehouses, hospitals, campuses, and industrial facilities. However, identifying areas with poor network coverage still relies heavily on manual site surveys, where engineers walk through an environment collecting signal strength measurements.

These surveys are **slow, repetitive, and difficult to reproduce consistently**.

This project explores how an autonomous mobile robot can perform the same task without human intervention. Instead of manually collecting WiFi measurements, the robot autonomously navigates through an environment, records simulated RSSI values at multiple locations, and generates a spatial heatmap showing wireless signal coverage.

---

## The Story

Imagine you're responsible for evaluating WiFi coverage inside a large office building. Employees frequently report weak internet connections in meeting rooms, hallways, and certain workspaces. Although access points are installed correctly, there is no clear visualization of signal strength throughout the building.

Rather than sending an engineer to manually inspect every room, an autonomous robot performs the survey:

1. The robot first builds a map of the environment using **SLAM**.
2. Once the map is available, it localizes itself and automatically generates hundreds of safe navigation waypoints.
3. At every waypoint, the robot estimates the received WiFi signal strength, stores the measurement together with its location, and continues until the entire environment has been surveyed.
4. Finally, all collected measurements are interpolated into a continuous heatmap that clearly highlights strong coverage areas, weak signal regions, and potential dead zones.

> **The complete workflow transforms scattered RSSI measurements into an intuitive visualization of wireless coverage.**

---

## Objective

Develop a complete autonomous ROS 2 pipeline capable of:

- Building a map using SLAM
- Localizing within the environment
- Generating safe navigation waypoints
- Visiting every waypoint using Nav2
- Measuring simulated WiFi RSSI
- Collecting all measurements
- Generating wireless signal heatmaps

**Overall pipeline:**

```
Map → Localize → Navigate → Measure → Aggregate → Visualize
```

---

## System Overview

The project consists of four major components.

### 1. Waypoint Publisher
Generates uniformly distributed collision-free waypoints across the occupancy map and sends them to Nav2 in batches for autonomous navigation.

### 2. RSSI Measurement Plugin
Runs as a Nav2 waypoint task plugin. Every time the robot reaches a waypoint, the plugin estimates the WiFi signal strength using a simulated log-distance propagation model and publishes the measurement.

### 3. RSSI Simulator
Implements a simplified wireless propagation model. The received signal strength depends on:
- Robot position
- Access Point position
- Path-loss exponent
- Transmit power
- Gaussian noise

### 4. Heatmap Generator
Receives RSSI measurements together with robot positions. After the survey is complete, it interpolates the sparse measurements into continuous RSSI heatmaps and saves the final visualization.

---

## What You Need To Implement

This repository contains several TODOs that must be completed.

### 1. Heatmap Generator — `rssi_heatmap_generator_package/node.py`

**TODO 1 — Coordinate Conversion**

Convert robot positions received in the ROS map frame (meters) into image pixel coordinates using the map origin and map resolution. These pixel coordinates will later be used for waypoint visualization and heatmap interpolation.

**TODO 2 — Heatmap Generation**

Generate two RSSI heatmaps from the collected measurements:
- **Absolute RSSI Heatmap**
- **Relative RSSI Heatmap**

These heatmaps estimate wireless signal strength across the entire environment by interpolating discrete waypoint measurements.

**TODO 3 — Visualization and Export**

Overlay the generated heatmaps on the occupancy map. Display the results and save:
- Waypoint map
- Absolute RSSI heatmap
- Relative RSSI heatmap

…using timestamped filenames.

---

### 2. RSSI Measurement Plugin — `nav2_read_rssi_at_waypoint_plugin/src/read_rssi_at_waypoint.cpp`

**TODO 1**

After reaching every waypoint:
- Collect multiple simulated RSSI measurements
- Ignore invalid readings
- Compute the average RSSI
- Store the averaged value in the outgoing ROS message

> Averaging multiple samples produces a more stable signal estimate before publishing it.

---

### 3. RSSI Simulator — `nav2_read_rssi_at_waypoint_plugin/include/simulated_rssi.hpp`

**TODO 1**

Implement the wireless propagation model by:
- Computing RSSI using the **log-distance path-loss equation**
- Adding Gaussian noise
- Clamping the result to the valid RSSI range
- Returning the simulated RSSI value

---

### 4. Waypoint Publisher — `waypoint_publisher_package/node.py`

**TODO 1 — Generate Safe Waypoints**

- Identify all navigable cells in the occupancy map
- Generate waypoints only in free space while avoiding locations too close to obstacles
- Convert valid pixel coordinates into ROS map coordinates

**TODO 2 — Send Navigation Goals**

Convert generated waypoints into `PoseStamped` messages and send them to the Nav2 `FollowWaypoints` action server in batches. Continue sending batches until every waypoint has been visited.

---

## Running the Project

> **Before opening any terminal, build the workspace (if needed):**
> ```bash
> cd ~/ros2_RSSI_Heatmap
> colcon build
> ```
> 
> **For every new terminal, source the workspace:**
> ```bash
> cd ~/ros2_RSSI_Heatmap
> source install/setup.bash
> ```

---

### Prerequisites — Install TurtleBot3 Packages

This project requires the TurtleBot3 packages for simulation. Install them before proceeding.

**Install TurtleBot3 and its dependencies:**
```bash
sudo apt update
sudo apt install -y \
  ros-jazzy-turtlebot3 \
  ros-jazzy-turtlebot3-simulations \
  ros-jazzy-turtlebot3-gazebo
```

**Set up the TurtleBot3 workspace (if building from source):**
```bash
mkdir -p ~/turtlebot3_ws/src
cd ~/turtlebot3_ws/src
git clone -b jazzy https://github.com/ROBOTIS-GIT/turtlebot3.git
git clone -b jazzy https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
cd ~/turtlebot3_ws
colcon build --symlink-install
```

**Set the default TurtleBot3 model** (add to your `~/.bashrc` for persistence):
```bash
echo "export TURTLEBOT3_MODEL=waffle" >> ~/.bashrc
source ~/.bashrc
```

---

### Step 1 — Launch Gazebo

```bash
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
```

Wait until Gazebo loads completely.

---

### Step 2 — Build a Map (SLAM)

**Launch SLAM:**
```bash
source /opt/ros/jazzy/setup.bash
source ~/turtlebot3_ws/install/setup.bash
source ~/ros2_RSSI_Heatmap/install/setup.bash
ros2 launch mappers_bringup sim_nav2_slam.launch.py
```

**Open another terminal for teleoperation:**
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard \
  --ros-args -r /cmd_vel:=/cmd_vel_teleop
```

Drive the robot around until the environment is completely mapped.

**Save the generated map:**
```bash
mkdir -p ~/ros2_RSSI_Heatmap/maps
ros2 run nav2_map_server map_saver_cli \
  -f ~/ros2_RSSI_Heatmap/maps/map \
  --ros-args -p use_sim_time:=true
```

This creates:
```
maps/
├── map.yaml
└── map.pgm
```

Stop SLAM and teleoperation after saving the map.

---

### Step 3 — Launch Navigation

Start localization and the Nav2 stack:
```bash
ros2 launch mappers_bringup sim_nav2_localization.launch.py \
  map:=$HOME/ros2_RSSI_Heatmap/maps/map.yaml
```

Wait about **10–15 seconds** for all lifecycle nodes to activate.

---

### Step 4 — Run the Autonomous Survey

Launch the waypoint publisher and heatmap generator:
```bash
ros2 launch mappers_bringup mappers.launch.py \
  path_to_yaml:=$HOME/ros2_RSSI_Heatmap/maps/map.yaml
```

The robot will now:
1. Generate safe waypoints
2. Navigate autonomously
3. Collect RSSI measurements
4. Generate wireless heatmaps

**Example output:**
```
[heatmap_generator]: Received RSSI=-46 at pixel (57,14)
[heatmap_generator]: Received RSSI=-49 at pixel (65,14)
...
[waypoint_publisher]: All batches complete — publishing trigger...
[heatmap_generator]: Generating heatmap...
[heatmap_generator]: Heatmaps saved successfully.
```

Generated images are stored in `~/ros2_RSSI_Heatmap/heatmaps/`, including:
```
waypoints_YYYYMMDD_HHMMSS.png
heatmap_abs_YYYYMMDD_HHMMSS.png
heatmap_rel_YYYYMMDD_HHMMSS.png
```

---

## Deliverables

### 1. Source Code
- Completed implementations for all TODOs
- Working ROS 2 packages
- Launch files

### 2. Demonstration Video

Show:
- Gazebo simulation
- SLAM map creation
- Autonomous waypoint navigation
- RSSI data collection
- Final generated heatmaps

### 3. Report

Briefly describe:
- Waypoint generation strategy
- RSSI simulation model
- Heatmap interpolation approach
- Overall system workflow
- Challenges faced and improvements made

---

## Final Message

WiFi dead zones don’t speak up — they have to be discovered.

This project turns that job over to a robot that doesn’t just move through space, but reads it. It senses signal strength, builds a map as it goes, and transforms invisible connectivity gaps into a clear, actionable heatmap.

Complete the system, and you won’t just have a robot that navigates a room — you’ll have one that understands it well enough to reveal what humans can’t easily see.

That’s the shift from robotics as movement… to robotics as insight.
