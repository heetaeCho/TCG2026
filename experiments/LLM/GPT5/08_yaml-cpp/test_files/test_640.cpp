// File: ./TestProjects/yaml-cpp/test/node_data_mark_defined_test_640.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

class NodeDataMarkDefinedTest_640 : public ::testing::Test {
protected:
  node_data data_;
};

TEST_F(NodeDataMarkDefinedTest_640, UndefinedTypeBecomesNullAndDefined_640) {
  data_.set_type(YAML::NodeType::Undefined);
  EXPECT_EQ(data_.type(), YAML::NodeType::Undefined);
  EXPECT_FALSE(data_.is_defined());

  data_.mark_defined();

  EXPECT_TRUE(data_.is_defined());
  EXPECT_EQ(data_.type(), YAML::NodeType::Null);
}

TEST_F(NodeDataMarkDefinedTest_640, NonUndefinedTypePreservedButDefined_640) {
  data_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(data_.type(), YAML::NodeType::Scalar);
  EXPECT_FALSE(data_.is_defined());

  data_.mark_defined();

  EXPECT_TRUE(data_.is_defined());
  EXPECT_EQ(data_.type(), YAML::NodeType::Scalar);
}

TEST_F(NodeDataMarkDefinedTest_640, CallingTwiceIsIdempotentAfterUndefined_640) {
  data_.set_type(YAML::NodeType::Undefined);

  data_.mark_defined();
  ASSERT_TRUE(data_.is_defined());
  ASSERT_EQ(data_.type(), YAML::NodeType::Null);

  data_.mark_defined();

  EXPECT_TRUE(data_.is_defined());
  EXPECT_EQ(data_.type(), YAML::NodeType::Null);
}

TEST_F(NodeDataMarkDefinedTest_640, SetsDefinedEvenIfTypeAlreadyNotUndefined_640) {
  const auto initial_type = data_.type();
  EXPECT_FALSE(data_.is_defined());

  data_.mark_defined();

  EXPECT_TRUE(data_.is_defined());
  // Only guaranteed observable behavior: if the type wasn't Undefined, it should remain unchanged.
  EXPECT_EQ(data_.type(), initial_type);
}

}  // namespace