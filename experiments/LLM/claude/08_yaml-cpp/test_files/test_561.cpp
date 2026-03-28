#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test fixture for Node tests
class NodeTest_561 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(NodeTest_561, DefaultConstructorCreatesNullNode_561) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_561, ConstructWithScalarType_561) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_561, ConstructWithSequenceType_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_561, ConstructWithMapType_561) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST_F(NodeTest_561, ConstructWithStringValue_561) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_561, ConstructWithIntValue_561) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_561, ConstructWithDoubleValue_561) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST_F(NodeTest_561, ConstructWithBoolValue_561) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

// ==================== Copy Constructor Tests ====================

TEST_F(NodeTest_561, CopyConstructor_561) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// ==================== Assignment Tests ====================

TEST_F(NodeTest_561, AssignStringValue_561) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_561, AssignIntValue_561) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(node.as<int>(), 100);
}

TEST_F(NodeTest_561, AssignNodeToNode_561) {
    YAML::Node a("a_value");
    YAML::Node b;
    b = a;
    EXPECT_EQ(b.Scalar(), "a_value");
}

// ==================== Type Check Tests ====================

TEST_F(NodeTest_561, IsNullOnDefault_561) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_561, IsScalarAfterAssignment_561) {
    YAML::Node node;
    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_561, IsSequenceAfterPushBack_561) {
    YAML::Node node;
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_561, IsMapAfterIndexing_561) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

// ==================== Bool Operator Tests ====================

TEST_F(NodeTest_561, BoolOperatorOnValidNode_561) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_561, BoolOperatorOnNullNode_561) {
    YAML::Node node;
    // A null node is valid but not defined the same way
    // Default node should still be "valid" even if null
    EXPECT_FALSE(!node);
}

// ==================== IsDefined Tests ====================

TEST_F(NodeTest_561, IsDefinedOnScalar_561) {
    YAML::Node node("defined");
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_561, UndefinedNodeFromMissingKey_561) {
    YAML::Node node(YAML::NodeType::Map);
    node["existing"] = "value";
    YAML::Node missing = node["nonexistent"];
    EXPECT_FALSE(missing.IsDefined());
}

// ==================== Scalar Tests ====================

TEST_F(NodeTest_561, ScalarReturnsCorrectValue_561) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST_F(NodeTest_561, ScalarEmptyOnNonScalar_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Scalar(), "");
}

// ==================== As Tests ====================

TEST_F(NodeTest_561, AsStringFromScalar_561) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_561, AsIntFromScalar_561) {
    YAML::Node node("42");
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_561, AsDoubleFromScalar_561) {
    YAML::Node node("3.14");
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST_F(NodeTest_561, AsBoolTrueFromScalar_561) {
    YAML::Node node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_561, AsBoolFalseFromScalar_561) {
    YAML::Node node("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_561, AsWithFallbackWhenConversionFails_561) {
    YAML::Node node("not_a_number");
    EXPECT_EQ(node.as<int>(99), 99);
}

TEST_F(NodeTest_561, AsWithFallbackWhenNodeUndefined_561) {
    YAML::Node map(YAML::NodeType::Map);
    map["key"] = "value";
    EXPECT_EQ(map["missing"].as<std::string>("fallback"), "fallback");
}

// ==================== Tag Tests ====================

TEST_F(NodeTest_561, SetAndGetTag_561) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST_F(NodeTest_561, DefaultTagIsEmpty_561) {
    YAML::Node node("value");
    // By default, tag should be empty or "?"
    // Depending on implementation
    std::string tag = node.Tag();
    EXPECT_TRUE(tag.empty() || tag == "?");
}

TEST_F(NodeTest_561, SetTagOnSequence_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetTag("!seq_tag");
    EXPECT_EQ(node.Tag(), "!seq_tag");
}

TEST_F(NodeTest_561, SetTagOnMap_561) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetTag("!map_tag");
    EXPECT_EQ(node.Tag(), "!map_tag");
}

// ==================== Style Tests ====================

TEST_F(NodeTest_561, SetStyleDefault_561) {
    YAML::Node node("value");
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeTest_561, SetStyleBlock_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeTest_561, SetStyleFlow_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_561, SetStyleOnMap_561) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_561, SetStyleOnScalar_561) {
    YAML::Node node("scalar_val");
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeTest_561, StyleChangePersists_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_561, DefaultStyleIsDefault_561) {
    YAML::Node node("value");
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// ==================== Sequence Tests ====================

TEST_F(NodeTest_561, PushBackCreatesSequence_561) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_561, PushBackNodeValue_561) {
    YAML::Node node;
    YAML::Node item("item_value");
    node.push_back(item);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "item_value");
}

TEST_F(NodeTest_561, SequenceIndexAccess_561) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

TEST_F(NodeTest_561, SequenceSizeIsCorrect_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_561, PushBackMultipleTypes_561) {
    YAML::Node node;
    node.push_back(42);
    node.push_back("hello");
    node.push_back(3.14);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.14);
}

// ==================== Map Tests ====================

TEST_F(NodeTest_561, MapIndexCreatesMap_561) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST_F(NodeTest_561, MapAccessByStringKey_561) {
    YAML::Node node;
    node["name"] = "John";
    EXPECT_EQ(node["name"].as<std::string>(), "John");
}

TEST_F(NodeTest_561, MapAccessByIntKey_561) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST_F(NodeTest_561, MapSizeIsCorrect_561) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
    node["a"] = 1;
    EXPECT_EQ(node.size(), 1u);
    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_561, MapOverwriteValue_561) {
    YAML::Node node;
    node["key"] = "old_value";
    node["key"] = "new_value";
    EXPECT_EQ(node["key"].as<std::string>(), "new_value");
}

TEST_F(NodeTest_561, MapRemoveByStringKey_561) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST_F(NodeTest_561, MapRemoveNonExistentKey_561) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_561, MapRemoveByNodeKey_561) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Node key("key");
    EXPECT_TRUE(node.remove(key));
    EXPECT_FALSE(node["key"].IsDefined());
}

// ==================== Force Insert Tests ====================

TEST_F(NodeTest_561, ForceInsertAddsEntry_561) {
    YAML::Node node;
    node["key1"] = "value1";
    node.force_insert("key2", "value2");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// ==================== Iterator Tests ====================

TEST_F(NodeTest_561, SequenceIterator_561) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(sum, 6);
}

TEST_F(NodeTest_561, MapIterator_561) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST_F(NodeTest_561, EmptySequenceIterator_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_561, EmptyMapIterator_561) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

// ==================== is() Tests ====================

TEST_F(NodeTest_561, IsReturnsTrueForSameNode_561) {
    YAML::Node a("value");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST_F(NodeTest_561, IsReturnsFalseForDifferentNodes_561) {
    YAML::Node a("value");
    YAML::Node b("value");
    EXPECT_FALSE(a.is(b));
}

// ==================== Reset Tests ====================

TEST_F(NodeTest_561, ResetToAnotherNode_561) {
    YAML::Node a("original");
    YAML::Node b("replaced");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "replaced");
}

// ==================== Size Tests ====================

TEST_F(NodeTest_561, SizeOfNullNodeIsZero_561) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_561, SizeOfScalarIsZero_561) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// ==================== YAML Parsing Tests ====================

TEST_F(NodeTest_561, ParseScalar_561) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_561, ParseSequence_561) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_561, ParseMap_561) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST_F(NodeTest_561, ParseNullValue_561) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_561, ParseEmptyDocument_561) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

// ==================== Style with Emitter Tests ====================

TEST_F(NodeTest_561, SetStyleFlowAffectsEmitter_561) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    node.SetStyle(YAML::EmitterStyle::Flow);
    
    YAML::Emitter emitter;
    emitter << node;
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(NodeTest_561, SetStyleBlockAffectsEmitter_561) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.SetStyle(YAML::EmitterStyle::Block);
    
    YAML::Emitter emitter;
    emitter << node;
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("- "), std::string::npos);
}

TEST_F(NodeTest_561, SetStyleFlowOnMap_561) {
    YAML::Node node;
    node["key"] = "value";
    node.SetStyle(YAML::EmitterStyle::Flow);
    
    YAML::Emitter emitter;
    emitter << node;
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

// ==================== Conversion Error Tests ====================

TEST_F(NodeTest_561, AsThrowsOnBadConversion_561) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST_F(NodeTest_561, AsThrowsOnUndefinedNode_561) {
    YAML::Node map(YAML::NodeType::Map);
    map["key"] = "value";
    EXPECT_THROW(map["missing"].as<std::string>(), YAML::TypedBadConversion<std::string>);
}

// ==================== Nested Structure Tests ====================

TEST_F(NodeTest_561, NestedMapAccess_561) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(NodeTest_561, NestedSequenceAccess_561) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

TEST_F(NodeTest_561, SetStyleOnNestedNodes_561) {
    YAML::Node outer;
    YAML::Node inner;
    inner.push_back(1);
    inner.push_back(2);
    inner.SetStyle(YAML::EmitterStyle::Flow);
    outer.push_back(inner);
    outer.SetStyle(YAML::EmitterStyle::Block);
    
    EXPECT_EQ(outer.Style(), YAML::EmitterStyle::Block);
    EXPECT_EQ(outer[0].Style(), YAML::EmitterStyle::Flow);
}

// ==================== Edge Cases ====================

TEST_F(NodeTest_561, EmptyStringScalar_561) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST_F(NodeTest_561, SetStyleMultipleTimes_561) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeTest_561, SetStyleOnDefaultConstructedThenAssigned_561) {
    YAML::Node node;
    node = "value";
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeTest_561, ConstNodeAccess_561) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_561, LargeSequence_561) {
    YAML::Node node;
    for (int i = 0; i < 1000; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(NodeTest_561, SetStyleOnNullNodeMakesItExist_561) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.SetStyle(YAML::EmitterStyle::Flow);
    // After SetStyle, node should still exist and have the style set
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}
