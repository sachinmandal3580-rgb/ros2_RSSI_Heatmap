// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosbot_interfaces/msg/rssi_at_waypoint.hpp"


#ifndef ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__TRAITS_HPP_
#define ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace rosbot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const RssiAtWaypoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: coordinates
  {
    out << "coordinates: ";
    to_flow_style_yaml(msg.coordinates, out);
    out << ", ";
  }

  // member: rssi
  {
    out << "rssi: ";
    rosidl_generator_traits::value_to_yaml(msg.rssi, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RssiAtWaypoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: coordinates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coordinates:\n";
    to_block_style_yaml(msg.coordinates, out, indentation + 2);
  }

  // member: rssi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rssi: ";
    rosidl_generator_traits::value_to_yaml(msg.rssi, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RssiAtWaypoint & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rosbot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rosbot_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rosbot_interfaces::msg::RssiAtWaypoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  rosbot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rosbot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rosbot_interfaces::msg::RssiAtWaypoint & msg)
{
  return rosbot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rosbot_interfaces::msg::RssiAtWaypoint>()
{
  return "rosbot_interfaces::msg::RssiAtWaypoint";
}

template<>
inline const char * name<rosbot_interfaces::msg::RssiAtWaypoint>()
{
  return "rosbot_interfaces/msg/RssiAtWaypoint";
}

template<>
struct has_fixed_size<rosbot_interfaces::msg::RssiAtWaypoint>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<rosbot_interfaces::msg::RssiAtWaypoint>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<rosbot_interfaces::msg::RssiAtWaypoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__TRAITS_HPP_
