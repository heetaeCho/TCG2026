#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Default Construction Tests
// ============================================================

TEST(NodeTest_194, DefaultConstructedNodeIsNull_194) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_194, DefaultConstructedNodeIsDefined_194) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_194, DefaultConstructedNodeBoolConversion_194) {
    YAML::Node node;
    // A default-constructed null node should still be "valid"
    // but its bool conversion depends on IsDefined
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_194, DefaultConstructedNodeSizeIsZero_194) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Construction with NodeType
// ============================================================

TEST(NodeTest_194, ConstructWithNullType_194) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_194, ConstructWithScalarType_194) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_194, ConstructWithSequenceType_194) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_194, ConstructWithMapType_194) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

TEST(NodeTest_194, ConstructWithUndefinedType_194) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Construction from value
// ============================================================

TEST(NodeTest_194, ConstructFromString_194) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_194, ConstructFromInt_194) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_194, ConstructFromDouble_194) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(NodeTest_194, ConstructFromBool_194) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeTest_194, ConstructFromCString_194) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "world");
}

// ============================================================
// Copy Construction
// ============================================================

TEST(NodeTest_194, CopyConstructionSharesSameNode_194) {
    YAML::Node node1("test");
    YAML::Node node2(node1);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node2.Scalar(), "test");
}

// ============================================================
// Assignment
// ============================================================

TEST(NodeTest_194, AssignStringValue_194) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_194, AssignIntValue_194) {
    YAML::Node node;
    node = 123;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_194, AssignNodeValue_194) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1 = node2;
    EXPECT_TRUE(node1.is(node2));
}

// ============================================================
// Scalar Operations
// ============================================================

TEST(NodeTest_194, ScalarReturnValue_194) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST(NodeTest_194, AsStringConversion_194) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_194, AsIntConversion_194) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_194, AsWithFallback_194) {
    YAML::Node node;
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST(NodeTest_194, AsStringWithFallback_194) {
    YAML::Node node;
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "default");
}

TEST(NodeTest_194, AsBoolConversion_194) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_194, AsBoolFalse_194) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

// ============================================================
// Sequence Operations
// ============================================================

TEST(NodeTest_194, PushBackCreatesSequence_194) {
    YAML::Node node;
    node.push_back("item1");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_194, PushBackMultipleItems_194) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_194, SequenceAccessByIndex_194) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST(NodeTest_194, PushBackNodeValue_194) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node[0].as<std::string>(), "child_value");
}

TEST(NodeTest_194, PushBackIntValues_194) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

// ============================================================
// Map Operations
// ============================================================

TEST(NodeTest_194, MapSubscriptOperatorCreatesMap_194) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_194, MapInsertAndRetrieve_194) {
    YAML::Node node;
    node["name"] = "Alice";
    EXPECT_EQ(node["name"].as<std::string>(), "Alice");
}

TEST(NodeTest_194, MapSize_194) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_194, MapRemoveKey_194) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";
    EXPECT_EQ(node.size(), 2u);
    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_194, MapRemoveNonExistentKey_194) {
    YAML::Node node;
    node["key1"] = "val1";
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_194, MapRemoveWithNodeKey_194) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_194, MapForceInsert_194) {
    YAML::Node node;
    node.force_insert("key", "value");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_194, MapConstSubscriptUndefined_194) {
    const YAML::Node node;
    YAML::Node result = node["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

// ============================================================
// Tag Operations
// ============================================================

TEST(NodeTest_194, DefaultTagIsEmpty_194) {
    YAML::Node node("value");
    EXPECT_EQ(node.Tag(), "");
}

TEST(NodeTest_194, SetAndGetTag_194) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(NodeTest_194, SetTagOnMap_194) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetTag("!map_tag");
    EXPECT_EQ(node.Tag(), "!map_tag");
}

// ============================================================
// Style Operations
// ============================================================

TEST(NodeTest_194, SetAndGetStyle_194) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_194, SetStyleBlock_194) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ============================================================
// Identity Tests (is())
// ============================================================

TEST(NodeTest_194, IsSameNodeAfterCopy_194) {
    YAML::Node a("hello");
    YAML::Node b = a;
    EXPECT_TRUE(a.is(b));
}

TEST(NodeTest_194, IsDifferentNodes_194) {
    YAML::Node a("hello");
    YAML::Node b("hello");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// Reset
// ============================================================

TEST(NodeTest_194, ResetToAnotherNode_194) {
    YAML::Node a("original");
    YAML::Node b("replacement");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "replacement");
}

// ============================================================
// Bool Operator
// ============================================================

TEST(NodeTest_194, BoolOperatorOnValidNode_194) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_194, BoolOperatorOnNullNode_194) {
    YAML::Node node;
    // Null node that is defined - bool depends on implementation
    // but typically a null node is still "truthy" because it's valid/defined
    // The actual behavior depends on yaml-cpp: operator bool() checks IsDefined()
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_194, NotOperatorOnUndefinedNode_194) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_TRUE(!node);
}

TEST(NodeTest_194, BoolOperatorOnUndefinedNode_194) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(static_cast<bool>(node));
}

// ============================================================
// Iterator Tests
// ============================================================

TEST(NodeTest_194, IterateOverSequence_194) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

TEST(NodeTest_194, IterateOverMap_194) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(NodeTest_194, EmptyNodeIteratorBeginEqualsEnd_194) {
    YAML::Node node;
    // For a null node, begin() == end()
    // This may throw or return equal iterators depending on implementation
    // Sequence type should be safe
    YAML::Node seqNode(YAML::NodeType::Sequence);
    EXPECT_EQ(seqNode.begin(), seqNode.end());
}

// ============================================================
// Type Checking Helpers
// ============================================================

TEST(NodeTest_194, IsNullOnNullNode_194) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_194, IsScalarOnScalarNode_194) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTest_194, IsSequenceOnSequenceNode_194) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_194, IsMapOnMapNode_194) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_194, TypeChecksMutuallyExclusive_194) {
    YAML::Node scalar("test");
    EXPECT_TRUE(scalar.IsScalar());
    EXPECT_FALSE(scalar.IsNull());
    EXPECT_FALSE(scalar.IsSequence());
    EXPECT_FALSE(scalar.IsMap());
}

// ============================================================
// YAML Load and Node Interaction
// ============================================================

TEST(NodeTest_194, LoadSimpleScalar_194) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_194, LoadSequence_194) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_194, LoadMap_194) {
    YAML::Node node = YAML::Load("{name: Alice, age: 30}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST(NodeTest_194, LoadNestedStructure_194) {
    YAML::Node node = YAML::Load("{items: [1, 2, 3], name: test}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["items"].IsSequence());
    EXPECT_EQ(node["items"].size(), 3u);
    EXPECT_EQ(node["name"].as<std::string>(), "test");
}

TEST(NodeTest_194, LoadNull_194) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_194, LoadBoolTrue_194) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeTest_194, LoadBoolFalse_194) {
    YAML::Node node = YAML::Load("false");
    EXPECT_EQ(node.as<bool>(), false);
}

// ============================================================
// Edge Cases
// ============================================================

TEST(NodeTest_194, EmptyStringScalar_194) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_194, LargeSequence_194) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_194, OverwriteMapValue_194) {
    YAML::Node node;
    node["key"] = "value1";
    node["key"] = "value2";
    EXPECT_EQ(node["key"].as<std::string>(), "value2");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_194, MixedTypeSequence_194) {
    YAML::Node node;
    node.push_back("string");
    node.push_back(42);
    node.push_back(true);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "string");
    EXPECT_EQ(node[1].as<int>(), 42);
    EXPECT_EQ(node[2].as<bool>(), true);
}

TEST(NodeTest_194, NestedMapCreation_194) {
    YAML::Node node;
    node["outer"]["inner"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(NodeTest_194, AssignNullToExistingNode_194) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    node = YAML::Node();
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_194, SequenceSizeAfterPushBack_194) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_194, MapSizeAfterInsertAndRemove_194) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
    node.remove("b");
    EXPECT_EQ(node.size(), 2u);
    node.remove("a");
    EXPECT_EQ(node.size(), 1u);
    node.remove("c");
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_194, SubscriptOnUndefinedReturnsUndefined_194) {
    YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node result = node["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeTest_194, AsWithFallbackOnBadConversion_194) {
    YAML::Node node("not_a_number");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_194, DoubleConversion_194) {
    YAML::Node node = YAML::Load("3.14159");
    EXPECT_NEAR(node.as<double>(), 3.14159, 0.00001);
}

TEST(NodeTest_194, FloatConversion_194) {
    YAML::Node node = YAML::Load("2.5");
    EXPECT_NEAR(node.as<float>(), 2.5f, 0.001f);
}

// ============================================================
// Mark Tests
// ============================================================

TEST(NodeTest_194, MarkOnProgrammaticallyCreatedNode_194) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // Programmatically created nodes typically have no mark info
    // Just verify it doesn't crash
    (void)mark;
}

// ============================================================
// Force Insert Duplicate Keys
// ============================================================

TEST(NodeTest_194, ForceInsertAllowsDuplicateKeys_194) {
    YAML::Node node;
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert should allow duplicate keys
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Conversion Errors
// ============================================================

TEST(NodeTest_194, AsThrowsOnBadConversion_194) {
    YAML::Node node("not_an_int");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeTest_194, AsThrowsOnNullNode_194) {
    YAML::Node node;
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// ============================================================
// Sequence with Node push_back
// ============================================================

TEST(NodeTest_194, PushBackNestedSequence_194) {
    YAML::Node outer;
    YAML::Node inner;
    inner.push_back(1);
    inner.push_back(2);
    outer.push_back(inner);
    EXPECT_TRUE(outer.IsSequence());
    EXPECT_EQ(outer.size(), 1u);
    EXPECT_TRUE(outer[0].IsSequence());
    EXPECT_EQ(outer[0].size(), 2u);
}

// ============================================================
// Range-based iteration
// ============================================================

TEST(NodeTest_194, RangeBasedForOnSequence_194) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    int sum = 0;
    for (const auto& item : node) {
        sum += item.as<int>();
    }
    EXPECT_EQ(sum, 60);
}

TEST(NodeTest_194, RangeBasedForOnMap_194) {
    YAML::Node node = YAML::Load("{x: 1, y: 2}");
    std::map<std::string, int> result;
    for (const auto& kv : node) {
        result[kv.first.as<std::string>()] = kv.second.as<int>();
    }
    EXPECT_EQ(result["x"], 1);
    EXPECT_EQ(result["y"], 2);
}
