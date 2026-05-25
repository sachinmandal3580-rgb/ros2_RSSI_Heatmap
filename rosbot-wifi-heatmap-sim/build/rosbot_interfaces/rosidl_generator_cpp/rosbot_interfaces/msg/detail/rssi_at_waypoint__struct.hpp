// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosbot_interfaces/msg/rssi_at_waypoint.hpp"


#ifndef ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_HPP_
#define ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rosbot_interfaces__msg__RssiAtWaypoint __attribute__((deprecated))
#else
# define DEPRECATED__rosbot_interfaces__msg__RssiAtWaypoint __declspec(deprecated)
#endif

namespace rosbot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RssiAtWaypoint_
{
  using Type = RssiAtWaypoint_<ContainerAllocator>;

  explicit RssiAtWaypoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : coordinates(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rssi = 0;
    }
  }

  explicit RssiAtWaypoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : coordinates(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rssi = 0;
    }
  }

  // field types and members
  using _coordinates_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _coordinates_type coordinates;
  using _rssi_type =
    int8_t;
  _rssi_type rssi;

  // setters for named parameter idiom
  Type & set__coordinates(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->coordinates = _arg;
    return *this;
  }
  Type & set__rssi(
    const int8_t & _arg)
  {
    this->rssi = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rosbot_interfaces__msg__RssiAtWaypoint
    std::shared_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rosbot_interfaces__msg__RssiAtWaypoint
    std::shared_ptr<rosbot_interfaces::msg::RssiAtWaypoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RssiAtWaypoint_ & other) const
  {
    if (this->coordinates != other.coordinates) {
      return false;
    }
    if (this->rssi != other.rssi) {
      return false;
    }
    return true;
  }
  bool operator!=(const RssiAtWaypoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RssiAtWaypoint_

// alias to use template instance with default allocator
using RssiAtWaypoint =
  rosbot_interfaces::msg::RssiAtWaypoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rosbot_interfaces

#endif  // ROSBOT_INTERFACES__MSG__DETAIL__RSSI_AT_WAYPOINT__STRUCT_HPP_
