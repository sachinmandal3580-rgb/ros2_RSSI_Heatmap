// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rosbot_interfaces:msg/RssiAtWaypoint.idl
// generated code does not contain a copyright notice
#include "rosbot_interfaces/msg/detail/rssi_at_waypoint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `coordinates`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
rosbot_interfaces__msg__RssiAtWaypoint__init(rosbot_interfaces__msg__RssiAtWaypoint * msg)
{
  if (!msg) {
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Point__init(&msg->coordinates)) {
    rosbot_interfaces__msg__RssiAtWaypoint__fini(msg);
    return false;
  }
  // rssi
  return true;
}

void
rosbot_interfaces__msg__RssiAtWaypoint__fini(rosbot_interfaces__msg__RssiAtWaypoint * msg)
{
  if (!msg) {
    return;
  }
  // coordinates
  geometry_msgs__msg__Point__fini(&msg->coordinates);
  // rssi
}

bool
rosbot_interfaces__msg__RssiAtWaypoint__are_equal(const rosbot_interfaces__msg__RssiAtWaypoint * lhs, const rosbot_interfaces__msg__RssiAtWaypoint * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->coordinates), &(rhs->coordinates)))
  {
    return false;
  }
  // rssi
  if (lhs->rssi != rhs->rssi) {
    return false;
  }
  return true;
}

bool
rosbot_interfaces__msg__RssiAtWaypoint__copy(
  const rosbot_interfaces__msg__RssiAtWaypoint * input,
  rosbot_interfaces__msg__RssiAtWaypoint * output)
{
  if (!input || !output) {
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Point__copy(
      &(input->coordinates), &(output->coordinates)))
  {
    return false;
  }
  // rssi
  output->rssi = input->rssi;
  return true;
}

rosbot_interfaces__msg__RssiAtWaypoint *
rosbot_interfaces__msg__RssiAtWaypoint__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosbot_interfaces__msg__RssiAtWaypoint * msg = (rosbot_interfaces__msg__RssiAtWaypoint *)allocator.allocate(sizeof(rosbot_interfaces__msg__RssiAtWaypoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rosbot_interfaces__msg__RssiAtWaypoint));
  bool success = rosbot_interfaces__msg__RssiAtWaypoint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rosbot_interfaces__msg__RssiAtWaypoint__destroy(rosbot_interfaces__msg__RssiAtWaypoint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rosbot_interfaces__msg__RssiAtWaypoint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__init(rosbot_interfaces__msg__RssiAtWaypoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosbot_interfaces__msg__RssiAtWaypoint * data = NULL;

  if (size) {
    data = (rosbot_interfaces__msg__RssiAtWaypoint *)allocator.zero_allocate(size, sizeof(rosbot_interfaces__msg__RssiAtWaypoint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rosbot_interfaces__msg__RssiAtWaypoint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rosbot_interfaces__msg__RssiAtWaypoint__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__fini(rosbot_interfaces__msg__RssiAtWaypoint__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rosbot_interfaces__msg__RssiAtWaypoint__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rosbot_interfaces__msg__RssiAtWaypoint__Sequence *
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosbot_interfaces__msg__RssiAtWaypoint__Sequence * array = (rosbot_interfaces__msg__RssiAtWaypoint__Sequence *)allocator.allocate(sizeof(rosbot_interfaces__msg__RssiAtWaypoint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rosbot_interfaces__msg__RssiAtWaypoint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__destroy(rosbot_interfaces__msg__RssiAtWaypoint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rosbot_interfaces__msg__RssiAtWaypoint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__are_equal(const rosbot_interfaces__msg__RssiAtWaypoint__Sequence * lhs, const rosbot_interfaces__msg__RssiAtWaypoint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rosbot_interfaces__msg__RssiAtWaypoint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rosbot_interfaces__msg__RssiAtWaypoint__Sequence__copy(
  const rosbot_interfaces__msg__RssiAtWaypoint__Sequence * input,
  rosbot_interfaces__msg__RssiAtWaypoint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rosbot_interfaces__msg__RssiAtWaypoint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rosbot_interfaces__msg__RssiAtWaypoint * data =
      (rosbot_interfaces__msg__RssiAtWaypoint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rosbot_interfaces__msg__RssiAtWaypoint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rosbot_interfaces__msg__RssiAtWaypoint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rosbot_interfaces__msg__RssiAtWaypoint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
