#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// ============================================================
// Tests for Node construction and basic type queries
// ============================================================

TEST(NodeTest_553, DefaultConstructorCreatesNullNode_553) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_553, ConstructWithScalarType_553) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTest_553, ConstructWithSequenceType_553) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_553, ConstructWithMapType_553) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_553, ConstructWithUndefinedType_553) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Tests for Node construction from values
// ============================================================

TEST(NodeTest_553, ConstructFromInt_553) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_553, ConstructFromString_553) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_553, ConstructFromDouble_553) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(NodeTest_553, ConstructFromBool_553) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeTest_553, ConstructFromCString_553) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "world");
}

// ============================================================
// Tests for as<T>() - normal operation
// ============================================================

TEST(NodeAsTest_553, AsIntFromScalar_553) {
    YAML::Node node = YAML::Load("123");
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeAsTest_553, AsStringFromScalar_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeAsTest_553, AsDoubleFromScalar_553) {
    YAML::Node node = YAML::Load("2.718");
    EXPECT_NEAR(node.as<double>(), 2.718, 0.001);
}

TEST(NodeAsTest_553, AsBoolTrue_553) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeAsTest_553, AsBoolFalse_553) {
    YAML::Node node = YAML::Load("false");
    EXPECT_EQ(node.as<bool>(), false);
}

TEST(NodeAsTest_553, AsFloatFromScalar_553) {
    YAML::Node node = YAML::Load("1.5");
    EXPECT_NEAR(node.as<float>(), 1.5f, 0.01f);
}

// ============================================================
// Tests for as<T>(fallback) - with fallback
// ============================================================

TEST(NodeAsFallbackTest_553, FallbackWhenNodeIsNull_553) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(99), 99);
}

TEST(NodeAsFallbackTest_553, FallbackNotUsedWhenConversionSucceeds_553) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.as<int>(99), 42);
}

TEST(NodeAsFallbackTest_553, FallbackStringWhenNodeIsNull_553) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>("default"), "default");
}

TEST(NodeAsFallbackTest_553, FallbackStringNotUsedWhenValid_553) {
    YAML::Node node = YAML::Load("actual");
    EXPECT_EQ(node.as<std::string>("default"), "actual");
}

TEST(NodeAsFallbackTest_553, FallbackWhenConversionFails_553) {
    YAML::Node node = YAML::Load("not_a_number");
    // int conversion from "not_a_number" should fail, fallback used
    EXPECT_EQ(node.as<int>(77), 77);
}

TEST(NodeAsFallbackTest_553, FallbackForUndefinedNode_553) {
    YAML::Node root = YAML::Load("{}");
    YAML::Node child = root["nonexistent"];
    EXPECT_EQ(child.as<int>(42), 42);
}

// ============================================================
// Tests for as<T>() - error cases (exceptions)
// ============================================================

TEST(NodeAsExceptionTest_553, ThrowsOnNullNodeWithoutFallback_553) {
    YAML::Node node;
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeAsExceptionTest_553, ThrowsOnBadConversionWithoutFallback_553) {
    YAML::Node node = YAML::Load("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeAsExceptionTest_553, ThrowsInvalidNodeForInvalidNode_553) {
    YAML::Node root = YAML::Load("a: 1");
    // Access a non-existent key on a const node to get an invalid node
    const YAML::Node constRoot = root;
    YAML::Node zombie = constRoot["nonexistent"];
    EXPECT_THROW(zombie.as<int>(), YAML::Exception);
}

TEST(NodeAsExceptionTest_553, ThrowsOnSequenceAsInt_553) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeAsExceptionTest_553, ThrowsOnMapAsInt_553) {
    YAML::Node node = YAML::Load("{a: 1}");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// ============================================================
// Tests for Scalar()
// ============================================================

TEST(NodeScalarTest_553, ScalarReturnsValue_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeScalarTest_553, ScalarEmptyForSequence_553) {
    YAML::Node node = YAML::Load("[1, 2]");
    EXPECT_TRUE(node.Scalar().empty());
}

// ============================================================
// Tests for Tag and SetTag
// ============================================================

TEST(NodeTagTest_553, DefaultTagIsEmpty_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.Tag().empty() || node.Tag() == "?");
}

TEST(NodeTagTest_553, SetTagAndGetTag_553) {
    YAML::Node node(42);
    node.SetTag("!mytag");
    EXPECT_EQ(node.Tag(), "!mytag");
}

// ============================================================
// Tests for Style and SetStyle
// ============================================================

TEST(NodeStyleTest_553, SetAndGetStyle_553) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// ============================================================
// Tests for operator bool and operator!
// ============================================================

TEST(NodeBoolTest_553, ValidNodeIsTrue_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(NodeBoolTest_553, DefaultNodeIsFalse_553) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

// ============================================================
// Tests for IsDefined
// ============================================================

TEST(NodeDefinedTest_553, LoadedNodeIsDefined_553) {
    YAML::Node node = YAML::Load("42");
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeDefinedTest_553, UndefinedTypeIsNotDefined_553) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Tests for is()
// ============================================================

TEST(NodeIsTest_553, SameNodeIsTrue_553) {
    YAML::Node node = YAML::Load("42");
    YAML::Node alias = node;
    EXPECT_TRUE(node.is(alias));
}

TEST(NodeIsTest_553, DifferentNodesIsFalse_553) {
    YAML::Node a = YAML::Load("42");
    YAML::Node b = YAML::Load("42");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// Tests for operator= (assignment)
// ============================================================

TEST(NodeAssignTest_553, AssignInt_553) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeAssignTest_553, AssignString_553) {
    YAML::Node node;
    node = std::string("test");
    EXPECT_EQ(node.as<std::string>(), "test");
}

TEST(NodeAssignTest_553, AssignNode_553) {
    YAML::Node a = YAML::Load("hello");
    YAML::Node b;
    b = a;
    EXPECT_TRUE(b.is(a));
}

// ============================================================
// Tests for reset
// ============================================================

TEST(NodeResetTest_553, ResetMakesNodesIdentical_553) {
    YAML::Node a = YAML::Load("hello");
    YAML::Node b = YAML::Load("world");
    b.reset(a);
    EXPECT_TRUE(b.is(a));
}

// ============================================================
// Tests for Sequence operations
// ============================================================

TEST(NodeSequenceTest_553, PushBackIncreasesSize_553) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeSequenceTest_553, IterateSequence_553) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

TEST(NodeSequenceTest_553, AccessByIndex_553) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST(NodeSequenceTest_553, PushBackNode_553) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node val(42);
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<int>(), 42);
}

// ============================================================
// Tests for Map operations
// ============================================================

TEST(NodeMapTest_553, AccessByStringKey_553) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST(NodeMapTest_553, MapSize_553) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeMapTest_553, InsertNewKeyValue_553) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    EXPECT_EQ(node["key"].as<std::string>(), "value");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeMapTest_553, IterateMap_553) {
    YAML::Node node = YAML::Load("{x: 1, y: 2}");
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result["x"], 1);
    EXPECT_EQ(result["y"], 2);
}

TEST(NodeMapTest_553, RemoveKey_553) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST(NodeMapTest_553, RemoveNonExistentKeyReturnsFalse_553) {
    YAML::Node node = YAML::Load("{a: 1}");
    EXPECT_FALSE(node.remove("z"));
}

TEST(NodeMapTest_553, ForceInsert_553) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value");
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// ============================================================
// Tests for copy constructor
// ============================================================

TEST(NodeCopyTest_553, CopyConstructorSharesNode_553) {
    YAML::Node a = YAML::Load("42");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(b.as<int>(), 42);
}

// ============================================================
// Tests for type checks
// ============================================================

TEST(NodeTypeTest_553, IsNullForNullNode_553) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTypeTest_553, IsScalarForStringNode_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
}

TEST(NodeTypeTest_553, IsSequenceForListNode_553) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTypeTest_553, IsMapForMappingNode_553) {
    YAML::Node node = YAML::Load("{a: 1}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

// ============================================================
// Tests for as<T>() with various types - boundary conditions
// ============================================================

TEST(NodeAsBoundaryTest_553, EmptyStringScalar_553) {
    YAML::Node node = YAML::Load("''");
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST(NodeAsBoundaryTest_553, LargeInteger_553) {
    YAML::Node node = YAML::Load("2147483647");
    EXPECT_EQ(node.as<int>(), 2147483647);
}

TEST(NodeAsBoundaryTest_553, NegativeInteger_553) {
    YAML::Node node = YAML::Load("-1");
    EXPECT_EQ(node.as<int>(), -1);
}

TEST(NodeAsBoundaryTest_553, ZeroInteger_553) {
    YAML::Node node = YAML::Load("0");
    EXPECT_EQ(node.as<int>(), 0);
}

TEST(NodeAsBoundaryTest_553, AsVectorFromSequence_553) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    auto vec = node.as<std::vector<int>>();
    ASSERT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(NodeAsBoundaryTest_553, AsMapFromMapping_553) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    auto m = node.as<std::map<std::string, int>>();
    EXPECT_EQ(m["a"], 1);
    EXPECT_EQ(m["b"], 2);
}

// ============================================================
// Tests for null/empty size
// ============================================================

TEST(NodeSizeTest_553, NullNodeSizeIsZero_553) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeSizeTest_553, ScalarNodeSizeIsZero_553) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeSizeTest_553, EmptySequenceSize_553) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeSizeTest_553, EmptyMapSize_553) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Tests for accessing non-existent keys on const node
// ============================================================

TEST(NodeConstAccessTest_553, ConstAccessNonExistentKeyReturnsUndefined_553) {
    const YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node result = node["b"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeConstAccessTest_553, NonConstAccessCreatesKey_553) {
    YAML::Node node = YAML::Load("{a: 1}");
    node["b"] = 2;
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Tests for remove with Node key
// ============================================================

TEST(NodeRemoveTest_553, RemoveWithNodeKey_553) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    YAML::Node key = YAML::Load("a");
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(node.size(), 1u);
}

// ============================================================
// Test as_if behavior through Node::as interface for invalid nodes
// ============================================================

TEST(NodeAsIfTest_553, InvalidNodeWithFallbackReturnsFallback_553) {
    const YAML::Node root = YAML::Load("{a: 1}");
    YAML::Node invalid = root["nonexistent"];
    // Invalid (zombie) node with fallback should return fallback
    EXPECT_EQ(invalid.as<int>(555), 555);
}

TEST(NodeAsIfTest_553, InvalidNodeWithoutFallbackThrows_553) {
    const YAML::Node root = YAML::Load("{a: 1}");
    YAML::Node invalid = root["nonexistent"];
    EXPECT_THROW(invalid.as<int>(), YAML::Exception);
}

TEST(NodeAsIfTest_553, InvalidNodeStringFallback_553) {
    const YAML::Node root = YAML::Load("{a: 1}");
    YAML::Node invalid = root["nonexistent"];
    EXPECT_EQ(invalid.as<std::string>("fallback_value"), "fallback_value");
}
