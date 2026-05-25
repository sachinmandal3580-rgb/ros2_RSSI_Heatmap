import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/sachin/rosbot-wifi-heatmap-sim/install/waypoint_publisher_package'
