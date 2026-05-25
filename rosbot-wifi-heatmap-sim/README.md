# ROSbot WiFi Heatmap — ROS 2 Jazzy + Gazebo Harmonic (Simulation Only)

Converted from [husarion/rosbot-demo-wifi-heatmap](https://github.com/husarion/rosbot-demo-wifi-heatmap)
(ROS 2 Galactic / Docker / real hardware) to run **natively on Ubuntu 24.04** with
**ROS 2 Jazzy Jalisco** and **Gazebo Harmonic**, purely in **simulation**.

---

## What this project does

1. A simulated ROSbot drives through a Gazebo world while SLAM Toolbox builds a map.
2. You save the map, then the **waypoint publisher** reads it, generates a grid of safe
   waypoints across free space, and sends them to Nav2's `FollowWaypoints` action.
3. At every waypoint, a **custom Nav2 waypoint-task-executor plugin** measures
   simulated WiFi RSSI (log-distance path-loss model from a virtual access point).
4. After all waypoints are visited, the **heatmap generator** node interpolates the
   RSSI samples and overlays an absolute + relative heatmap on the map image.

Since there is no real WiFi hardware in Gazebo, the RSSI is computed from the
robot's distance to a configurable access-point coordinate using:

```
RSSI = tx_power − 10 · n · log₁₀(d / d₀) + noise
```

You can place multiple virtual APs by changing the params and re-running.

---

## Prerequisites

| Component | How to install |
|---|---|
| **Ubuntu 24.04 LTS** | Native or VM |
| **ROS 2 Jazzy** | `sudo apt install ros-jazzy-desktop` |
| **Gazebo Harmonic** | Comes with `ros-jazzy-ros-gz` (vendor packages) |
| **Nav2** | `sudo apt install ros-jazzy-navigation2 ros-jazzy-nav2-bringup` |
| **SLAM Toolbox** | `sudo apt install ros-jazzy-slam-toolbox` |
| **ros_gz bridge** | `sudo apt install ros-jazzy-ros-gz-bridge ros-jazzy-ros-gz-sim` |
| **Teleop** | `sudo apt install ros-jazzy-teleop-twist-keyboard` |
| **Python deps** | `sudo apt install python3-colcon-common-extensions python3-scipy python3-numpy python3-matplotlib python3-opencv python3-tk python3-yaml` |
| **vcs tool** | `sudo apt install python3-vcstool` |

### Install everything in one go

```bash
sudo apt update && sudo apt install -y \
  ros-jazzy-desktop \
  ros-jazzy-navigation2 ros-jazzy-nav2-bringup \
  ros-jazzy-slam-toolbox \
  ros-jazzy-ros-gz ros-jazzy-ros-gz-bridge ros-jazzy-ros-gz-sim \
  ros-jazzy-teleop-twist-keyboard \
  python3-colcon-common-extensions python3-vcstool \
  python3-scipy python3-numpy python3-matplotlib python3-opencv python3-tk python3-yaml
```

---

## Project structure

```
rosbot-wifi-heatmap-sim/
├── README.md                          ← you are here
├── config/
│   ├── nav2_params.yaml               ← Nav2 Jazzy params (use_sim_time: true)
│   └── slam_params.yaml               ← SLAM Toolbox params
├── maps/                              ← saved maps go here
├── heatmaps/                          ← generated heatmap images land here
└── src/
    ├── rosbot_interfaces/             ← RssiAtWaypoint.msg (geometry_msgs/Point + int8)
    ├── nav2_read_rssi_at_waypoint_plugin/  ← C++ Nav2 plugin (simulated RSSI)
    ├── waypoint_publisher_package/    ← Python: reads map, generates waypoints, calls Nav2
    ├── rssi_heatmap_generator_package/← Python: collects RSSI data, generates heatmaps
    └── mappers_bringup/               ← Launch files + installed configs
        ├── launch/
        │   ├── sim_nav2_slam.launch.py    ← Nav2 + SLAM + RViz (you launch Gazebo separately)
        │   └── mappers.launch.py          ← waypoint publisher + heatmap generator
        └── config/                        ← copies of nav2/slam params (installed by colcon)
```

---

## Step-by-step: Full simulation run

### Step 0 — Build the ROSbot Gazebo simulation

Husarion's official `rosbot_ros` repo has a `jazzy` branch with a Gazebo Harmonic
simulation package (`rosbot_gazebo`). Build it in a **separate workspace**:

```bash
mkdir -p ~/rosbot_ws/src && cd ~/rosbot_ws
git clone -b jazzy https://github.com/husarion/rosbot_ros.git src/rosbot_ros

source /opt/ros/jazzy/setup.bash
vcs import src < src/rosbot_ros/rosbot/rosbot_simulation.repos

export PIP_BREAK_SYSTEM_PACKAGES=1
sudo rosdep init 2>/dev/null || true
rosdep update --rosdistro jazzy
rosdep install -i --from-path src --rosdistro jazzy -y

colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
```

> **Tip:** If `rosbot_ros` is too heavy for you, a TurtleBot3 Gazebo or any diff-drive
> robot publishing `/scan`, `/odom`, `/cmd_vel`, and `/tf` will also work — just skip
> Step 0 and use `ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py` instead.

### Step 1 — Build the heatmap packages

```bash
cd ~/rosbot-wifi-heatmap-sim
source /opt/ros/jazzy/setup.bash
# Also source the rosbot_ws so the URDF/robot model is available:
source ~/rosbot_ws/install/setup.bash

colcon build --symlink-install
source install/setup.bash
```

### Step 2 — Launch Gazebo with the ROSbot

In **Terminal 1**:

```bash
source ~/rosbot_ws/install/setup.bash
ros2 launch rosbot_gazebo simulation.launch.py
```

This starts Gazebo Harmonic with a ROSbot model in `husarion_world.sdf`.
You should see the robot in Gazebo and it will publish topics like:
`/scan`, `/odom`, `/cmd_vel`, `/tf`, `/tf_static`, `/imu/data`.

> **Using TurtleBot3 instead?**
> ```bash
> export TURTLEBOT3_MODEL=waffle
> ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
> ```

### Step 3 — Launch Nav2 + SLAM + RViz

In **Terminal 2**:

```bash
source ~/rosbot-wifi-heatmap-sim/install/setup.bash
# Also source rosbot_ws for transforms:
source ~/rosbot_ws/install/setup.bash
ros2 launch mappers_bringup sim_nav2_slam.launch.py
```

This launches:
- **Nav2** navigation stack (with the simulated RSSI waypoint plugin loaded)
- **SLAM Toolbox** in online async mode (builds the map as the robot moves)
- **RViz2** with Nav2 default view

### Step 4 — Drive around to build a map

In **Terminal 3**, use teleop to explore:

```bash
source /opt/ros/jazzy/setup.bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -p stamped:=true
```

Drive the robot around the environment until you have a complete map visible in
RViz. Then **save the map**:

```bash
# Terminal 4
source /opt/ros/jazzy/setup.bash
mkdir -p ~/rosbot-wifi-heatmap-sim/maps
ros2 run nav2_map_server map_saver_cli \
  -f ~/rosbot-wifi-heatmap-sim/maps/map \
  --ros-args -p use_sim_time:=true
```

This creates `maps/map.yaml` + `maps/map.pgm`.

### Step 5 — Run the WiFi heatmap pipeline

Stop teleop (Ctrl+C in Terminal 3). Then:

```bash
# Terminal 3 (reuse)
source ~/rosbot-wifi-heatmap-sim/install/setup.bash
ros2 launch mappers_bringup mappers.launch.py \
  path_to_yaml:=$HOME/rosbot-wifi-heatmap-sim/maps/map.yaml
```

What happens now:
1. **Waypoint publisher** reads `map.yaml` + the PGM image, identifies free pixels,
   generates a grid of safe waypoints (green dots), and sends them to Nav2's
   `/follow_waypoints` action. A matplotlib window pops up showing the waypoints.
2. **Nav2** drives the robot to each waypoint sequentially.
3. At each waypoint, the **RSSI plugin** computes simulated signal strength based on
   the robot's distance from the virtual access point (default at origin `0, 0`).
   Each measurement is published on `/rssi_data`.
4. The **heatmap generator** node collects all `/rssi_data` messages.
5. When all waypoints are done, the waypoint publisher sends a trigger on
   `/heatmap_generator_trigger`, and the heatmap generator produces:
   - **Absolute heatmap** (RSSI scaled to -100…0 dBm)
   - **Relative heatmap** (RSSI scaled to measured min…max)
   - **Waypoints overlay**

   Images are saved to `~/rosbot-wifi-heatmap-sim/heatmaps/` and displayed in matplotlib windows.

---

## Configuring the simulated WiFi signal

The virtual access point parameters are in `config/nav2_params.yaml` under
`waypoint_follower`:

```yaml
waypoint_follower:
  ros__parameters:
    waypoint_task_executor_plugin: "nav2_read_rssi_at_waypoint"
    nav2_read_rssi_at_waypoint:
      plugin: "nav2_read_rssi_at_waypoint::ReadRssiAtWaypoint"
      enabled: True
      number_of_measurements: 5       # samples averaged per waypoint
      ap_x: 0.0                       # access-point X in map frame (metres)
      ap_y: 0.0                       # access-point Y in map frame (metres)
      tx_power: -30.0                 # TX power at 1m reference (dBm)
      path_loss_exponent: 3.0         # 2.0=free-space, 3.0-4.0=indoor with walls
```

### Simulating multiple access points

Run the heatmap pipeline multiple times with different `ap_x`/`ap_y` values:

```bash
# AP in the kitchen (example: x=3.0, y=2.0)
ros2 launch mappers_bringup mappers.launch.py \
  path_to_yaml:=$HOME/rosbot-wifi-heatmap-sim/maps/map.yaml

# Before each run, edit ap_x/ap_y in config/nav2_params.yaml,
# rebuild (colcon build --symlink-install), and re-run.
# Each run saves timestamped images to heatmaps/.
```

### Tuning for realistic results

| Parameter | Effect |
|---|---|
| `tx_power: -20` | Stronger signal, covers larger area |
| `tx_power: -40` | Weaker signal, more localised |
| `path_loss_exponent: 2.0` | Free-space / open floor plan |
| `path_loss_exponent: 4.0` | Lots of walls / concrete |
| `number_of_measurements: 1` | Faster but noisier |
| `number_of_measurements: 20` | Smoother but slower |

The simulation also adds Gaussian noise (σ=2 dBm) to each measurement for realism.

### Waypoint density

The waypoint publisher has two params (set in the `mappers.launch.py` args):

```bash
ros2 launch mappers_bringup mappers.launch.py \
  density:=4 \                    # lower = more waypoints (default: 8)
  collision_range:=6 \            # pixels of safety margin from walls (default: 4)
  path_to_yaml:=.../map.yaml
```

---

## Understanding the Gazebo world

The default Husarion world (`husarion_world.sdf`) has rooms and corridors — good for
WiFi heatmap demos. The simulated AP at `(0, 0)` means signal is strongest near the
world origin and degrades with distance.

You can use **any** Gazebo world. For a custom world:

```bash
ros2 launch rosbot_gazebo simulation.launch.py \
  world:=/path/to/your/custom_world.sdf
```

Or create a simple apartment-style world in Gazebo's GUI and save it.

---

## Key differences from the original repo

| Aspect | Original | This version |
|---|---|---|
| ROS distro | Galactic | **Jazzy** |
| Simulator | None (real hardware only) | **Gazebo Harmonic** |
| Deployment | Docker Compose (5+ containers) | **Native colcon build** |
| RSSI source | `/proc/net/wireless` on real ROSbot | **Simulated** (log-distance model) |
| Nav2 config | Galactic API (`recoveries_server`) | **Jazzy API** (`behavior_server`) |
| C++ standard | C++14 | **C++17** |
| ROS 1 bridge | Required (rosbot firmware was ROS 1) | **Removed** (pure ROS 2) |
| Platform | ROSbot HW + remote PC | **Ubuntu 24.04 desktop** |

---

## Troubleshooting

**"Waiting for server..." hangs forever**
→ Make sure Nav2 is fully started (check Terminal 2 for "Lifecycle nodes active").
   SLAM needs at least a few `/scan` messages before Nav2 can plan.

**Map image not found**
→ Check that the `image:` path in your `map.yaml` is correct (relative to the yaml
  file). The waypoint publisher resolves relative paths automatically.

**Only N data points — need at least 3**
→ The robot didn't visit enough waypoints. Lower the `density` param or make a
  bigger map with more free space.

**Matplotlib window doesn't appear**
→ Install `python3-tk` and make sure you have a display. In SSH, use `ssh -X`.

**Gazebo crashes on start**
→ Known issue with some GPU drivers. Try `export LIBGL_ALWAYS_SOFTWARE=1` before
  launching, or update your Mesa/GPU drivers.

---

## License

Apache License 2.0 (same as the original repository).
