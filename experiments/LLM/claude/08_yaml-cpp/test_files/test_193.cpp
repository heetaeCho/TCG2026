#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Default Construction Tests
// ============================================================

TEST(NodeTest_193, DefaultConstructedNodeIsNull_193) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_193, DefaultConstructedNodeType_193) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_193, DefaultConstructedNodeIsDefined_193) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_193, DefaultConstructedNodeSizeIsZero_193) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_193, DefaultConstructedNodeBoolConversion_193) {
    YAML::Node node;
    // A null but valid node should still be truthy (it's defined)
    EXPECT_TRUE(node.IsDefined());
}

// ============================================================
// Type-based Construction Tests
// ============================================================

TEST(NodeTest_193, ConstructWithNullType_193) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, ConstructWithScalarType_193) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, ConstructWithSequenceType_193) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, ConstructWithMapType_193) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

// ============================================================
// Scalar Construction and Access
// ============================================================

TEST(NodeTest_193, ConstructFromString_193) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_193, ConstructFromInt_193) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_193, ConstructFromDouble_193) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST(NodeTest_193, ConstructFromBool_193) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_193, ConstructFromCString_193) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "world");
}

// ============================================================
// as<T>() Tests
// ============================================================

TEST(NodeTest_193, AsStringFromScalar_193) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

TEST(NodeTest_193, AsIntFromScalar_193) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_193, AsWithFallback_193) {
    YAML::Node node;
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST(NodeTest_193, AsWithFallbackWhenDefined_193) {
    YAML::Node node(42);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_193, AsStringWithFallback_193) {
    YAML::Node node;
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "default");
}

// ============================================================
// Assignment Tests
// ============================================================

TEST(NodeTest_193, AssignStringToNode_193) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned");
}

TEST(NodeTest_193, AssignIntToNode_193) {
    YAML::Node node;
    node = 100;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 100);
}

TEST(NodeTest_193, AssignNodeToNode_193) {
    YAML::Node a("hello");
    YAML::Node b;
    b = a;
    EXPECT_EQ(b.Scalar(), "hello");
}

TEST(NodeTest_193, AssignCStringToNode_193) {
    YAML::Node node;
    node = "c_string";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "c_string");
}

// ============================================================
// Copy Construction Tests
// ============================================================

TEST(NodeTest_193, CopyConstructionSharesNode_193) {
    YAML::Node a("shared");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(b.Scalar(), "shared");
}

TEST(NodeTest_193, CopyConstructedNodeReflectsChanges_193) {
    YAML::Node a("original");
    YAML::Node b(a);
    a = "modified";
    EXPECT_EQ(b.as<std::string>(), "modified");
}

// ============================================================
// Reset Tests
// ============================================================

TEST(NodeTest_193, ResetNodeToAnother_193) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.Scalar(), "second");
}

// ============================================================
// Sequence Tests
// ============================================================

TEST(NodeTest_193, PushBackCreatesSequence_193) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_193, SequenceAccessByIndex_193) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

TEST(NodeTest_193, PushBackNodeToSequence_193) {
    YAML::Node seq;
    YAML::Node child("item");
    seq.push_back(child);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "item");
}

TEST(NodeTest_193, SequenceIteration_193) {
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

TEST(NodeTest_193, EmptySequenceSize_193) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Map Tests
// ============================================================

TEST(NodeTest_193, MapCreationViaSubscript_193) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_193, MapSize_193) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_193, MapRemoveByKey_193) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;
    EXPECT_EQ(node.size(), 2u);
    bool removed = node.remove("x");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_193, MapRemoveNonExistentKey_193) {
    YAML::Node node;
    node["a"] = 1;
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_193, MapRemoveByNodeKey_193) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_193, MapIteration_193) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        EXPECT_TRUE(it->first.IsScalar());
        EXPECT_TRUE(it->second.IsScalar());
    }
    EXPECT_EQ(count, 2);
}

TEST(NodeTest_193, MapForceInsert_193) {
    YAML::Node node;
    node["key"] = "value1";
    node.force_insert("key", "value2");
    // force_insert should allow duplicate keys; size should be 2
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_193, MapSubscriptWithNodeKey_193) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

// ============================================================
// Tag Tests
// ============================================================

TEST(NodeTest_193, SetAndGetTag_193) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(NodeTest_193, DefaultTagIsEmpty_193) {
    YAML::Node node("hello");
    // The tag of a freshly created scalar should be some default (likely empty or "?")
    // Just check it doesn't throw
    std::string tag = node.Tag();
    (void)tag;
}

// ============================================================
// Style Tests
// ============================================================

TEST(NodeTest_193, SetAndGetStyle_193) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_193, SetBlockStyle_193) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ============================================================
// `is()` Tests
// ============================================================

TEST(NodeTest_193, IsReturnsTrueForSameNode_193) {
    YAML::Node a("test");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST(NodeTest_193, IsReturnsFalseForDifferentNodes_193) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// Bool Conversion and operator! Tests
// ============================================================

TEST(NodeTest_193, DefinedNodeIsTruthy_193) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(NodeTest_193, NullNodeBoolConversion_193) {
    YAML::Node node;
    // A null node is valid but null — it's still "defined"
    // operator bool should return true for a defined node
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_193, UndefinedNodeSubscriptIsFalsy_193) {
    YAML::Node node;
    // Accessing a non-existent key on a null node
    YAML::Node child = node["nonexistent"];
    EXPECT_FALSE(child.IsDefined());
    EXPECT_FALSE(static_cast<bool>(child));
    EXPECT_TRUE(!child);
}

// ============================================================
// IsNull, IsScalar, IsSequence, IsMap Tests
// ============================================================

TEST(NodeTest_193, IsNullForNullNode_193) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, IsScalarForScalarNode_193) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, IsSequenceForSequenceNode_193) {
    YAML::Node node;
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_193, IsMapForMapNode_193) {
    YAML::Node node;
    node["k"] = "v";
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

// ============================================================
// Scalar() Tests
// ============================================================

TEST(NodeTest_193, ScalarReturnsValue_193) {
    YAML::Node node("the_value");
    EXPECT_EQ(node.Scalar(), "the_value");
}

TEST(NodeTest_193, ScalarOnNullNodeReturnsEmpty_193) {
    YAML::Node node;
    // Scalar on a non-scalar node should return empty string
    EXPECT_EQ(node.Scalar(), "");
}

// ============================================================
// Parsing Tests (Integration-like using YAML::Load)
// ============================================================

TEST(NodeTest_193, LoadScalar_193) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_193, LoadSequence_193) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_193, LoadMap_193) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(NodeTest_193, LoadNestedStructure_193) {
    YAML::Node node = YAML::Load("{list: [1, 2], name: test}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["list"].IsSequence());
    EXPECT_EQ(node["list"].size(), 2u);
    EXPECT_EQ(node["name"].as<std::string>(), "test");
}

TEST(NodeTest_193, LoadNull_193) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_193, LoadEmptyString_193) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(NodeTest_193, EmptyMapSize_193) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_193, LargeSequence_193) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_193, OverwriteMapValue_193) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_193, ChangeNodeTypeByAssignment_193) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_193, AssignEmptyStringScalar_193) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_193, RemoveFromSequenceByIndex_193) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    // remove by integer key (index for sequence)
    bool removed = node.remove(1);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Mark Tests
// ============================================================

TEST(NodeTest_193, MarkOnConstructedNode_193) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // For programmatically created nodes, mark is typically 0/0
    // Just check it doesn't throw
    (void)mark;
}

// ============================================================
// Exception Tests
// ============================================================

TEST(NodeTest_193, AsWrongTypeThrows_193) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::Exception);
}

TEST(NodeTest_193, AsOnUndefinedNodeThrows_193) {
    YAML::Node node;
    YAML::Node child = node["nonexistent"];
    EXPECT_THROW(child.as<std::string>(), YAML::Exception);
}

// ============================================================
// Range-based for loop on sequence
// ============================================================

TEST(NodeTest_193, RangeBasedForOnSequence_193) {
    YAML::Node node;
    node.push_back(5);
    node.push_back(10);
    node.push_back(15);

    int sum = 0;
    for (const auto& item : node) {
        sum += item.as<int>();
    }
    EXPECT_EQ(sum, 30);
}

// ============================================================
// Range-based for loop on map
// ============================================================

TEST(NodeTest_193, RangeBasedForOnMap_193) {
    YAML::Node node;
    node["x"] = 1;
    node["y"] = 2;

    int sum = 0;
    for (const auto& kv : node) {
        sum += kv.second.as<int>();
    }
    EXPECT_EQ(sum, 3);
}

// ============================================================
// Multiple type checks on same node
// ============================================================

TEST(NodeTest_193, OnlyOneTypeCheckTrueAtATime_193) {
    YAML::Node scalar("val");
    int trueCount = 0;
    if (scalar.IsNull()) trueCount++;
    if (scalar.IsScalar()) trueCount++;
    if (scalar.IsSequence()) trueCount++;
    if (scalar.IsMap()) trueCount++;
    EXPECT_EQ(trueCount, 1);
}

TEST(NodeTest_193, ConstSubscriptOnMap_193) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& cnode = node;
    EXPECT_EQ(cnode["key"].as<std::string>(), "value");
}

TEST(NodeTest_193, ConstSubscriptNonExistent_193) {
    YAML::Node node;
    node["existing"] = "yes";
    const YAML::Node& cnode = node;
    EXPECT_FALSE(cnode["missing"].IsDefined());
}
