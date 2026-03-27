// TEST_ID: 561
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>  // Provides YAML::Node, YAML::EmitterStyle, YAML::NodeType

namespace {

class NodeSetStyleTest_561 : public ::testing::Test {};

TEST_F(NodeSetStyleTest_561, SetStyleUpdatesStyleOnDefaultConstructedNode_561) {
  YAML::Node n;
  EXPECT_NO_THROW(n.SetStyle(YAML::EmitterStyle::Flow));
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Flow);

  EXPECT_NO_THROW(n.SetStyle(YAML::EmitterStyle::Block));
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeSetStyleTest_561, SetStyleLastCallWinsWhenCalledMultipleTimes_561) {
  YAML::Node n;

  EXPECT_NO_THROW(n.SetStyle(YAML::EmitterStyle::Block));
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Block);

  EXPECT_NO_THROW(n.SetStyle(YAML::EmitterStyle::Flow));
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Flow);

  // Repeat the same style to ensure it remains stable / does not error.
  EXPECT_NO_THROW(n.SetStyle(YAML::EmitterStyle::Flow));
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeSetStyleTest_561, SetStyleWorksForExplicitlyTypedNodes_561) {
  YAML::Node nullNode(YAML::NodeType::Null);
  YAML::Node scalarNode(YAML::NodeType::Scalar);
  YAML::Node seqNode(YAML::NodeType::Sequence);
  YAML::Node mapNode(YAML::NodeType::Map);

  EXPECT_NO_THROW(nullNode.SetStyle(YAML::EmitterStyle::Flow));
  EXPECT_EQ(nullNode.Style(), YAML::EmitterStyle::Flow);

  EXPECT_NO_THROW(scalarNode.SetStyle(YAML::EmitterStyle::Block));
  EXPECT_EQ(scalarNode.Style(), YAML::EmitterStyle::Block);

  EXPECT_NO_THROW(seqNode.SetStyle(YAML::EmitterStyle::Flow));
  EXPECT_EQ(seqNode.Style(), YAML::EmitterStyle::Flow);

  EXPECT_NO_THROW(mapNode.SetStyle(YAML::EmitterStyle::Block));
  EXPECT_EQ(mapNode.Style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeSetStyleTest_561, SetStyleDoesNotThrowOnNodeObtainedFromMissingKey_561) {
  YAML::Node root(YAML::NodeType::Map);

  // NOTE: operator[] const returns a const Node; copying into a non-const Node
  // allows calling SetStyle. We do not assume whether this makes the node defined,
  // we only check the call is safe/observable via public API.
  YAML::Node child = root["missing_key"];

  EXPECT_NO_THROW(child.SetStyle(YAML::EmitterStyle::Flow));

  // If the library exposes the chosen style for this node, it should match.
  // This is the most direct observable behavior for SetStyle via the public API.
  EXPECT_EQ(child.Style(), YAML::EmitterStyle::Flow);
}

}  // namespace