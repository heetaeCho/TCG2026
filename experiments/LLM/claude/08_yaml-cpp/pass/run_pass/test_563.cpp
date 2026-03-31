#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// ============================================================
// Default Construction Tests
// ============================================================

TEST(NodeTest_563, DefaultConstructor_IsNull_563) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_563, DefaultConstructor_IsDefined_563) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_563, DefaultConstructor_SizeIsZero_563) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Typed Construction Tests
// ============================================================

TEST(NodeTest_563, ConstructWithScalarType_563) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(NodeTest_563, ConstructWithSequenceType_563) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodeTest_563, ConstructWithMapType_563) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(NodeTest_563, ConstructWithNullType_563) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_563, ConstructWithUndefinedType_563) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Template Value Construction Tests
// ============================================================

TEST(NodeTest_563, ConstructWithString_563) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_563, ConstructWithInt_563) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_563, ConstructWithDouble_563) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(NodeTest_563, ConstructWithBool_563) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// ============================================================
// Copy Construction and Assignment Tests
// ============================================================

TEST(NodeTest_563, CopyConstructor_563) {
    YAML::Node original;
    original = "test_value";
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test_value");
}

TEST(NodeTest_563, AssignmentOperatorWithValue_563) {
    YAML::Node node;
    node = 123;
    EXPECT_EQ(node.as<int>(), 123);
    EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTest_563, AssignmentOperatorWithString_563) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_EQ(node.Scalar(), "assigned");
}

TEST(NodeTest_563, AssignmentOperatorWithCString_563) {
    YAML::Node node;
    node = "c_string";
    EXPECT_EQ(node.Scalar(), "c_string");
}

TEST(NodeTest_563, AssignmentOperatorWithNode_563) {
    YAML::Node src;
    src = "source";
    YAML::Node dest;
    dest = src;
    EXPECT_EQ(dest.as<std::string>(), "source");
}

// ============================================================
// Reset Tests
// ============================================================

TEST(NodeTest_563, ResetToAnotherNode_563) {
    YAML::Node node1;
    node1 = "node1";
    YAML::Node node2;
    node2 = "node2";
    node1.reset(node2);
    EXPECT_EQ(node1.as<std::string>(), "node2");
    EXPECT_TRUE(node1.is(node2));
}

// ============================================================
// Scalar Tests
// ============================================================

TEST(NodeTest_563, ScalarReturnsValue_563) {
    YAML::Node node;
    node = "scalar_value";
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

TEST(NodeTest_563, ScalarEmptyForNonScalar_563) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Scalar(), "");
}

// ============================================================
// as<T> Tests
// ============================================================

TEST(NodeTest_563, AsInt_563) {
    YAML::Node node;
    node = 99;
    EXPECT_EQ(node.as<int>(), 99);
}

TEST(NodeTest_563, AsString_563) {
    YAML::Node node;
    node = "hello";
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_563, AsBool_563) {
    YAML::Node node;
    node = true;
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_563, AsWithFallback_563) {
    YAML::Node node;
    // Node is null/undefined, so fallback should be returned
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_563, AsWithFallbackWhenValid_563) {
    YAML::Node node;
    node = 10;
    int result = node.as<int>(42);
    EXPECT_EQ(result, 10);
}

TEST(NodeTest_563, AsFloat_563) {
    YAML::Node node;
    node = 2.5f;
    EXPECT_NEAR(node.as<float>(), 2.5f, 0.001f);
}

// ============================================================
// Tag Tests
// ============================================================

TEST(NodeTest_563, SetAndGetTag_563) {
    YAML::Node node;
    node = "value";
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(NodeTest_563, DefaultTagIsEmpty_563) {
    YAML::Node node;
    node = "value";
    EXPECT_EQ(node.Tag(), "?");
}

// ============================================================
// Style Tests
// ============================================================

TEST(NodeTest_563, SetAndGetStyle_563) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_563, SetBlockStyle_563) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ============================================================
// is() Tests
// ============================================================

TEST(NodeTest_563, IsReturnsTrueForSameNode_563) {
    YAML::Node node;
    node = "test";
    YAML::Node alias = node;
    EXPECT_TRUE(node.is(alias));
}

TEST(NodeTest_563, IsReturnsFalseForDifferentNodes_563) {
    YAML::Node node1;
    node1 = "test1";
    YAML::Node node2;
    node2 = "test2";
    EXPECT_FALSE(node1.is(node2));
}

// ============================================================
// Bool Conversion Tests
// ============================================================

TEST(NodeTest_563, BoolConversionTrueForDefinedNode_563) {
    YAML::Node node;
    node = "value";
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_563, NotOperatorForDefinedNode_563) {
    YAML::Node node;
    node = "value";
    EXPECT_FALSE(!node);
}

TEST(NodeTest_563, BoolConversionForNullNode_563) {
    YAML::Node node;
    // A default-constructed node is Null but valid
    // operator bool() should return true for valid nodes
    EXPECT_TRUE(static_cast<bool>(node));
}

// ============================================================
// Sequence Operations Tests
// ============================================================

TEST(NodeTest_563, PushBackIncreasesSize_563) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_563, PushBackNode_563) {
    YAML::Node seq;
    YAML::Node val;
    val = "item";
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "item");
}

TEST(NodeTest_563, SequenceIndexAccess_563) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST(NodeTest_563, SequenceIteration_563) {
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

TEST(NodeTest_563, PushBackStringValues_563) {
    YAML::Node node;
    node.push_back("alpha");
    node.push_back("beta");
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "alpha");
    EXPECT_EQ(node[1].as<std::string>(), "beta");
}

// ============================================================
// Map Operations Tests
// ============================================================

TEST(NodeTest_563, MapInsertAndAccess_563) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST(NodeTest_563, MapSize_563) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_563, MapRemoveByKey_563) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.remove("key1"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_563, MapRemoveNonexistentKey_563) {
    YAML::Node node;
    node["key1"] = "value1";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_563, MapRemoveByNodeKey_563) {
    YAML::Node node;
    node["key1"] = "value1";
    YAML::Node key;
    key = "key1";
    EXPECT_TRUE(node.remove(key));
}

TEST(NodeTest_563, MapIterationKeyValue_563) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result["x"], 10);
    EXPECT_EQ(result["y"], 20);
}

TEST(NodeTest_563, MapAccessWithNodeKey_563) {
    YAML::Node node;
    node["hello"] = "world";
    YAML::Node key;
    key = "hello";
    EXPECT_EQ(node[key].as<std::string>(), "world");
}

TEST(NodeTest_563, ForceInsert_563) {
    YAML::Node node;
    node.force_insert("key1", "value1");
    node.force_insert("key1", "value2");
    // force_insert allows duplicate keys
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Type Check Tests
// ============================================================

TEST(NodeTest_563, IsNullForDefaultNode_563) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_563, IsScalarAfterAssignment_563) {
    YAML::Node node;
    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_563, IsSequenceAfterPushBack_563) {
    YAML::Node node;
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_563, IsMapAfterSubscript_563) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

// ============================================================
// YAML Parsing Tests
// ============================================================

TEST(NodeTest_563, ParseScalar_563) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_563, ParseSequence_563) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_563, ParseMap_563) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(NodeTest_563, ParseNull_563) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_563, ParseNestedMap_563) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(NodeTest_563, ParseNestedSequence_563) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(NodeTest_563, EmptyStringScalar_563) {
    YAML::Node node;
    node = std::string("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_563, LargeSequence_563) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_563, OverwriteScalarValue_563) {
    YAML::Node node;
    node = "first";
    node = "second";
    EXPECT_EQ(node.as<std::string>(), "second");
}

TEST(NodeTest_563, OverwriteMapValue_563) {
    YAML::Node node;
    node["key"] = "old";
    node["key"] = "new";
    EXPECT_EQ(node["key"].as<std::string>(), "new");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_563, AccessNonexistentKeyConst_563) {
    const YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node result = node["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeTest_563, EmptySequenceSize_563) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_563, EmptyMapSize_563) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Exception / Error Tests
// ============================================================

TEST(NodeTest_563, AsWrongTypeThrows_563) {
    YAML::Node node;
    node = "not_a_number";
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeTest_563, InvalidYAMLThrows_563) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: {["), YAML::ParserException);
}

// ============================================================
// Conversion Between Types Tests
// ============================================================

TEST(NodeTest_563, ScalarToSequenceByPushBack_563) {
    YAML::Node node;
    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    // Assigning as sequence
    node = YAML::Node(YAML::NodeType::Sequence);
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_563, NullToMapBySubscript_563) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_563, NullToSequenceByPushBack_563) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back(42);
    EXPECT_TRUE(node.IsSequence());
}

// ============================================================
// Integer Key in Map Tests
// ============================================================

TEST(NodeTest_563, IntegerKeyInMap_563) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

// ============================================================
// Mixed Type Sequence Tests
// ============================================================

TEST(NodeTest_563, MixedTypeSequence_563) {
    YAML::Node node;
    node.push_back(42);
    node.push_back("hello");
    node.push_back(3.14);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_NEAR(node[2].as<double>(), 3.14, 0.001);
}

// ============================================================
// Mark Tests
// ============================================================

TEST(NodeTest_563, MarkOnParsedNode_563) {
    YAML::Node node = YAML::Load("hello");
    YAML::Mark mark = node.Mark();
    // Parsed from beginning, so line and column should be 0
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// ============================================================
// Begin/End on Empty Container Tests
// ============================================================

TEST(NodeTest_563, BeginEqualsEndOnEmptySequence_563) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_EQ(node.begin(), node.end());
}

TEST(NodeTest_563, BeginEqualsEndOnEmptyMap_563) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_EQ(node.begin(), node.end());
}

// ============================================================
// Multiple Assignment Tests
// ============================================================

TEST(NodeTest_563, AssignDifferentTypes_563) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
    EXPECT_TRUE(node.IsScalar());

    node = "string_now";
    EXPECT_EQ(node.as<std::string>(), "string_now");
    EXPECT_TRUE(node.IsScalar());
}

// ============================================================
// Remove from Sequence Tests
// ============================================================

TEST(NodeTest_563, RemoveFromSequenceByIndex_563) {
    YAML::Node node = YAML::Load("[a, b, c]");
    EXPECT_EQ(node.size(), 3u);
    node.remove(1);
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// as<T> fallback for undefined node
// ============================================================

TEST(NodeTest_563, UndefinedNodeFallback_563) {
    const YAML::Node root = YAML::Load("{a: 1}");
    std::string val = root["missing"].as<std::string>("default_val");
    EXPECT_EQ(val, "default_val");
}

// ============================================================
// Boolean parsing
// ============================================================

TEST(NodeTest_563, ParseBoolTrue_563) {
    YAML::Node node = YAML::Load("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_563, ParseBoolFalse_563) {
    YAML::Node node = YAML::Load("false");
    EXPECT_FALSE(node.as<bool>());
}

// ============================================================
// Multiline YAML
// ============================================================

TEST(NodeTest_563, MultilineYAML_563) {
    std::string yaml = "name: John\nage: 30\ncity: NYC";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
    EXPECT_EQ(node["city"].as<std::string>(), "NYC");
}
