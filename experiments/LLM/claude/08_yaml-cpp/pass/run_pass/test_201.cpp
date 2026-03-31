#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/iterator.h"

class IteratorBaseTest_201 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructed iterators are equal
TEST_F(IteratorBaseTest_201, DefaultConstructedIteratorsAreEqual_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    // Two begin iterators of an empty sequence should be equal
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test begin equals end for empty sequence
TEST_F(IteratorBaseTest_201, BeginEqualsEndForEmptySequence_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test begin equals end for empty map
TEST_F(IteratorBaseTest_201, BeginEqualsEndForEmptyMap_201) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test begin not equal end for non-empty sequence
TEST_F(IteratorBaseTest_201, BeginNotEqualEndForNonEmptySequence_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    EXPECT_TRUE(node.begin() != node.end());
}

// Test begin not equal end for non-empty map
TEST_F(IteratorBaseTest_201, BeginNotEqualEndForNonEmptyMap_201) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    EXPECT_TRUE(node.begin() != node.end());
}

// Test prefix increment advances iterator
TEST_F(IteratorBaseTest_201, PrefixIncrementAdvancesIterator_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    auto it = node.begin();
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test postfix increment advances iterator
TEST_F(IteratorBaseTest_201, PostfixIncrementAdvancesIterator_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    auto it = node.begin();
    it++;
    EXPECT_TRUE(it == node.end());
}

// Test postfix increment returns old value
TEST_F(IteratorBaseTest_201, PostfixIncrementReturnsOldValue_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(42);
    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 42);
    EXPECT_TRUE(it == node.end());
}

// Test dereference operator for sequence
TEST_F(IteratorBaseTest_201, DereferenceOperatorForSequence_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(42);
    auto it = node.begin();
    YAML::Node value = *it;
    EXPECT_EQ(value.as<int>(), 42);
}

// Test dereference for map returns key-value pair
TEST_F(IteratorBaseTest_201, DereferenceOperatorForMap_201) {
    YAML::Node node(YAML::NodeType::Map);
    node["hello"] = "world";
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "hello");
    EXPECT_EQ(it->second.as<std::string>(), "world");
}

// Test iterating over multiple sequence elements
TEST_F(IteratorBaseTest_201, IterateOverMultipleSequenceElements_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 3);
    EXPECT_EQ(sum, 6);
}

// Test iterating over multiple map elements
TEST_F(IteratorBaseTest_201, IterateOverMultipleMapElements_201) {
    YAML::Node node(YAML::NodeType::Map);
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test inequality operator
TEST_F(IteratorBaseTest_201, InequalityOperator_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    auto begin = node.begin();
    auto end = node.end();
    EXPECT_TRUE(begin != end);
    EXPECT_FALSE(begin == end);
}

// Test equality is symmetric
TEST_F(IteratorBaseTest_201, EqualityIsSymmetric_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_TRUE(it2 == it1);
}

// Test arrow operator for sequence
TEST_F(IteratorBaseTest_201, ArrowOperatorForSequence_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("test_string");
    auto it = node.begin();
    EXPECT_EQ(it->as<std::string>(), "test_string");
}

// Test iterator with single element sequence - increment reaches end
TEST_F(IteratorBaseTest_201, SingleElementIncrementReachesEnd_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(100);
    auto it = node.begin();
    EXPECT_FALSE(it == node.end());
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test const iterator from const node
TEST_F(IteratorBaseTest_201, ConstIteratorFromConstNode_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(5);
    node.push_back(10);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test iterating and verifying values in sequence
TEST_F(IteratorBaseTest_201, IterateAndVerifySequenceValues_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("first");
    node.push_back("second");

    auto it = node.begin();
    EXPECT_EQ(it->as<std::string>(), "first");
    ++it;
    EXPECT_EQ(it->as<std::string>(), "second");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test iterator copy preserves position
TEST_F(IteratorBaseTest_201, IteratorCopyPreservesPosition_201) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    ++it1; // pointing to second element
    auto it2 = it1; // copy
    EXPECT_TRUE(it1 == it2);
    EXPECT_EQ((*it2).as<int>(), 2);
}

// Test parsed YAML iteration
TEST_F(IteratorBaseTest_201, ParsedYamlSequenceIteration_201) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// Test parsed YAML map iteration
TEST_F(IteratorBaseTest_201, ParsedYamlMapIteration_201) {
    YAML::Node node = YAML::Load("{x: 1, y: 2}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_TRUE(it->first.IsDefined());
        EXPECT_TRUE(it->second.IsDefined());
        count++;
    }
    EXPECT_EQ(count, 2);
}
