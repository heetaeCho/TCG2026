// node_is_sequence_test.cpp
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

class NodeIsSequenceTest_193 : public ::testing::Test {};

TEST_F(NodeIsSequenceTest_193, DefaultConstructedNodeIsNotSequence_193) {
  const YAML::Node n;
  EXPECT_FALSE(n.IsSequence());
}

TEST_F(NodeIsSequenceTest_193, ExplicitSequenceTypeConstructedNodeIsSequence_193) {
  const YAML::Node n(YAML::NodeType::Sequence);
  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, ExplicitNonSequenceTypeConstructedNodeIsNotSequence_193) {
  const YAML::Node n_scalar(YAML::NodeType::Scalar);
  const YAML::Node n_map(YAML::NodeType::Map);
  const YAML::Node n_null(YAML::NodeType::Null);
  const YAML::Node n_undef(YAML::NodeType::Undefined);

  EXPECT_FALSE(n_scalar.IsSequence());
  EXPECT_FALSE(n_map.IsSequence());
  EXPECT_FALSE(n_null.IsSequence());
  EXPECT_FALSE(n_undef.IsSequence());
}

TEST_F(NodeIsSequenceTest_193, LoadedYamlSequenceIsSequence_193) {
  const YAML::Node n = YAML::Load("[1, 2, 3]");
  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, LoadedYamlEmptySequenceIsSequence_193) {
  const YAML::Node n = YAML::Load("[]");
  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, LoadedYamlScalarIsNotSequence_193) {
  const YAML::Node n = YAML::Load("hello");
  EXPECT_FALSE(n.IsSequence());
}

TEST_F(NodeIsSequenceTest_193, LoadedYamlMapIsNotSequence_193) {
  const YAML::Node n = YAML::Load("{a: 1, b: 2}");
  EXPECT_FALSE(n.IsSequence());
}

TEST_F(NodeIsSequenceTest_193, LoadedYamlNullIsNotSequence_193) {
  const YAML::Node n = YAML::Load("null");
  EXPECT_FALSE(n.IsSequence());
}

TEST_F(NodeIsSequenceTest_193, CopyConstructedPreservesIsSequence_193) {
  const YAML::Node original = YAML::Load("[x, y]");
  const YAML::Node copy(original);

  EXPECT_TRUE(original.IsSequence());
  EXPECT_TRUE(copy.IsSequence());
  EXPECT_EQ(copy.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, AssignedPreservesIsSequence_193) {
  YAML::Node n = YAML::Load("hello");
  ASSERT_FALSE(n.IsSequence());

  n = YAML::Load("[1]");
  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, PushBackKeepsSequenceTypeAndIsSequenceTrue_193) {
  YAML::Node n(YAML::NodeType::Sequence);
  ASSERT_TRUE(n.IsSequence());

  n.push_back(1);
  n.push_back("two");
  n.push_back(YAML::Load("{k: v}"));

  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeIsSequenceTest_193, IsSequenceMatchesTypeForVariousNodes_193) {
  const YAML::Node seq = YAML::Load("[1]");
  const YAML::Node map = YAML::Load("{k: v}");
  const YAML::Node scalar = YAML::Load("s");
  const YAML::Node null_node = YAML::Load("null");

  EXPECT_EQ(seq.IsSequence(), seq.Type() == YAML::NodeType::Sequence);
  EXPECT_EQ(map.IsSequence(), map.Type() == YAML::NodeType::Sequence);
  EXPECT_EQ(scalar.IsSequence(), scalar.Type() == YAML::NodeType::Sequence);
  EXPECT_EQ(null_node.IsSequence(), null_node.Type() == YAML::NodeType::Sequence);
}

}  // namespace