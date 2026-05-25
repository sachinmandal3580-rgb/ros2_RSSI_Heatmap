#include <chrono>
#include <thread>

#include "nav2_read_rssi_at_waypoint/read_rssi_at_waypoint.hpp"
#include "nav2_read_rssi_at_waypoint/simulated_rssi.hpp"
#include "nav2_util/node_utils.hpp"
#include "rosbot_interfaces/msg/rssi_at_waypoint.hpp"

namespace nav2_read_rssi_at_waypoint
{

ReadRssiAtWaypoint::ReadRssiAtWaypoint()
: is_enabled_(true), n_measurements_(10),
  ap_x_(0.0), ap_y_(0.0), tx_power_(-30.0), path_loss_exponent_(3.0) {}

ReadRssiAtWaypoint::~ReadRssiAtWaypoint() {}

void ReadRssiAtWaypoint::initialize(
  const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent,
  const std::string & plugin_name)
{
  auto node = parent.lock();
  if (!node) {
    throw std::runtime_error{"Failed to lock node in ReadRssiAtWaypoint plugin!"};
  }
  logger_ = node->get_logger();
  RCLCPP_INFO(logger_, "Initializing ReadRssiAtWaypoint (simulation mode)...");

  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".enabled", rclcpp::ParameterValue(true));
  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".number_of_measurements", rclcpp::ParameterValue(10));
  // Simulated AP parameters
  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".ap_x", rclcpp::ParameterValue(0.0));
  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".ap_y", rclcpp::ParameterValue(0.0));
  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".tx_power", rclcpp::ParameterValue(-30.0));
  nav2_util::declare_parameter_if_not_declared(
    node, plugin_name + ".path_loss_exponent", rclcpp::ParameterValue(3.0));

  node->get_parameter(plugin_name + ".enabled", is_enabled_);
  node->get_parameter(plugin_name + ".number_of_measurements", n_measurements_);
  node->get_parameter(plugin_name + ".ap_x", ap_x_);
  node->get_parameter(plugin_name + ".ap_y", ap_y_);
  node->get_parameter(plugin_name + ".tx_power", tx_power_);
  node->get_parameter(plugin_name + ".path_loss_exponent", path_loss_exponent_);

  if (n_measurements_ == 0) {
    is_enabled_ = false;
  }

  if (is_enabled_) {
    RCLCPP_INFO(logger_,
      "Simulated RSSI plugin enabled  —  AP at (%.1f, %.1f), tx_power=%.0f, n=%.1f",
      ap_x_, ap_y_, tx_power_, path_loss_exponent_);
    rssi_data_publisher =
      node->create_publisher<rosbot_interfaces::msg::RssiAtWaypoint>("rssi_data", 10);
    rssi_data_publisher->on_activate();
  }
}

bool ReadRssiAtWaypoint::processAtWaypoint(
  const geometry_msgs::msg::PoseStamped & curr_pose,
  const int & curr_pose_index)
{
  (void)curr_pose_index;
  if (!is_enabled_) {
    return true;
  }

  RCLCPP_INFO(logger_, "Measuring simulated RSSI at waypoint %d ...", curr_pose_index);

  double robot_x = curr_pose.pose.position.x;
  double robot_y = curr_pose.pose.position.y;

  int rssi_sum = 0;
  int valid = 0;
  for (int i = 0; i < n_measurements_; ++i) {
    int rssi = simulate_rssi(robot_x, robot_y, ap_x_, ap_y_, tx_power_, path_loss_exponent_);
    if (rssi <= 0) {
      rssi_sum += rssi;
      ++valid;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // faster in sim
  }

  auto msg = rosbot_interfaces::msg::RssiAtWaypoint();
  msg.coordinates.x = robot_x;
  msg.coordinates.y = robot_y;
  msg.coordinates.z = curr_pose.pose.position.z;
  msg.rssi = (valid > 0) ? static_cast<int8_t>(rssi_sum / valid) : -100;

  RCLCPP_INFO(logger_, "  RSSI = %d dBm at (%.2f, %.2f)", msg.rssi, robot_x, robot_y);
  rssi_data_publisher->publish(msg);
  return true;
}

}  // namespace nav2_read_rssi_at_waypoint

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  nav2_read_rssi_at_waypoint::ReadRssiAtWaypoint,
  nav2_core::WaypointTaskExecutor)
