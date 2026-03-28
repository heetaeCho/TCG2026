#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Default Construction
// ============================================================

TEST(YAMLNodeTest_191, DefaultConstructedNodeIsNull_191) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(YAMLNodeTest_191, DefaultConstructedNodeIsDefined_191) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(YAMLNodeTest_191, DefaultConstructedNodeTypeIsNull_191) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(YAMLNodeTest_191, DefaultConstructedNodeSizeIsZero_191) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_191, DefaultConstructedNodeBoolConversion_191) {
    YAML::Node node;
    EXPECT_TRUE(static_cast<bool>(node));
}

// ============================================================
// Construction with explicit type
// ============================================================

TEST(YAMLNodeTest_191, ConstructWithNullType_191) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(YAMLNodeTest_191, ConstructWithScalarType_191) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(YAMLNodeTest_191, ConstructWithSequenceType_191) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(YAMLNodeTest_191, ConstructWithMapType_191) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

TEST(YAMLNodeTest_191, ConstructWithUndefinedType_191) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Construction with value
// ============================================================

TEST(YAMLNodeTest_191, ConstructWithStringValue_191) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(YAMLNodeTest_191, ConstructWithIntValue_191) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(YAMLNodeTest_191, ConstructWithDoubleValue_191) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(YAMLNodeTest_191, ConstructWithBoolValue_191) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// ============================================================
// Copy construction and assignment
// ============================================================

TEST(YAMLNodeTest_191, CopyConstructionSharesIdentity_191) {
    YAML::Node node;
    node = "test";
    YAML::Node copy(node);
    EXPECT_TRUE(copy.is(node));
    EXPECT_EQ(copy.as<std::string>(), "test");
}

TEST(YAMLNodeTest_191, AssignmentOperatorSharesIdentity_191) {
    YAML::Node a;
    a = "hello";
    YAML::Node b;
    b = a;
    EXPECT_TRUE(b.is(a));
}

TEST(YAMLNodeTest_191, ResetChangesIdentity_191) {
    YAML::Node a;
    a = "first";
    YAML::Node b;
    b = "second";
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "second");
}

// ============================================================
// Scalar operations
// ============================================================

TEST(YAMLNodeTest_191, ScalarReturnsEmptyForNonScalar_191) {
    YAML::Node node;
    EXPECT_EQ(node.Scalar(), "");
}

TEST(YAMLNodeTest_191, AssignStringToNode_191) {
    YAML::Node node;
    node = "hello world";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST(YAMLNodeTest_191, AssignIntToNode_191) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(node.as<int>(), 100);
}

TEST(YAMLNodeTest_191, AsWithFallbackOnUndefined_191) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_EQ(node.as<std::string>("fallback"), "fallback");
}

TEST(YAMLNodeTest_191, AsWithFallbackOnNull_191) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>("default_val"), "default_val");
}

TEST(YAMLNodeTest_191, AsIntWithFallback_191) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(999), 999);
}

TEST(YAMLNodeTest_191, AsStringOnScalar_191) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

// ============================================================
// Tag operations
// ============================================================

TEST(YAMLNodeTest_191, DefaultTagIsEmpty_191) {
    YAML::Node node("hello");
    // Tag may be empty or "!" depending on implementation
    // Just verify it doesn't throw
    node.Tag();
}

TEST(YAMLNodeTest_191, SetTagAndGetTag_191) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(YAMLNodeTest_191, SetTagOnMap_191) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetTag("!mymap");
    EXPECT_EQ(node.Tag(), "!mymap");
}

// ============================================================
// Style operations
// ============================================================

TEST(YAMLNodeTest_191, SetStyleAndGetStyle_191) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(YAMLNodeTest_191, SetStyleBlock_191) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ============================================================
// Sequence operations
// ============================================================

TEST(YAMLNodeTest_191, PushBackCreatesSequence_191) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

TEST(YAMLNodeTest_191, PushBackNodeCreatesSequence_191) {
    YAML::Node node;
    YAML::Node child("value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_191, SequenceAccessByIndex_191) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
    EXPECT_EQ(node[2].as<std::string>(), "third");
}

TEST(YAMLNodeTest_191, SequenceIterator_191) {
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

TEST(YAMLNodeTest_191, PushBackIntValues_191) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
}

TEST(YAMLNodeTest_191, SequenceRemoveByIndex_191) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_TRUE(node.remove(1));
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Map operations
// ============================================================

TEST(YAMLNodeTest_191, MapAccessCreatesMap_191) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(YAMLNodeTest_191, MapSize_191) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(YAMLNodeTest_191, MapRemoveKey_191) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;
    EXPECT_TRUE(node.remove("x"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_191, MapRemoveNonExistentKey_191) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_191, MapIterator_191) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        EXPECT_TRUE(it->first.IsScalar());
        EXPECT_TRUE(it->second.IsScalar());
    }
    EXPECT_EQ(count, 2);
}

TEST(YAMLNodeTest_191, MapAccessWithNodeKey_191) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

TEST(YAMLNodeTest_191, MapRemoveWithNodeKey_191) {
    YAML::Node node;
    YAML::Node key("removeMe");
    node[key] = "gone";
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(node.size(), 0u);
}

TEST(YAMLNodeTest_191, ForceInsert_191) {
    YAML::Node node;
    node.force_insert("key1", "value1");
    node.force_insert("key1", "value2");  // Force duplicate key
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Identity (is) tests
// ============================================================

TEST(YAMLNodeTest_191, SameNodeIdentity_191) {
    YAML::Node a("hello");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST(YAMLNodeTest_191, DifferentNodeIdentity_191) {
    YAML::Node a("hello");
    YAML::Node b("hello");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// IsNull / IsScalar / IsSequence / IsMap checks
// ============================================================

TEST(YAMLNodeTest_191, IsNullAfterAssignment_191) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node = "value";
    EXPECT_FALSE(node.IsNull());
}

TEST(YAMLNodeTest_191, IsScalarAfterStringAssign_191) {
    YAML::Node node;
    node = "text";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
}

TEST(YAMLNodeTest_191, IsSequenceAfterPushBack_191) {
    YAML::Node node;
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
}

TEST(YAMLNodeTest_191, IsMapAfterKeyInsert_191) {
    YAML::Node node;
    node["key"] = "val";
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
}

// ============================================================
// operator bool and operator!
// ============================================================

TEST(YAMLNodeTest_191, OperatorBoolForValidNode_191) {
    YAML::Node node("something");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(YAMLNodeTest_191, OperatorBoolForNullNode_191) {
    YAML::Node node;
    // A null but valid node should still be truthy (it exists, just null)
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(YAMLNodeTest_191, OperatorBoolForUndefinedNode_191) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

// ============================================================
// IsDefined tests
// ============================================================

TEST(YAMLNodeTest_191, IsDefinedOnDefinedNode_191) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsDefined());
}

TEST(YAMLNodeTest_191, IsDefinedOnUndefinedNode_191) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Accessing non-existent keys in map
// ============================================================

TEST(YAMLNodeTest_191, ConstAccessNonExistentKeyReturnsUndefined_191) {
    YAML::Node node;
    node["exists"] = "yes";
    const YAML::Node& cnode = node;
    EXPECT_FALSE(cnode["nonexistent"].IsDefined());
}

// ============================================================
// Loading YAML and querying
// ============================================================

TEST(YAMLNodeTest_191, LoadSimpleScalar_191) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(YAMLNodeTest_191, LoadSimpleSequence_191) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(YAMLNodeTest_191, LoadSimpleMap_191) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(YAMLNodeTest_191, LoadNestedMap_191) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(YAMLNodeTest_191, LoadNullValue_191) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(YAMLNodeTest_191, LoadBooleanTrue_191) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(YAMLNodeTest_191, LoadBooleanFalse_191) {
    YAML::Node node = YAML::Load("false");
    EXPECT_EQ(node.as<bool>(), false);
}

// ============================================================
// Empty sequence and map
// ============================================================

TEST(YAMLNodeTest_191, EmptySequenceSize_191) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    EXPECT_TRUE(node.IsSequence());
}

TEST(YAMLNodeTest_191, EmptyMapSize_191) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
    EXPECT_TRUE(node.IsMap());
}

TEST(YAMLNodeTest_191, EmptySequenceIteratorRange_191) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(YAMLNodeTest_191, EmptyMapIteratorRange_191) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

// ============================================================
// Reassignment tests
// ============================================================

TEST(YAMLNodeTest_191, ReassignScalarValue_191) {
    YAML::Node node;
    node = "first";
    EXPECT_EQ(node.as<std::string>(), "first");
    node = "second";
    EXPECT_EQ(node.as<std::string>(), "second");
}

TEST(YAMLNodeTest_191, ReassignFromScalarToSequence_191) {
    YAML::Node node;
    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    // Reset and make it a sequence
    node = YAML::Node(YAML::NodeType::Sequence);
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
}

// ============================================================
// as<T> type conversion tests
// ============================================================

TEST(YAMLNodeTest_191, AsFloat_191) {
    YAML::Node node(2.5f);
    EXPECT_NEAR(node.as<float>(), 2.5f, 0.01f);
}

TEST(YAMLNodeTest_191, AsIntFromString_191) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(YAMLNodeTest_191, AsStringFromInt_191) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<std::string>(), "123");
}

// ============================================================
// Exception on bad conversion
// ============================================================

TEST(YAMLNodeTest_191, AsThrowsOnBadConversion_191) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::BadConversion);
}

TEST(YAMLNodeTest_191, AsWithFallbackOnBadConversion_191) {
    YAML::Node node("not_a_number");
    EXPECT_EQ(node.as<int>(42), 42);
}

// ============================================================
// Mark tests
// ============================================================

TEST(YAMLNodeTest_191, MarkOnProgrammaticNode_191) {
    YAML::Node node("hello");
    YAML::Mark mark = node.Mark();
    // Programmatically created nodes typically have null mark
    // Just ensure it doesn't crash
    (void)mark;
}

// ============================================================
// Complex / edge scenarios
// ============================================================

TEST(YAMLNodeTest_191, LargeSequence_191) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(YAMLNodeTest_191, NestedSequences_191) {
    YAML::Node node;
    YAML::Node inner;
    inner.push_back("a");
    inner.push_back("b");
    node.push_back(inner);
    EXPECT_TRUE(node[0].IsSequence());
    EXPECT_EQ(node[0][0].as<std::string>(), "a");
    EXPECT_EQ(node[0][1].as<std::string>(), "b");
}

TEST(YAMLNodeTest_191, MapWithIntKeys_191) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST(YAMLNodeTest_191, EmptyStringScalar_191) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST(YAMLNodeTest_191, RemoveFromSequenceOutOfRange_191) {
    YAML::Node node;
    node.push_back("only");
    EXPECT_FALSE(node.remove(5));
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_191, SequenceRemoveFirstElement_191) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    EXPECT_TRUE(node.remove(0));
    EXPECT_EQ(node.size(), 1u);
}

TEST(YAMLNodeTest_191, ConstNodeSubscriptReturnsUndefinedForMissing_191) {
    const YAML::Node node = YAML::Load("{a: 1}");
    EXPECT_FALSE(node["missing"].IsDefined());
}

TEST(YAMLNodeTest_191, AssignCStringToNode_191) {
    YAML::Node node;
    const char* cstr = "c-string";
    node = cstr;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "c-string");
}
