// TEST_ID: 566
//
// Unit tests for YAML::Node::size() based strictly on observable behavior.
//
// These tests assume yaml-cpp is available in the build and that YAML::InvalidNode
// is the exception thrown for invalid (Zombie) nodes, as indicated by the interface.

#include <gtest/gtest.h>

#include <iterator>
#include <string>

#include <yaml-cpp/yaml.h>

namespace {

std::size_t IterDistance(const YAML::Node& n) {
  return static_cast<std::size_t>(std::distance(n.begin(), n.end()));
}

class NodeSizeTest_566 : public ::testing::Test {};

}  // namespace

TEST_F(NodeSizeTest_566, DefaultConstructedNodeHasSizeZero_566) {
  YAML::Node n;
  EXPECT_EQ(n.size(), 0u);
}

TEST_F(NodeSizeTest_566, EmptySequenceHasSizeZero_566) {
  YAML::Node seq(YAML::NodeType::Sequence);
  EXPECT_EQ(seq.size(), 0u);
  EXPECT_EQ(IterDistance(seq), 0u);
}

TEST_F(NodeSizeTest_566, EmptyMapHasSizeZero_566) {
  YAML::Node map(YAML::NodeType::Map);
  EXPECT_EQ(map.size(), 0u);
  EXPECT_EQ(IterDistance(map), 0u);
}

TEST_F(NodeSizeTest_566, SequenceSizeMatchesIteratorDistanceAfterPushBack_566) {
  YAML::Node seq(YAML::NodeType::Sequence);

  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  EXPECT_EQ(seq.size(), 3u);
  EXPECT_EQ(IterDistance(seq), seq.size());
}

TEST_F(NodeSizeTest_566, MapSizeMatchesIteratorDistanceAfterForceInsert_566) {
  YAML::Node map(YAML::NodeType::Map);

  map.force_insert("a", 1);
  map.force_insert("b", 2);

  EXPECT_EQ(map.size(), 2u);
  EXPECT_EQ(IterDistance(map), map.size());
}

TEST_F(NodeSizeTest_566, CallingSizeOnInvalidNodeThrowsInvalidNode_566) {
  // Create a map with one key, then access a missing key through a *const* view.
  // In yaml-cpp, const operator[] for a missing key returns an invalid (Zombie) node,
  // which should throw InvalidNode on size().
  YAML::Node map(YAML::NodeType::Map);
  map.force_insert("present", 1);

  const YAML::Node cmap = map;
  const YAML::Node missing = cmap["missing_key"];

  EXPECT_THROW((void)missing.size(), YAML::InvalidNode);
}

TEST_F(NodeSizeTest_566, SizeDoesNotThrowForValidNodes_566) {
  YAML::Node n;  // valid (even if empty)
  EXPECT_NO_THROW((void)n.size());

  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back("x");
  EXPECT_NO_THROW((void)seq.size());

  YAML::Node map(YAML::NodeType::Map);
  map.force_insert("k", "v");
  EXPECT_NO_THROW((void)map.size());
}