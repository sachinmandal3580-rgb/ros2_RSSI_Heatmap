// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__functions.h"
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rosbot_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void RssiAtWaypoint_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rosbot_interfaces::msg::RssiAtWaypoint(_init);
}

void RssiAtWaypoint_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rosbot_interfaces::msg::RssiAtWaypoint *>(message_memory);
  typed_message->~RssiAtWaypoint();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RssiAtWaypoint_message_member_array[2] = {
  {
    "coordinates",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Point>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rosbot_interfaces::msg::RssiAtWaypoint, coordinates),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "rssi",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rosbot_interfaces::msg::RssiAtWaypoint, rssi),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RssiAtWaypoint_message_members = {
  "rosbot_interfaces::msg",  // message namespace
  "RssiAtWaypoint",  // message name
  2,  // number of fields
  sizeof(rosbot_interfaces::msg::RssiAtWaypoint),
  false,  // has_any_key_member_
  RssiAtWaypoint_message_member_array,  // message members
  RssiAtWaypoint_init_function,  // function to initialize message memory (memory has to be allocated)
  RssiAtWaypoint_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RssiAtWaypoint_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RssiAtWaypoint_message_members,
  get_message_typesupport_handle_function,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_hash,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_description,
  &rosbot_interfaces__msg__RssiAtWaypoint__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rosbot_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rosbot_interfaces::msg::RssiAtWaypoint>()
{
  return &::rosbot_interfaces::msg::rosidl_typesupport_introspection_cpp::RssiAtWaypoint_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rosbot_interfaces, msg, RssiAtWaypoint)() {
  return &::rosbot_interfaces::msg::rosidl_typesupport_introspection_cpp::RssiAtWaypoint_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
