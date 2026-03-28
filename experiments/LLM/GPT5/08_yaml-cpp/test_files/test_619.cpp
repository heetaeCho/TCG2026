// TEST_ID: 619
//
// Unit tests for YAML::convert<std::pair<T, U>>::encode (partial implementation shown)
// File under test: yaml-cpp/node/convert.h
//
// These tests treat the implementation as a black box and verify only observable behavior
// via the public YAML::Node interface.

#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class PairEncodeTest_619 : public ::testing::Test {};

template <typename T>
static void ExpectNodeAsEquals_619(const YAML::Node& n, const T& expected) {
  T value{};
  EXPECT_NO_THROW(value = n.as<T>()) << "Node::as<T>() should succeed for expected type";
  EXPECT_EQ(value, expected);
}

}  // namespace

TEST_F(PairEncodeTest_619, EncodesPairAsSequenceOfSizeTwo_619) {
  const std::pair<int, int> p{1, 2};

  const YAML::Node node = YAML::encode(p);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(static_cast<bool>(node));
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 2u);
}

TEST_F(PairEncodeTest_619, PreservesOrderFirstThenSecond_ForHomogeneousInts_619) {
  const std::pair<int, int> p{42, -7};

  const YAML::Node node = YAML::encode(p);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 2u);

  ExpectNodeAsEquals_619<int>(node[0], p.first);
  ExpectNodeAsEquals_619<int>(node[1], p.second);
}

TEST_F(PairEncodeTest_619, EncodesHeterogeneousTypes_IntAndString_619) {
  const std::pair<int, std::string> p{7, "seven"};

  const YAML::Node node = YAML::encode(p);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 2u);

  ExpectNodeAsEquals_619<int>(node[0], p.first);
  ExpectNodeAsEquals_619<std::string>(node[1], p.second);
}

TEST_F(PairEncodeTest_619, EncodesEmptyStrings_619) {
  const std::pair<std::string, std::string> p{"", ""};

  const YAML::Node node = YAML::encode(p);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 2u);

  ExpectNodeAsEquals_619<std::string>(node[0], p.first);
  ExpectNodeAsEquals_619<std::string>(node[1], p.second);
}

TEST_F(PairEncodeTest_619, EncodesNestedNodes_WhenPairHoldsNodes_619) {
  YAML::Node first;
  first = 123;

  YAML::Node second(YAML::NodeType::Sequence);
  second.push_back("a");
  second.push_back("b");

  const std::pair<YAML::Node, YAML::Node> p{first, second};

  const YAML::Node node = YAML::encode(p);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 2u);

  // Verify first element content
  EXPECT_TRUE(node[0].IsDefined());
  ExpectNodeAsEquals_619<int>(node[0], 123);

  // Verify second element is a sequence with expected contents
  EXPECT_TRUE(node[1].IsSequence());
  ASSERT_EQ(node[1].size(), 2u);
  ExpectNodeAsEquals_619<std::string>(node[1][0], "a");
  ExpectNodeAsEquals_619<std::string>(node[1][1], "b");
}

TEST_F(PairEncodeTest_619, MultipleCallsProduceIndependentNodes_619) {
  const std::pair<int, int> p1{1, 2};
  const std::pair<int, int> p2{3, 4};

  const YAML::Node n1 = YAML::encode(p1);
  const YAML::Node n2 = YAML::encode(p2);

  ASSERT_TRUE(n1.IsSequence());
  ASSERT_TRUE(n2.IsSequence());
  ASSERT_EQ(n1.size(), 2u);
  ASSERT_EQ(n2.size(), 2u);

  ExpectNodeAsEquals_619<int>(n1[0], 1);
  ExpectNodeAsEquals_619<int>(n1[1], 2);
  ExpectNodeAsEquals_619<int>(n2[0], 3);
  ExpectNodeAsEquals_619<int>(n2[1], 4);
}