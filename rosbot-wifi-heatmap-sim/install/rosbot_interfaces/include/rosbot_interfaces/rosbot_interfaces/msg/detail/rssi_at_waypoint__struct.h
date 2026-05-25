// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosbot_interfaces/msg/rssi_at_waypoint.h"


#ifndef ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_H_
#define ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/RssiAtWaypoint in the package rosbot_interfaces.
/**
  * Interface for measuring rssi at waypoints
  * Waypoint coordinates
 */
typedef struct rosbot_interfaces__msg__RssiAtWaypoint
{
  geometry_msgs__msg__Point coordinates;
  /// Rssi value (from -100 to 0)
  int8_t rssi;
} rosbot_interfaces__msg__RssiAtWaypoint;

// Struct for a sequence of rosbot_interfaces__msg__RssiAtWaypoint.
typedef struct rosbot_interfaces__msg__RssiAtWaypoint__Sequence
{
  rosbot_interfaces__msg__RssiAtWaypoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rosbot_interfaces__msg__RssiAtWaypoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_H_
