// TEST_ID: 549
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>  // YAML::Node, YAML::Load, YAML::InvalidNode, YAML::Mark

namespace {

class NodeMarkTest_549 : public ::testing::Test {};

TEST_F(NodeMarkTest_549, DefaultConstructedNodeReturnsNullMark_549) {
  YAML::Node n;  // default constructed; should be valid but may not have backing node
  const YAML::Mark m = n.Mark();

  // Observable behavior: when there is no backing node, Mark() returns a "null" mark.
  EXPECT_TRUE(m.is_null());
}

TEST_F(NodeMarkTest_549, MarkFromParsedScalarIsNotNull_549) {
  YAML::Node n = YAML::Load("abc");
  const YAML::Mark m = n.Mark();

  // Parsed nodes should have a concrete source mark (not the null mark).
  EXPECT_FALSE(m.is_null());
}

TEST_F(NodeMarkTest_549, MarkFromNestedParsedNodeIsNotNull_549) {
  YAML::Node n = YAML::Load("a:\n  b: 1\n");
  YAML::Node b = n["a"]["b"];

  const YAML::Mark mb = b.Mark();
  EXPECT_FALSE(mb.is_null());
}

TEST_F(NodeMarkTest_549, MarkOnInvalidNodeThrowsInvalidNode_549) {
  // Create a situation that is observable through the public API where a node becomes invalid:
  // indexing into a non-map node.
  YAML::Node scalar = YAML::Load("foo");
  YAML::Node child = scalar["missing_key"];

  EXPECT_THROW(
      {
        // Mark() should throw if the node is invalid.
        (void)child.Mark();
      },
      YAML::InvalidNode);
}

TEST_F(NodeMarkTest_549, MarkDoesNotThrowForValidButUndefinedNode_549) {
  YAML::Node n;  // valid handle, but typically undefined / no backing node
  EXPECT_NO_THROW({
    const YAML::Mark m = n.Mark();
    (void)m;
  });
}

}  // namespace