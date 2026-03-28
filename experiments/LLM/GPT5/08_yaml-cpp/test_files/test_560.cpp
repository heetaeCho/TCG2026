// File: test/node_style_test.cpp
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

class NodeStyleTest_560 : public ::testing::Test {};

TEST_F(NodeStyleTest_560, DefaultConstructedNodeReturnsDefaultStyle_560) {
  YAML::Node n;
  EXPECT_NO_THROW({
    auto style = n.Style();
    EXPECT_EQ(style, YAML::EmitterStyle::Default);
  });
}

TEST_F(NodeStyleTest_560, ExplicitTypeConstructedNodeDoesNotThrow_560) {
  // We only assert that Style() is observable and does not throw on a valid node.
  // (Exact style value is not assumed beyond what the public interface exposes.)
  YAML::Node mapNode(YAML::NodeType::Map);
  EXPECT_NO_THROW((void)mapNode.Style());

  YAML::Node seqNode(YAML::NodeType::Sequence);
  EXPECT_NO_THROW((void)seqNode.Style());

  YAML::Node scalarNode(YAML::NodeType::Scalar);
  EXPECT_NO_THROW((void)scalarNode.Style());
}

TEST_F(NodeStyleTest_560, StyleIsStableAcrossRepeatedCalls_560) {
  YAML::Node n;
  const auto s1 = n.Style();
  const auto s2 = n.Style();
  const auto s3 = n.Style();
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(NodeStyleTest_560, InvalidChildNodeStyleThrowsInvalidNode_560) {
  // Accessing a missing key is expected to yield an invalid node that throws
  // on operations requiring validity (like Style()).
  YAML::Node root(YAML::NodeType::Map);

  YAML::Node missing = root["definitely_missing_key_560"];
  EXPECT_THROW((void)missing.Style(), YAML::InvalidNode);
}

TEST_F(NodeStyleTest_560, InvalidNestedLookupStyleThrowsInvalidNode_560) {
  YAML::Node root(YAML::NodeType::Map);

  YAML::Node missing = root["missing_560"];
  YAML::Node nested = missing["still_missing_560"];

  EXPECT_THROW((void)nested.Style(), YAML::InvalidNode);
}

}  // namespace