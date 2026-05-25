#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to rosbot_interfaces__msg__RssiAtWaypoint
/// Interface for measuring rssi at waypoints
/// Waypoint coordinates

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RssiAtWaypoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub coordinates: geometry_msgs::msg::Point,

    /// Rssi value (from -100 to 0)
    pub rssi: i8,

}



impl Default for RssiAtWaypoint {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RssiAtWaypoint::default())
  }
}

impl rosidl_runtime_rs::Message for RssiAtWaypoint {
  type RmwMsg = super::msg::rmw::RssiAtWaypoint;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        coordinates: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.coordinates)).into_owned(),
        rssi: msg.rssi,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        coordinates: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.coordinates)).into_owned(),
      rssi: msg.rssi,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      coordinates: geometry_msgs::msg::Point::from_rmw_message(msg.coordinates),
      rssi: msg.rssi,
    }
  }
}


