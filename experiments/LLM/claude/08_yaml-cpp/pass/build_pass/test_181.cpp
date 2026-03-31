#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"

// Test ID: 181

// Test basic iteration over a YAML sequence node
TEST(NodeIteratorTest_181, SequenceIterationBasic_181) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over an empty sequence
TEST(NodeIteratorTest_181, EmptySequenceIteration_181) {
    YAML::Node node = YAML::Load("[]");
    ASSERT_TRUE(node.IsSequence());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test basic iteration over a YAML map node
TEST(NodeIteratorTest_181, MapIterationBasic_181) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    ASSERT_TRUE(node.IsMap());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over an empty map
TEST(NodeIteratorTest_181, EmptyMapIteration_181) {
    YAML::Node node = YAML::Load("{}");
    ASSERT_TRUE(node.IsMap());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test iterator equality (begin == end for empty container)
TEST(NodeIteratorTest_181, BeginEqualsEndForEmptySequence_181) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.begin() == node.end());
}

// Test iterator inequality (begin != end for non-empty container)
TEST(NodeIteratorTest_181, BeginNotEqualsEndForNonEmptySequence_181) {
    YAML::Node node = YAML::Load("[1]");
    EXPECT_TRUE(node.begin() != node.end());
}

// Test dereferencing sequence iterator
TEST(NodeIteratorTest_181, DereferenceSequenceIterator_181) {
    YAML::Node node = YAML::Load("[42]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 42);
}

// Test dereferencing map iterator to access key and value
TEST(NodeIteratorTest_181, DereferenceMapIterator_181) {
    YAML::Node node = YAML::Load("{key: value}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");
}

// Test pre-increment of iterator
TEST(NodeIteratorTest_181, PreIncrementIterator_181) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 10);
    ++it;
    EXPECT_EQ(it->as<int>(), 20);
    ++it;
    EXPECT_EQ(it->as<int>(), 30);
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test post-increment of iterator
TEST(NodeIteratorTest_181, PostIncrementIterator_181) {
    YAML::Node node = YAML::Load("[10, 20]");
    auto it = node.begin();
    auto prev = it++;
    EXPECT_EQ(prev->as<int>(), 10);
    EXPECT_EQ(it->as<int>(), 20);
}

// Test const iteration over sequence
TEST(NodeIteratorTest_181, ConstSequenceIteration_181) {
    const YAML::Node node = YAML::Load("[1, 2, 3]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test const iteration over map
TEST(NodeIteratorTest_181, ConstMapIteration_181) {
    const YAML::Node node = YAML::Load("{x: 1, y: 2}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test sequence iterator values are correct
TEST(NodeIteratorTest_181, SequenceIteratorValuesCorrect_181) {
    YAML::Node node = YAML::Load("[alpha, beta, gamma]");
    std::vector<std::string> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<std::string>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "alpha");
    EXPECT_EQ(values[1], "beta");
    EXPECT_EQ(values[2], "gamma");
}

// Test map iterator keys and values
TEST(NodeIteratorTest_181, MapIteratorKeysAndValues_181) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    std::map<std::string, std::string> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<std::string>();
    }
    EXPECT_EQ(result["name"], "John");
    EXPECT_EQ(result["age"], "30");
}

// Test single element sequence iteration
TEST(NodeIteratorTest_181, SingleElementSequence_181) {
    YAML::Node node = YAML::Load("[only]");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test single element map iteration
TEST(NodeIteratorTest_181, SingleElementMap_181) {
    YAML::Node node = YAML::Load("{solo: value}");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "solo");
    EXPECT_EQ(it->second.as<std::string>(), "value");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test that scalar node begin equals end
TEST(NodeIteratorTest_181, ScalarNodeBeginEqualsEnd_181) {
    YAML::Node node = YAML::Load("scalar_value");
    ASSERT_TRUE(node.IsScalar());
    EXPECT_EQ(node.begin(), node.end());
}

// Test that null node begin equals end
TEST(NodeIteratorTest_181, NullNodeBeginEqualsEnd_181) {
    YAML::Node node = YAML::Load("~");
    ASSERT_TRUE(node.IsNull());
    EXPECT_EQ(node.begin(), node.end());
}

// Test range-based for loop with sequence
TEST(NodeIteratorTest_181, RangeBasedForSequence_181) {
    YAML::Node node = YAML::Load("[a, b, c]");
    int count = 0;
    for (const auto& item : node) {
        (void)item;
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test range-based for loop with map
TEST(NodeIteratorTest_181, RangeBasedForMap_181) {
    YAML::Node node = YAML::Load("{k1: v1, k2: v2}");
    int count = 0;
    for (const auto& pair : node) {
        (void)pair;
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test iterator copy semantics
TEST(NodeIteratorTest_181, IteratorCopy_181) {
    YAML::Node node = YAML::Load("[100, 200, 300]");
    auto it1 = node.begin();
    auto it2 = it1;
    EXPECT_EQ(it1, it2);
    EXPECT_EQ(it1->as<int>(), it2->as<int>());
    ++it1;
    EXPECT_NE(it1, it2);
}

// Test nested structure iteration
TEST(NodeIteratorTest_181, NestedStructureIteration_181) {
    YAML::Node node = YAML::Load("{outer: {inner: val}}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "outer");
    ASSERT_TRUE(it->second.IsMap());
    
    auto inner_it = it->second.begin();
    EXPECT_EQ(inner_it->first.as<std::string>(), "inner");
    EXPECT_EQ(inner_it->second.as<std::string>(), "val");
}
