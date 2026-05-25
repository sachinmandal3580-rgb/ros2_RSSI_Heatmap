// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosbot_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__struct.h"
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "geometry_msgs/msg/detail/point__functions.h"  // coordinates

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
bool cdr_serialize_geometry_msgs__msg__Point(
  const geometry_msgs__msg__Point * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
bool cdr_deserialize_geometry_msgs__msg__Point(
  eprosima::fastcdr::Cdr & cdr,
  geometry_msgs__msg__Point * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
size_t get_serialized_size_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
size_t max_serialized_size_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
bool cdr_serialize_key_geometry_msgs__msg__Point(
  const geometry_msgs__msg__Point * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
size_t get_serialized_size_key_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
size_t max_serialized_size_key_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rosbot_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point)();


using _RssiAtWaypoint__ros_msg_type = rosbot_interfaces__msg__RssiAtWaypoint;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_serialize_rosbot_interfaces__msg__RssiAtWaypoint(
  const rosbot_interfaces__msg__RssiAtWaypoint * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: coordinates
  {
    cdr_serialize_geometry_msgs__msg__Point(
      &ros_message->coordinates, cdr);
  }

  // Field name: rssi
  {
    cdr << ros_message->rssi;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_deserialize_rosbot_interfaces__msg__RssiAtWaypoint(
  eprosima::fastcdr::Cdr & cdr,
  rosbot_interfaces__msg__RssiAtWaypoint * ros_message)
{
  // Field name: coordinates
  {
    cdr_deserialize_geometry_msgs__msg__Point(cdr, &ros_message->coordinates);
  }

  // Field name: rssi
  {
    cdr >> ros_message->rssi;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t get_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RssiAtWaypoint__ros_msg_type * ros_message = static_cast<const _RssiAtWaypoint__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: coordinates
  current_alignment += get_serialized_size_geometry_msgs__msg__Point(
    &(ros_message->coordinates), current_alignment);

  // Field name: rssi
  {
    size_t item_size = sizeof(ros_message->rssi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t max_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: coordinates
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: rssi
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rosbot_interfaces__msg__RssiAtWaypoint;
    is_plain =
      (
      offsetof(DataType, rssi) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
bool cdr_serialize_key_rosbot_interfaces__msg__RssiAtWaypoint(
  const rosbot_interfaces__msg__RssiAtWaypoint * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: coordinates
  {
    cdr_serialize_key_geometry_msgs__msg__Point(
      &ros_message->coordinates, cdr);
  }

  // Field name: rssi
  {
    cdr << ros_message->rssi;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t get_serialized_size_key_rosbot_interfaces__msg__RssiAtWaypoint(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RssiAtWaypoint__ros_msg_type * ros_message = static_cast<const _RssiAtWaypoint__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: coordinates
  current_alignment += get_serialized_size_key_geometry_msgs__msg__Point(
    &(ros_message->coordinates), current_alignment);

  // Field name: rssi
  {
    size_t item_size = sizeof(ros_message->rssi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rosbot_interfaces
size_t max_serialized_size_key_rosbot_interfaces__msg__RssiAtWaypoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: coordinates
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: rssi
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rosbot_interfaces__msg__RssiAtWaypoint;
    is_plain =
      (
      offsetof(DataType, rssi) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _RssiAtWaypoint__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const rosbot_interfaces__msg__RssiAtWaypoint * ros_message = static_cast<const rosbot_interfaces__msg__RssiAtWaypoint *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_rosbot_interfaces__msg__RssiAtWaypoint(ros_message, cdr);
}

static bool _RssiAtWaypoint__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  rosbot_interfaces__msg__RssiAtWaypoint * ros_message = static_cast<rosbot_interfaces__msg__RssiAtWaypoint *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_rosbot_interfaces__msg__RssiAtWaypoint(cdr, ros_message);
}

static uint32_t _RssiAtWaypoint__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
      untyped_ros_message, 0));
}

static size_t _RssiAtWaypoint__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rosbot_interfaces__msg__RssiAtWaypoint(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_RssiAtWaypoint = {
  "rosbot_interfaces::msg",
  "RssiAtWaypoint",
  _RssiAtWaypoint__cdr_serialize,
  _RssiAtWaypoint__cdr_deserialize,
  _RssiAtWaypoint__get_serialized_size,
  _RssiAtWaypoint__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _RssiAtWaypoint__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_RssiAtWaypoint,
  get_message_typesupport_handle_function,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_hash,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_description,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rosbot_interfaces, msg, RssiAtWaypoint)() {
  return &_RssiAtWaypoint__type_support;
}

#if defined(__cplusplus)
}
#endif
