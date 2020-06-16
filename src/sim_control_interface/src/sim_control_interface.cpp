// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include <sim_control_interface/msg/excavator_controller.hpp>

using std::placeholders::_1;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class SimControlInterface : public rclcpp::Node
{
public:
  SimControlInterface()
  : Node("sim_interface") 
  {
    publisher_ = this->create_publisher<sim_control_interface::msg::ExcavatorController>("sim_interface", 10);
    subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
    "joy", 10, std::bind(&SimControlInterface::joy_callback, this, _1));
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: %f", msg->axes[6]);
  }
  rclcpp::Publisher<sim_control_interface::msg::ExcavatorController>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimControlInterface>());
  
  rclcpp::shutdown();
  return 0;
}
