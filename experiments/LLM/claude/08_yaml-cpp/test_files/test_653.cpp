#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class NodeDataRemoveTest_653 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test removing a key from a map node returns true and the key is no longer present
TEST_F(NodeDataRemoveTest_653, RemoveExistingKeyFromMap_653) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    node["key3"] = "value3";

    ASSERT_TRUE(node.IsMap());
    ASSERT_EQ(node.size(), 3u);

    bool result = node.remove("key2");
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node["key1"].IsDefined());
    EXPECT_FALSE(node["key2"].IsDefined());
    EXPECT_TRUE(node["key3"].IsDefined());
}

// Test removing a non-existing key from a map returns false
TEST_F(NodeDataRemoveTest_653, RemoveNonExistingKeyFromMap_653) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";

    ASSERT_TRUE(node.IsMap());
    bool result = node.remove("nonexistent");
    EXPECT_FALSE(result);
    EXPECT_EQ(node.size(), 2u);
}

// Test removing from a sequence node returns false (not a map)
TEST_F(NodeDataRemoveTest_653, RemoveFromSequenceReturnsFalse_653) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");

    ASSERT_TRUE(node.IsSequence());
    bool result = node.remove("item1");
    EXPECT_FALSE(result);
}

// Test removing from a scalar node returns false (not a map)
TEST_F(NodeDataRemoveTest_653, RemoveFromScalarReturnsFalse_653) {
    YAML::Node node = YAML::Node("scalar_value");

    ASSERT_TRUE(node.IsScalar());
    bool result = node.remove("something");
    EXPECT_FALSE(result);
}

// Test removing from a null/undefined node returns false (not a map)
TEST_F(NodeDataRemoveTest_653, RemoveFromNullNodeReturnsFalse_653) {
    YAML::Node node;

    ASSERT_TRUE(node.IsNull());
    bool result = node.remove("something");
    EXPECT_FALSE(result);
}

// Test removing the only key in a map
TEST_F(NodeDataRemoveTest_653, RemoveOnlyKeyFromMap_653) {
    YAML::Node node;
    node["onlykey"] = "onlyvalue";

    ASSERT_EQ(node.size(), 1u);
    bool result = node.remove("onlykey");
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 0u);
}

// Test removing from an empty map returns false
TEST_F(NodeDataRemoveTest_653, RemoveFromEmptyMap_653) {
    YAML::Node node = YAML::Load("{}");

    ASSERT_TRUE(node.IsMap());
    ASSERT_EQ(node.size(), 0u);
    bool result = node.remove("anykey");
    EXPECT_FALSE(result);
}

// Test removing a key twice - second removal should return false
TEST_F(NodeDataRemoveTest_653, RemoveSameKeyTwice_653) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";

    bool firstRemove = node.remove("key1");
    EXPECT_TRUE(firstRemove);

    bool secondRemove = node.remove("key1");
    EXPECT_FALSE(secondRemove);
    EXPECT_EQ(node.size(), 1u);
}

// Test removing with integer key from a map
TEST_F(NodeDataRemoveTest_653, RemoveIntegerKeyFromMap_653) {
    YAML::Node node;
    node[1] = "value1";
    node[2] = "value2";
    node[3] = "value3";

    ASSERT_TRUE(node.IsMap());
    bool result = node.remove(2);
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 2u);
}

// Test removing all keys one by one
TEST_F(NodeDataRemoveTest_653, RemoveAllKeysOneByOne_653) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;

    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_TRUE(node.remove("c"));
    EXPECT_EQ(node.size(), 0u);
}
