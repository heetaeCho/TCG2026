#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// Test fixture for Node tests
class NodeTest_573 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(NodeTest_573, DefaultConstructor_CreatesNullNode_573) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_573, ConstructWithScalarType_573) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_573, ConstructWithSequenceType_573) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_573, ConstructWithMapType_573) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST_F(NodeTest_573, ConstructWithStringValue_573) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_573, ConstructWithIntValue_573) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_573, CopyConstructor_573) {
    YAML::Node original;
    original = "test";
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// ==================== Type Check Tests ====================

TEST_F(NodeTest_573, IsNull_DefaultNode_573) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_573, IsScalar_ScalarNode_573) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_573, IsSequence_SequenceNode_573) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_573, IsMap_MapNode_573) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

// ==================== Bool Conversion Tests ====================

TEST_F(NodeTest_573, BoolOperator_NullNode_573) {
    YAML::Node node;
    // Null nodes are still valid, but not "defined" in the truthy sense
    // operator bool() should return true for a valid node
    // (even null nodes are valid)
}

TEST_F(NodeTest_573, BoolOperator_ScalarNode_573) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

// ==================== Scalar Tests ====================

TEST_F(NodeTest_573, Scalar_ReturnsCorrectValue_573) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.Scalar(), "test_value");
}

TEST_F(NodeTest_573, AsString_573) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(NodeTest_573, AsInt_573) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST_F(NodeTest_573, AsDouble_573) {
    YAML::Node node(3.14);
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(NodeTest_573, AsBool_True_573) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_573, AsBool_False_573) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_573, AsWithFallback_ValidConversion_573) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(99), 42);
}

TEST_F(NodeTest_573, AsWithFallback_InvalidConversion_573) {
    YAML::Node node;
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

// ==================== Assignment Tests ====================

TEST_F(NodeTest_573, AssignString_573) {
    YAML::Node node;
    node = "assigned_value";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned_value");
}

TEST_F(NodeTest_573, AssignInt_573) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(node.as<int>(), 100);
}

TEST_F(NodeTest_573, AssignNode_573) {
    YAML::Node source("source_value");
    YAML::Node target;
    target = source;
    EXPECT_EQ(target.Scalar(), "source_value");
    EXPECT_TRUE(target.is(source));
}

TEST_F(NodeTest_573, ResetNode_573) {
    YAML::Node node("original");
    YAML::Node other("other");
    node.reset(other);
    EXPECT_TRUE(node.is(other));
    EXPECT_EQ(node.Scalar(), "other");
}

// ==================== Sequence Tests ====================

TEST_F(NodeTest_573, PushBack_CreatesSequence_573) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_573, PushBack_IntValues_573) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_573, PushBack_NodeValues_573) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "child_value");
}

TEST_F(NodeTest_573, SequenceAccess_ByIndex_573) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

TEST_F(NodeTest_573, SequenceSize_Empty_573) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_573, SequenceIteration_573) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// ==================== Map Tests ====================

TEST_F(NodeTest_573, MapAccess_StringKey_573) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST_F(NodeTest_573, MapAccess_IntKey_573) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST_F(NodeTest_573, MapSize_573) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_573, MapIteration_573) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        std::string key = it->first.as<std::string>();
        int value = it->second.as<int>();
        if (key == "x") {
            EXPECT_EQ(value, 10);
        } else if (key == "y") {
            EXPECT_EQ(value, 20);
        }
    }
    EXPECT_EQ(count, 2);
}

TEST_F(NodeTest_573, MapAccess_NodeKey_573) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

// ==================== Remove Tests ====================

TEST_F(NodeTest_573, Remove_StringKey_FromMap_573) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node.size(), 2u);

    bool result = node.remove("key1");
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["key1"].IsDefined());
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST_F(NodeTest_573, Remove_NonExistentKey_ReturnsFalse_573) {
    YAML::Node node;
    node["key1"] = "value1";

    bool result = node.remove("nonexistent");
    EXPECT_FALSE(result);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_573, Remove_IntKey_FromMap_573) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    node[3] = "three";

    bool result = node.remove(2);
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_573, Remove_NodeKey_FromMap_573) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    node["other"] = "othervalue";

    bool result = node.remove(key);
    EXPECT_TRUE(result);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_573, Remove_AllKeys_FromMap_573) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;

    EXPECT_TRUE(node.remove("a"));
    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_573, Remove_SameKeyTwice_573) {
    YAML::Node node;
    node["key"] = "value";

    EXPECT_TRUE(node.remove("key"));
    EXPECT_FALSE(node.remove("key"));
}

// ==================== Tag Tests ====================

TEST_F(NodeTest_573, SetAndGetTag_573) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST_F(NodeTest_573, DefaultTag_Empty_573) {
    YAML::Node node("value");
    EXPECT_EQ(node.Tag(), "?");
}

// ==================== Style Tests ====================

TEST_F(NodeTest_573, SetAndGetStyle_Block_573) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeTest_573, SetAndGetStyle_Flow_573) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// ==================== IsDefined Tests ====================

TEST_F(NodeTest_573, IsDefined_ScalarNode_573) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_573, IsDefined_NullNode_573) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_573, IsDefined_UndefinedMapAccess_573) {
    YAML::Node node;
    node["exists"] = "yes";
    // Accessing a const node with non-existent key should return undefined
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["nonexistent"].IsDefined());
}

// ==================== Identity Tests ====================

TEST_F(NodeTest_573, Is_SameNode_573) {
    YAML::Node node("value");
    YAML::Node alias = node;
    EXPECT_TRUE(node.is(alias));
}

TEST_F(NodeTest_573, Is_DifferentNodes_573) {
    YAML::Node node1("value");
    YAML::Node node2("value");
    EXPECT_FALSE(node1.is(node2));
}

// ==================== Force Insert Tests ====================

TEST_F(NodeTest_573, ForceInsert_573) {
    YAML::Node node;
    node.force_insert("key1", "value1");
    node.force_insert("key2", "value2");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST_F(NodeTest_573, ForceInsert_DuplicateKeys_573) {
    YAML::Node node;
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert should add both entries (unlike operator[]=)
    EXPECT_EQ(node.size(), 2u);
}

// ==================== YAML Parsing and Remove Tests ====================

TEST_F(NodeTest_573, ParseAndRemoveFromMap_573) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);

    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_FALSE(node["b"].IsDefined());
    EXPECT_EQ(node["c"].as<int>(), 3);
}

TEST_F(NodeTest_573, ParseSequence_573) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_573, ParseScalar_573) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// ==================== Null / Empty Size Tests ====================

TEST_F(NodeTest_573, Size_NullNode_573) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_573, Size_ScalarNode_573) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// ==================== Complex Node Tests ====================

TEST_F(NodeTest_573, NestedMap_573) {
    YAML::Node node;
    node["outer"]["inner"] = "deep_value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "deep_value");
}

TEST_F(NodeTest_573, SequenceOfMaps_573) {
    YAML::Node node;
    YAML::Node item1;
    item1["name"] = "Alice";
    item1["age"] = 30;
    YAML::Node item2;
    item2["name"] = "Bob";
    item2["age"] = 25;

    node.push_back(item1);
    node.push_back(item2);

    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[1]["age"].as<int>(), 25);
}

TEST_F(NodeTest_573, Remove_FromNestedMap_573) {
    YAML::Node node;
    node["parent"]["child1"] = "val1";
    node["parent"]["child2"] = "val2";

    EXPECT_TRUE(node["parent"].remove("child1"));
    EXPECT_EQ(node["parent"].size(), 1u);
    EXPECT_FALSE(node["parent"]["child1"].IsDefined());
    EXPECT_EQ(node["parent"]["child2"].as<std::string>(), "val2");
}

// ==================== Edge Cases ====================

TEST_F(NodeTest_573, EmptyStringKey_573) {
    YAML::Node node;
    node[""] = "empty_key_value";
    EXPECT_EQ(node[""].as<std::string>(), "empty_key_value");
}

TEST_F(NodeTest_573, Remove_EmptyStringKey_573) {
    YAML::Node node;
    node[""] = "value";
    EXPECT_TRUE(node.remove(""));
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_573, AssignNewValueAfterRemove_573) {
    YAML::Node node;
    node["key"] = "old_value";
    node.remove("key");
    node["key"] = "new_value";
    EXPECT_EQ(node["key"].as<std::string>(), "new_value");
}

TEST_F(NodeTest_573, OverwriteMapValue_573) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_573, ConstNodeAccess_573) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_573, Mark_DefaultNode_573) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    // Default constructed node should have null mark
    EXPECT_EQ(mark.line, -1);
    EXPECT_EQ(mark.column, -1);
}

TEST_F(NodeTest_573, LargeMap_Remove_573) {
    YAML::Node node;
    for (int i = 0; i < 100; i++) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), 100u);

    for (int i = 0; i < 50; i++) {
        EXPECT_TRUE(node.remove(std::to_string(i)));
    }
    EXPECT_EQ(node.size(), 50u);

    for (int i = 50; i < 100; i++) {
        EXPECT_EQ(node[std::to_string(i)].as<int>(), i);
    }
}

TEST_F(NodeTest_573, Remove_FromSequenceStyleMap_573) {
    YAML::Node node = YAML::Load("{foo: bar, baz: qux, hello: world}");
    EXPECT_EQ(node.size(), 3u);
    EXPECT_TRUE(node.remove("baz"));
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["foo"].as<std::string>(), "bar");
    EXPECT_EQ(node["hello"].as<std::string>(), "world");
}
