#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/iterator.h"

// Test basic iteration over a YAML sequence
TEST(IteratorTest_198, SequenceIterationBasic_198) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over an empty sequence
TEST(IteratorTest_198, EmptySequenceIteration_198) {
    YAML::Node node = YAML::Load("[]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test iteration over a YAML map
TEST(IteratorTest_198, MapIterationBasic_198) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over an empty map
TEST(IteratorTest_198, EmptyMapIteration_198) {
    YAML::Node node = YAML::Load("{}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test iterator dereference for sequence
TEST(IteratorTest_198, SequenceIteratorDereference_198) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 10);
    ++it;
    EXPECT_EQ(it->as<int>(), 20);
    ++it;
    EXPECT_EQ(it->as<int>(), 30);
}

// Test iterator dereference for map (key-value pairs)
TEST(IteratorTest_198, MapIteratorDereference_198) {
    YAML::Node node = YAML::Load("{key1: val1}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "key1");
    EXPECT_EQ(it->second.as<std::string>(), "val1");
}

// Test iterator equality
TEST(IteratorTest_198, IteratorEquality_198) {
    YAML::Node node = YAML::Load("[1]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test iterator inequality
TEST(IteratorTest_198, IteratorInequality_198) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it1 = node.begin();
    auto it2 = node.end();
    EXPECT_TRUE(it1 != it2);
}

// Test pre-increment operator
TEST(IteratorTest_198, PreIncrementOperator_198) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto it = node.begin();
    auto& ref = ++it;
    EXPECT_EQ(it->as<int>(), 2);
    // Pre-increment should return reference to same iterator
    EXPECT_TRUE(ref == it);
}

// Test post-increment operator
TEST(IteratorTest_198, PostIncrementOperator_198) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 1);
    EXPECT_EQ(it->as<int>(), 2);
}

// Test begin equals end for empty sequence
TEST(IteratorTest_198, BeginEqualsEndForEmptySequence_198) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.begin() == node.end());
}

// Test begin equals end for empty map
TEST(IteratorTest_198, BeginEqualsEndForEmptyMap_198) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.begin() == node.end());
}

// Test const iteration over sequence
TEST(IteratorTest_198, ConstSequenceIteration_198) {
    const YAML::Node node = YAML::Load("[a, b, c]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test const iteration over map
TEST(IteratorTest_198, ConstMapIteration_198) {
    const YAML::Node node = YAML::Load("{x: 1, y: 2}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test iterating to end and comparing
TEST(IteratorTest_198, IterateToEnd_198) {
    YAML::Node node = YAML::Load("[42]");
    auto it = node.begin();
    EXPECT_TRUE(it != node.end());
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test range-based for loop with sequence
TEST(IteratorTest_198, RangeBasedForSequence_198) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    std::vector<int> values;
    for (const auto& elem : node) {
        values.push_back(elem.as<int>());
    }
    EXPECT_EQ(values.size(), 5u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[4], 5);
}

// Test range-based for loop with map
TEST(IteratorTest_198, RangeBasedForMap_198) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    std::map<std::string, int> result;
    for (const auto& kv : node) {
        result[kv.first.as<std::string>()] = kv.second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// Test single element sequence
TEST(IteratorTest_198, SingleElementSequence_198) {
    YAML::Node node = YAML::Load("[only]");
    auto it = node.begin();
    EXPECT_EQ(it->as<std::string>(), "only");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test single element map
TEST(IteratorTest_198, SingleElementMap_198) {
    YAML::Node node = YAML::Load("{solo: value}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "solo");
    EXPECT_EQ(it->second.as<std::string>(), "value");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test iterator with nested structures
TEST(IteratorTest_198, NestedStructureIteration_198) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    auto it = node.begin();
    EXPECT_TRUE(it->IsSequence());
    EXPECT_EQ((*it)[0].as<int>(), 1);
    ++it;
    EXPECT_TRUE(it->IsSequence());
    EXPECT_EQ((*it)[0].as<int>(), 3);
}

// Test that multiple independent iterations work correctly
TEST(IteratorTest_198, MultipleIndependentIterations_198) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    
    auto it1 = node.begin();
    auto it2 = node.begin();
    
    ++it1;
    EXPECT_EQ(it1->as<int>(), 20);
    EXPECT_EQ(it2->as<int>(), 10);
}

// Test large sequence iteration
TEST(IteratorTest_198, LargeSequenceIteration_198) {
    std::string yaml = "[";
    for (int i = 0; i < 100; i++) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    
    YAML::Node node = YAML::Load(yaml);
    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 100);
    EXPECT_EQ(sum, 4950); // sum of 0..99
}
