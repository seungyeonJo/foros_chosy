/*
 * Copyright (c) 2021 42dot All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <chrono>
#include <string>
#include <vector>

#include "akit/failsafe/fsros/cluster_node.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv) {
  uint32_t id = 1;
  const std::string kClusterName = "test_cluster";
  const std::string kTopicName = "test_cluster_echo";
  const std::vector<uint32_t> kClusterNodeIds = {1, 2, 3, 4};

  if (argc >= 2) {
    id = std::stoul(argv[1]);
    if (id > 4 || id == 0) {
      std::cerr << "please use id out of 1, 2, 3, 4" << std::endl;
    }
  }

  rclcpp::init(argc, argv);

  auto node = akit::failsafe::fsros::ClusterNode::make_shared(kClusterName, id,
                                                              kClusterNodeIds);

  auto publisher = node->create_publisher<std_msgs::msg::String>(kTopicName, 1);

  auto timer_ =
      rclcpp::create_timer(node, rclcpp::Clock::make_shared(), 1s, [&]() {
        auto msg = std_msgs::msg::String();
        msg.data = node->get_name();
        publisher->publish(msg);
      });

  rclcpp::spin(node->get_node_base_interface());
  rclcpp::shutdown();

  return 0;
}
