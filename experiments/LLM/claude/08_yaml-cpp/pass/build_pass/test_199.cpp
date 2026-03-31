#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class IteratorTest_199 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default constructed iterators are equal
TEST_F(IteratorTest_199, DefaultConstructedIteratorsAreEqual_199) {
    YAML::Node node;
    YAML::iterator it1;
    YAML::iterator it2;
    // Default constructed iterators should compare equal
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test: Begin and end are equal for empty sequence
TEST_F(IteratorTest_199, EmptySequenceBeginEqualsEnd_199) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Begin and end are equal for empty map
TEST_F(IteratorTest_199, EmptyMapBeginEqualsEnd_199) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Iterating over a sequence with elements
TEST_F(IteratorTest_199, SequenceIterationNormal_199) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Iterating over a map with elements
TEST_F(IteratorTest_199, MapIterationNormal_199) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Pre-increment returns reference to same iterator
TEST_F(IteratorTest_199, PreIncrementReturnsSelf_199) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto it = node.begin();
    auto& ref = ++it;
    EXPECT_EQ(&ref, &it);
}

// Test: Post-increment returns copy of previous state
TEST_F(IteratorTest_199, PostIncrementReturnsPreviousState_199) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto it = node.begin();
    auto prev = it++;
    // prev should point to first element, it should point to second
    EXPECT_EQ(prev->as<int>(), 1);
    EXPECT_EQ(it->as<int>(), 2);
}

// Test: Dereference operator returns correct value for sequence
TEST_F(IteratorTest_199, DereferenceSequenceValue_199) {
    YAML::Node node = YAML::Load("[hello, world]");
    auto it = node.begin();
    EXPECT_EQ((*it).as<std::string>(), "hello");
    ++it;
    EXPECT_EQ((*it).as<std::string>(), "world");
}

// Test: Arrow operator returns correct value for sequence
TEST_F(IteratorTest_199, ArrowOperatorSequenceValue_199) {
    YAML::Node node = YAML::Load("[42]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 42);
}

// Test: Map iterator dereference gives key-value pair
TEST_F(IteratorTest_199, MapIteratorDereference_199) {
    YAML::Node node = YAML::Load("{key: value}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");
}

// Test: Inequality operator for different positions
TEST_F(IteratorTest_199, InequalityForDifferentPositions_199) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it2;
    EXPECT_TRUE(it1 != it2);
    EXPECT_FALSE(it1 == it2);
}

// Test: Equality operator for same positions
TEST_F(IteratorTest_199, EqualityForSamePositions_199) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test: Iterating to end makes it equal to end()
TEST_F(IteratorTest_199, IteratingToEndEqualsEnd_199) {
    YAML::Node node = YAML::Load("[1]");
    auto it = node.begin();
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Single element sequence
TEST_F(IteratorTest_199, SingleElementSequence_199) {
    YAML::Node node = YAML::Load("[only]");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Single element map
TEST_F(IteratorTest_199, SingleElementMap_199) {
    YAML::Node node = YAML::Load("{solo: one}");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "solo");
    EXPECT_EQ(it->second.as<std::string>(), "one");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: const_iterator from non-const node
TEST_F(IteratorTest_199, ConstIteratorFromNonConst_199) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    YAML::const_iterator cit = node.begin();
    int count = 0;
    for (; cit != node.end(); ++cit) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Copy construction of iterator
TEST_F(IteratorTest_199, CopyConstructIterator_199) {
    YAML::Node node = YAML::Load("[a, b, c]");
    auto it1 = node.begin();
    auto it2 = it1;
    EXPECT_EQ(it1, it2);
    EXPECT_EQ((*it1).as<std::string>(), (*it2).as<std::string>());
}

// Test: Incrementing copy doesn't affect original
TEST_F(IteratorTest_199, IncrementCopyDoesNotAffectOriginal_199) {
    YAML::Node node = YAML::Load("[x, y, z]");
    auto it1 = node.begin();
    auto it2 = it1;
    ++it2;
    EXPECT_NE(it1, it2);
    EXPECT_EQ((*it1).as<std::string>(), "x");
    EXPECT_EQ((*it2).as<std::string>(), "y");
}

// Test: Large sequence iteration
TEST_F(IteratorTest_199, LargeSequenceIteration_199) {
    YAML::Node node;
    const int N = 100;
    for (int i = 0; i < N; i++) {
        node.push_back(i);
    }
    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, N);
    EXPECT_EQ(sum, N * (N - 1) / 2);
}

// Test: Map iteration accesses all key-value pairs
TEST_F(IteratorTest_199, MapIterationAccessAllPairs_199) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
    EXPECT_EQ(result["c"], 3);
}

// Test: Scalar node has no iteration (begin == end)
TEST_F(IteratorTest_199, ScalarNodeBeginEqualsEnd_199) {
    YAML::Node node = YAML::Load("scalar_value");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Null node has no iteration (begin == end)
TEST_F(IteratorTest_199, NullNodeBeginEqualsEnd_199) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Range-based for loop on sequence
TEST_F(IteratorTest_199, RangeBasedForSequence_199) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    std::vector<int> values;
    for (const auto& val : node) {
        values.push_back(val.as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// Test: Range-based for loop on map
TEST_F(IteratorTest_199, RangeBasedForMap_199) {
    YAML::Node node = YAML::Load("{x: 100, y: 200}");
    std::map<std::string, int> result;
    for (const auto& pair : node) {
        result[pair.first.as<std::string>()] = pair.second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["x"], 100);
    EXPECT_EQ(result["y"], 200);
}

// Test: Nested sequence iteration
TEST_F(IteratorTest_199, NestedSequenceIteration_199) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    auto it = node.begin();
    EXPECT_TRUE(it->IsSequence());
    EXPECT_EQ((*it)[0].as<int>(), 1);
    EXPECT_EQ((*it)[1].as<int>(), 2);
    ++it;
    EXPECT_TRUE(it->IsSequence());
    EXPECT_EQ((*it)[0].as<int>(), 3);
    EXPECT_EQ((*it)[1].as<int>(), 4);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Multiple increments chain correctly
TEST_F(IteratorTest_199, MultiplePreIncrementChain_199) {
    YAML::Node node = YAML::Load("[a, b, c, d]");
    auto it = node.begin();
    ++(++it);
    EXPECT_EQ(it->as<std::string>(), "c");
}
