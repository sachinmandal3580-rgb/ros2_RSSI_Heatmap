# ROS
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from nav2_msgs.action import FollowWaypoints
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Empty
# Utils
import os
import tkinter  # noqa: F401 — imported so matplotlib can use TkAgg
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt  # noqa: E402
import cv2
import yaml
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
        # Action client
        self._action_client = ActionClient(self, FollowWaypoints, '/follow_waypoints')
        # Trigger publisher
        self.publisher = self.create_publisher(Empty, '/heatmap_generator_trigger', 1)
        # User params
        self.declare_parameter('density', 8)
        self.declare_parameter('collision_range', 4)
        self.declare_parameter('path_to_yaml', 'map.yaml')
        self.density = self.get_parameter('density').get_parameter_value().integer_value
        self.collision_range = self.get_parameter('collision_range').get_parameter_value().integer_value
        # Map params
        yaml_path = self.get_parameter('path_to_yaml').get_parameter_value().string_value
        with open(yaml_path, 'r') as file:
            data = yaml.safe_load(file)
        self.origin = Waypoint(data['origin'][0], data['origin'][1])
        self.resolution = data['resolution']
        # Resolve image path relative to the yaml file
        image_path = data['image']
        if not os.path.isabs(image_path):
            image_path = os.path.join(os.path.dirname(yaml_path), image_path)
        self.map = cv2.imread(image_path)
        if self.map is None:
            self.get_logger().error(f'Failed to load map image: {image_path}')
            raise FileNotFoundError(f'Map image not found: {image_path}')
        self.waypoint_array = []
        self.robot_frame_waypoint_array = []
        self.p = Process(target=show_map, args=(self.map,))

    def send_goal(self):
        """Generate waypoints and send to FollowWaypoints action."""
        self.set_waypoints()
        msg = FollowWaypoints.Goal()
        goals = []
        for wp in self.robot_frame_waypoint_array:
            waypoint = PoseStamped()
            waypoint.header.frame_id = 'map'
            waypoint.header.stamp = self.get_clock().now().to_msg()
            waypoint.pose.position.x = wp.x
            waypoint.pose.position.y = wp.y
            waypoint.pose.position.z = 0.0
            waypoint.pose.orientation.w = 1.0
            goals.append(waypoint)
        msg.poses = goals
        self.get_logger().info(f'Sending {len(goals)} waypoints, waiting for server...')
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(msg)
        self._send_goal_future.add_done_callback(self.response_callback)

    def response_callback(self, future):
        goal_handle = future.result()
        self.get_logger().info('Goal received by server')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.result_callback)

    def result_callback(self, future):
        msg = Empty()
        self.get_logger().info('All waypoints visited — publishing trigger...')
        self.publisher.publish(msg)
        self.p.kill()
        self.get_logger().info('Done, shutting down.')
        rclpy.shutdown()

    def set_waypoints(self):
        """Create array of waypoints based on saved map and user params."""
        waypoint_array = []
        for i in range(0, len(self.map), self.density):
            for j in range(0, len(self.map[0]), self.density):
                if self.map[i][j][0] == 254:
                    waypoint_array.append(Waypoint(i, j))

        valid_waypoint_array = [
            wp for wp in waypoint_array if self.check_safety(wp)
        ]

        for wp in valid_waypoint_array:
            self.map[wp.x, wp.y] = [0, 255, 0]
        self.p.start()

        for wp in valid_waypoint_array:
            x = wp.y * self.resolution + self.origin.x
            y = (len(self.map) - 1 - wp.x) * self.resolution + self.origin.y
            self.robot_frame_waypoint_array.append(Waypoint(x, y))

        self.get_logger().info(f'Generated {len(self.robot_frame_waypoint_array)} valid waypoints')

    def check_safety(self, waypoint: Waypoint):
        """Check if waypoint is not too close to occupied or unknown space."""
        xbegin = max(0, waypoint.x - self.collision_range)
        xend = min(len(self.map) - 1, waypoint.x + self.collision_range)
        ybegin = max(0, waypoint.y - self.collision_range)
        yend = min(len(self.map[0]) - 1, waypoint.y + self.collision_range)
        for i in range(xbegin, xend + 1):
            for j in range(ybegin, yend + 1):
                if self.map[i][j][0] == 205 or self.map[i][j][0] == 0:
                    self.map[waypoint.x][waypoint.y] = [255, 0, 0]
                    return False
        return True


def main(args=None):
    rclpy.init(args=args)
    action_client = FollowWaypointsClient()
    action_client.send_goal()
    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
