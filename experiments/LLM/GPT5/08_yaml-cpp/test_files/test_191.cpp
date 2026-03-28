// TEST_ID: 191
#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"

namespace {

TEST(NodeIsNullTest_191, ReturnsTrueWhenTypeIsNull_191) {
  const YAML::Node n(YAML::NodeType::Null);
  EXPECT_TRUE(n.IsNull());
}

TEST(NodeIsNullTest_191, ReturnsFalseWhenTypeIsScalar_191) {
  const YAML::Node n(YAML::NodeType::Scalar);
  EXPECT_FALSE(n.IsNull());
}

TEST(NodeIsNullTest_191, ReturnsFalseWhenTypeIsSequence_191) {
  const YAML::Node n(YAML::NodeType::Sequence);
  EXPECT_FALSE(n.IsNull());
}

TEST(NodeIsNullTest_191, ReturnsFalseWhenTypeIsMap_191) {
  const YAML::Node n(YAML::NodeType::Map);
  EXPECT_FALSE(n.IsNull());
}

// Boundary/consistency check without assuming what the default Node's type is.
TEST(NodeIsNullTest_191, DefaultConstructedNodeIsNullMatchesTypeComparison_191) {
  const YAML::Node n;
  EXPECT_EQ(n.IsNull(), n.Type() == YAML::NodeType::Null);
}

}  // namespace