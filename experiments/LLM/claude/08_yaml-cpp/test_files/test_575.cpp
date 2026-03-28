#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class NodeRemoveTest_575 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test removing an existing key from a map node
TEST_F(NodeRemoveTest_575, RemoveExistingKeyFromMap_575) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    node["key3"] = "value3";

    YAML::Node key("key2");
    bool result = node.remove(key);

    EXPECT_TRUE(result);
    EXPECT_FALSE(node["key2"].IsDefined());
    EXPECT_EQ(node.size(), 2u);
}

// Test removing a non-existing key from a map node
TEST_F(NodeRemoveTest_575, RemoveNonExistingKeyFromMap_575) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";

    YAML::Node key("key3");
    bool result = node.remove(key);

    EXPECT_FALSE(result);
    EXPECT_EQ(node.size(), 2u);
}

// Test removing a key using string template version
TEST_F(NodeRemoveTest_575, RemoveKeyByStringTemplate_575) {
    YAML::Node node;
    node["apple"] = 1;
    node["banana"] = 2;
    node["cherry"] = 3;

    bool result = node.remove(std::string("banana"));

    EXPECT_TRUE(result);
    EXPECT_FALSE(node["banana"].IsDefined());
    EXPECT_EQ(node.size(), 2u);
}

// Test removing a key using const char* template version
TEST_F(NodeRemoveTest_575, RemoveKeyByConstChar_575) {
    YAML::Node node;
    node["foo"] = "bar";
    node["baz"] = "qux";

    bool result = node.remove("foo");

    EXPECT_TRUE(result);
    EXPECT_FALSE(node["foo"].IsDefined());
}

// Test removing from an empty map
TEST_F(NodeRemoveTest_575, RemoveFromEmptyMap_575) {
    YAML::Node node(YAML::NodeType::Map);

    YAML::Node key("nonexistent");
    bool result = node.remove(key);

    EXPECT_FALSE(result);
    EXPECT_EQ(node.size(), 0u);
}

// Test removing with integer key
TEST_F(NodeRemoveTest_575, RemoveIntegerKey_575) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    node[3] = "three";

    bool result = node.remove(2);

    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 2u);
}

// Test removing the only key in a map
TEST_F(NodeRemoveTest_575, RemoveOnlyKeyInMap_575) {
    YAML::Node node;
    node["only"] = "value";

    bool result = node.remove("only");

    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 0u);
}

// Test removing same key twice
TEST_F(NodeRemoveTest_575, RemoveSameKeyTwice_575) {
    YAML::Node node;
    node["key"] = "value";

    bool result1 = node.remove("key");
    EXPECT_TRUE(result1);

    bool result2 = node.remove("key");
    EXPECT_FALSE(result2);
}

// Test that remaining keys are still accessible after removal
TEST_F(NodeRemoveTest_575, RemainingKeysAccessibleAfterRemoval_575) {
    YAML::Node node;
    node["a"] = "alpha";
    node["b"] = "beta";
    node["c"] = "gamma";

    node.remove("b");

    EXPECT_EQ(node["a"].as<std::string>(), "alpha");
    EXPECT_EQ(node["c"].as<std::string>(), "gamma");
}

// Test removing with a Node key that is itself a map
TEST_F(NodeRemoveTest_575, RemoveWithComplexNodeKey_575) {
    YAML::Node node;
    YAML::Node key;
    key["nested"] = "key";
    node[key] = "value";

    bool result = node.remove(key);
    EXPECT_TRUE(result);
}

// Test removing from sequence-like scenario (index-based removal)
TEST_F(NodeRemoveTest_575, RemoveFromSequenceByIndex_575) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");

    // Removing by integer key from a sequence
    bool result = node.remove(1);
    EXPECT_TRUE(result);
}

// Test remove preserves map type
TEST_F(NodeRemoveTest_575, RemovePreservesMapType_575) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;

    node.remove("x");

    EXPECT_TRUE(node.IsMap());
}

// Test multiple removes until map is empty
TEST_F(NodeRemoveTest_575, MultipleRemovesUntilEmpty_575) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;

    EXPECT_TRUE(node.remove("a"));
    EXPECT_TRUE(node.remove("b"));
    EXPECT_TRUE(node.remove("c"));
    EXPECT_EQ(node.size(), 0u);
}

// Test remove with Node key referencing same node value
TEST_F(NodeRemoveTest_575, RemoveUsingNodeObjectAsKey_575) {
    YAML::Node map;
    map["hello"] = "world";

    YAML::Node keyNode("hello");
    bool result = map.remove(keyNode);

    EXPECT_TRUE(result);
    EXPECT_FALSE(map["hello"].IsDefined());
}

// Test that adding a key back after removal works
TEST_F(NodeRemoveTest_575, AddKeyBackAfterRemoval_575) {
    YAML::Node node;
    node["key"] = "value1";

    node.remove("key");
    EXPECT_FALSE(node["key"].IsDefined());

    node["key"] = "value2";
    EXPECT_TRUE(node["key"].IsDefined());
    EXPECT_EQ(node["key"].as<std::string>(), "value2");
}

// Test remove with boolean key
TEST_F(NodeRemoveTest_575, RemoveBooleanKey_575) {
    YAML::Node node;
    node[true] = "yes";
    node[false] = "no";

    bool result = node.remove(true);
    EXPECT_TRUE(result);
}

// Test remove does not affect unrelated entries
TEST_F(NodeRemoveTest_575, RemoveDoesNotAffectUnrelatedEntries_575) {
    YAML::Node node;
    node["stay1"] = "val1";
    node["remove_me"] = "val2";
    node["stay2"] = "val3";

    node.remove("remove_me");

    EXPECT_EQ(node["stay1"].as<std::string>(), "val1");
    EXPECT_EQ(node["stay2"].as<std::string>(), "val3");
    EXPECT_EQ(node.size(), 2u);
}

// Test remove on a loaded YAML map
TEST_F(NodeRemoveTest_575, RemoveFromParsedYAML_575) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");

    bool result = node.remove("b");
    EXPECT_TRUE(result);
    EXPECT_FALSE(node["b"].IsDefined());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

// Test remove non-existing key from parsed YAML
TEST_F(NodeRemoveTest_575, RemoveNonExistingFromParsedYAML_575) {
    YAML::Node node = YAML::Load("{x: 10, y: 20}");

    bool result = node.remove("z");
    EXPECT_FALSE(result);
    EXPECT_EQ(node.size(), 2u);
}
