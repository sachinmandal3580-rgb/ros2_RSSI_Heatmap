// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice
#ifndef ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "rosbot_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_serialize_rosbot_interfaces__msg__RssiAtWaypoint(
  const rosbot_interfaces__msg__RssiAtWaypoint * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_deserialize_rosbot_interfaces__msg__RssiAtWaypoint(
  eprosima::fastcdr::Cdr &,
  rosbot_interfaces__msg__RssiAtWaypoint * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t get_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t max_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_serialize_key_rosbot_interfaces__msg__RssiAtWaypoint(
  const rosbot_interfaces__msg__RssiAtWaypoint * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t get_serialized_size_key_rosbot_interfaces__msg__RssiAtWaypoint(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t max_serialized_size_key_rosbot_interfaces__msg__RssiAtWaypoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rosbot_interfaces, msg, RssiAtWaypoint)();

#ifdef __cplusplus
}
#endif

#endif  // ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
