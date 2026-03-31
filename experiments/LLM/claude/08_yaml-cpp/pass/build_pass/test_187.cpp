#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/iterator.h"

namespace {

// Test fixture for node_iterator tests
class NodeIteratorTest_187 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default-constructed iterator dereference returns empty/none value_type
TEST_F(NodeIteratorTest_187, DefaultConstructedIteratorDereference_187) {
  YAML::Node node;
  // An empty node should have begin() == end()
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Sequence iterator dereferences to valid node values
TEST_F(NodeIteratorTest_187, SequenceIteratorDereference_187) {
  YAML::Node node;
  node.push_back(42);
  node.push_back("hello");
  node.push_back(3.14);

  auto it = node.begin();
  EXPECT_EQ((*it).as<int>(), 42);
  ++it;
  EXPECT_EQ((*it).as<std::string>(), "hello");
  ++it;
  EXPECT_NEAR((*it).as<double>(), 3.14, 0.001);
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Map iterator dereferences to key-value pairs
TEST_F(NodeIteratorTest_187, MapIteratorDereference_187) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";

  bool foundKey1 = false;
  bool foundKey2 = false;

  for (auto it = node.begin(); it != node.end(); ++it) {
    std::string key = it->first.as<std::string>();
    std::string value = it->second.as<std::string>();
    if (key == "key1") {
      EXPECT_EQ(value, "value1");
      foundKey1 = true;
    } else if (key == "key2") {
      EXPECT_EQ(value, "value2");
      foundKey2 = true;
    }
  }
  EXPECT_TRUE(foundKey1);
  EXPECT_TRUE(foundKey2);
}

// Test: Prefix increment advances the iterator in a sequence
TEST_F(NodeIteratorTest_187, PrefixIncrementSequence_187) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);

  auto it = node.begin();
  EXPECT_EQ((*it).as<int>(), 1);
  auto& ref = ++it;
  EXPECT_EQ((*ref).as<int>(), 2);
  EXPECT_EQ((*it).as<int>(), 2);
}

// Test: Postfix increment advances the iterator but returns old position
TEST_F(NodeIteratorTest_187, PostfixIncrementSequence_187) {
  YAML::Node node;
  node.push_back(10);
  node.push_back(20);

  auto it = node.begin();
  auto old = it++;
  EXPECT_EQ((*old).as<int>(), 10);
  EXPECT_EQ((*it).as<int>(), 20);
}

// Test: Equality comparison for iterators
TEST_F(NodeIteratorTest_187, EqualityOperator_187) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);

  auto it1 = node.begin();
  auto it2 = node.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);

  ++it1;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

// Test: End iterator equality
TEST_F(NodeIteratorTest_187, EndIteratorEquality_187) {
  YAML::Node node;
  node.push_back(1);

  auto it = node.begin();
  EXPECT_NE(it, node.end());
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Empty sequence has begin == end
TEST_F(NodeIteratorTest_187, EmptySequenceBeginEqualsEnd_187) {
  YAML::Node node(YAML::NodeType::Sequence);
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Empty map has begin == end
TEST_F(NodeIteratorTest_187, EmptyMapBeginEqualsEnd_187) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Scalar node has begin == end
TEST_F(NodeIteratorTest_187, ScalarNodeBeginEqualsEnd_187) {
  YAML::Node node("scalar");
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Null/undefined node has begin == end
TEST_F(NodeIteratorTest_187, NullNodeBeginEqualsEnd_187) {
  YAML::Node node;
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Arrow operator on map iterator gives access to first and second
TEST_F(NodeIteratorTest_187, ArrowOperatorMapIterator_187) {
  YAML::Node node;
  node["alpha"] = 100;

  auto it = node.begin();
  EXPECT_EQ(it->first.as<std::string>(), "alpha");
  EXPECT_EQ(it->second.as<int>(), 100);
}

// Test: Iterate through full sequence with count check
TEST_F(NodeIteratorTest_187, SequenceFullIteration_187) {
  YAML::Node node;
  for (int i = 0; i < 5; ++i) {
    node.push_back(i);
  }

  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    EXPECT_EQ((*it).as<int>(), count);
    ++count;
  }
  EXPECT_EQ(count, 5);
}

// Test: Iterate through full map with count check
TEST_F(NodeIteratorTest_187, MapFullIteration_187) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  node["c"] = 3;

  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    EXPECT_TRUE(it->first.IsDefined());
    EXPECT_TRUE(it->second.IsDefined());
    ++count;
  }
  EXPECT_EQ(count, 3);
}

// Test: Single element sequence iteration
TEST_F(NodeIteratorTest_187, SingleElementSequence_187) {
  YAML::Node node;
  node.push_back("only");

  auto it = node.begin();
  EXPECT_NE(it, node.end());
  EXPECT_EQ((*it).as<std::string>(), "only");
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Single element map iteration
TEST_F(NodeIteratorTest_187, SingleElementMap_187) {
  YAML::Node node;
  node["single"] = "entry";

  auto it = node.begin();
  EXPECT_NE(it, node.end());
  EXPECT_EQ(it->first.as<std::string>(), "single");
  EXPECT_EQ(it->second.as<std::string>(), "entry");
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Const iterator from const node
TEST_F(NodeIteratorTest_187, ConstIterator_187) {
  YAML::Node mutableNode;
  mutableNode.push_back(1);
  mutableNode.push_back(2);

  const YAML::Node& node = mutableNode;
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2);
}

// Test: Nested structure iteration (sequence of maps)
TEST_F(NodeIteratorTest_187, NestedStructureIteration_187) {
  YAML::Node node;
  YAML::Node inner1;
  inner1["x"] = 1;
  YAML::Node inner2;
  inner2["y"] = 2;
  node.push_back(inner1);
  node.push_back(inner2);

  auto it = node.begin();
  EXPECT_TRUE((*it).IsMap());
  EXPECT_EQ((*it)["x"].as<int>(), 1);
  ++it;
  EXPECT_TRUE((*it).IsMap());
  EXPECT_EQ((*it)["y"].as<int>(), 2);
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Multiple prefix increments
TEST_F(NodeIteratorTest_187, MultiplePrefixIncrements_187) {
  YAML::Node node;
  node.push_back(0);
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);

  auto it = node.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*it).as<int>(), 3);
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Postfix increment returns copy of previous state
TEST_F(NodeIteratorTest_187, PostfixIncrementReturnsCopy_187) {
  YAML::Node node;
  node.push_back("a");
  node.push_back("b");
  node.push_back("c");

  auto it = node.begin();
  auto copy1 = it++;
  auto copy2 = it++;

  EXPECT_EQ((*copy1).as<std::string>(), "a");
  EXPECT_EQ((*copy2).as<std::string>(), "b");
  EXPECT_EQ((*it).as<std::string>(), "c");
}

}  // namespace
