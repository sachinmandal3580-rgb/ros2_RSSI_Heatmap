# ROS
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from nav2_msgs.action import FollowWaypoints
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Empty

# Utils
import os
import tkinter  # noqa: F401
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt  # noqa: E402
import cv2
import yaml
import numpy as np
from collections import namedtuple
from multiprocessing import Process


def show_map(map_img):
    """Display map of waypoints in a separate process."""
    plt.imshow(map_img)
    plt.axis('off')
    plt.title('Waypoints (green=valid, red=too close to obstacle)')
    plt.show()


Waypoint = namedtuple('Waypoint', 'x y')


class FollowWaypointsClient(Node):
    def __init__(self):
        super().__init__('navigate_through_poses_client')
        self._action_client = ActionClient(self, FollowWaypoints, '/follow_waypoints')
        self.publisher = self.create_publisher(Empty, '/heatmap_generator_trigger', 1)

        self.declare_parameter('density', 8)
        self.declare_parameter('collision_range', 4)
        self.declare_parameter('path_to_yaml', 'map.yaml')
        self.declare_parameter('batch_size', 20)

        self.density = self.get_parameter('density').get_parameter_value().integer_value
        self.collision_range = self.get_parameter('collision_range').get_parameter_value().integer_value
        self.batch_size = self.get_parameter('batch_size').get_parameter_value().integer_value

        yaml_path = self.get_parameter('path_to_yaml').get_parameter_value().string_value
        with open(yaml_path, 'r') as file:
            data = yaml.safe_load(file)

        self.origin = Waypoint(data['origin'][0], data['origin'][1])
        self.resolution = data['resolution']

        image_path = data['image']
        if not os.path.isabs(image_path):
            image_path = os.path.join(os.path.dirname(yaml_path), image_path)

        self.map = cv2.imread(image_path)
        if self.map is None:
            self.get_logger().error(f'Failed to load map image: {image_path}')
            raise FileNotFoundError(f'Map image not found: {image_path}')

        self.robot_frame_waypoint_array = []
        self.batch_index = 0
        self.p = Process(target=show_map, args=(self.map,))

    def send_goal(self):
        """Generate waypoints and send first batch."""
        self._generate_waypoints()

        total = len(self.robot_frame_waypoint_array)
        self.get_logger().info(
            f'Generated {total} waypoints — sending in batches of {self.batch_size}')

        self._send_next_batch()

    def _generate_waypoints(self):
        """Generate waypoints from the occupancy map."""

        # ------------------------------------------------------------------
        # TODO 1: Generate collision-free waypoints from the occupancy map
        # ------------------------------------------------------------------
        # The saved occupancy map represents the environment as an image,
        # where each pixel corresponds to either free space, an obstacle,
        # or an unknown region. Before the robot can navigate, determine
        # which locations are safe to visit.
        #
        # Your task is to generate a list of valid sampling waypoints by:
        #
        #   1. Reading the occupancy information from the map image.
        #      (Hint: free space, obstacles and unknown regions have
        #      different pixel values.)
        #
        #   2. Creating an obstacle mask that marks every obstacle and
        #      unknown cell as occupied.
        #
        #   3. Inflating the obstacle mask using the configured
        #      collision_range so that locations too close to walls are
        #      also considered unsafe. This provides a safety margin for
        #      robot navigation.
        #
        #   4. Sampling the map every 'density' pixels instead of checking
        #      every pixel. This creates a uniform grid of candidate
        #      waypoints while reducing computation.
        #
        #   5. For every sampled location:
        #        • If it lies in free space and outside the inflated
        #          obstacle region, accept it as a valid waypoint.
        #        • Otherwise reject it.
        #
        #   6. Colour accepted waypoints green and rejected ones red on the
        #      map image for visualization.
        #
        #   7. Convert every accepted waypoint from image (pixel)
        #      coordinates into robot/map-frame coordinates using the map
        #      resolution and origin loaded from the YAML file, then store
        #      them in self.robot_frame_waypoint_array.
        #
        # At the end of this step, the robot should have a complete list of
        # safe navigation targets covering the environment.

        self.p.start()

        self.get_logger().info(
            f'{len(self.robot_frame_waypoint_array)} valid waypoints generated')

    def _send_next_batch(self):
        """Send the next batch of waypoints to Nav2."""

        start = self.batch_index * self.batch_size
        end = min(start + self.batch_size,
                  len(self.robot_frame_waypoint_array))
        batch = self.robot_frame_waypoint_array[start:end]

        if not batch:
            self.get_logger().info(
                'All batches complete — publishing trigger...')
            self.publisher.publish(Empty())

            if self.p.is_alive():
                self.p.kill()

            rclpy.shutdown()
            return

        self.get_logger().info(
            f'Sending batch {self.batch_index + 1}: '
            f'waypoints {start + 1}-{end} of '
            f'{len(self.robot_frame_waypoint_array)}')

        msg = FollowWaypoints.Goal()

        # ------------------------------------------------------------------
        # TODO 2: Convert sampled waypoints into Nav2 navigation goals
        # ------------------------------------------------------------------
        # Nav2 accepts navigation targets as PoseStamped messages rather
        # than simple (x, y) coordinates. Convert every waypoint in the
        # current batch into a navigation goal.
        #
        # Your task is to:
        #
        #   1. Iterate through every waypoint in the current batch.
        #
        #   2. Create a PoseStamped message for each waypoint.
        #
        #   3. Set:
        #        • frame_id = "map"
        #        • timestamp = current ROS time
        #
        #   4. Assign the waypoint's x and y coordinates to the pose.
        #      The robot should remain on the ground (z = 0).
        #
        #   5. Use a default orientation (identity quaternion) so the
        #      robot simply navigates to the waypoint without enforcing a
        #      specific heading.
        #
        #   6. Append every generated PoseStamped message to a list and
        #      assign that list to msg.poses.
        #
        # Once completed, the FollowWaypoints action server will receive
        # the batch and autonomously navigate through each waypoint in
        # sequence.
        
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(msg)
        self._send_goal_future.add_done_callback(self._response_callback)

    def _response_callback(self, future):
        goal_handle = future.result()

        self.get_logger().info(
            f'Batch {self.batch_index + 1} accepted by server')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self._result_callback)

    def _result_callback(self, future):
        self.get_logger().info(
            f'Batch {self.batch_index + 1} complete')

        self.batch_index += 1
        self._send_next_batch()


def main(args=None):
    rclpy.init(args=args)

    action_client = FollowWaypointsClient()
    action_client.send_goal()

    rclpy.spin(action_client)


if __name__ == '__main__':
    main()