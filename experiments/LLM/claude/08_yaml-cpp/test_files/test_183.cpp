#include <gtest/gtest.h>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"

namespace YAML {
namespace detail {

// We'll work through the public Node interface to test iterators indirectly,
// since node_iterator_base depends on internal types that are hard to construct directly.

class NodeIteratorTest_183 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default-constructed iterators (NoneType) should be equal
TEST_F(NodeIteratorTest_183, DefaultConstructedIteratorsAreEqual_183) {
    YAML::Node node;
    // An undefined/null node should have begin() == end()
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Empty sequence has begin == end
TEST_F(NodeIteratorTest_183, EmptySequenceBeginEqualsEnd_183) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Empty map has begin == end
TEST_F(NodeIteratorTest_183, EmptyMapBeginEqualsEnd_183) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Sequence with elements - begin != end
TEST_F(NodeIteratorTest_183, NonEmptySequenceBeginNotEqualsEnd_183) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_FALSE(node.begin() == node.end());
    EXPECT_TRUE(node.begin() != node.end());
}

// Test: Map with elements - begin != end
TEST_F(NodeIteratorTest_183, NonEmptyMapBeginNotEqualsEnd_183) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_FALSE(node.begin() == node.end());
    EXPECT_TRUE(node.begin() != node.end());
}

// Test: Iterating through a sequence yields all elements
TEST_F(NodeIteratorTest_183, SequenceIterationYieldsAllElements_183) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    int count = 0;
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
        count++;
    }
    EXPECT_EQ(count, 3);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// Test: Iterating through a map yields all key-value pairs
TEST_F(NodeIteratorTest_183, MapIterationYieldsAllPairs_183) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_TRUE(it->first.IsDefined());
        EXPECT_TRUE(it->second.IsDefined());
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Pre-increment operator advances iterator
TEST_F(NodeIteratorTest_183, PreIncrementAdvancesSequenceIterator_183) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");

    auto it = node.begin();
    EXPECT_EQ(it->as<std::string>(), "a");
    ++it;
    EXPECT_EQ(it->as<std::string>(), "b");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test: Post-increment operator advances iterator but returns old value
TEST_F(NodeIteratorTest_183, PostIncrementReturnsOldValue_183) {
    YAML::Node node;
    node.push_back(100);
    node.push_back(200);

    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 100);
    EXPECT_EQ(it->as<int>(), 200);
}

// Test: Iterator equality - same position
TEST_F(NodeIteratorTest_183, SamePositionIteratorsAreEqual_183) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test: Iterator inequality - different positions
TEST_F(NodeIteratorTest_183, DifferentPositionIteratorsAreNotEqual_183) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it2;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

// Test: Dereference operator on sequence iterator
TEST_F(NodeIteratorTest_183, DereferenceSequenceIterator_183) {
    YAML::Node node;
    node.push_back(42);

    auto it = node.begin();
    YAML::Node val = *it;
    EXPECT_EQ(val.as<int>(), 42);
}

// Test: Arrow operator on map iterator gives key-value access
TEST_F(NodeIteratorTest_183, ArrowOperatorOnMapIterator_183) {
    YAML::Node node;
    node["hello"] = "world";

    auto it = node.begin();
    std::string key = it->first.as<std::string>();
    std::string value = it->second.as<std::string>();
    EXPECT_EQ(key, "hello");
    EXPECT_EQ(value, "world");
}

// Test: Scalar node has begin == end (no iteration possible)
TEST_F(NodeIteratorTest_183, ScalarNodeBeginEqualsEnd_183) {
    YAML::Node node("scalar_value");
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Null node has begin == end
TEST_F(NodeIteratorTest_183, NullNodeBeginEqualsEnd_183) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Single element sequence iteration
TEST_F(NodeIteratorTest_183, SingleElementSequence_183) {
    YAML::Node node;
    node.push_back("only");

    auto it = node.begin();
    EXPECT_FALSE(it == node.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test: Single entry map iteration
TEST_F(NodeIteratorTest_183, SingleEntryMap_183) {
    YAML::Node node;
    node["sole"] = "entry";

    auto it = node.begin();
    EXPECT_FALSE(it == node.end());
    EXPECT_EQ(it->first.as<std::string>(), "sole");
    EXPECT_EQ(it->second.as<std::string>(), "entry");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test: Const iterator on sequence
TEST_F(NodeIteratorTest_183, ConstIteratorOnSequence_183) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Const iterator on map
TEST_F(NodeIteratorTest_183, ConstIteratorOnMap_183) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Large sequence iteration
TEST_F(NodeIteratorTest_183, LargeSequenceIteration_183) {
    YAML::Node node;
    const int N = 1000;
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

// Test: End iterators are equal to each other
TEST_F(NodeIteratorTest_183, EndIteratorsAreEqual_183) {
    YAML::Node node;
    node.push_back(1);

    auto end1 = node.end();
    auto end2 = node.end();
    EXPECT_TRUE(end1 == end2);
}

// Test: Operator!= is negation of operator==
TEST_F(NodeIteratorTest_183, NotEqualIsNegationOfEqual_183) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_EQ(!(it1 == it2), (it1 != it2));

    ++it2;
    EXPECT_EQ(!(it1 == it2), (it1 != it2));
}

// Test: Parsed YAML sequence iteration
TEST_F(NodeIteratorTest_183, ParsedYAMLSequenceIteration_183) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 5);
}

// Test: Parsed YAML map iteration
TEST_F(NodeIteratorTest_183, ParsedYAMLMapIteration_183) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_TRUE(it->first.IsDefined());
        EXPECT_TRUE(it->second.IsDefined());
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Mixed types in sequence
TEST_F(NodeIteratorTest_183, MixedTypesInSequence_183) {
    YAML::Node node = YAML::Load("[1, hello, 3.14, true]");
    
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 1);
    ++it;
    EXPECT_EQ(it->as<std::string>(), "hello");
    ++it;
    EXPECT_NEAR(it->as<double>(), 3.14, 0.001);
    ++it;
    EXPECT_EQ(it->as<bool>(), true);
    ++it;
    EXPECT_TRUE(it == node.end());
}

}  // namespace detail
}  // namespace YAML
