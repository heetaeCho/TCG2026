#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"
#include "yaml-cpp/node/node.h"

namespace {

class NodeIteratorTest_680 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default-constructed iterators are equal
TEST_F(NodeIteratorTest_680, DefaultConstructedIteratorsAreEqual_680) {
    YAML::Node node;
    auto it1 = node.begin();
    auto it2 = node.end();
    EXPECT_TRUE(it1 == it2);
}

// Test: Sequence iteration - basic
TEST_F(NodeIteratorTest_680, SequenceIterationBasic_680) {
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

// Test: Sequence iteration - values are correct
TEST_F(NodeIteratorTest_680, SequenceIterationValues_680) {
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
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test: Map iteration - basic
TEST_F(NodeIteratorTest_680, MapIterationBasic_680) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Map iteration - key-value pairs accessible
TEST_F(NodeIteratorTest_680, MapIterationKeyValuePairs_680) {
    YAML::Node node;
    node["key1"] = "value1";

    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key1");
    EXPECT_EQ(it->second.as<std::string>(), "value1");
}

// Test: Empty sequence - begin equals end
TEST_F(NodeIteratorTest_680, EmptySequenceBeginEqualsEnd_680) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Empty map - begin equals end
TEST_F(NodeIteratorTest_680, EmptyMapBeginEqualsEnd_680) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Post-increment returns previous position
TEST_F(NodeIteratorTest_680, PostIncrementReturnsPreviousPosition_680) {
    YAML::Node node;
    node.push_back(100);
    node.push_back(200);

    auto it = node.begin();
    auto prev = it++;
    EXPECT_EQ(prev->as<int>(), 100);
    EXPECT_EQ(it->as<int>(), 200);
}

// Test: Pre-increment returns next position
TEST_F(NodeIteratorTest_680, PreIncrementReturnsNextPosition_680) {
    YAML::Node node;
    node.push_back(100);
    node.push_back(200);

    auto it = node.begin();
    auto& ref = ++it;
    EXPECT_EQ(ref->as<int>(), 200);
    EXPECT_EQ(it->as<int>(), 200);
}

// Test: Inequality operator
TEST_F(NodeIteratorTest_680, InequalityOperator_680) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it = node.begin();
    auto end = node.end();
    EXPECT_TRUE(it != end);
    ++it;
    EXPECT_TRUE(it != end);
    ++it;
    EXPECT_FALSE(it != end);
}

// Test: Dereference operator on sequence
TEST_F(NodeIteratorTest_680, DereferenceOperatorSequence_680) {
    YAML::Node node;
    node.push_back("hello");

    auto it = node.begin();
    YAML::Node val = *it;
    EXPECT_EQ(val.as<std::string>(), "hello");
}

// Test: Dereference operator on map
TEST_F(NodeIteratorTest_680, DereferenceOperatorMap_680) {
    YAML::Node node;
    node["foo"] = "bar";

    auto it = node.begin();
    auto pair = *it;
    EXPECT_EQ(pair.first.as<std::string>(), "foo");
    EXPECT_EQ(pair.second.as<std::string>(), "bar");
}

// Test: Arrow operator on sequence
TEST_F(NodeIteratorTest_680, ArrowOperatorSequence_680) {
    YAML::Node node;
    node.push_back(42);

    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 42);
}

// Test: Arrow operator on map
TEST_F(NodeIteratorTest_680, ArrowOperatorMap_680) {
    YAML::Node node;
    node["x"] = 99;

    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "x");
    EXPECT_EQ(it->second.as<int>(), 99);
}

// Test: Scalar node - begin equals end
TEST_F(NodeIteratorTest_680, ScalarNodeBeginEqualsEnd_680) {
    YAML::Node node("scalar_value");
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Null node - begin equals end
TEST_F(NodeIteratorTest_680, NullNodeBeginEqualsEnd_680) {
    YAML::Node node;
    EXPECT_TRUE(node.begin() == node.end());
}

// Test: Undefined node - begin equals end
TEST_F(NodeIteratorTest_680, UndefinedNodeBeginEqualsEnd_680) {
    YAML::Node node;
    YAML::Node undefined = node["nonexistent"];
    // Accessing a nonexistent key on a non-map may or may not throw,
    // but if we have an undefined node, iterating should work gracefully
    EXPECT_TRUE(undefined.begin() == undefined.end());
}

// Test: Single element sequence
TEST_F(NodeIteratorTest_680, SingleElementSequence_680) {
    YAML::Node node;
    node.push_back("only");

    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Single element map
TEST_F(NodeIteratorTest_680, SingleElementMap_680) {
    YAML::Node node;
    node["single"] = "entry";

    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "single");
    EXPECT_EQ(it->second.as<std::string>(), "entry");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Multiple iterations produce same results
TEST_F(NodeIteratorTest_680, MultipleIterationsConsistent_680) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    std::vector<int> first_pass;
    for (auto it = node.begin(); it != node.end(); ++it) {
        first_pass.push_back(it->as<int>());
    }

    std::vector<int> second_pass;
    for (auto it = node.begin(); it != node.end(); ++it) {
        second_pass.push_back(it->as<int>());
    }

    EXPECT_EQ(first_pass, second_pass);
}

// Test: Const iterator from const node (sequence)
TEST_F(NodeIteratorTest_680, ConstIteratorSequence_680) {
    YAML::Node node;
    node.push_back(5);
    node.push_back(10);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Const iterator from const node (map)
TEST_F(NodeIteratorTest_680, ConstIteratorMap_680) {
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

// Test: Map with removed/undefined entries (if applicable)
TEST_F(NodeIteratorTest_680, MapWithRemovedEntry_680) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    node.remove("b");

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Large sequence iteration
TEST_F(NodeIteratorTest_680, LargeSequenceIteration_680) {
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

// Test: Iterator copy equality
TEST_F(NodeIteratorTest_680, IteratorCopyEquality_680) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);

    auto it1 = node.begin();
    auto it2 = it1;
    EXPECT_TRUE(it1 == it2);
    ++it1;
    EXPECT_TRUE(it1 != it2);
}

// Test: Parsed YAML sequence iteration
TEST_F(NodeIteratorTest_680, ParsedYAMLSequenceIteration_680) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 5);
}

// Test: Parsed YAML map iteration
TEST_F(NodeIteratorTest_680, ParsedYAMLMapIteration_680) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Nested node iteration - only top-level elements
TEST_F(NodeIteratorTest_680, NestedNodeIterationTopLevel_680) {
    YAML::Node node = YAML::Load("[1, [2, 3], 4]");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Map iterator skips undefined entries
TEST_F(NodeIteratorTest_680, MapIteratorSkipsUndefinedEntries_680) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    
    // Remove an entry and verify iteration skips it
    node.remove("a");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        EXPECT_EQ(it->first.as<std::string>(), "b");
        count++;
    }
    EXPECT_EQ(count, 1);
}

} // namespace
