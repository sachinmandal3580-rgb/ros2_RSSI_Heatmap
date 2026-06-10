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
        self.declare_parameter('batch_size', 20)   # NEW: send N waypoints at a time

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
        """Generate waypoints using fast numpy safety check."""
        # Build obstacle mask: True where pixel is obstacle (0) or unknown (205)
        gray = self.map[:, :, 0]
        obstacle_mask = (gray == 0) | (gray == 205)

        # Dilate the obstacle mask by collision_range — equivalent to the old nested loop
        # but done in one vectorised operation
        kernel_size = 2 * self.collision_range + 1
        kernel = np.ones((kernel_size, kernel_size), np.uint8)
        dilated = cv2.dilate(obstacle_mask.astype(np.uint8), kernel, iterations=1)

        valid_waypoints = []
        for i in range(0, len(self.map), self.density):
            for j in range(0, len(self.map[0]), self.density):
                if gray[i][j] == 254:  # free space
                    if dilated[i][j] == 0:  # not near obstacle
                        self.map[i, j] = [0, 255, 0]   # green
                        valid_waypoints.append(Waypoint(i, j))
                    else:
                        self.map[i, j] = [255, 0, 0]   # red

        self.p.start()

        for wp in valid_waypoints:
            x = wp.y * self.resolution + self.origin.x
            y = (len(self.map) - 1 - wp.x) * self.resolution + self.origin.y
            self.robot_frame_waypoint_array.append(Waypoint(x, y))

        self.get_logger().info(
            f'{len(self.robot_frame_waypoint_array)} valid waypoints from '
            f'{len(valid_waypoints)} candidates')

    def _send_next_batch(self):
        """Send the next batch of waypoints to Nav2."""
        start = self.batch_index * self.batch_size
        end = min(start + self.batch_size, len(self.robot_frame_waypoint_array))
        batch = self.robot_frame_waypoint_array[start:end]

        if not batch:
            # All batches done
            self.get_logger().info('All batches complete — publishing trigger...')
            msg = Empty()
            self.publisher.publish(msg)
            if self.p.is_alive():
                self.p.kill()
            rclpy.shutdown()
            return

        self.get_logger().info(
            f'Sending batch {self.batch_index + 1}: '
            f'waypoints {start + 1}–{end} of {len(self.robot_frame_waypoint_array)}')

        msg = FollowWaypoints.Goal()
        goals = []
        for wp in batch:
            waypoint = PoseStamped()
            waypoint.header.frame_id = 'map'
            waypoint.header.stamp = self.get_clock().now().to_msg()
            waypoint.pose.position.x = wp.x
            waypoint.pose.position.y = wp.y
            waypoint.pose.position.z = 0.0
            waypoint.pose.orientation.w = 1.0
            goals.append(waypoint)
        msg.poses = goals

        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(msg)
        self._send_goal_future.add_done_callback(self._response_callback)

    def _response_callback(self, future):
        goal_handle = future.result()
        self.get_logger().info(f'Batch {self.batch_index + 1} accepted by server')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self._result_callback)

    def _result_callback(self, future):
        self.get_logger().info(f'Batch {self.batch_index + 1} complete')
        self.batch_index += 1
        self._send_next_batch()


def main(args=None):
    rclpy.init(args=args)
    action_client = FollowWaypointsClient()
    action_client.send_goal()
    rclpy.spin(action_client)


if __name__ == '__main__':
    main()