// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosbot_interfaces/msg/rssi_at_waypoint.hpp"


#ifndef ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__BUILDER_HPP_
#define ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rosbot_interfaces
{

namespace msg
{

namespace builder
{

class Init_RssiAtWaypoint_rssi
{
public:
  explicit Init_RssiAtWaypoint_rssi(::rosbot_interfaces::msg::RssiAtWaypoint & msg)
  : msg_(msg)
  {}
  ::rosbot_interfaces::msg::RssiAtWaypoint rssi(::rosbot_interfaces::msg::RssiAtWaypoint::_rssi_type arg)
  {
    msg_.rssi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rosbot_interfaces::msg::RssiAtWaypoint msg_;
};

class Init_RssiAtWaypoint_coordinates
{
public:
  Init_RssiAtWaypoint_coordinates()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RssiAtWaypoint_rssi coordinates(::rosbot_interfaces::msg::RssiAtWaypoint::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return Init_RssiAtWaypoint_rssi(msg_);
  }

private:
  ::rosbot_interfaces::msg::RssiAtWaypoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rosbot_interfaces::msg::RssiAtWaypoint>()
{
  return rosbot_interfaces::msg::builder::Init_RssiAtWaypoint_coordinates();
}

}  // namespace rosbot_interfaces

#endif  // ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__BUILDER_HPP_
