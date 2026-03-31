#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <sstream>

// ============================================================
// Default Construction Tests
// ============================================================

TEST(YAMLNodeTest_196, DefaultConstructor_CreatesNullNode_196) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(YAMLNodeTest_196, DefaultConstructor_OperatorBoolFalse_196) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

// ============================================================
// Type-based Construction Tests
// ============================================================

TEST(YAMLNodeTest_196, ConstructWithScalarType_196) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(YAMLNodeTest_196, ConstructWithSequenceType_196) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(YAMLNodeTest_196, ConstructWithMapType_196) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(YAMLNodeTest_196, ConstructWithNullType_196) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(YAMLNodeTest_196, ConstructWithUndefinedType_196) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// ============================================================
// Value Construction Tests
// ============================================================

TEST(YAMLNodeTest_196, ConstructWithStringValue_196) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(YAMLNodeTest_196, ConstructWithIntValue_196) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(YAMLNodeTest_196, ConstructWithDoubleValue_196) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(YAMLNodeTest_196, ConstructWithBoolValue_196) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(YAMLNodeTest_196, ConstructWithCStringValue_196) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "world");
}

// ============================================================
// Copy Construction Tests
// ============================================================

TEST(YAMLNodeTest_196, CopyConstructor_SharesSameNode_196) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_TRUE(copy.is(original));
    EXPECT_EQ(copy.Scalar(), "test");
}

// ============================================================
// Assignment Tests
// ============================================================

TEST(YAMLNodeTest_196, AssignString_196) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned");
}

TEST(YAMLNodeTest_196, AssignInt_196) {
    YAML::Node node;
    node = 100;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 100);
}

TEST(YAMLNodeTest_196, AssignNode_196) {
    YAML::Node a("hello");
    YAML::Node b("world");
    a = b;
    EXPECT_TRUE(a.is(b));
}

// ============================================================
// Scalar Access Tests
// ============================================================

TEST(YAMLNodeTest_196, ScalarReturnsValue_196) {
    YAML::Node node("scalar_value");
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

TEST(YAMLNodeTest_196, AsStringConversion_196) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(YAMLNodeTest_196, AsIntConversion_196) {
    YAML::Node node("123");
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(YAMLNodeTest_196, AsDoubleConversion_196) {
    YAML::Node node("2.718");
    EXPECT_NEAR(node.as<double>(), 2.718, 0.001);
}

TEST(YAMLNodeTest_196, AsBoolConversion_196) {
    YAML::Node node("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(YAMLNodeTest_196, AsWithFallback_WhenConversionFails_196) {
    YAML::Node node("not_an_int");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(YAMLNodeTest_196, AsWithFallback_WhenConversionSucceeds_196) {
    YAML::Node node("10");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 10);
}

TEST(YAMLNodeTest_196, AsWithFallback_UndefinedNode_196) {
    YAML::Node node;
    std::string result = node.as<std::string>("default_val");
    EXPECT_EQ(result, "default_val");
}

// ============================================================
// IsDefined / Type Check Tests
// ============================================================

TEST(YAMLNodeTest_196, IsDefinedReturnsTrueForScalar_196) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

TEST(YAMLNodeTest_196, IsNullForDefaultNode_196) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(YAMLNodeTest_196, OperatorBoolTrueForDefined_196) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(YAMLNodeTest_196, OperatorNotForUndefined_196) {
    YAML::Node node;
    // Default node is Null but valid; operator! checks IsDefined
    // A Null node that is valid: IsDefined returns false for Null type (depending on impl)
    // Let's just check the operator
    bool result = !node;
    // For a default constructed node, it's Null and not defined
    EXPECT_TRUE(result);
}

// ============================================================
// Tag Tests
// ============================================================

TEST(YAMLNodeTest_196, SetAndGetTag_196) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(YAMLNodeTest_196, DefaultTagIsEmpty_196) {
    YAML::Node node("value");
    // Tag for a scalar without explicit tag
    EXPECT_EQ(node.Tag(), "?");
}

// ============================================================
// Style Tests
// ============================================================

TEST(YAMLNodeTest_196, SetAndGetStyle_196) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(YAMLNodeTest_196, DefaultStyleIsDefault_196) {
    YAML::Node node("value");
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// ============================================================
// Sequence Tests
// ============================================================

TEST(YAMLNodeTest_196, PushBackCreatesSequence_196) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

TEST(YAMLNodeTest_196, PushBackWithNode_196) {
    YAML::Node node;
    YAML::Node child("child_val");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "child_val");
}

TEST(YAMLNodeTest_196, SequenceAccessByIndex_196) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST(YAMLNodeTest_196, SequenceIteration_196) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");

    std::vector<std::string> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<std::string>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "a");
    EXPECT_EQ(values[1], "b");
    EXPECT_EQ(values[2], "c");
}

TEST(YAMLNodeTest_196, SequenceSizeIsCorrect_196) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST(YAMLNodeTest_196, PushBackIntValue_196) {
    YAML::Node node;
    node.push_back(42);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node[0].as<int>(), 42);
}

// ============================================================
// Map Tests
// ============================================================

TEST(YAMLNodeTest_196, MapAccessByStringKey_196) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST(YAMLNodeTest_196, MapAccessByIntKey_196) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST(YAMLNodeTest_196, MapSize_196) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(YAMLNodeTest_196, MapIteration_196) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;

    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["x"], 10);
    EXPECT_EQ(result["y"], 20);
}

TEST(YAMLNodeTest_196, MapAccessNonExistentKeyConst_196) {
    YAML::Node node;
    node["exists"] = "yes";
    const YAML::Node& cnode = node;
    EXPECT_FALSE(cnode["nonexistent"].IsDefined());
}

TEST(YAMLNodeTest_196, MapRemoveByStringKey_196) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST(YAMLNodeTest_196, MapRemoveNonExistentKey_196) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("b"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_196, MapRemoveByNodeKey_196) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Node keyNode("key");
    EXPECT_TRUE(node.remove(keyNode));
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_196, ForceInsert_196) {
    YAML::Node node;
    node.force_insert("key1", "val1");
    node.force_insert("key1", "val2");  // duplicate key
    EXPECT_TRUE(node.IsMap());
    // force_insert allows duplicates, so size should be 2
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// is() Tests
// ============================================================

TEST(YAMLNodeTest_196, IsReturnsTrueForSameNode_196) {
    YAML::Node a("test");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST(YAMLNodeTest_196, IsReturnsFalseForDifferentNodes_196) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// reset() Tests
// ============================================================

TEST(YAMLNodeTest_196, ResetChangesNodeReference_196) {
    YAML::Node a("original");
    YAML::Node b("replacement");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "replacement");
}

// ============================================================
// YAML Parse Tests
// ============================================================

TEST(YAMLNodeTest_196, ParseScalar_196) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(YAMLNodeTest_196, ParseSequence_196) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(YAMLNodeTest_196, ParseMap_196) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(YAMLNodeTest_196, ParseNull_196) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(YAMLNodeTest_196, ParseEmptyString_196) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

TEST(YAMLNodeTest_196, ParseNestedStructure_196) {
    std::string yaml = R"(
outer:
  inner:
    key: value
)";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["outer"]["inner"]["key"].as<std::string>(), "value");
}

TEST(YAMLNodeTest_196, ParseSequenceOfMaps_196) {
    std::string yaml = R"(
- name: Alice
  age: 30
- name: Bob
  age: 25
)";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[0]["age"].as<int>(), 30);
    EXPECT_EQ(node[1]["name"].as<std::string>(), "Bob");
    EXPECT_EQ(node[1]["age"].as<int>(), 25);
}

// ============================================================
// Exception / Error Cases
// ============================================================

TEST(YAMLNodeTest_196, AsThrowsOnTypeMismatch_196) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(YAMLNodeTest_196, AsThrowsOnUndefinedNode_196) {
    YAML::Node node;
    const YAML::Node& cnode = node;
    YAML::Node child = cnode["nonexistent"];
    EXPECT_THROW(child.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

TEST(YAMLNodeTest_196, InvalidYAMLThrows_196) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: ]]"), YAML::ParserException);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(YAMLNodeTest_196, EmptySequence_196) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(YAMLNodeTest_196, EmptyMap_196) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(YAMLNodeTest_196, EmptyStringScalar_196) {
    YAML::Node node = YAML::Load("''");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST(YAMLNodeTest_196, LargeSequence_196) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(YAMLNodeTest_196, LargeMap_196) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node["0"].as<int>(), 0);
    EXPECT_EQ(node["999"].as<int>(), 999);
}

TEST(YAMLNodeTest_196, ScalarSizeIsZero_196) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_196, NullNodeSizeIsZero_196) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Mixed Type Modification Tests
// ============================================================

TEST(YAMLNodeTest_196, OverwriteScalarWithSequence_196) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_196, OverwriteScalarWithMap_196) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST(YAMLNodeTest_196, AssignNewValueChangesType_196) {
    YAML::Node node;
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
    node = "now_scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "now_scalar");
}

// ============================================================
// Mark Tests
// ============================================================

TEST(YAMLNodeTest_196, MarkForLoadedNode_196) {
    YAML::Node node = YAML::Load("hello");
    YAML::Mark mark = node.Mark();
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// ============================================================
// Operator[] with Node key
// ============================================================

TEST(YAMLNodeTest_196, OperatorBracketWithNodeKey_196) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

TEST(YAMLNodeTest_196, RemoveWithNodeKey_196) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    EXPECT_TRUE(node.remove(key));
    EXPECT_FALSE(node["key1"].IsDefined());
}

// ============================================================
// Boolean conversion edge cases
// ============================================================

TEST(YAMLNodeTest_196, BoolConversionTrueValues_196) {
    YAML::Node nodeTrue = YAML::Load("true");
    EXPECT_EQ(nodeTrue.as<bool>(), true);

    YAML::Node nodeYes = YAML::Load("yes");
    EXPECT_EQ(nodeYes.as<bool>(), true);
}

TEST(YAMLNodeTest_196, BoolConversionFalseValues_196) {
    YAML::Node nodeFalse = YAML::Load("false");
    EXPECT_EQ(nodeFalse.as<bool>(), false);

    YAML::Node nodeNo = YAML::Load("no");
    EXPECT_EQ(nodeNo.as<bool>(), false);
}

// ============================================================
// Sequence remove by index (via int key)
// ============================================================

TEST(YAMLNodeTest_196, RemoveFromSequenceByIndex_196) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_TRUE(node.remove(1));
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Self-assignment
// ============================================================

TEST(YAMLNodeTest_196, SelfAssignment_196) {
    YAML::Node node("test");
    node = node;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "test");
}

// ============================================================
// Complex nested operations
// ============================================================

TEST(YAMLNodeTest_196, NestedMapCreation_196) {
    YAML::Node node;
    node["level1"]["level2"]["level3"] = "deep_value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["level1"].IsMap());
    EXPECT_TRUE(node["level1"]["level2"].IsMap());
    EXPECT_EQ(node["level1"]["level2"]["level3"].as<std::string>(), "deep_value");
}

TEST(YAMLNodeTest_196, MixedSequenceAndMap_196) {
    YAML::Node node;
    node["list"].push_back("item1");
    node["list"].push_back("item2");
    node["scalar"] = "value";

    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["list"].IsSequence());
    EXPECT_EQ(node["list"].size(), 2u);
    EXPECT_TRUE(node["scalar"].IsScalar());
}
