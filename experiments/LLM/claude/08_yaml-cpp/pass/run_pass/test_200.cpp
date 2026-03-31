#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/iterator.h"

// Test fixture for iterator tests
class IteratorTest_200 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Iterating over a sequence node using iterators
TEST_F(IteratorTest_200, SequenceIteratorTraversal_200) {
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

// Test: Post-increment returns the iterator before increment
TEST_F(IteratorTest_200, PostIncrementReturnsOldValue_200) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");

    auto it = node.begin();
    auto old_it = it++;
    // old_it should point to the first element
    EXPECT_EQ(old_it->as<std::string>(), "a");
    // it should now point to the second element
    EXPECT_EQ(it->as<std::string>(), "b");
}

// Test: Pre-increment moves iterator forward
TEST_F(IteratorTest_200, PreIncrementMovesForward_200) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 10);
    ++it;
    EXPECT_EQ(it->as<int>(), 20);
    ++it;
    EXPECT_EQ(it->as<int>(), 30);
}

// Test: Iterator equality comparison
TEST_F(IteratorTest_200, IteratorEqualityComparison_200) {
    YAML::Node node;
    node.push_back(1);

    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test: Iterator inequality comparison
TEST_F(IteratorTest_200, IteratorInequalityComparison_200) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it = node.begin();
    auto end = node.end();
    EXPECT_TRUE(it != end);
}

// Test: Iterating over an empty sequence
TEST_F(IteratorTest_200, EmptySequenceIterator_200) {
    YAML::Node node(YAML::NodeType::Sequence);

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test: Begin equals end for empty sequence
TEST_F(IteratorTest_200, EmptySequenceBeginEqualsEnd_200) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Map iterator traversal
TEST_F(IteratorTest_200, MapIteratorTraversal_200) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Map iterator key-value access
TEST_F(IteratorTest_200, MapIteratorKeyValueAccess_200) {
    YAML::Node node;
    node["hello"] = "world";

    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "hello");
    EXPECT_EQ(it->second.as<std::string>(), "world");
}

// Test: Post-increment on map iterator
TEST_F(IteratorTest_200, MapPostIncrementReturnsOldValue_200) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;

    auto it = node.begin();
    std::string first_key = it->first.as<std::string>();
    auto old_it = it++;
    EXPECT_EQ(old_it->first.as<std::string>(), first_key);
    EXPECT_TRUE(it != old_it);
}

// Test: Const iterator over sequence
TEST_F(IteratorTest_200, ConstIteratorSequence_200) {
    YAML::Node node;
    node.push_back(42);
    node.push_back(43);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Const iterator over map
TEST_F(IteratorTest_200, ConstIteratorMap_200) {
    YAML::Node node;
    node["x"] = "y";

    const YAML::Node& constNode = node;
    auto it = constNode.begin();
    EXPECT_EQ(it->first.as<std::string>(), "x");
    EXPECT_EQ(it->second.as<std::string>(), "y");
}

// Test: Single element sequence - post increment reaches end
TEST_F(IteratorTest_200, SingleElementPostIncrementReachesEnd_200) {
    YAML::Node node;
    node.push_back(99);

    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 99);
    EXPECT_TRUE(it == node.end());
}

// Test: Copy of iterator is independent
TEST_F(IteratorTest_200, IteratorCopyIndependence_200) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    auto it = node.begin();
    auto copy = it;
    ++it;
    // copy should still point to original position
    EXPECT_EQ(copy->as<int>(), 1);
    EXPECT_EQ(it->as<int>(), 2);
}

// Test: Multiple post-increments in sequence
TEST_F(IteratorTest_200, MultiplePostIncrements_200) {
    YAML::Node node;
    node.push_back("x");
    node.push_back("y");
    node.push_back("z");

    auto it = node.begin();
    EXPECT_EQ((it++)->as<std::string>(), "x");
    EXPECT_EQ((it++)->as<std::string>(), "y");
    EXPECT_EQ((it++)->as<std::string>(), "z");
    EXPECT_TRUE(it == node.end());
}

// Test: Empty map begin equals end
TEST_F(IteratorTest_200, EmptyMapBeginEqualsEnd_200) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Dereference sequence iterator
TEST_F(IteratorTest_200, DereferenceSequenceIterator_200) {
    YAML::Node node;
    node.push_back(3.14);

    auto it = node.begin();
    YAML::Node val = *it;
    EXPECT_DOUBLE_EQ(val.as<double>(), 3.14);
}
