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

#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>

#include <memory>
#include <string>
#include <vector>

#include "akit/failover/foros/cluster_node.hpp"

class TestClusterNode : public ::testing::Test {
 protected:
  static void SetUpTestCase() { rclcpp::init(0, nullptr); }

  static void TearDownTestCase() { rclcpp::shutdown(); }
};

const char *kClusterName = "test_cluster";
const char *kNamespace = "/ns_cluster";
const char *kInvalidNodeName = "invalid_cluster?";

TEST_F(TestClusterNode, TestConstructor) {
  {
    auto cluster_node = std::make_shared<akit::failover::foros::ClusterNode>(
        kClusterName, 1, std::initializer_list<uint32_t>{1, 2, 3, 4});
  }

  {
    ASSERT_THROW(
        {
          auto cluster_node =
              std::make_shared<akit::failover::foros::ClusterNode>(
                  kInvalidNodeName, 1,
                  std::initializer_list<uint32_t>{1, 2, 3, 4});

          (void)cluster_node;
        },
        rclcpp::exceptions::InvalidNodeNameError);
  }
}

TEST_F(TestClusterNode, TestGetNodeInfo) {
  auto cluster_node = std::make_shared<akit::failover::foros::ClusterNode>(
      kClusterName, 1, std::initializer_list<uint32_t>{1, 2, 3, 4}, kNamespace);
  EXPECT_EQ(std::string(cluster_node->get_name()),
            std::string(kClusterName + std::to_string(1)));
  EXPECT_EQ(std::string(cluster_node->get_namespace()),
            std::string(kNamespace));
}
