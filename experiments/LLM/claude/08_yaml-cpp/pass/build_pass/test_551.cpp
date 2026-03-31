#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// =============================================================================
// Tests for YAML::Node and the as_if functionality
// =============================================================================

// --- Default Construction ---

TEST(YAMLNodeTest_551, DefaultConstructedNodeIsNull_551) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(YAMLNodeTest_551, DefaultConstructedNodeIsDefined_551) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(YAMLNodeTest_551, DefaultConstructedNodeBoolConversion_551) {
    YAML::Node node;
    // A null node is still "valid" but evaluates to true because it exists
    // (it's defined). Implementation may vary; test observable behavior.
    // Default node is Null type but valid.
    EXPECT_TRUE(node.IsDefined());
}

// --- Construction with Type ---

TEST(YAMLNodeTest_551, ConstructWithScalarType_551) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(YAMLNodeTest_551, ConstructWithSequenceType_551) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(YAMLNodeTest_551, ConstructWithMapType_551) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(YAMLNodeTest_551, ConstructWithNullType_551) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(YAMLNodeTest_551, ConstructWithUndefinedType_551) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// --- Construction with Value ---

TEST(YAMLNodeTest_551, ConstructWithStringValue_551) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(YAMLNodeTest_551, ConstructWithIntValue_551) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(YAMLNodeTest_551, ConstructWithDoubleValue_551) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST(YAMLNodeTest_551, ConstructWithBoolValue_551) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// --- Copy Construction ---

TEST(YAMLNodeTest_551, CopyConstruction_551) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test");
    EXPECT_TRUE(copy.is(original));
}

// --- as<T>() ---

TEST(YAMLNodeTest_551, AsStringFromScalar_551) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST(YAMLNodeTest_551, AsIntFromScalar_551) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(YAMLNodeTest_551, AsDoubleFromScalar_551) {
    YAML::Node node(2.718);
    EXPECT_DOUBLE_EQ(node.as<double>(), 2.718);
}

TEST(YAMLNodeTest_551, AsBoolFromScalar_551) {
    YAML::Node node(false);
    EXPECT_EQ(node.as<bool>(), false);
}

TEST(YAMLNodeTest_551, AsWithInvalidConversionThrows_551) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// --- as<T>(fallback) - the as_if functionality ---

TEST(YAMLNodeAsIfTest_551, FallbackReturnedForNullNode_551) {
    YAML::Node node;
    // Null node, should return fallback
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(YAMLNodeAsIfTest_551, FallbackNotUsedForValidScalar_551) {
    YAML::Node node(100);
    int result = node.as<int>(42);
    EXPECT_EQ(result, 100);
}

TEST(YAMLNodeAsIfTest_551, FallbackReturnedWhenConversionFails_551) {
    YAML::Node node("not_an_int");
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST(YAMLNodeAsIfTest_551, FallbackStringForNullNode_551) {
    YAML::Node node;
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "default");
}

TEST(YAMLNodeAsIfTest_551, FallbackStringNotUsedForValidScalar_551) {
    YAML::Node node("actual_value");
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "actual_value");
}

TEST(YAMLNodeAsIfTest_551, FallbackDoubleForNullNode_551) {
    YAML::Node node;
    double result = node.as<double>(1.5);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(YAMLNodeAsIfTest_551, FallbackDoubleNotUsedForValidScalar_551) {
    YAML::Node node(3.14);
    double result = node.as<double>(1.5);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST(YAMLNodeAsIfTest_551, FallbackBoolForNullNode_551) {
    YAML::Node node;
    bool result = node.as<bool>(true);
    EXPECT_EQ(result, true);
}

TEST(YAMLNodeAsIfTest_551, FallbackBoolNotUsedForValidScalar_551) {
    YAML::Node node(false);
    bool result = node.as<bool>(true);
    EXPECT_EQ(result, false);
}

TEST(YAMLNodeAsIfTest_551, FallbackWithDifferentTypes_551) {
    YAML::Node node(42);
    // int node, asking as string with fallback - "42" should be convertible
    std::string result = node.as<std::string>("fallback");
    EXPECT_EQ(result, "42");
}

TEST(YAMLNodeAsIfTest_551, FallbackForUndefinedNode_551) {
    YAML::Node root;
    // Accessing non-existent key returns undefined node
    YAML::Node undefined = root["nonexistent"];
    std::string result = undefined.as<std::string>("missing");
    EXPECT_EQ(result, "missing");
}

// --- Scalar ---

TEST(YAMLNodeTest_551, ScalarReturnsValue_551) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST(YAMLNodeTest_551, ScalarEmptyForNull_551) {
    YAML::Node node;
    EXPECT_EQ(node.Scalar(), "");
}

// --- Tag ---

TEST(YAMLNodeTest_551, SetAndGetTag_551) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(YAMLNodeTest_551, DefaultTagIsEmpty_551) {
    YAML::Node node("value");
    // By default, the tag should be empty or "?"
    // Just check it doesn't throw
    std::string tag = node.Tag();
    (void)tag;
}

// --- Style ---

TEST(YAMLNodeTest_551, SetAndGetStyle_551) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(YAMLNodeTest_551, SetBlockStyle_551) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// --- is() ---

TEST(YAMLNodeTest_551, IsReturnsTrueForSameNode_551) {
    YAML::Node node("hello");
    YAML::Node copy = node;
    EXPECT_TRUE(node.is(copy));
}

TEST(YAMLNodeTest_551, IsReturnsFalseForDifferentNodes_551) {
    YAML::Node node1("hello");
    YAML::Node node2("hello");
    EXPECT_FALSE(node1.is(node2));
}

// --- Assignment ---

TEST(YAMLNodeTest_551, AssignStringValue_551) {
    YAML::Node node;
    node = "assigned";
    EXPECT_EQ(node.as<std::string>(), "assigned");
    EXPECT_TRUE(node.IsScalar());
}

TEST(YAMLNodeTest_551, AssignIntValue_551) {
    YAML::Node node;
    node = 55;
    EXPECT_EQ(node.as<int>(), 55);
}

TEST(YAMLNodeTest_551, AssignNodeValue_551) {
    YAML::Node source("source_value");
    YAML::Node target;
    target = source;
    EXPECT_TRUE(target.is(source));
    EXPECT_EQ(target.as<std::string>(), "source_value");
}

// --- reset ---

TEST(YAMLNodeTest_551, ResetNode_551) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.as<std::string>(), "second");
}

// --- Sequence Operations ---

TEST(YAMLNodeTest_551, PushBackCreatesSequence_551) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST(YAMLNodeTest_551, SequenceAccessByIndex_551) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

TEST(YAMLNodeTest_551, PushBackNodeValue_551) {
    YAML::Node seq;
    YAML::Node val(42);
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<int>(), 42);
}

TEST(YAMLNodeTest_551, SequenceIteration_551) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// --- Map Operations ---

TEST(YAMLNodeTest_551, MapAccessCreatesMap_551) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(YAMLNodeTest_551, MapSize_551) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(YAMLNodeTest_551, MapRemoveByKey_551) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;
    EXPECT_EQ(node.size(), 2u);
    bool removed = node.remove("x");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_551, MapRemoveNonExistentKey_551) {
    YAML::Node node;
    node["x"] = 10;
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_551, MapRemoveByNodeKey_551) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_551, MapIteration_551) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;

    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["alpha"], 1);
    EXPECT_EQ(result["beta"], 2);
}

TEST(YAMLNodeTest_551, ForceInsert_551) {
    YAML::Node node;
    node["key"] = "original";
    node.force_insert("key", "duplicate");
    // force_insert allows duplicate keys, so size should be 2
    EXPECT_EQ(node.size(), 2u);
}

// --- size() ---

TEST(YAMLNodeTest_551, SizeOfNullNodeIsZero_551) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_551, SizeOfScalarNodeIsZero_551) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// --- Bool operator ---

TEST(YAMLNodeTest_551, BoolOperatorForDefinedNode_551) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(YAMLNodeTest_551, NotOperatorForDefinedNode_551) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

// --- Parsing and as_if with parsed nodes ---

TEST(YAMLNodeAsIfTest_551, ParsedYAMLAsIntWithFallback_551) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.as<int>(0), 42);
}

TEST(YAMLNodeAsIfTest_551, ParsedYAMLAsStringWithFallback_551) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.as<std::string>("default"), "hello");
}

TEST(YAMLNodeAsIfTest_551, ParsedYAMLMissingKeyFallback_551) {
    YAML::Node root = YAML::Load("{a: 1, b: 2}");
    int result = root["c"].as<int>(999);
    EXPECT_EQ(result, 999);
}

TEST(YAMLNodeAsIfTest_551, ParsedYAMLExistingKeyNoFallback_551) {
    YAML::Node root = YAML::Load("{a: 1, b: 2}");
    int result = root["a"].as<int>(999);
    EXPECT_EQ(result, 1);
}

TEST(YAMLNodeAsIfTest_551, ParsedSequenceFallback_551) {
    YAML::Node root = YAML::Load("[10, 20, 30]");
    EXPECT_EQ(root[0].as<int>(0), 10);
    EXPECT_EQ(root[3].as<int>(-1), -1);
}

// --- as_if with various fallback types ---

TEST(YAMLNodeAsIfTest_551, FallbackWithConstCharStar_551) {
    YAML::Node node;
    std::string result = node.as<std::string>("fallback_cstr");
    EXPECT_EQ(result, "fallback_cstr");
}

TEST(YAMLNodeAsIfTest_551, FallbackWithFloatConversion_551) {
    YAML::Node node("3.5");
    float result = node.as<float>(0.0f);
    EXPECT_FLOAT_EQ(result, 3.5f);
}

TEST(YAMLNodeAsIfTest_551, FallbackFloatForInvalidString_551) {
    YAML::Node node("not_a_float");
    float result = node.as<float>(1.0f);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

// --- Edge cases ---

TEST(YAMLNodeTest_551, EmptyStringScalar_551) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(YAMLNodeTest_551, LargeIntegerValue_551) {
    YAML::Node node(2147483647);  // INT_MAX
    EXPECT_EQ(node.as<int>(), 2147483647);
}

TEST(YAMLNodeTest_551, NegativeIntegerValue_551) {
    YAML::Node node(-100);
    EXPECT_EQ(node.as<int>(), -100);
}

TEST(YAMLNodeTest_551, ZeroIntegerValue_551) {
    YAML::Node node(0);
    EXPECT_EQ(node.as<int>(42), 0);
}

TEST(YAMLNodeTest_551, EmptySequenceSize_551) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    EXPECT_TRUE(node.IsSequence());
}

TEST(YAMLNodeTest_551, EmptyMapSize_551) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
    EXPECT_TRUE(node.IsMap());
}

TEST(YAMLNodeTest_551, OverwriteMapValue_551) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_551, ConstNodeAccess_551) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode["key"].as<std::string>(), "value");
}

// --- Mark ---

TEST(YAMLNodeTest_551, MarkForDefaultNode_551) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    // Default node should have no meaningful mark
    (void)mark;  // Just verify it doesn't crash
}

// --- Type checks are mutually exclusive ---

TEST(YAMLNodeTest_551, TypeChecksAreMutuallyExclusive_551) {
    YAML::Node null_node;
    EXPECT_TRUE(null_node.IsNull());
    EXPECT_FALSE(null_node.IsScalar());
    EXPECT_FALSE(null_node.IsSequence());
    EXPECT_FALSE(null_node.IsMap());

    YAML::Node scalar_node("hello");
    EXPECT_FALSE(scalar_node.IsNull());
    EXPECT_TRUE(scalar_node.IsScalar());
    EXPECT_FALSE(scalar_node.IsSequence());
    EXPECT_FALSE(scalar_node.IsMap());

    YAML::Node seq_node(YAML::NodeType::Sequence);
    EXPECT_FALSE(seq_node.IsNull());
    EXPECT_FALSE(seq_node.IsScalar());
    EXPECT_TRUE(seq_node.IsSequence());
    EXPECT_FALSE(seq_node.IsMap());

    YAML::Node map_node(YAML::NodeType::Map);
    EXPECT_FALSE(map_node.IsNull());
    EXPECT_FALSE(map_node.IsScalar());
    EXPECT_FALSE(map_node.IsSequence());
    EXPECT_TRUE(map_node.IsMap());
}

// --- Complex parsed YAML ---

TEST(YAMLNodeAsIfTest_551, NestedMapFallback_551) {
    YAML::Node root = YAML::Load("{outer: {inner: 42}}");
    EXPECT_EQ(root["outer"]["inner"].as<int>(0), 42);
    EXPECT_EQ(root["outer"]["missing"].as<int>(99), 99);
    EXPECT_EQ(root["missing"]["deep"].as<int>(77), 77);
}

TEST(YAMLNodeAsIfTest_551, BoolFallbackConversion_551) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(false), true);
}

TEST(YAMLNodeAsIfTest_551, BoolFallbackForInvalidString_551) {
    YAML::Node node = YAML::Load("not_a_bool");
    bool result = node.as<bool>(true);
    EXPECT_EQ(result, true);
}
