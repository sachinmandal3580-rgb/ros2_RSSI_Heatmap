# ROS
import rclpy
from rclpy.node import Node
from rosbot_interfaces.msg import RssiAtWaypoint
from std_msgs.msg import Empty
# Utils
import os
from collections import namedtuple
import yaml
import cv2
from .submodules.generate_heatmap import generate_heatmap, add_heatmap, add_waypoints, cmapGR
import tkinter  # noqa: F401
import numpy as np
from multiprocessing import Process
import datetime
from matplotlib import gridspec, pyplot as plt
import matplotlib
from matplotlib.colors import LinearSegmentedColormap  # noqa: F401

matplotlib.use('TkAgg')

RssiWaypoint = namedtuple('RssiWaypoint', 'x y rssi')
Waypoint = namedtuple('Waypoint', 'x y')


class HeatmapGenerator(Node):
    def __init__(self):
        super().__init__('heatmap_generator')
        # Subscribers
        self.create_subscription(RssiAtWaypoint, '/rssi_data', self.rssi_data_callback, 10)
        self.create_subscription(Empty, '/heatmap_generator_trigger', self.trigger_callback, 10)
        # Params
        self.declare_parameter('path_to_yaml', 'map.yaml')
        self.declare_parameter('heatmaps_dir', os.path.expanduser('~/ros2_RSSI_Heatmap/src/heatmaps'))
        # Map params
        yaml_path = self.get_parameter('path_to_yaml').get_parameter_value().string_value
        with open(yaml_path, 'r') as file:
            map_data = yaml.safe_load(file)
        self.map_origin = Waypoint(map_data['origin'][0], map_data['origin'][1])
        self.map_resolution = map_data['resolution']
        image_path = map_data['image']
        if not os.path.isabs(image_path):
            image_path = os.path.join(os.path.dirname(yaml_path), image_path)
        self.map = cv2.imread(image_path)
        if self.map is None:
            self.get_logger().error(f'Failed to load map image: {image_path}')
            raise FileNotFoundError(f'Map image not found: {image_path}')
        # Data
        self.rssi_data = []
        self.heatmaps_dir = self.get_parameter('heatmaps_dir').get_parameter_value().string_value
        os.makedirs(self.heatmaps_dir, exist_ok=True)
        self.get_logger().info('Heatmap generator node starting...')

    def rssi_data_callback(self, msg: RssiAtWaypoint):
        x = int((msg.coordinates.x - self.map_origin.x) / self.map_resolution)
        y = len(self.map) - int((msg.coordinates.y - self.map_origin.y) / self.map_resolution)
        data = RssiWaypoint(x, y, int(msg.rssi))
        self.rssi_data.append(data)
        self.get_logger().info(f'Received RSSI={msg.rssi} at pixel ({x},{y})')

    def display_maps(self, map_with_waypoints, heatmap, final_map,
                     rel_heatmap, rel_final_map, rssi_bounds):
        fig1 = plt.figure()
        fig1.suptitle('Absolute WiFi RSSI Heatmap')
        gs = gridspec.GridSpec(ncols=1, nrows=2, wspace=0.000001, hspace=0.35,
                               height_ratios=[25, 1])
        ax1 = fig1.add_subplot(gs[0, 0])
        ax1.imshow(final_map)
        xticks = ax1.get_xticks().tolist()
        yticks = ax1.get_yticks().tolist()
        xticks = [round(t * self.map_resolution, 2) for t in xticks]
        yticks = [round(t * self.map_resolution, 2) for t in yticks]
        ax1.set_xticklabels(xticks)
        ax1.set_yticklabels(yticks)
        ax1.set_xlabel('[m]')
        ax1.set_ylabel('[m]')
        ax2 = fig1.add_subplot(gs[1, 0])
        norm1 = matplotlib.colors.Normalize(vmin=-100, vmax=0)
        matplotlib.colorbar.ColorbarBase(ax2, cmap=cmapGR, norm=norm1, orientation='horizontal')
        ax2.set_title('RSSI [dBm]')

        fig2 = plt.figure()
        fig2.suptitle('Relative WiFi RSSI Heatmap')
        gs = gridspec.GridSpec(ncols=1, nrows=2, wspace=0.000001, hspace=0.35,
                               height_ratios=[25, 1])
        ax1 = fig2.add_subplot(gs[0, 0])
        ax1.imshow(rel_final_map)
        ax1.set_xticklabels(xticks)
        ax1.set_yticklabels(yticks)
        ax1.set_xlabel('[m]')
        ax1.set_ylabel('[m]')
        ax2 = fig2.add_subplot(gs[1, 0])
        norm1 = matplotlib.colors.Normalize(vmin=rssi_bounds[0], vmax=rssi_bounds[1])
        matplotlib.colorbar.ColorbarBase(ax2, cmap=cmapGR, norm=norm1, orientation='horizontal')
        ax2.set_title('RSSI [dBm]')

        fig3 = plt.figure()
        plt.axis('off')
        fig3.suptitle('Waypoints Map')
        plt.imshow(map_with_waypoints)

        plt.show()

    def trigger_callback(self, msg):
        if len(self.rssi_data) < 3:
            self.get_logger().warn(
                f'Only {len(self.rssi_data)} data points — need at least 3 for interpolation')
            return
        self.get_logger().info('Adding waypoints to map...')
        map_with_waypoints = add_waypoints(self.map, self.rssi_data)
        self.get_logger().info('Generating heatmap...')
        heatmap = generate_heatmap(
            self.rssi_data, len(self.map), len(self.map[0]), 1, filtered=False)[0]
        rel_heatmap, rssi_bounds = generate_heatmap(
            self.rssi_data, len(self.map), len(self.map[0]), 1, filtered=True, relative=True)
        self.get_logger().info('Adding heatmap to map...')
        final_map = add_heatmap(self.map, heatmap)
        rel_final_map = add_heatmap(self.map, rel_heatmap)
        self.get_logger().info('Maps generated — displaying and saving...')

        p = Process(target=self.display_maps,
                    args=(map_with_waypoints, heatmap, final_map,
                          rel_heatmap, rel_final_map, rssi_bounds))
        p.start()

        now = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        cv2.imwrite(
            os.path.join(self.heatmaps_dir, f'waypoints_{now}.png'),
            cv2.cvtColor(map_with_waypoints, cv2.COLOR_RGB2BGR))
        cv2.imwrite(
            os.path.join(self.heatmaps_dir, f'heatmap_abs_{now}.png'),
            cv2.cvtColor(final_map, cv2.COLOR_RGB2BGR))
        cv2.imwrite(
            os.path.join(self.heatmaps_dir, f'heatmap_rel_{now}.png'),
            cv2.cvtColor(rel_final_map, cv2.COLOR_RGB2BGR))
        self.get_logger().info(f'Heatmaps saved to {self.heatmaps_dir}')


def main(args=None):
    rclpy.init(args=args)
    node = HeatmapGenerator()
    rclpy.spin(node)


if __name__ == '__main__':
    main()
