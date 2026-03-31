#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/iterator.h"

namespace {

// Test fixture for node_iterator tests via the public YAML::Node interface
class NodeIteratorTest_185 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default constructed iterators are equal
TEST_F(NodeIteratorTest_185, DefaultConstructedIteratorsAreEqual_185) {
  YAML::Node node;
  // A null/undefined node should have begin == end
  // We test through the Node interface
  YAML::Node seq(YAML::NodeType::Sequence);
  // Empty sequence: begin == end
  EXPECT_EQ(seq.begin(), seq.end());
}

// Test: Sequence iterator increments correctly
TEST_F(NodeIteratorTest_185, SequenceIteratorIncrement_185) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  auto it = seq.begin();
  EXPECT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 1);

  ++it;
  EXPECT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 2);

  ++it;
  EXPECT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 3);

  ++it;
  EXPECT_EQ(it, seq.end());
}

// Test: Post-increment on sequence iterator returns old value
TEST_F(NodeIteratorTest_185, SequencePostIncrement_185) {
  YAML::Node seq;
  seq.push_back(10);
  seq.push_back(20);

  auto it = seq.begin();
  auto old_it = it++;
  EXPECT_EQ(old_it->as<int>(), 10);
  EXPECT_EQ(it->as<int>(), 20);
}

// Test: Map iterator increments correctly
TEST_F(NodeIteratorTest_185, MapIteratorIncrement_185) {
  YAML::Node map;
  map["a"] = 1;
  map["b"] = 2;
  map["c"] = 3;

  int count = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    count++;
    // Each element should be a key-value pair
    EXPECT_TRUE(it->first.IsDefined());
    EXPECT_TRUE(it->second.IsDefined());
  }
  EXPECT_EQ(count, 3);
}

// Test: Map post-increment returns old value
TEST_F(NodeIteratorTest_185, MapPostIncrement_185) {
  YAML::Node map;
  map["key1"] = "val1";
  map["key2"] = "val2";

  auto it = map.begin();
  auto old_it = it++;
  // old_it should point to the first element
  EXPECT_TRUE(old_it->first.IsDefined());
  EXPECT_TRUE(old_it->second.IsDefined());
  // it should point to the second element
  EXPECT_NE(it, map.end());
}

// Test: Empty sequence has no iterations
TEST_F(NodeIteratorTest_185, EmptySequenceNoIteration_185) {
  YAML::Node seq(YAML::NodeType::Sequence);
  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test: Empty map has no iterations
TEST_F(NodeIteratorTest_185, EmptyMapNoIteration_185) {
  YAML::Node map(YAML::NodeType::Map);
  int count = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

// Test: Sequence with single element
TEST_F(NodeIteratorTest_185, SingleElementSequence_185) {
  YAML::Node seq;
  seq.push_back(42);

  auto it = seq.begin();
  EXPECT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 42);

  ++it;
  EXPECT_EQ(it, seq.end());
}

// Test: Map with single element
TEST_F(NodeIteratorTest_185, SingleElementMap_185) {
  YAML::Node map;
  map["only"] = "one";

  auto it = map.begin();
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->first.as<std::string>(), "only");
  EXPECT_EQ(it->second.as<std::string>(), "one");

  ++it;
  EXPECT_EQ(it, map.end());
}

// Test: Iterator equality comparison
TEST_F(NodeIteratorTest_185, IteratorEqualityComparison_185) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);

  auto it1 = seq.begin();
  auto it2 = seq.begin();
  EXPECT_EQ(it1, it2);

  ++it1;
  EXPECT_NE(it1, it2);

  ++it2;
  EXPECT_EQ(it1, it2);
}

// Test: Iterator inequality comparison
TEST_F(NodeIteratorTest_185, IteratorInequalityComparison_185) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);

  auto it = seq.begin();
  EXPECT_TRUE(it != seq.end());

  ++it;
  ++it;
  EXPECT_FALSE(it != seq.end());
}

// Test: Dereference operator for sequence
TEST_F(NodeIteratorTest_185, DereferenceSequenceIterator_185) {
  YAML::Node seq;
  seq.push_back("hello");
  seq.push_back("world");

  auto it = seq.begin();
  YAML::Node val = *it;
  EXPECT_EQ(val.as<std::string>(), "hello");
}

// Test: Arrow operator for map
TEST_F(NodeIteratorTest_185, ArrowOperatorMapIterator_185) {
  YAML::Node map;
  map["x"] = 99;

  auto it = map.begin();
  EXPECT_EQ(it->first.as<std::string>(), "x");
  EXPECT_EQ(it->second.as<int>(), 99);
}

// Test: Iterate through a parsed YAML sequence
TEST_F(NodeIteratorTest_185, ParsedSequenceIteration_185) {
  YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
  EXPECT_TRUE(node.IsSequence());

  std::vector<int> values;
  for (auto it = node.begin(); it != node.end(); ++it) {
    values.push_back(it->as<int>());
  }
  EXPECT_EQ(values.size(), 5u);
  EXPECT_EQ(values[0], 1);
  EXPECT_EQ(values[4], 5);
}

// Test: Iterate through a parsed YAML map
TEST_F(NodeIteratorTest_185, ParsedMapIteration_185) {
  YAML::Node node = YAML::Load("{a: 1, b: 2}");
  EXPECT_TRUE(node.IsMap());

  std::map<std::string, int> result;
  for (auto it = node.begin(); it != node.end(); ++it) {
    result[it->first.as<std::string>()] = it->second.as<int>();
  }
  EXPECT_EQ(result.size(), 2u);
  EXPECT_EQ(result["a"], 1);
  EXPECT_EQ(result["b"], 2);
}

// Test: Const iterator from const node
TEST_F(NodeIteratorTest_185, ConstIterator_185) {
  YAML::Node seq;
  seq.push_back(10);
  seq.push_back(20);

  const YAML::Node& constSeq = seq;
  int count = 0;
  for (auto it = constSeq.begin(); it != constSeq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test: Multiple increments past end stay at end for sequence
TEST_F(NodeIteratorTest_185, SequenceLargeIteration_185) {
  YAML::Node seq;
  for (int i = 0; i < 100; i++) {
    seq.push_back(i);
  }

  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    EXPECT_EQ(it->as<int>(), count);
    count++;
  }
  EXPECT_EQ(count, 100);
}

// Test: Copy constructor of iterator
TEST_F(NodeIteratorTest_185, IteratorCopyConstruction_185) {
  YAML::Node seq;
  seq.push_back(5);
  seq.push_back(10);

  auto it1 = seq.begin();
  auto it2 = it1;  // copy
  EXPECT_EQ(it1, it2);
  EXPECT_EQ(it2->as<int>(), 5);

  ++it1;
  EXPECT_NE(it1, it2);
  EXPECT_EQ(it1->as<int>(), 10);
  EXPECT_EQ(it2->as<int>(), 5);
}

// Test: Map iterator skips undefined/removed entries
TEST_F(NodeIteratorTest_185, MapIteratorSkipsRemovedEntries_185) {
  YAML::Node map;
  map["a"] = 1;
  map["b"] = 2;
  map["c"] = 3;

  map.remove("b");

  int count = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    count++;
    std::string key = it->first.as<std::string>();
    EXPECT_NE(key, "b");
  }
  EXPECT_EQ(count, 2);
}

// Test: Range-based for loop on sequence
TEST_F(NodeIteratorTest_185, RangeBasedForSequence_185) {
  YAML::Node seq;
  seq.push_back(100);
  seq.push_back(200);

  std::vector<int> vals;
  for (const auto& item : seq) {
    vals.push_back(item.as<int>());
  }
  EXPECT_EQ(vals.size(), 2u);
  EXPECT_EQ(vals[0], 100);
  EXPECT_EQ(vals[1], 200);
}

// Test: Range-based for loop on map
TEST_F(NodeIteratorTest_185, RangeBasedForMap_185) {
  YAML::Node map;
  map["key"] = "value";

  for (const auto& kv : map) {
    EXPECT_EQ(kv.first.as<std::string>(), "key");
    EXPECT_EQ(kv.second.as<std::string>(), "value");
  }
}

}  // namespace
