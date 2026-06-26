# ROS
import rclpy
from rclpy.node import Node
from rosbot_interfaces.msg import RssiAtWaypoint
from std_msgs.msg import Empty
import os
from collections import namedtuple
import yaml
import cv2
from .submodules.generate_heatmap import generate_heatmap, add_heatmap, add_waypoints, cmapGR
import tkinter  # noqa: F401
from multiprocessing import Process
import datetime
from matplotlib import gridspec, pyplot as plt
import matplotlib
matplotlib.use('TkAgg')

RssiWaypoint = namedtuple('RssiWaypoint', 'x y rssi')
Waypoint = namedtuple('Waypoint', 'x y')

class HeatmapGenerator(Node):
    def __init__(self):
        super().__init__('heatmap_generator')
        self.create_subscription(RssiAtWaypoint,'/rssi_data',self.rssi_data_callback,10)
        self.create_subscription(Empty,'/heatmap_generator_trigger',self.trigger_callback,10)

        self.declare_parameter('path_to_yaml','map.yaml')
        self.declare_parameter('heatmaps_dir',os.path.expanduser('~/ros2_RSSI_Heatmap/src/heatmaps'))

        yaml_path=self.get_parameter('path_to_yaml').get_parameter_value().string_value
        with open(yaml_path,'r') as file:
            map_data=yaml.safe_load(file)

        self.map_origin=Waypoint(map_data['origin'][0],map_data['origin'][1])
        self.map_resolution=map_data['resolution']

        image_path=map_data['image']
        if not os.path.isabs(image_path):
            image_path=os.path.join(os.path.dirname(yaml_path),image_path)

        self.map=cv2.imread(image_path)
        if self.map is None:
            raise FileNotFoundError(image_path)

        self.rssi_data=[]
        self.heatmaps_dir=self.get_parameter('heatmaps_dir').get_parameter_value().string_value
        os.makedirs(self.heatmaps_dir,exist_ok=True)

    def rssi_data_callback(self,msg):

        # ---------------------------------------------------------------
        # TODO 1: Convert world coordinates into map pixel coordinates
        # ---------------------------------------------------------------
        # RSSI measurements are received in the map (world) coordinate frame,
        # expressed in meters. However, the heatmap is generated on the map
        # image, whose coordinate system is defined in pixels.
        #
        # Using the map origin and map resolution loaded from the YAML file:
        #
        #   1. Translate the robot's world position relative to the map origin.
        #   2. Convert the translated position from meters to pixels using the
        #      map resolution (meters/pixel).
        #   3. Invert the Y coordinate because image coordinates start at the
        #      top-left corner, whereas ROS map coordinates originate from the
        #      bottom-left.
        #   4. Create an RssiWaypoint containing the converted pixel position
        #      and the received RSSI value, then store it for later processing.
        #
        # The generated pixel coordinates will later be used for waypoint
        # visualization and spatial interpolation.

        x=int((msg.coordinates.x-self.map_origin.x)/self.map_resolution)
        y=len(self.map)-int((msg.coordinates.y-self.map_origin.y)/self.map_resolution)
        self.rssi_data.append(RssiWaypoint(x,y,int(msg.rssi)))

    def display_maps(self,*args):
        pass

    def trigger_callback(self,msg):
        if len(self.rssi_data)<3:
            return

        map_with_waypoints=add_waypoints(self.map,self.rssi_data)
        # ---------------------------------------------------------------
        # TODO 2: Generate spatial RSSI heatmaps
        # ---------------------------------------------------------------
        # At this stage, RSSI measurements exist only at discrete waypoint
        # locations visited by the robot. To estimate signal strength across
        # the entire environment, these sparse samples must be spatially
        # interpolated into continuous heatmaps.
        #
        # Generate two separate heatmaps:
        #
        #   • Absolute Heatmap:
        #       Displays the actual RSSI values (dBm) measured throughout
        #       the environment.
        #
        #   • Relative Heatmap:
        #       Normalizes the measurements with respect to the collected
        #       dataset, improving visualization when comparing coverage
        #       within a single survey.
        #
        # The relative heatmap generation should also return the minimum and
        # maximum RSSI values so the colorbar can accurately represent the
        # measurement range.
        # This separation allows users to analyze both the true signal strength
        # and the relative signal distribution within a single survey.

        heatmap=generate_heatmap(
            self.rssi_data,len(self.map),len(self.map[0]),1,filtered=False)[0]

        rel_heatmap,rssi_bounds=generate_heatmap(
            self.rssi_data,len(self.map),len(self.map[0]),1,
            filtered=True,relative=True)

        # ---------------------------------------------------------------
        # TODO 3: Visualize and export the completed survey
        # ---------------------------------------------------------------
        # After interpolation, overlay each generated heatmap onto the
        # original occupancy map to provide spatial context for the wireless
        # signal distribution.
        #
        # The completed survey should then:
        #
        #   1. Display the waypoint map, absolute heatmap, and relative
        #      heatmap in separate visualization windows.
        #
        #   2. Save all generated images to the configured output directory.
        #
        #   3. Append a timestamp to each filename so previous survey results
        #      are preserved instead of being overwritten.
        #
        # This marks the completion of the autonomous signal-mapping pipeline,
        # transforming raw RSSI measurements into an interpretable spatial
        # visualization of wireless coverage.

        final_map=add_heatmap(self.map,heatmap)
        rel_final_map=add_heatmap(self.map,rel_heatmap)

        p=Process(target=self.display_maps,
                  args=(map_with_waypoints,heatmap,final_map,
                        rel_heatmap,rel_final_map,rssi_bounds))
        p.start()

        now=datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        cv2.imwrite(os.path.join(self.heatmaps_dir,f'waypoints_{now}.png'),cv2.cvtColor(map_with_waypoints,cv2.COLOR_RGB2BGR))
        cv2.imwrite(os.path.join(self.heatmaps_dir,f'heatmap_abs_{now}.png'),cv2.cvtColor(final_map,cv2.COLOR_RGB2BGR))
        cv2.imwrite(os.path.join(self.heatmaps_dir,f'heatmap_rel_{now}.png'),cv2.cvtColor(rel_final_map,cv2.COLOR_RGB2BGR))

def main(args=None):
    rclpy.init(args=args)
    node=HeatmapGenerator()
    rclpy.spin(node)

if __name__=="__main__":
    main()
