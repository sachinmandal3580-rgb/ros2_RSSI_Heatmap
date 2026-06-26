# AUTONOMOUS SPATIAL SIGNAL MAPPER

---

## Problem Statement

Wireless connectivity has become a critical part of modern buildings, warehouses, hospitals, campuses, and industrial facilities. However, understanding how signal strength varies across a large environment remains a time-consuming and largely manual task.

Traditional site surveys require engineers to walk through buildings with handheld devices, collecting signal measurements at different locations. These surveys are slow, inconsistent, and difficult to reproduce, especially in large or frequently changing environments.

What if a robot could perform this survey autonomously?

This project explores that idea by developing an autonomous robotic system capable of navigating an environment, collecting wireless signal measurements, and transforming those measurements into an intuitive spatial heatmap.

Rather than relying on human operators, the robot systematically visits every reachable location, records simulated RSSI values, and builds a complete picture of wireless coverage across the environment.

The result is an automated site-survey pipeline that combines autonomous navigation, environmental mapping, wireless signal modeling, and data visualization.

---

## The Story

Imagine you're responsible for maintaining the wireless network inside a large office building.

Employees complain about slow internet near conference rooms, dropped connections in hallways, and unreliable coverage around stairwells. The access points appear to be functioning correctly, yet nobody knows exactly where the weak spots are.

Sending an engineer to manually walk the building with a laptop or smartphone is tedious, expensive, and rarely produces consistent results.

Instead, a mobile robot is deployed.

The robot first creates a map of the building using SLAM. Once the environment is known, it localizes itself and begins a systematic survey.

It plans paths to hundreds of predefined waypoints, stopping briefly at each location to measure the received signal strength from nearby wireless access points. Every measurement is tagged with its position and stored for later analysis.

After the survey is complete, the collected data is interpolated into a continuous heatmap, revealing areas of strong coverage, weak reception, and dead zones that would otherwise remain invisible.

What began as thousands of individual signal measurements becomes a clear visual representation of the building's wireless environment.

The robot doesn't simply move—it explores, measures, analyzes, and visualizes.

---

## Objective

Develop a fully autonomous ROS 2 system capable of:

- Building a map of an unknown environment
- Localizing itself within the map
- Generating a complete waypoint survey
- Navigating autonomously using Nav2
- Measuring simulated WiFi RSSI at every waypoint
- Aggregating all collected measurements
- Producing a spatial wireless signal heatmap

The complete workflow is:

**Map → Localize → Navigate → Measure → Aggregate → Visualize**

This project demonstrates how autonomous robots can be used for wireless site surveying, infrastructure monitoring, and environmental sensing without human intervention.

# What you're given


