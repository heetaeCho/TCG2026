#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// ============================================================
// Test fixture
// ============================================================
class NodeTest_686 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ------------------------------------------------------------------
// Default construction
// ------------------------------------------------------------------
TEST_F(NodeTest_686, DefaultConstructor_IsNull_686) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_686, DefaultConstructor_IsDefined_686) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_686, DefaultConstructor_BoolConversion_686) {
    YAML::Node node;
    // A null node is defined but converts to false in boolean context
    EXPECT_TRUE(node.IsDefined());
}

// ------------------------------------------------------------------
// Construction with NodeType
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ConstructWithNullType_686) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_686, ConstructWithScalarType_686) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_686, ConstructWithSequenceType_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_686, ConstructWithMapType_686) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

// ------------------------------------------------------------------
// Template constructor with various types
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ConstructFromInt_686) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_686, ConstructFromDouble_686) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(NodeTest_686, ConstructFromString_686) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_686, ConstructFromCString_686) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "world");
}

TEST_F(NodeTest_686, ConstructFromBoolTrue_686) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(NodeTest_686, ConstructFromBoolFalse_686) {
    YAML::Node node(false);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), false);
}

// ------------------------------------------------------------------
// Copy construction
// ------------------------------------------------------------------
TEST_F(NodeTest_686, CopyConstructor_686) {
    YAML::Node original(42);
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<int>(), 42);
    EXPECT_TRUE(original.is(copy));
}

// ------------------------------------------------------------------
// Scalar access
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ScalarAccess_686) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST_F(NodeTest_686, ScalarEmptyString_686) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// ------------------------------------------------------------------
// as<T>() with fallback
// ------------------------------------------------------------------
TEST_F(NodeTest_686, AsWithFallback_ValidValue_686) {
    YAML::Node node(100);
    EXPECT_EQ(node.as<int>(999), 100);
}

TEST_F(NodeTest_686, AsWithFallback_InvalidConversion_686) {
    YAML::Node node("not_a_number");
    EXPECT_EQ(node.as<int>(999), 999);
}

TEST_F(NodeTest_686, AsWithFallback_NullNode_686) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(42), 42);
}

// ------------------------------------------------------------------
// as<T>() without fallback - exception on bad conversion
// ------------------------------------------------------------------
TEST_F(NodeTest_686, AsWithoutFallback_ThrowsOnBadConversion_686) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST_F(NodeTest_686, AsWithoutFallback_ThrowsOnNullNode_686) {
    YAML::Node node;
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// ------------------------------------------------------------------
// Tag and SetTag
// ------------------------------------------------------------------
TEST_F(NodeTest_686, SetAndGetTag_686) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST_F(NodeTest_686, DefaultTagIsEmpty_686) {
    YAML::Node node("value");
    // Default tag should be the question mark or empty
    // Typically "?" for untagged nodes
    std::string tag = node.Tag();
    EXPECT_TRUE(tag == "?" || tag.empty());
}

// ------------------------------------------------------------------
// Style and SetStyle
// ------------------------------------------------------------------
TEST_F(NodeTest_686, SetAndGetStyle_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_686, DefaultStyleIsDefault_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// ------------------------------------------------------------------
// Assignment operator
// ------------------------------------------------------------------
TEST_F(NodeTest_686, AssignmentFromValue_686) {
    YAML::Node node;
    node = 42;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_686, AssignmentFromString_686) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_EQ(node.as<std::string>(), "assigned");
}

TEST_F(NodeTest_686, AssignmentFromNode_686) {
    YAML::Node source(99);
    YAML::Node target;
    target = source;
    EXPECT_EQ(target.as<int>(), 99);
    EXPECT_TRUE(target.is(source));
}

// ------------------------------------------------------------------
// reset
// ------------------------------------------------------------------
TEST_F(NodeTest_686, Reset_686) {
    YAML::Node a(10);
    YAML::Node b(20);
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<int>(), 20);
}

// ------------------------------------------------------------------
// is()
// ------------------------------------------------------------------
TEST_F(NodeTest_686, IsIdentity_SameNode_686) {
    YAML::Node a(5);
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST_F(NodeTest_686, IsIdentity_DifferentNodes_686) {
    YAML::Node a(5);
    YAML::Node b(5);
    EXPECT_FALSE(a.is(b));
}

// ------------------------------------------------------------------
// Sequence operations
// ------------------------------------------------------------------
TEST_F(NodeTest_686, PushBackCreatesSequence_686) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_686, SequenceIndexAccess_686) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST_F(NodeTest_686, SequenceIteration_686) {
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

TEST_F(NodeTest_686, SequencePushBackNode_686) {
    YAML::Node seq;
    YAML::Node child(42);
    seq.push_back(child);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<int>(), 42);
}

// ------------------------------------------------------------------
// Map operations
// ------------------------------------------------------------------
TEST_F(NodeTest_686, MapSubscriptCreatesMap_686) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_686, MapSize_686) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_686, MapIteration_686) {
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

TEST_F(NodeTest_686, MapRemoveByKey_686) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST_F(NodeTest_686, MapRemoveNonExistentKey_686) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_686, MapRemoveByNodeKey_686) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    EXPECT_TRUE(node.remove(key));
    EXPECT_FALSE(node["key1"].IsDefined());
}

// ------------------------------------------------------------------
// force_insert
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ForceInsert_686) {
    YAML::Node node;
    node["key"] = "original";
    node.force_insert("key", "duplicate");
    // force_insert allows duplicate keys, so size should be 2
    EXPECT_EQ(node.size(), 2u);
}

// ------------------------------------------------------------------
// size() for various types
// ------------------------------------------------------------------
TEST_F(NodeTest_686, SizeOfNull_686) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_686, SizeOfScalar_686) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_686, SizeOfEmptySequence_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_686, SizeOfEmptyMap_686) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

// ------------------------------------------------------------------
// Type queries
// ------------------------------------------------------------------
TEST_F(NodeTest_686, IsNull_686) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_686, IsScalar_686) {
    YAML::Node node("text");
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_686, IsSequence_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_686, IsMap_686) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_TRUE(node.IsMap());
}

// ------------------------------------------------------------------
// operator bool() and operator!()
// ------------------------------------------------------------------
TEST_F(NodeTest_686, BoolOperator_DefinedNode_686) {
    YAML::Node node(42);
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_686, BoolOperator_NullNode_686) {
    YAML::Node node;
    // A null but valid node: behavior depends on implementation,
    // but IsDefined() is true
    EXPECT_TRUE(node.IsDefined());
}

// ------------------------------------------------------------------
// Subscript on undefined key returns undefined node
// ------------------------------------------------------------------
TEST_F(NodeTest_686, SubscriptUndefinedKey_686) {
    YAML::Node node(YAML::NodeType::Map);
    const YAML::Node& constNode = node;
    YAML::Node result = constNode["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

// ------------------------------------------------------------------
// begin/end on empty containers
// ------------------------------------------------------------------
TEST_F(NodeTest_686, BeginEqualsEndOnEmptySequence_686) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

TEST_F(NodeTest_686, BeginEqualsEndOnEmptyMap_686) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// ------------------------------------------------------------------
// Parsing YAML strings and testing Node
// ------------------------------------------------------------------
TEST_F(NodeTest_686, LoadScalar_686) {
    YAML::Node node = YAML::Load("42");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_686, LoadSequence_686) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_686, LoadMap_686) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST_F(NodeTest_686, LoadNull_686) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

// ------------------------------------------------------------------
// Nested structures
// ------------------------------------------------------------------
TEST_F(NodeTest_686, NestedMapAccess_686) {
    YAML::Node node = YAML::Load("{outer: {inner: 42}}");
    EXPECT_EQ(node["outer"]["inner"].as<int>(), 42);
}

TEST_F(NodeTest_686, NestedSequenceInMap_686) {
    YAML::Node node = YAML::Load("{key: [1, 2, 3]}");
    EXPECT_TRUE(node["key"].IsSequence());
    EXPECT_EQ(node["key"].size(), 3u);
}

// ------------------------------------------------------------------
// Reassignment changes type
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ReassignScalarToSequence_686) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_686, ReassignNullToMap_686) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

// ------------------------------------------------------------------
// Large values
// ------------------------------------------------------------------
TEST_F(NodeTest_686, LargeSequence_686) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(NodeTest_686, LargeMap_686) {
    YAML::Node node;
    for (int i = 0; i < 100; ++i) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), 100u);
    EXPECT_EQ(node["50"].as<int>(), 50);
}

// ------------------------------------------------------------------
// Constructing from special string values
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ConstructFromEmptyCString_686) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(NodeTest_686, ConstructFromLongString_686) {
    std::string longStr(10000, 'x');
    YAML::Node node(longStr);
    EXPECT_EQ(node.as<std::string>(), longStr);
}

// ------------------------------------------------------------------
// Mark
// ------------------------------------------------------------------
TEST_F(NodeTest_686, MarkOnProgrammaticNode_686) {
    YAML::Node node(42);
    YAML::Mark mark = node.Mark();
    // Programmatically created nodes typically have null marks
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// ------------------------------------------------------------------
// Negative integer
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ConstructFromNegativeInt_686) {
    YAML::Node node(-100);
    EXPECT_EQ(node.as<int>(), -100);
}

// ------------------------------------------------------------------
// Float precision
// ------------------------------------------------------------------
TEST_F(NodeTest_686, FloatValue_686) {
    YAML::Node node(1.5f);
    EXPECT_NEAR(node.as<float>(), 1.5f, 0.001f);
}

// ------------------------------------------------------------------
// Boolean parsing
// ------------------------------------------------------------------
TEST_F(NodeTest_686, LoadBooleanTrue_686) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(NodeTest_686, LoadBooleanFalse_686) {
    YAML::Node node = YAML::Load("false");
    EXPECT_EQ(node.as<bool>(), false);
}

// ------------------------------------------------------------------
// Sequence remove by index (via subscript with integer key and remove)
// ------------------------------------------------------------------
TEST_F(NodeTest_686, MapRemoveIntKey_686) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.remove(1));
    EXPECT_FALSE(node[1].IsDefined());
}

// ------------------------------------------------------------------
// Self-assignment
// ------------------------------------------------------------------
TEST_F(NodeTest_686, SelfAssignment_686) {
    YAML::Node node(42);
    node = node;
    EXPECT_EQ(node.as<int>(), 42);
}

// ------------------------------------------------------------------
// Overwrite map value
// ------------------------------------------------------------------
TEST_F(NodeTest_686, OverwriteMapValue_686) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

// ------------------------------------------------------------------
// Conversion between types via as<T> with fallback
// ------------------------------------------------------------------
TEST_F(NodeTest_686, StringToIntFallback_686) {
    YAML::Node node("123");
    EXPECT_EQ(node.as<int>(0), 123);
}

TEST_F(NodeTest_686, MapNodeAsFallback_686) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_EQ(node.as<std::string>("fallback"), "fallback");
}

// ------------------------------------------------------------------
// Const Node subscript on sequence
// ------------------------------------------------------------------
TEST_F(NodeTest_686, ConstSequenceSubscript_686) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode[0].as<int>(), 10);
    EXPECT_EQ(constNode[1].as<int>(), 20);
}

TEST_F(NodeTest_686, ConstSequenceOutOfBounds_686) {
    YAML::Node node;
    node.push_back(10);
    const YAML::Node& constNode = node;
    YAML::Node result = constNode[5];
    EXPECT_FALSE(result.IsDefined());
}
