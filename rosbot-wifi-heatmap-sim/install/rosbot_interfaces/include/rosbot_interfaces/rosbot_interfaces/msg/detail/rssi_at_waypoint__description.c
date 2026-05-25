// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice

#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rosbot_interfaces
const rosidl_type_hash_t *
rosbot_interfaces__msg__RssiAtWaypoint__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9a, 0x5f, 0x4c, 0x55, 0x62, 0x4e, 0x4f, 0xa7,
      0x03, 0x16, 0x50, 0x3c, 0x4e, 0x7a, 0x6f, 0xd9,
      0xde, 0x10, 0xae, 0x10, 0x60, 0xdf, 0xd7, 0x09,
      0x88, 0x4a, 0x5b, 0x26, 0x81, 0x01, 0x96, 0xef,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
#endif

static char rosbot_interfaces__msg__RssiAtWaypoint__TYPE_NAME[] = "rosbot_interfaces/msg/RssiAtWaypoint";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";

// Define type names, field names, and default values
static char rosbot_interfaces__msg__RssiAtWaypoint__FIELD_NAME__coordinates[] = "coordinates";
static char rosbot_interfaces__msg__RssiAtWaypoint__FIELD_NAME__rssi[] = "rssi";

static rosidl_runtime_c__type_description__Field rosbot_interfaces__msg__RssiAtWaypoint__FIELDS[] = {
  {
    {rosbot_interfaces__msg__RssiAtWaypoint__FIELD_NAME__coordinates, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {rosbot_interfaces__msg__RssiAtWaypoint__FIELD_NAME__rssi, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rosbot_interfaces__msg__RssiAtWaypoint__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rosbot_interfaces__msg__RssiAtWaypoint__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rosbot_interfaces__msg__RssiAtWaypoint__TYPE_NAME, 36, 36},
      {rosbot_interfaces__msg__RssiAtWaypoint__FIELDS, 2, 2},
    },
    {rosbot_interfaces__msg__RssiAtWaypoint__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "#Interface for measuring rssi at waypoints\n"
  "#Waypoint coordinates\n"
  "geometry_msgs/Point coordinates\n"
  "#Rssi value (from -100 to 0)\n"
  "int8 rssi";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rosbot_interfaces__msg__RssiAtWaypoint__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rosbot_interfaces__msg__RssiAtWaypoint__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 135, 135},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rosbot_interfaces__msg__RssiAtWaypoint__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rosbot_interfaces__msg__RssiAtWaypoint__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
