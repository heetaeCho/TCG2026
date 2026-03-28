// TEST_ID: 645
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;
using YAML::NodeType;

class NodeDataSetNullTest_645 : public ::testing::Test {};

TEST_F(NodeDataSetNullTest_645, DefaultConstructedIsNotDefined_645) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataSetNullTest_645, SetNullMarksDefined_645) {
  node_data nd;

  nd.set_null();

  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataSetNullTest_645, SetNullSetsTypeToNull_645) {
  node_data nd;

  nd.set_null();

  EXPECT_EQ(nd.type(), NodeType::Null);
}

TEST_F(NodeDataSetNullTest_645, SetNullIsIdempotent_645) {
  node_data nd;

  nd.set_null();
  ASSERT_TRUE(nd.is_defined());
  ASSERT_EQ(nd.type(), NodeType::Null);

  // Call again: should still be defined and still be Null.
  nd.set_null();

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

TEST_F(NodeDataSetNullTest_645, SetNullOverridesPriorType_645) {
  node_data nd;

  // Put the node into a non-null type first.
  nd.set_type(NodeType::Scalar);
  ASSERT_EQ(nd.type(), NodeType::Scalar);

  nd.set_null();

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

TEST_F(NodeDataSetNullTest_645, SetNullAfterScalarDoesNotThrowAndSetsNullType_645) {
  node_data nd;

  nd.set_scalar("hello");
  ASSERT_TRUE(nd.is_defined());
  ASSERT_EQ(nd.type(), NodeType::Scalar);

  EXPECT_NO_THROW(nd.set_null());
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

}  // namespace