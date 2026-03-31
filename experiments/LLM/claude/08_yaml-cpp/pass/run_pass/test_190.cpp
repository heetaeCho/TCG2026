#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/iterator.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"

namespace {

// Test fixture for node_iterator tests
class NodeIteratorTest_190 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default constructed iterators are equal
TEST_F(NodeIteratorTest_190, DefaultConstructedIteratorsAreEqual_190) {
  YAML::Node node;
  YAML::iterator it1;
  YAML::iterator it2;
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);
}

// Test: Sequence iterator - begin equals end on empty sequence
TEST_F(NodeIteratorTest_190, EmptySequenceBeginEqualsEnd_190) {
  YAML::Node node(YAML::NodeType::Sequence);
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Map iterator - begin equals end on empty map
TEST_F(NodeIteratorTest_190, EmptyMapBeginEqualsEnd_190) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_EQ(node.begin(), node.end());
}

// Test: Sequence iterator normal operation
TEST_F(NodeIteratorTest_190, SequenceIteratorNormalOperation_190) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);

  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test: Sequence iterator dereference
TEST_F(NodeIteratorTest_190, SequenceIteratorDereference_190) {
  YAML::Node node;
  node.push_back(42);
  node.push_back(99);

  auto it = node.begin();
  EXPECT_EQ((*it).as<int>(), 42);
  ++it;
  EXPECT_EQ((*it).as<int>(), 99);
}

// Test: Map iterator normal operation
TEST_F(NodeIteratorTest_190, MapIteratorNormalOperation_190) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";

  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test: Map iterator dereference gives key-value pair
TEST_F(NodeIteratorTest_190, MapIteratorDereferenceKeyValue_190) {
  YAML::Node node;
  node["hello"] = "world";

  auto it = node.begin();
  EXPECT_EQ(it->first.as<std::string>(), "hello");
  EXPECT_EQ(it->second.as<std::string>(), "world");
}

// Test: Post-increment returns old value
TEST_F(NodeIteratorTest_190, PostIncrementReturnsOldValue_190) {
  YAML::Node node;
  node.push_back(10);
  node.push_back(20);

  auto it = node.begin();
  auto old = it++;
  EXPECT_EQ((*old).as<int>(), 10);
  EXPECT_EQ((*it).as<int>(), 20);
}

// Test: Pre-increment returns new value
TEST_F(NodeIteratorTest_190, PreIncrementReturnsNewValue_190) {
  YAML::Node node;
  node.push_back(10);
  node.push_back(20);

  auto it = node.begin();
  auto& ref = ++it;
  EXPECT_EQ((*ref).as<int>(), 20);
  EXPECT_EQ((*it).as<int>(), 20);
}

// Test: Iterator inequality
TEST_F(NodeIteratorTest_190, IteratorInequality_190) {
  YAML::Node node;
  node.push_back(1);

  EXPECT_NE(node.begin(), node.end());
}

// Test: Iterator reaches end after traversal
TEST_F(NodeIteratorTest_190, IteratorReachesEndAfterTraversal_190) {
  YAML::Node node;
  node.push_back(1);

  auto it = node.begin();
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Const iterator from sequence
TEST_F(NodeIteratorTest_190, ConstIteratorFromSequence_190) {
  YAML::Node node;
  node.push_back(5);
  node.push_back(10);

  const YAML::Node& constNode = node;
  int count = 0;
  for (auto it = constNode.begin(); it != constNode.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test: Const iterator from map
TEST_F(NodeIteratorTest_190, ConstIteratorFromMap_190) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;

  const YAML::Node& constNode = node;
  int count = 0;
  for (auto it = constNode.begin(); it != constNode.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test: Sequence with single element
TEST_F(NodeIteratorTest_190, SequenceSingleElement_190) {
  YAML::Node node;
  node.push_back("only");

  auto it = node.begin();
  EXPECT_NE(it, node.end());
  EXPECT_EQ((*it).as<std::string>(), "only");
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Map with single element
TEST_F(NodeIteratorTest_190, MapSingleElement_190) {
  YAML::Node node;
  node["sole"] = "entry";

  auto it = node.begin();
  EXPECT_NE(it, node.end());
  EXPECT_EQ(it->first.as<std::string>(), "sole");
  EXPECT_EQ(it->second.as<std::string>(), "entry");
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Arrow operator on sequence
TEST_F(NodeIteratorTest_190, ArrowOperatorOnSequence_190) {
  YAML::Node node;
  node.push_back("test");

  auto it = node.begin();
  // For sequence, operator-> should work
  EXPECT_TRUE(it->IsDefined());
}

// Test: Multiple increments on map
TEST_F(NodeIteratorTest_190, MultipleIncrementsOnMap_190) {
  YAML::Node node;
  node["x"] = 1;
  node["y"] = 2;
  node["z"] = 3;

  auto it = node.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(it, node.end());
}

// Test: Undefined node has no iterations
TEST_F(NodeIteratorTest_190, UndefinedNodeIteration_190) {
  YAML::Node node;
  // An undefined/null node should have begin == end
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test: Scalar node has no iterations
TEST_F(NodeIteratorTest_190, ScalarNodeNoIteration_190) {
  YAML::Node node(42);
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test: Large sequence iteration
TEST_F(NodeIteratorTest_190, LargeSequenceIteration_190) {
  YAML::Node node;
  const int N = 100;
  for (int i = 0; i < N; ++i) {
    node.push_back(i);
  }

  int count = 0;
  int sum = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    sum += (*it).as<int>();
    count++;
  }
  EXPECT_EQ(count, N);
  EXPECT_EQ(sum, N * (N - 1) / 2);
}

// Test: Copy of iterator
TEST_F(NodeIteratorTest_190, CopyOfIterator_190) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);

  auto it1 = node.begin();
  auto it2 = it1;
  EXPECT_EQ(it1, it2);
  EXPECT_EQ((*it1).as<int>(), (*it2).as<int>());

  ++it1;
  EXPECT_NE(it1, it2);
}

// Test: Parsed YAML sequence iteration
TEST_F(NodeIteratorTest_190, ParsedYAMLSequenceIteration_190) {
  YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
  
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 5);
}

// Test: Parsed YAML map iteration
TEST_F(NodeIteratorTest_190, ParsedYAMLMapIteration_190) {
  YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
  
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

}  // namespace
