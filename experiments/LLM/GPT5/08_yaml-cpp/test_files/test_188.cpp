// node_iterator_operator_arrow_test_188.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

namespace {

class NodeIteratorOperatorArrowTest_188 : public ::testing::Test {};

TEST_F(NodeIteratorOperatorArrowTest_188, SequenceIteratorArrowBehavesLikeDereference_188) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back(2);

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());

  // Observable behavior: operator-> should allow access to the same element as operator*.
  EXPECT_EQ(it->as<int>(), (*it).as<int>());

  ++it;
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), (*it).as<int>());
}

TEST_F(NodeIteratorOperatorArrowTest_188, ConstSequenceIteratorArrowBehavesLikeDereference_188) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(10);

  const YAML::Node cseq = seq;
  auto it = cseq.begin();
  ASSERT_NE(it, cseq.end());

  EXPECT_EQ(it->as<int>(), (*it).as<int>());
}

TEST_F(NodeIteratorOperatorArrowTest_188, MapIteratorArrowProvidesAccessToKeyAndValue_188) {
  YAML::Node map(YAML::NodeType::Map);
  map["alpha"] = 123;

  auto it = map.begin();
  ASSERT_NE(it, map.end());

  // Observable behavior: for map iterators, operator-> should expose "first"/"second".
  EXPECT_TRUE(it->first.IsScalar());
  EXPECT_EQ(it->first.as<std::string>(), "alpha");
  EXPECT_EQ(it->second.as<int>(), 123);
}

TEST_F(NodeIteratorOperatorArrowTest_188, ConstMapIteratorArrowProvidesAccessToKeyAndValue_188) {
  YAML::Node map(YAML::NodeType::Map);
  map["k"] = "v";

  const YAML::Node cmap = map;
  auto it = cmap.begin();
  ASSERT_NE(it, cmap.end());

  EXPECT_EQ(it->first.as<std::string>(), "k");
  EXPECT_EQ(it->second.as<std::string>(), "v");
}

TEST_F(NodeIteratorOperatorArrowTest_188, ArrowUsableInChainedExpressions_188) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(7);

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());

  // Just verify common chained use compiles and returns expected value.
  EXPECT_EQ(it->as<int>(), 7);
}

}  // namespace