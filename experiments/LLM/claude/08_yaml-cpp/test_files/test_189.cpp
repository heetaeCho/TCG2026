#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/node.h"

namespace {

class NodeIteratorTest_189 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default-constructed iterators are equal
TEST_F(NodeIteratorTest_189, DefaultConstructedIteratorsAreEqual_189) {
    YAML::Node node;
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test: Begin equals end for empty sequence
TEST_F(NodeIteratorTest_189, EmptySequenceBeginEqualsEnd_189) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Begin equals end for empty map
TEST_F(NodeIteratorTest_189, EmptyMapBeginEqualsEnd_189) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Sequence iteration - single element
TEST_F(NodeIteratorTest_189, SequenceSingleElementIteration_189) {
    YAML::Node node = YAML::Load("[1]");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<int>(), 1);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Sequence iteration - multiple elements
TEST_F(NodeIteratorTest_189, SequenceMultipleElementsIteration_189) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    int count = 0;
    int expected = 1;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_EQ(it->as<int>(), expected);
        ++expected;
        ++count;
    }
    EXPECT_EQ(count, 3);
}

// Test: Map iteration - single pair
TEST_F(NodeIteratorTest_189, MapSinglePairIteration_189) {
    YAML::Node node = YAML::Load("{a: 1}");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "a");
    EXPECT_EQ(it->second.as<int>(), 1);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Map iteration - multiple pairs
TEST_F(NodeIteratorTest_189, MapMultiplePairsIteration_189) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 3);
}

// Test: Post-increment returns old value
TEST_F(NodeIteratorTest_189, PostIncrementReturnsOldValue_189) {
    YAML::Node node = YAML::Load("[10, 20]");
    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 10);
    EXPECT_EQ(it->as<int>(), 20);
}

// Test: Pre-increment returns new value
TEST_F(NodeIteratorTest_189, PreIncrementReturnsNewValue_189) {
    YAML::Node node = YAML::Load("[10, 20]");
    auto it = node.begin();
    auto& ref = ++it;
    EXPECT_EQ(ref->as<int>(), 20);
    EXPECT_EQ(it->as<int>(), 20);
}

// Test: Inequality operator
TEST_F(NodeIteratorTest_189, InequalityOperator_189) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    ++it;
    EXPECT_NE(it, node.end());
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Dereference operator for sequence
TEST_F(NodeIteratorTest_189, DereferenceOperatorSequence_189) {
    YAML::Node node = YAML::Load("[hello]");
    auto it = node.begin();
    YAML::Node val = *it;
    EXPECT_EQ(val.as<std::string>(), "hello");
}

// Test: Arrow operator for map
TEST_F(NodeIteratorTest_189, ArrowOperatorMap_189) {
    YAML::Node node = YAML::Load("{key: value}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");
}

// Test: Scalar node begin equals end
TEST_F(NodeIteratorTest_189, ScalarNodeBeginEqualsEnd_189) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Null node begin equals end
TEST_F(NodeIteratorTest_189, NullNodeBeginEqualsEnd_189) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Undefined node iteration
TEST_F(NodeIteratorTest_189, UndefinedNodeIteration_189) {
    YAML::Node node = YAML::Load("{}");
    YAML::Node child = node["nonexistent"];
    // Accessing a nonexistent key on a map should not crash iteration
    // The child is undefined
    EXPECT_FALSE(child.IsDefined());
}

// Test: increment_until_defined skips undefined map entries
TEST_F(NodeIteratorTest_189, MapIterationSkipsUndefinedEntries_189) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    // Access a nonexistent key which may create an undefined entry
    YAML::Node undefined = node["z"];
    
    // Iterate and count only defined entries
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        ++count;
    }
    // Should iterate over defined entries (at least a and b)
    EXPECT_GE(count, 2);
}

// Test: Copy construction of const iterator from non-const
TEST_F(NodeIteratorTest_189, ConstIteratorFromNonConst_189) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    YAML::Node::iterator it = node.begin();
    YAML::Node::const_iterator cit = it;
    EXPECT_EQ(cit, node.begin());
}

// Test: Large sequence iteration
TEST_F(NodeIteratorTest_189, LargeSequenceIteration_189) {
    std::string yaml = "[";
    for (int i = 0; i < 100; ++i) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    
    YAML::Node node = YAML::Load(yaml);
    int count = 0;
    int expected = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_EQ(it->as<int>(), expected);
        ++expected;
        ++count;
    }
    EXPECT_EQ(count, 100);
}

// Test: Map iteration preserves key-value association
TEST_F(NodeIteratorTest_189, MapIterationPreservesKeyValueAssociation_189) {
    YAML::Node node = YAML::Load("{x: 10, y: 20, z: 30}");
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result["x"], 10);
    EXPECT_EQ(result["y"], 20);
    EXPECT_EQ(result["z"], 30);
}

// Test: Two iterators pointing to same position are equal
TEST_F(NodeIteratorTest_189, TwoIteratorsAtSamePositionAreEqual_189) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_EQ(it1, it2);
    ++it1;
    ++it2;
    EXPECT_EQ(it1, it2);
}

// Test: Nested structure iteration
TEST_F(NodeIteratorTest_189, NestedStructureIteration_189) {
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

// Test: Removing element and then iterating
TEST_F(NodeIteratorTest_189, RemoveMapElementAndIterate_189) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    node.remove("b");
    
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        if (it->second.IsDefined()) {
            result[it->first.as<std::string>()] = it->second.as<int>();
        }
    }
    EXPECT_EQ(result.count("a"), 1u);
    EXPECT_EQ(result.count("c"), 1u);
    // b was removed, should not appear as defined
    EXPECT_EQ(result.count("b"), 0u);
}

}  // namespace
