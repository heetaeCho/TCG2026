#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test ID: 188

// Tests for node_iterator_base through the public YAML::Node interface,
// since node_iterator_base is an internal detail class accessed via Node iterators.

class NodeIteratorTest_188 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default-constructed iterator equality
TEST_F(NodeIteratorTest_188, DefaultConstructedIteratorsAreEqual_188) {
    YAML::Node::iterator it1;
    YAML::Node::iterator it2;
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test iterating over a sequence node
TEST_F(NodeIteratorTest_188, SequenceIteration_188) {
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

// Test iterating over an empty sequence
TEST_F(NodeIteratorTest_188, EmptySequenceIteration_188) {
    YAML::Node seq = YAML::Load("[]");
    int count = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test begin equals end for empty sequence
TEST_F(NodeIteratorTest_188, EmptySequenceBeginEqualsEnd_188) {
    YAML::Node seq = YAML::Load("[]");
    EXPECT_TRUE(seq.begin() == seq.end());
}

// Test iterating over a map node
TEST_F(NodeIteratorTest_188, MapIteration_188) {
    YAML::Node map;
    map["key1"] = "val1";
    map["key2"] = "val2";

    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test iterating over an empty map
TEST_F(NodeIteratorTest_188, EmptyMapIteration_188) {
    YAML::Node map = YAML::Load("{}");
    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test begin equals end for empty map
TEST_F(NodeIteratorTest_188, EmptyMapBeginEqualsEnd_188) {
    YAML::Node map = YAML::Load("{}");
    EXPECT_TRUE(map.begin() == map.end());
}

// Test dereference operator on sequence iterator
TEST_F(NodeIteratorTest_188, SequenceDereferenceOperator_188) {
    YAML::Node seq;
    seq.push_back(42);

    auto it = seq.begin();
    YAML::Node val = *it;
    EXPECT_EQ(val.as<int>(), 42);
}

// Test dereference operator on map iterator
TEST_F(NodeIteratorTest_188, MapDereferenceOperator_188) {
    YAML::Node map;
    map["hello"] = "world";

    auto it = map.begin();
    EXPECT_EQ(it->first.as<std::string>(), "hello");
    EXPECT_EQ(it->second.as<std::string>(), "world");
}

// Test post-increment operator on sequence
TEST_F(NodeIteratorTest_188, SequencePostIncrement_188) {
    YAML::Node seq;
    seq.push_back(10);
    seq.push_back(20);

    auto it = seq.begin();
    auto old_it = it++;
    EXPECT_EQ((*old_it).as<int>(), 10);
    EXPECT_EQ((*it).as<int>(), 20);
}

// Test pre-increment operator on sequence
TEST_F(NodeIteratorTest_188, SequencePreIncrement_188) {
    YAML::Node seq;
    seq.push_back(10);
    seq.push_back(20);

    auto it = seq.begin();
    auto& ref = ++it;
    EXPECT_EQ((*ref).as<int>(), 20);
    EXPECT_EQ((*it).as<int>(), 20);
}

// Test inequality operator
TEST_F(NodeIteratorTest_188, InequalityOperator_188) {
    YAML::Node seq;
    seq.push_back(1);

    EXPECT_TRUE(seq.begin() != seq.end());
}

// Test equality of begin iterators
TEST_F(NodeIteratorTest_188, BeginIteratorsAreEqual_188) {
    YAML::Node seq;
    seq.push_back(1);
    seq.push_back(2);

    auto it1 = seq.begin();
    auto it2 = seq.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test that incrementing to end works
TEST_F(NodeIteratorTest_188, IncrementToEnd_188) {
    YAML::Node seq;
    seq.push_back(1);

    auto it = seq.begin();
    ++it;
    EXPECT_TRUE(it == seq.end());
}

// Test const_iterator on sequence
TEST_F(NodeIteratorTest_188, ConstIteratorSequence_188) {
    YAML::Node seq;
    seq.push_back("abc");
    seq.push_back("def");

    const YAML::Node& constSeq = seq;
    int count = 0;
    for (auto it = constSeq.begin(); it != constSeq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test const_iterator on map
TEST_F(NodeIteratorTest_188, ConstIteratorMap_188) {
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

// Test arrow operator on map iterator
TEST_F(NodeIteratorTest_188, ArrowOperatorMap_188) {
    YAML::Node map;
    map["key"] = "value";

    auto it = map.begin();
    std::string key = it->first.as<std::string>();
    std::string val = it->second.as<std::string>();
    EXPECT_EQ(key, "key");
    EXPECT_EQ(val, "value");
}

// Test iterating over a sequence with multiple types
TEST_F(NodeIteratorTest_188, SequenceMultipleTypes_188) {
    YAML::Node seq = YAML::Load("[1, hello, 3.14, true]");

    std::vector<std::string> values;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        values.push_back(it->as<std::string>());
    }

    EXPECT_EQ(values.size(), 4u);
    EXPECT_EQ(values[0], "1");
    EXPECT_EQ(values[1], "hello");
    EXPECT_EQ(values[2], "3.14");
    EXPECT_EQ(values[3], "true");
}

// Test iterating over a larger sequence
TEST_F(NodeIteratorTest_188, LargeSequenceIteration_188) {
    YAML::Node seq;
    const int N = 100;
    for (int i = 0; i < N; i++) {
        seq.push_back(i);
    }

    int count = 0;
    int sum = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, N);
    EXPECT_EQ(sum, N * (N - 1) / 2);
}

// Test iterating over a single element sequence
TEST_F(NodeIteratorTest_188, SingleElementSequence_188) {
    YAML::Node seq;
    seq.push_back("only");

    auto it = seq.begin();
    EXPECT_NE(it, seq.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_EQ(it, seq.end());
}

// Test iterating over a single element map
TEST_F(NodeIteratorTest_188, SingleElementMap_188) {
    YAML::Node map;
    map["sole"] = "entry";

    auto it = map.begin();
    EXPECT_NE(it, map.end());
    EXPECT_EQ(it->first.as<std::string>(), "sole");
    EXPECT_EQ(it->second.as<std::string>(), "entry");
    ++it;
    EXPECT_EQ(it, map.end());
}

// Test that scalar node has begin == end
TEST_F(NodeIteratorTest_188, ScalarNodeBeginEqualsEnd_188) {
    YAML::Node scalar = YAML::Load("42");
    EXPECT_TRUE(scalar.begin() == scalar.end());
}

// Test that null node has begin == end
TEST_F(NodeIteratorTest_188, NullNodeBeginEqualsEnd_188) {
    YAML::Node null = YAML::Load("~");
    EXPECT_TRUE(null.begin() == null.end());
}

// Test post-increment on map iterator
TEST_F(NodeIteratorTest_188, MapPostIncrement_188) {
    YAML::Node map;
    map["a"] = 1;
    map["b"] = 2;

    auto it = map.begin();
    auto old = it++;
    // old should still point to first element
    EXPECT_NE(old, it);
}

// Test nested structure iteration
TEST_F(NodeIteratorTest_188, NestedStructureIteration_188) {
    YAML::Node node = YAML::Load("{outer: {inner1: val1, inner2: val2}}");

    auto it = node.begin();
    EXPECT_NE(it, node.end());

    YAML::Node inner = it->second;
    EXPECT_TRUE(inner.IsMap());

    int innerCount = 0;
    for (auto innerIt = inner.begin(); innerIt != inner.end(); ++innerIt) {
        innerCount++;
    }
    EXPECT_EQ(innerCount, 2);
}

// Test conversion from non-const to const iterator (implicit conversion)
TEST_F(NodeIteratorTest_188, IteratorToConstIteratorConversion_188) {
    YAML::Node seq;
    seq.push_back(1);
    seq.push_back(2);

    YAML::Node::iterator it = seq.begin();
    YAML::const_iterator cit = it;  // Should compile and work
    EXPECT_EQ((*cit).as<int>(), 1);
}

// Test range-based for loop on sequence
TEST_F(NodeIteratorTest_188, RangeBasedForSequence_188) {
    YAML::Node seq = YAML::Load("[a, b, c]");
    std::vector<std::string> result;
    for (const auto& item : seq) {
        result.push_back(item.as<std::string>());
    }
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

// Test range-based for loop on map
TEST_F(NodeIteratorTest_188, RangeBasedForMap_188) {
    YAML::Node map = YAML::Load("{x: 1, y: 2}");
    int count = 0;
    for (const auto& kv : map) {
        EXPECT_TRUE(kv.first.IsDefined());
        EXPECT_TRUE(kv.second.IsDefined());
        count++;
    }
    EXPECT_EQ(count, 2);
}
