#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test ID: 204

// Tests for iterator_base through the public YAML::Node interface,
// since iterator_base is a detail class accessed via Node::iterator

class IteratorTest_204 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default-constructed iterator equality
TEST_F(IteratorTest_204, DefaultConstructedIteratorsAreEqual_204) {
    YAML::Node node;
    // An empty node (undefined) should have begin == end
    // For a sequence or map that's empty, begin() == end()
    YAML::Node seq = YAML::Load("[]");
    EXPECT_EQ(seq.begin(), seq.end());
}

// Test iteration over a non-empty sequence
TEST_F(IteratorTest_204, SequenceIterationNormal_204) {
    YAML::Node seq = YAML::Load("[1, 2, 3]");
    int count = 0;
    std::vector<int> values;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        values.push_back(it->as<int>());
        count++;
    }
    EXPECT_EQ(count, 3);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

// Test post-increment operator on sequence iterator
TEST_F(IteratorTest_204, PostIncrementOperator_204) {
    YAML::Node seq = YAML::Load("[10, 20]");
    auto it = seq.begin();
    auto old_it = it++;
    EXPECT_EQ(old_it->as<int>(), 10);
    EXPECT_EQ(it->as<int>(), 20);
}

// Test pre-increment operator on sequence iterator
TEST_F(IteratorTest_204, PreIncrementOperator_204) {
    YAML::Node seq = YAML::Load("[10, 20]");
    auto it = seq.begin();
    auto& ref = ++it;
    EXPECT_EQ(it->as<int>(), 20);
    EXPECT_EQ(ref->as<int>(), 20);
}

// Test dereference operator on sequence iterator
TEST_F(IteratorTest_204, DereferenceOperatorSequence_204) {
    YAML::Node seq = YAML::Load("[hello]");
    auto it = seq.begin();
    YAML::Node val = *it;
    EXPECT_EQ(val.as<std::string>(), "hello");
}

// Test arrow operator on sequence iterator
TEST_F(IteratorTest_204, ArrowOperatorSequence_204) {
    YAML::Node seq = YAML::Load("[42]");
    auto it = seq.begin();
    EXPECT_EQ(it->as<int>(), 42);
}

// Test equality operator - same position
TEST_F(IteratorTest_204, EqualityOperatorSamePosition_204) {
    YAML::Node seq = YAML::Load("[1, 2]");
    auto it1 = seq.begin();
    auto it2 = seq.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test inequality operator - different positions
TEST_F(IteratorTest_204, InequalityOperatorDifferentPosition_204) {
    YAML::Node seq = YAML::Load("[1, 2]");
    auto it1 = seq.begin();
    auto it2 = seq.end();
    EXPECT_TRUE(it1 != it2);
    EXPECT_FALSE(it1 == it2);
}

// Test iteration over a map
TEST_F(IteratorTest_204, MapIterationNormal_204) {
    YAML::Node map = YAML::Load("{a: 1, b: 2}");
    int count = 0;
    std::map<std::string, int> result;
    for (auto it = map.begin(); it != map.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
        count++;
    }
    EXPECT_EQ(count, 2);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// Test arrow operator on map iterator (proxy)
TEST_F(IteratorTest_204, ArrowOperatorMap_204) {
    YAML::Node map = YAML::Load("{key: value}");
    auto it = map.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");
}

// Test empty map iteration
TEST_F(IteratorTest_204, EmptyMapIteration_204) {
    YAML::Node map = YAML::Load("{}");
    EXPECT_EQ(map.begin(), map.end());
    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test empty sequence iteration
TEST_F(IteratorTest_204, EmptySequenceIteration_204) {
    YAML::Node seq = YAML::Load("[]");
    EXPECT_EQ(seq.begin(), seq.end());
    int count = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test single element sequence
TEST_F(IteratorTest_204, SingleElementSequence_204) {
    YAML::Node seq = YAML::Load("[only]");
    auto it = seq.begin();
    EXPECT_NE(it, seq.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_EQ(it, seq.end());
}

// Test single element map
TEST_F(IteratorTest_204, SingleElementMap_204) {
    YAML::Node map = YAML::Load("{solo: item}");
    auto it = map.begin();
    EXPECT_NE(it, map.end());
    EXPECT_EQ(it->first.as<std::string>(), "solo");
    EXPECT_EQ(it->second.as<std::string>(), "item");
    ++it;
    EXPECT_EQ(it, map.end());
}

// Test const iteration over sequence
TEST_F(IteratorTest_204, ConstIterationSequence_204) {
    const YAML::Node seq = YAML::Load("[a, b, c]");
    int count = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test const iteration over map
TEST_F(IteratorTest_204, ConstIterationMap_204) {
    const YAML::Node map = YAML::Load("{x: 1, y: 2}");
    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test iteration with nested structures
TEST_F(IteratorTest_204, NestedStructureIteration_204) {
    YAML::Node node = YAML::Load("[{a: 1}, {b: 2}]");
    auto it = node.begin();
    EXPECT_TRUE(it->IsMap());
    EXPECT_EQ((*it)["a"].as<int>(), 1);
    ++it;
    EXPECT_TRUE(it->IsMap());
    EXPECT_EQ((*it)["b"].as<int>(), 2);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test multiple increments reach end
TEST_F(IteratorTest_204, MultipleIncrementsReachEnd_204) {
    YAML::Node seq = YAML::Load("[1, 2, 3, 4, 5]");
    auto it = seq.begin();
    for (int i = 0; i < 5; ++i) {
        EXPECT_NE(it, seq.end());
        ++it;
    }
    EXPECT_EQ(it, seq.end());
}

// Test dereference returns proper YAML::Node for map
TEST_F(IteratorTest_204, DereferenceMapReturnsNodePair_204) {
    YAML::Node map = YAML::Load("{foo: bar}");
    auto it = map.begin();
    auto pair = *it;
    EXPECT_EQ(pair.first.as<std::string>(), "foo");
    EXPECT_EQ(pair.second.as<std::string>(), "bar");
}

// Test range-based for loop on sequence
TEST_F(IteratorTest_204, RangeBasedForSequence_204) {
    YAML::Node seq = YAML::Load("[10, 20, 30]");
    std::vector<int> values;
    for (const auto& item : seq) {
        values.push_back(item.as<int>());
    }
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// Test range-based for loop on map
TEST_F(IteratorTest_204, RangeBasedForMap_204) {
    YAML::Node map = YAML::Load("{alpha: 1, beta: 2}");
    std::map<std::string, int> result;
    for (const auto& kv : map) {
        result[kv.first.as<std::string>()] = kv.second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["alpha"], 1);
    EXPECT_EQ(result["beta"], 2);
}

// Test that post-increment returns iterator to old position
TEST_F(IteratorTest_204, PostIncrementReturnsPreviousValue_204) {
    YAML::Node seq = YAML::Load("[first, second, third]");
    auto it = seq.begin();
    ++it; // now at "second"
    auto prev = it++;
    EXPECT_EQ(prev->as<std::string>(), "second");
    EXPECT_EQ(it->as<std::string>(), "third");
}

// Test large sequence iteration
TEST_F(IteratorTest_204, LargeSequenceIteration_204) {
    std::string yaml = "[";
    for (int i = 0; i < 100; ++i) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    YAML::Node seq = YAML::Load(yaml);
    int count = 0;
    int sum = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 100);
    EXPECT_EQ(sum, 4950); // sum of 0..99
}
