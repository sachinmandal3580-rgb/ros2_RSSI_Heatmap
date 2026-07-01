#ifndef SIMULATED_RSSI_HPP_
#define SIMULATED_RSSI_HPP_

#include <cmath>
#include <random>

/**
 * Simulate WiFi RSSI using a log-distance path-loss model.
 *
 *   RSSI = tx_power - 10 * n * log10(d / d0) + noise
 *
 * @param robot_x  Robot X position in map frame
 * @param robot_y  Robot Y position in map frame
 * @param ap_x     Access-point X position
 * @param ap_y     Access-point Y position
 * @param tx_power Transmit power (dBm) at reference distance
 * @param n        Path-loss exponent (2=free-space, 3-4=indoor)
 */
inline int simulate_rssi(
  double robot_x, double robot_y,
  double ap_x, double ap_y,
  double tx_power = -30.0,
  double n = 3.0)
{
  double dx = robot_x - ap_x;
  double dy = robot_y - ap_y;
  double dist = std::sqrt(dx * dx + dy * dy);

  const double d0 = 1.0;
  if (dist < d0) {
    dist = d0;
  }

  // ---------------------------------------------------------------
  // TODO 1 : Compute the simulated RSSI value
  // ---------------------------------------------------------------
  // Using the computed distance, estimate the received signal
  // strength between the robot and the Access Point.
  //
  // Requirements:
  //   1. Apply the log-distance path-loss equation:
  //
  //          RSSI = tx_power - 10 * n * log10(d / d0)
  //
  //   2. Add a small Gaussian noise component to simulate
  //      real-world wireless signal fluctuations.
  //
  //   3. Round the computed RSSI to the nearest integer.
  //
  //   4. Clamp the final RSSI value to the valid range
  //      [-100, 0] dBm.
  //
  //   5. Return the simulated RSSI value.
}

#endif  // SIMULATED_RSSI_HPP_
