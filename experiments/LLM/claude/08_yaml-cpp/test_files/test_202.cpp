#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/iterator.h"

// Test fixture for iterator tests
class IteratorBaseTest_202 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default-constructed iterators are equal
TEST_F(IteratorBaseTest_202, DefaultConstructedIteratorsAreEqual_202) {
    YAML::Node node(YAML::NodeType::Sequence);
    // begin == end for empty sequence
    EXPECT_TRUE(node.begin() == node.end());
}

// Test that default-constructed iterators satisfy !(begin != end) for empty
TEST_F(IteratorBaseTest_202, DefaultConstructedIteratorsNotNotEqual_202) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_FALSE(node.begin() != node.end());
}

// Test iteration over a non-empty sequence
TEST_F(IteratorBaseTest_202, SequenceIterationNonEmpty_202) {
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

// Test that begin != end for non-empty sequence
TEST_F(IteratorBaseTest_202, BeginNotEqualEndForNonEmptySequence_202) {
    YAML::Node node;
    node.push_back("hello");
    EXPECT_TRUE(node.begin() != node.end());
}

// Test that begin == end for empty sequence
TEST_F(IteratorBaseTest_202, BeginEqualsEndForEmptySequence_202) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
    EXPECT_FALSE(node.begin() != node.end());
}

// Test pre-increment operator
TEST_F(IteratorBaseTest_202, PreIncrementAdvancesIterator_202) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);

    auto it = node.begin();
    EXPECT_EQ((*it).as<int>(), 10);
    ++it;
    EXPECT_EQ((*it).as<int>(), 20);
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test post-increment operator
TEST_F(IteratorBaseTest_202, PostIncrementAdvancesIterator_202) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);

    auto it = node.begin();
    auto prev = it++;
    EXPECT_EQ((*prev).as<int>(), 10);
    EXPECT_EQ((*it).as<int>(), 20);
}

// Test dereference operator on sequence elements
TEST_F(IteratorBaseTest_202, DereferenceOperatorOnSequence_202) {
    YAML::Node node;
    node.push_back("alpha");
    node.push_back("beta");

    auto it = node.begin();
    EXPECT_EQ((*it).as<std::string>(), "alpha");
    ++it;
    EXPECT_EQ((*it).as<std::string>(), "beta");
}

// Test arrow operator on sequence elements
TEST_F(IteratorBaseTest_202, ArrowOperatorOnSequence_202) {
    YAML::Node node;
    node.push_back(42);

    auto it = node.begin();
    // The arrow operator should work similarly to dereference
    EXPECT_EQ(it->as<int>(), 42);
}

// Test iteration over a map
TEST_F(IteratorBaseTest_202, MapIterationNonEmpty_202) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        // Map iterator dereference gives key-value pair
        EXPECT_TRUE(it->first.IsDefined());
        EXPECT_TRUE(it->second.IsDefined());
    }
    EXPECT_EQ(count, 2);
}

// Test empty map iteration
TEST_F(IteratorBaseTest_202, EmptyMapBeginEqualsEnd_202) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
    EXPECT_FALSE(node.begin() != node.end());
}

// Test map dereference gives correct key-value pairs
TEST_F(IteratorBaseTest_202, MapDereferenceGivesCorrectPairs_202) {
    YAML::Node node;
    node["name"] = "test";

    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "name");
    EXPECT_EQ(it->second.as<std::string>(), "test");
}

// Test equality is reflexive
TEST_F(IteratorBaseTest_202, EqualityIsReflexive_202) {
    YAML::Node node;
    node.push_back(1);

    auto it = node.begin();
    EXPECT_TRUE(it == it);
    EXPECT_FALSE(it != it);
}

// Test that two copies of begin are equal
TEST_F(IteratorBaseTest_202, CopiedIteratorsAreEqual_202) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test that incrementing one copy makes them unequal
TEST_F(IteratorBaseTest_202, IncrementedCopyIsNotEqual_202) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it1;
    EXPECT_TRUE(it1 != it2);
    EXPECT_FALSE(it1 == it2);
}

// Test single-element sequence
TEST_F(IteratorBaseTest_202, SingleElementSequence_202) {
    YAML::Node node;
    node.push_back(99);

    auto it = node.begin();
    EXPECT_TRUE(it != node.end());
    EXPECT_EQ((*it).as<int>(), 99);
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test const iteration over sequence
TEST_F(IteratorBaseTest_202, ConstIterationOverSequence_202) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test const iteration over map
TEST_F(IteratorBaseTest_202, ConstIterationOverMap_202) {
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

// Test iterating through all elements yields correct values
TEST_F(IteratorBaseTest_202, IterationYieldsAllElements_202) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    node.push_back(40);

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back((*it).as<int>());
    }

    ASSERT_EQ(values.size(), 4u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
    EXPECT_EQ(values[3], 40);
}

// Test parsed YAML sequence iteration
TEST_F(IteratorBaseTest_202, ParsedSequenceIteration_202) {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test parsed YAML map iteration
TEST_F(IteratorBaseTest_202, ParsedMapIteration_202) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test that end iterators are equal
TEST_F(IteratorBaseTest_202, EndIteratorsAreEqual_202) {
    YAML::Node node;
    node.push_back(1);

    auto end1 = node.end();
    auto end2 = node.end();
    EXPECT_TRUE(end1 == end2);
    EXPECT_FALSE(end1 != end2);
}

// Test range-based for loop compatibility (which uses begin/end and iterator operators)
TEST_F(IteratorBaseTest_202, RangeBasedForLoopCompatibility_202) {
    YAML::Node node;
    node.push_back("x");
    node.push_back("y");
    node.push_back("z");

    std::vector<std::string> values;
    for (const auto& item : node) {
        values.push_back(item.as<std::string>());
    }

    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "x");
    EXPECT_EQ(values[1], "y");
    EXPECT_EQ(values[2], "z");
}
