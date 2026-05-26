import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/sachin/rosbot-wifi-heatmap-sim/install/rssi_heatmap_generator_package'
