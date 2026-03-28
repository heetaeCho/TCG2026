#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// Test fixture for Node tests
class NodeTest_572 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Construction Tests ====================

TEST_F(NodeTest_572, DefaultConstructedNodeIsNull_572) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_572, DefaultConstructedNodeIsDefined_572) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_572, DefaultConstructedNodeBoolConversion_572) {
    YAML::Node node;
    // A null node should still be "valid" but null
    EXPECT_TRUE(node.IsDefined());
}

// ==================== Type Construction Tests ====================

TEST_F(NodeTest_572, ConstructWithScalarType_572) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_572, ConstructWithSequenceType_572) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_572, ConstructWithMapType_572) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST_F(NodeTest_572, ConstructWithNullType_572) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_572, ConstructWithUndefinedType_572) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// ==================== Value Construction Tests ====================

TEST_F(NodeTest_572, ConstructWithStringValue_572) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_572, ConstructWithIntValue_572) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_572, ConstructWithDoubleValue_572) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(NodeTest_572, ConstructWithBoolValue_572) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// ==================== Copy Construction Tests ====================

TEST_F(NodeTest_572, CopyConstruction_572) {
    YAML::Node original;
    original = "test_value";
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test_value");
}

TEST_F(NodeTest_572, CopyConstructionSharesData_572) {
    YAML::Node original;
    original = "initial";
    YAML::Node copy(original);
    EXPECT_TRUE(copy.is(original));
}

// ==================== Assignment Tests ====================

TEST_F(NodeTest_572, AssignStringValue_572) {
    YAML::Node node;
    node = "hello world";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(NodeTest_572, AssignIntValue_572) {
    YAML::Node node;
    node = 100;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 100);
}

TEST_F(NodeTest_572, AssignNodeValue_572) {
    YAML::Node node1;
    node1 = "first";
    YAML::Node node2;
    node2 = node1;
    EXPECT_EQ(node2.as<std::string>(), "first");
}

// ==================== Scalar Tests ====================

TEST_F(NodeTest_572, ScalarReturnsValue_572) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST_F(NodeTest_572, EmptyScalar_572) {
    YAML::Node node("");
    EXPECT_EQ(node.Scalar(), "");
}

// ==================== As Tests ====================

TEST_F(NodeTest_572, AsStringFromScalar_572) {
    YAML::Node node("value");
    EXPECT_EQ(node.as<std::string>(), "value");
}

TEST_F(NodeTest_572, AsIntFromScalar_572) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_572, AsWithFallback_572) {
    YAML::Node node;
    // Undefined node should use fallback
    YAML::Node undefined(YAML::NodeType::Undefined);
    int result = undefined.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST_F(NodeTest_572, AsWithFallbackWhenDefined_572) {
    YAML::Node node(42);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 42);
}

TEST_F(NodeTest_572, AsBoolFromTrue_572) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_572, AsBoolFromFalse_572) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

// ==================== Sequence Tests ====================

TEST_F(NodeTest_572, PushBackCreatesSequence_572) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_572, SequenceAccessByIndex_572) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST_F(NodeTest_572, SequenceSize_572) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_572, EmptySequenceSize_572) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_572, PushBackNode_572) {
    YAML::Node seq;
    YAML::Node item("item_value");
    seq.push_back(item);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq[0].as<std::string>(), "item_value");
}

// ==================== Map Tests ====================

TEST_F(NodeTest_572, MapAccessByStringKey_572) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST_F(NodeTest_572, MapSize_572) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_572, MapAccessByIntKey_572) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST_F(NodeTest_572, ConstMapAccessNonExistentKey_572) {
    YAML::Node node;
    node["exists"] = "yes";
    const YAML::Node& constNode = node;
    YAML::Node result = constNode["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST_F(NodeTest_572, ConstMapAccessExistingKey_572) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    YAML::Node result = constNode["key"];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "value");
}

TEST_F(NodeTest_572, MapAccessByNodeKey_572) {
    YAML::Node node;
    YAML::Node key("my_key");
    node[key] = "my_value";
    EXPECT_EQ(node[key].as<std::string>(), "my_value");
}

// ==================== Remove Tests ====================

TEST_F(NodeTest_572, RemoveExistingKey_572) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_572, RemoveNonExistentKey_572) {
    YAML::Node node;
    node["key1"] = "value1";
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_572, RemoveByNodeKey_572) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Node key("key");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
}

// ==================== Tag Tests ====================

TEST_F(NodeTest_572, SetAndGetTag_572) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST_F(NodeTest_572, DefaultTag_572) {
    YAML::Node node("value");
    // Default tag should be "?" or empty
    std::string tag = node.Tag();
    EXPECT_TRUE(tag == "?" || tag.empty());
}

// ==================== Style Tests ====================

TEST_F(NodeTest_572, SetAndGetStyle_572) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_572, SetBlockStyle_572) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ==================== Iterator Tests ====================

TEST_F(NodeTest_572, SequenceIteration_572) {
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

TEST_F(NodeTest_572, MapIteration_572) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST_F(NodeTest_572, EmptySequenceIteration_572) {
    YAML::Node node(YAML::NodeType::Sequence);
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// ==================== Is Tests ====================

TEST_F(NodeTest_572, IsReturnsTrueForSameNode_572) {
    YAML::Node node("value");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST_F(NodeTest_572, IsReturnsFalseForDifferentNodes_572) {
    YAML::Node node1("value1");
    YAML::Node node2("value2");
    EXPECT_FALSE(node1.is(node2));
}

// ==================== Reset Tests ====================

TEST_F(NodeTest_572, ResetToAnotherNode_572) {
    YAML::Node node1("original");
    YAML::Node node2("replacement");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.as<std::string>(), "replacement");
}

// ==================== Bool Operator Tests ====================

TEST_F(NodeTest_572, BoolOperatorForDefinedNode_572) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST_F(NodeTest_572, NotOperatorForDefinedNode_572) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_572, BoolOperatorForUndefinedNode_572) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(static_cast<bool>(node));
}

TEST_F(NodeTest_572, NotOperatorForUndefinedNode_572) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_TRUE(!node);
}

// ==================== Null Check Tests ====================

TEST_F(NodeTest_572, IsNullForNullNode_572) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_572, IsNullForScalarNode_572) {
    YAML::Node node("value");
    EXPECT_FALSE(node.IsNull());
}

TEST_F(NodeTest_572, IsScalarForScalarNode_572) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsScalar());
}

TEST_F(NodeTest_572, IsSequenceForSequenceNode_572) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_572, IsMapForMapNode_572) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

// ==================== YAML Load and Operator[] Tests ====================

TEST_F(NodeTest_572, LoadYAMLAndAccessMap_572) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST_F(NodeTest_572, LoadYAMLSequence_572) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 5u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[4].as<int>(), 5);
}

TEST_F(NodeTest_572, LoadYAMLScalar_572) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_572, LoadNullYAML_572) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_572, ConstOperatorBracketOnSequenceExistingIndex_572) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode[0].as<int>(), 10);
    EXPECT_EQ(constNode[1].as<int>(), 20);
    EXPECT_EQ(constNode[2].as<int>(), 30);
}

TEST_F(NodeTest_572, ConstOperatorBracketOnSequenceOutOfRange_572) {
    YAML::Node node = YAML::Load("[10, 20]");
    const YAML::Node& constNode = node;
    YAML::Node result = constNode[5];
    EXPECT_FALSE(result.IsDefined());
}

// ==================== Nested Map Tests ====================

TEST_F(NodeTest_572, NestedMapAccess_572) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(NodeTest_572, NestedSequenceAccess_572) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// ==================== Force Insert Tests ====================

TEST_F(NodeTest_572, ForceInsertIntoMap_572) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value");
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_572, ForceInsertDuplicateKeys_572) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert should allow duplicate keys
    EXPECT_EQ(node.size(), 2u);
}

// ==================== Zombie Node Tests ====================

TEST_F(NodeTest_572, ZombieNodeFromConstAccessNonExistentKey_572) {
    YAML::Node node;
    node["existing"] = "value";
    const YAML::Node& constNode = node;
    YAML::Node zombie = constNode["nonexistent"];
    EXPECT_FALSE(zombie.IsDefined());
    EXPECT_FALSE(static_cast<bool>(zombie));
}

TEST_F(NodeTest_572, ZombieNodeIsNotValid_572) {
    const YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node result = node["missing_key"];
    EXPECT_FALSE(result.IsDefined());
}

// ==================== Size Tests ====================

TEST_F(NodeTest_572, SizeOfNullNode_572) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_572, SizeOfScalarNode_572) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// ==================== Mixed Type Conversion Tests ====================

TEST_F(NodeTest_572, StringToIntConversion_572) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.as<int>(), 42);
    EXPECT_EQ(node.as<std::string>(), "42");
}

TEST_F(NodeTest_572, StringToDoubleConversion_572) {
    YAML::Node node = YAML::Load("3.14");
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(NodeTest_572, InvalidConversionWithFallback_572) {
    YAML::Node node = YAML::Load("not_a_number");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

// ==================== Edge Cases ====================

TEST_F(NodeTest_572, EmptyMapSize_572) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_572, LargeSequence_572) {
    YAML::Node node;
    for (int i = 0; i < 1000; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(NodeTest_572, OverwriteMapValue_572) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_572, EmptyStringScalar_572) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST_F(NodeTest_572, SequenceOfMaps_572) {
    YAML::Node node = YAML::Load("[{a: 1}, {b: 2}]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["a"].as<int>(), 1);
    EXPECT_EQ(node[1]["b"].as<int>(), 2);
}

TEST_F(NodeTest_572, MapOfSequences_572) {
    YAML::Node node = YAML::Load("{list1: [1, 2], list2: [3, 4]}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["list1"][0].as<int>(), 1);
    EXPECT_EQ(node["list2"][1].as<int>(), 4);
}
