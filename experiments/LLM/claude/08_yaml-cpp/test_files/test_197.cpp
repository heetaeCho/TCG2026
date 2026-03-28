#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/iterator.h"
#include <string>
#include <vector>

class IteratorProxyTest_197 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that iterating over a YAML sequence works correctly
TEST_F(IteratorProxyTest_197, SequenceIteratorDereference_197) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        EXPECT_TRUE(it->IsDefined());
    }
    EXPECT_EQ(3, count);
}

// Test that iterating over a YAML map works correctly
TEST_F(IteratorProxyTest_197, MapIteratorDereference_197) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    ASSERT_TRUE(node.IsMap());
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        // For maps, the iterator yields key-value pairs
        EXPECT_TRUE(it->first.IsDefined());
        EXPECT_TRUE(it->second.IsDefined());
    }
    EXPECT_EQ(2, count);
}

// Test arrow operator on sequence iterator
TEST_F(IteratorProxyTest_197, SequenceIteratorArrowOperator_197) {
    YAML::Node node = YAML::Load("[hello, world]");
    ASSERT_TRUE(node.IsSequence());
    
    auto it = node.begin();
    // Using arrow operator through proxy
    EXPECT_TRUE(it->IsScalar());
    EXPECT_EQ("hello", it->as<std::string>());
}

// Test arrow operator on map iterator accessing first and second
TEST_F(IteratorProxyTest_197, MapIteratorArrowOperatorFirstSecond_197) {
    YAML::Node node = YAML::Load("{key: value}");
    ASSERT_TRUE(node.IsMap());
    
    auto it = node.begin();
    EXPECT_EQ("key", it->first.as<std::string>());
    EXPECT_EQ("value", it->second.as<std::string>());
}

// Test empty sequence iteration (boundary)
TEST_F(IteratorProxyTest_197, EmptySequenceIteration_197) {
    YAML::Node node = YAML::Load("[]");
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.begin(), node.end());
}

// Test empty map iteration (boundary)
TEST_F(IteratorProxyTest_197, EmptyMapIteration_197) {
    YAML::Node node = YAML::Load("{}");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node.begin(), node.end());
}

// Test single element sequence
TEST_F(IteratorProxyTest_197, SingleElementSequence_197) {
    YAML::Node node = YAML::Load("[42]");
    ASSERT_TRUE(node.IsSequence());
    
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(42, it->as<int>());
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test that proxy works with post-increment
TEST_F(IteratorProxyTest_197, PostIncrementIterator_197) {
    YAML::Node node = YAML::Load("[a, b, c]");
    auto it = node.begin();
    
    EXPECT_EQ("a", it->as<std::string>());
    it++;
    EXPECT_EQ("b", it->as<std::string>());
    it++;
    EXPECT_EQ("c", it->as<std::string>());
}

// Test nested structure access through iterator proxy
TEST_F(IteratorProxyTest_197, NestedMapIteratorProxy_197) {
    YAML::Node node = YAML::Load("{outer: {inner: 42}}");
    auto it = node.begin();
    
    EXPECT_EQ("outer", it->first.as<std::string>());
    EXPECT_TRUE(it->second.IsMap());
    EXPECT_EQ(42, it->second["inner"].as<int>());
}
