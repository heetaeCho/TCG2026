// TEST_ID: 562
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/yaml.h"

namespace {

class NodeIsTest_562 : public ::testing::Test {};

TEST_F(NodeIsTest_562, DefaultConstructedNodesDoNotThrow_562) {
  YAML::Node a;
  YAML::Node b;

  EXPECT_NO_THROW((void)a.is(b));
  EXPECT_NO_THROW((void)b.is(a));
}

TEST_F(NodeIsTest_562, DefaultConstructedNodesReturnFalseWhenCompared_562) {
  YAML::Node a;
  YAML::Node b;

  EXPECT_FALSE(a.is(b));
  EXPECT_FALSE(b.is(a));
  EXPECT_FALSE(a.is(a));
}

TEST_F(NodeIsTest_562, NodeIsTrueForSelf_562) {
  YAML::Node n("value");
  EXPECT_TRUE(n.is(n));
}

TEST_F(NodeIsTest_562, NodeIsTrueForCopyConstructedAlias_562) {
  YAML::Node original("value");
  YAML::Node copy(original);

  EXPECT_TRUE(original.is(copy));
  EXPECT_TRUE(copy.is(original));
}

TEST_F(NodeIsTest_562, NodeIsTrueForAssignedAlias_562) {
  YAML::Node original("value");
  YAML::Node assigned;
  assigned = original;

  EXPECT_TRUE(original.is(assigned));
  EXPECT_TRUE(assigned.is(original));
}

TEST_F(NodeIsTest_562, NodeIsFalseForDistinctNodesEvenIfSameScalar_562) {
  YAML::Node a("same");
  YAML::Node b("same");

  EXPECT_FALSE(a.is(b));
  EXPECT_FALSE(b.is(a));
}

TEST_F(NodeIsTest_562, ComparisonWithDefaultConstructedNodeReturnsFalse_562) {
  YAML::Node empty;
  YAML::Node scalar("x");

  EXPECT_FALSE(empty.is(scalar));
  EXPECT_FALSE(scalar.is(empty));
}

TEST_F(NodeIsTest_562, InvalidRhsNodeThrowsInvalidNode_562) {
  // Create a "valid" map node, then take a const view and index a missing key.
  // In yaml-cpp, const operator[] on a missing key is observable as an invalid node.
  YAML::Node map(YAML::NodeType::Map);
  const YAML::Node cmap = map;

  YAML::Node missing = cmap["missing_key_562"];

  EXPECT_THROW((void)map.is(missing), YAML::InvalidNode);
}

TEST_F(NodeIsTest_562, InvalidLhsNodeThrowsInvalidNode_562) {
  YAML::Node map(YAML::NodeType::Map);
  const YAML::Node cmap = map;

  YAML::Node missing = cmap["missing_key_562"];

  EXPECT_THROW((void)missing.is(map), YAML::InvalidNode);
}

TEST_F(NodeIsTest_562, InvalidBothSidesThrowsInvalidNode_562) {
  YAML::Node map(YAML::NodeType::Map);
  const YAML::Node cmap = map;

  YAML::Node missing1 = cmap["missing_key_a_562"];
  YAML::Node missing2 = cmap["missing_key_b_562"];

  EXPECT_THROW((void)missing1.is(missing2), YAML::InvalidNode);
}

}  // namespace
`