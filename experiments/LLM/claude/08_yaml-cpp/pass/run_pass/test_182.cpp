#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/node.h"

namespace {

// Test basic iteration over a sequence node
TEST(NodeIteratorTest_182, SequenceIterationBasic_182) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test iteration over an empty sequence
TEST(NodeIteratorTest_182, EmptySequenceIteration_182) {
  YAML::Node seq(YAML::NodeType::Sequence);
  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test iteration over a map node
TEST(NodeIteratorTest_182, MapIterationBasic_182) {
  YAML::Node map;
  map["key1"] = "value1";
  map["key2"] = "value2";

  int count = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test that map iterator provides first and second
TEST(NodeIteratorTest_182, MapIteratorFirstSecond_182) {
  YAML::Node map;
  map["hello"] = "world";

  auto it = map.begin();
  EXPECT_TRUE(it->first.IsScalar());
  EXPECT_TRUE(it->second.IsScalar());
  EXPECT_EQ(it->first.as<std::string>(), "hello");
  EXPECT_EQ(it->second.as<std::string>(), "world");
}

// Test sequence iterator dereference
TEST(NodeIteratorTest_182, SequenceIteratorDereference_182) {
  YAML::Node seq;
  seq.push_back("test");

  auto it = seq.begin();
  YAML::Node val = *it;
  EXPECT_EQ(val.as<std::string>(), "test");
}

// Test iterator equality
TEST(NodeIteratorTest_182, IteratorEquality_182) {
  YAML::Node seq;
  seq.push_back(1);

  auto it1 = seq.begin();
  auto it2 = seq.begin();
  EXPECT_TRUE(it1 == it2);
}

// Test iterator inequality
TEST(NodeIteratorTest_182, IteratorInequality_182) {
  YAML::Node seq;
  seq.push_back(1);

  auto begin = seq.begin();
  auto end = seq.end();
  EXPECT_TRUE(begin != end);
}

// Test iterator increment (prefix)
TEST(NodeIteratorTest_182, IteratorPrefixIncrement_182) {
  YAML::Node seq;
  seq.push_back(10);
  seq.push_back(20);

  auto it = seq.begin();
  ++it;
  EXPECT_EQ((*it).as<int>(), 20);
}

// Test iterator increment (postfix)
TEST(NodeIteratorTest_182, IteratorPostfixIncrement_182) {
  YAML::Node seq;
  seq.push_back(10);
  seq.push_back(20);

  auto it = seq.begin();
  auto prev = it++;
  EXPECT_EQ((*prev).as<int>(), 10);
  EXPECT_EQ((*it).as<int>(), 20);
}

// Test begin equals end for empty map
TEST(NodeIteratorTest_182, EmptyMapBeginEqualsEnd_182) {
  YAML::Node map(YAML::NodeType::Map);
  EXPECT_TRUE(map.begin() == map.end());
}

// Test const iteration over sequence
TEST(NodeIteratorTest_182, ConstSequenceIteration_182) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);

  const YAML::Node& constSeq = seq;
  int count = 0;
  for (auto it = constSeq.begin(); it != constSeq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test const iteration over map
TEST(NodeIteratorTest_182, ConstMapIteration_182) {
  YAML::Node map;
  map["a"] = 1;
  map["b"] = 2;

  const YAML::Node& constMap = map;
  int count = 0;
  for (auto it = constMap.begin(); it != constMap.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test iterator with single element sequence
TEST(NodeIteratorTest_182, SingleElementSequence_182) {
  YAML::Node seq;
  seq.push_back(42);

  auto it = seq.begin();
  EXPECT_NE(it, seq.end());
  EXPECT_EQ((*it).as<int>(), 42);
  ++it;
  EXPECT_EQ(it, seq.end());
}

// Test iterator arrow operator for map
TEST(NodeIteratorTest_182, MapIteratorArrowOperator_182) {
  YAML::Node map;
  map["key"] = "val";

  auto it = map.begin();
  EXPECT_EQ(it->first.as<std::string>(), "key");
  EXPECT_EQ(it->second.as<std::string>(), "val");
}

// Test iteration preserves sequence order
TEST(NodeIteratorTest_182, SequenceOrderPreserved_182) {
  YAML::Node seq;
  seq.push_back("a");
  seq.push_back("b");
  seq.push_back("c");

  std::vector<std::string> result;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    result.push_back((*it).as<std::string>());
  }
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], "a");
  EXPECT_EQ(result[1], "b");
  EXPECT_EQ(result[2], "c");
}

// Test iterating a scalar node (begin == end)
TEST(NodeIteratorTest_182, ScalarNodeIterationEmpty_182) {
  YAML::Node scalar("hello");
  // Scalar nodes should not be iterable in a meaningful sense
  // begin() and end() should be equal
  // (This tests boundary behavior)
  EXPECT_TRUE(scalar.begin() == scalar.end());
}

// Test null node iteration
TEST(NodeIteratorTest_182, NullNodeIteration_182) {
  YAML::Node null(YAML::NodeType::Null);
  EXPECT_TRUE(null.begin() == null.end());
}

// Test multiple increments through a larger sequence
TEST(NodeIteratorTest_182, LargerSequenceIteration_182) {
  YAML::Node seq;
  for (int i = 0; i < 100; i++) {
    seq.push_back(i);
  }

  int count = 0;
  int sum = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    sum += (*it).as<int>();
    count++;
  }
  EXPECT_EQ(count, 100);
  EXPECT_EQ(sum, 4950);  // sum of 0..99
}

// Test map iteration gives valid key-value pairs
TEST(NodeIteratorTest_182, MapIterationKeyValuePairs_182) {
  YAML::Node map;
  map["x"] = 10;
  map["y"] = 20;
  map["z"] = 30;

  std::map<std::string, int> result;
  for (auto it = map.begin(); it != map.end(); ++it) {
    result[it->first.as<std::string>()] = it->second.as<int>();
  }
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result["x"], 10);
  EXPECT_EQ(result["y"], 20);
  EXPECT_EQ(result["z"], 30);
}

}  // namespace
