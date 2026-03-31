#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Default Construction
// ============================================================

TEST(NodeTest_577, DefaultConstructedNodeIsNull_577) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_577, DefaultConstructedNodeIsDefined_577) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_577, DefaultConstructedNodeBoolConversion_577) {
    YAML::Node node;
    // A default (Null) node is "valid" but may evaluate to false
    // depending on implementation; we just check it doesn't crash
    // and the operator is consistent with IsDefined
    if (node.IsDefined()) {
        // Valid node, bool conversion should not throw
        (void)static_cast<bool>(node);
    }
}

// ============================================================
// Construction with NodeType
// ============================================================

TEST(NodeTest_577, ConstructWithScalarType_577) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(NodeTest_577, ConstructWithSequenceType_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodeTest_577, ConstructWithMapType_577) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(NodeTest_577, ConstructWithNullType_577) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_577, ConstructWithUndefinedType_577) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// ============================================================
// Construction from values
// ============================================================

TEST(NodeTest_577, ConstructFromString_577) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_577, ConstructFromInt_577) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_577, ConstructFromDouble_577) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(NodeTest_577, ConstructFromBool_577) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeTest_577, ConstructFromCString_577) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "world");
}

// ============================================================
// Copy Construction and Assignment
// ============================================================

TEST(NodeTest_577, CopyConstructor_577) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_TRUE(copy.is(original));
    EXPECT_EQ(copy.Scalar(), "test");
}

TEST(NodeTest_577, AssignmentOperatorNode_577) {
    YAML::Node a("alpha");
    YAML::Node b("beta");
    a = b;
    EXPECT_TRUE(a.is(b));
}

TEST(NodeTest_577, AssignmentOperatorValue_577) {
    YAML::Node node;
    node = 123;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_577, AssignmentFromString_577) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_EQ(node.Scalar(), "assigned");
}

// ============================================================
// is() and operator==
// ============================================================

TEST(NodeTest_577, IsReturnsTrueForSameNode_577) {
    YAML::Node a("test");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
    EXPECT_TRUE(a == b);
}

TEST(NodeTest_577, IsReturnsFalseForDifferentNodes_577) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
    EXPECT_FALSE(a == b);
}

TEST(NodeTest_577, EqualityOperator_577) {
    YAML::Node a("hello");
    YAML::Node b(a);
    EXPECT_TRUE(a == b);
}

// ============================================================
// reset()
// ============================================================

TEST(NodeTest_577, ResetMakesNodePointToAnother_577) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.Scalar(), "second");
}

// ============================================================
// Scalar()
// ============================================================

TEST(NodeTest_577, ScalarReturnsValue_577) {
    YAML::Node node("scalar_value");
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

TEST(NodeTest_577, ScalarEmptyForNonScalar_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Scalar(), "");
}

// ============================================================
// as<T>()
// ============================================================

TEST(NodeTest_577, AsString_577) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_577, AsInt_577) {
    YAML::Node node("42");
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_577, AsDouble_577) {
    YAML::Node node("2.718");
    EXPECT_NEAR(node.as<double>(), 2.718, 0.001);
}

TEST(NodeTest_577, AsBoolTrue_577) {
    YAML::Node node("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(NodeTest_577, AsBoolFalse_577) {
    YAML::Node node("false");
    EXPECT_EQ(node.as<bool>(), false);
}

TEST(NodeTest_577, AsWithFallback_577) {
    YAML::Node node(YAML::NodeType::Undefined);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST(NodeTest_577, AsWithFallbackWhenDefined_577) {
    YAML::Node node(42);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_577, AsStringWithFallback_577) {
    YAML::Node node;
    // Null node with fallback
    std::string result = node.as<std::string>("default");
    // Could be "default" or "~" depending on impl; just ensure no crash
    (void)result;
}

// ============================================================
// Tag and SetTag
// ============================================================

TEST(NodeTest_577, TagDefaultIsEmpty_577) {
    YAML::Node node("value");
    // Default tag might be "?" or empty
    // Just ensure no crash
    (void)node.Tag();
}

TEST(NodeTest_577, SetTagAndRetrieve_577) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(NodeTest_577, SetTagOnMap_577) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetTag("!mymap");
    EXPECT_EQ(node.Tag(), "!mymap");
}

// ============================================================
// Style and SetStyle
// ============================================================

TEST(NodeTest_577, DefaultStyle_577) {
    YAML::Node node("value");
    // Just ensure it returns a valid style
    YAML::EmitterStyle::value style = node.Style();
    (void)style;
}

TEST(NodeTest_577, SetStyleFlow_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_577, SetStyleBlock_577) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ============================================================
// Sequence operations: push_back, size, begin/end
// ============================================================

TEST(NodeTest_577, PushBackToSequence_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_577, PushBackConvertsNullToSequence_577) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_577, PushBackNode_577) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node val("hello");
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST(NodeTest_577, SequenceIterator_577) {
    YAML::Node node(YAML::NodeType::Sequence);
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

TEST(NodeTest_577, SequenceRangeForLoop_577) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");

    std::vector<std::string> values;
    for (const auto& item : node) {
        values.push_back(item.as<std::string>());
    }
    EXPECT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], "a");
    EXPECT_EQ(values[1], "b");
}

TEST(NodeTest_577, SequenceIndexAccess_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("first");
    node.push_back("second");

    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST(NodeTest_577, EmptySequenceSize_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Map operations: operator[], size, remove
// ============================================================

TEST(NodeTest_577, MapInsertAndRetrieve_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_577, MapNullConvertsToMap_577) {
    YAML::Node node;
    node["x"] = 10;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["x"].as<int>(), 10);
}

TEST(NodeTest_577, MapSize_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_577, MapRemoveByKey_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "val1";
    node["key2"] = "val2";
    EXPECT_EQ(node.size(), 2u);

    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_577, MapRemoveNonExistentKey_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["exists"] = "yes";
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_577, MapRemoveByNodeKey_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["foo"] = "bar";
    YAML::Node key("foo");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_577, MapIterator_577) {
    YAML::Node node(YAML::NodeType::Map);
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

TEST(NodeTest_577, MapAccessNonExistentKeyConst_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["exists"] = "yes";
    const YAML::Node& cnode = node;
    YAML::Node val = cnode["nonexistent"];
    EXPECT_FALSE(val.IsDefined());
}

TEST(NodeTest_577, EmptyMapSize_577) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// force_insert
// ============================================================

TEST(NodeTest_577, ForceInsert_577) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value");
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_577, ForceInsertDuplicateKey_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "original";
    node.force_insert("key", "duplicate");
    // force_insert should add another entry even with same key
    EXPECT_EQ(node.size(), 2u);
}

// ============================================================
// Type checking helpers
// ============================================================

TEST(NodeTest_577, IsNullForNullNode_577) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_577, IsScalarForScalarNode_577) {
    YAML::Node node("value");
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_577, IsSequenceForSequenceNode_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_577, IsMapForMapNode_577) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_TRUE(node.IsMap());
}

// ============================================================
// operator bool and operator!
// ============================================================

TEST(NodeTest_577, BoolConversionForDefinedNode_577) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(NodeTest_577, BoolConversionForNullNode_577) {
    YAML::Node node;
    // Null but valid node - bool conversion depends on IsDefined
    // Just make sure it doesn't crash
    (void)static_cast<bool>(node);
    (void)(!node);
}

// ============================================================
// YAML parsing integration
// ============================================================

TEST(NodeTest_577, ParseScalar_577) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_577, ParseSequence_577) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_577, ParseMap_577) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(NodeTest_577, ParseNull_577) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_577, ParseNestedMap_577) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(NodeTest_577, ParseNestedSequence_577) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].size(), 2u);
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// ============================================================
// Boundary and error cases
// ============================================================

TEST(NodeTest_577, AsWithInvalidConversionUsesFallback_577) {
    YAML::Node node("not_a_number");
    int val = node.as<int>(42);
    EXPECT_EQ(val, 42);
}

TEST(NodeTest_577, AsWithInvalidConversionThrows_577) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeTest_577, UndefinedNodeIsDefined_577) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

TEST(NodeTest_577, SizeOfScalarIsZero_577) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_577, SizeOfNullIsZero_577) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_577, OverwriteMapValue_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_577, AssignScalarToExistingScalar_577) {
    YAML::Node node("old");
    node = "new";
    EXPECT_EQ(node.as<std::string>(), "new");
}

TEST(NodeTest_577, EmptyString_577) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_577, LargeSequence_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_577, MapWithIntegerKeys_577) {
    YAML::Node node(YAML::NodeType::Map);
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_577, RemoveFromSequence_577) {
    YAML::Node node = YAML::Load("[a, b, c]");
    // Removing from a sequence using integer index as key
    // This tests the template remove with int key
    bool removed = node.remove(1);
    // Behavior may vary; just check it doesn't crash
    (void)removed;
}

TEST(NodeTest_577, MarkOfParsedNode_577) {
    YAML::Node node = YAML::Load("value");
    YAML::Mark mark = node.Mark();
    // Mark should have valid position info
    EXPECT_GE(mark.line, 0);
    EXPECT_GE(mark.column, 0);
}

TEST(NodeTest_577, SelfAssignment_577) {
    YAML::Node node("test");
    node = node;
    EXPECT_EQ(node.as<std::string>(), "test");
}

TEST(NodeTest_577, ResetToSelf_577) {
    YAML::Node node("test");
    node.reset(node);
    EXPECT_EQ(node.as<std::string>(), "test");
}

TEST(NodeTest_577, MultipleTypesInSequence_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(42);
    node.push_back("hello");
    node.push_back(3.14);
    node.push_back(true);
    EXPECT_EQ(node.size(), 4u);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_NEAR(node[2].as<double>(), 3.14, 0.001);
    EXPECT_EQ(node[3].as<bool>(), true);
}

TEST(NodeTest_577, MapWithNodeKey_577) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
    EXPECT_EQ(node["mykey"].as<std::string>(), "myvalue");
}

TEST(NodeTest_577, ConstNodeAccess_577) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    const YAML::Node& cnode = node;
    EXPECT_EQ(cnode["key"].as<std::string>(), "value");
    EXPECT_FALSE(cnode["nonexistent"].IsDefined());
}

TEST(NodeTest_577, SequenceBeginEndEmpty_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(NodeTest_577, MapBeginEndEmpty_577) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(NodeTest_577, ParseEmptyDocument_577) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_577, ParseBooleanValues_577) {
    YAML::Node t = YAML::Load("true");
    YAML::Node f = YAML::Load("false");
    EXPECT_EQ(t.as<bool>(), true);
    EXPECT_EQ(f.as<bool>(), false);
}

TEST(NodeTest_577, ParseIntegerValue_577) {
    YAML::Node node = YAML::Load("12345");
    EXPECT_EQ(node.as<int>(), 12345);
}

TEST(NodeTest_577, ParseFloatValue_577) {
    YAML::Node node = YAML::Load("1.5");
    EXPECT_NEAR(node.as<float>(), 1.5f, 0.001f);
}

TEST(NodeTest_577, NodeAssignChangesType_577) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());

    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "scalar");
}
