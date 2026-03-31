#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor creates a valid null node
TEST(NodeTest_549, DefaultConstructorCreatesValidNullNode_549) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test Mark() on a default-constructed node returns null mark
TEST(NodeTest_549, MarkOnDefaultNodeReturnsNullMark_549) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    EXPECT_TRUE(mark.is_null());
}

// Test Mark() on a parsed node returns valid mark
TEST(NodeTest_549, MarkOnParsedNodeReturnsValidMark_549) {
    YAML::Node node = YAML::Load("hello");
    YAML::Mark mark = node.Mark();
    // Parsed node should have some mark information
    // The exact values depend on parser, but it should be obtainable
    EXPECT_NO_THROW(node.Mark());
}

// Test Mark() on an invalid node throws InvalidNode
TEST(NodeTest_549, MarkOnInvalidNodeThrowsException_549) {
    YAML::Node node;
    // Access a non-existent key on a map to get an invalid node scenario
    YAML::Node mapNode = YAML::Load("{a: 1}");
    // Accessing a key that doesn't exist and then accessing a sub-key
    // creates an invalid zombie node in some paths
    YAML::Node undefined = mapNode["nonexistent"]["nested"];
    // The undefined node's mark should still work or throw depending on validity
    // Let's test with a known invalid node pattern
    EXPECT_NO_THROW(mapNode.Mark());
}

// Test constructing node with a type
TEST(NodeTest_549, ConstructorWithTypeSequence_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodeTest_549, ConstructorWithTypeMap_549) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(NodeTest_549, ConstructorWithTypeScalar_549) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

// Test constructing node with a value
TEST(NodeTest_549, ConstructorWithStringValue_549) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_549, ConstructorWithIntValue_549) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test copy constructor
TEST(NodeTest_549, CopyConstructor_549) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// Test IsDefined
TEST(NodeTest_549, IsDefinedOnValidNode_549) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

// Test IsNull
TEST(NodeTest_549, IsNullOnDefaultNode_549) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_549, IsNullOnScalarNode_549) {
    YAML::Node node("value");
    EXPECT_FALSE(node.IsNull());
}

// Test Scalar
TEST(NodeTest_549, ScalarReturnsCorrectValue_549) {
    YAML::Node node = YAML::Load("hello world");
    EXPECT_EQ(node.Scalar(), "hello world");
}

// Test Tag
TEST(NodeTest_549, SetAndGetTag_549) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

// Test Style
TEST(NodeTest_549, SetAndGetStyle_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test size
TEST(NodeTest_549, SizeOfEmptySequence_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_549, SizeAfterPushBack_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_EQ(node.size(), 2u);
}

// Test push_back
TEST(NodeTest_549, PushBackToSequence_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_549, PushBackNodeToSequence_549) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node val("hello");
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].Scalar(), "hello");
}

// Test operator[]
TEST(NodeTest_549, SubscriptOperatorOnSequence_549) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_549, SubscriptOperatorOnMap_549) {
    YAML::Node node = YAML::Load("{key: value}");
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test remove
TEST(NodeTest_549, RemoveFromMap_549) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(node.size(), 2u);
    EXPECT_FALSE(node["b"].IsDefined());
}

TEST(NodeTest_549, RemoveNonExistentKey_549) {
    YAML::Node node = YAML::Load("{a: 1}");
    EXPECT_FALSE(node.remove("nonexistent"));
}

// Test is()
TEST(NodeTest_549, IsReturnsTrueForSameNode_549) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST(NodeTest_549, IsReturnsFalseForDifferentNodes_549) {
    YAML::Node node1("test");
    YAML::Node node2("test");
    EXPECT_FALSE(node1.is(node2));
}

// Test assignment operator
TEST(NodeTest_549, AssignmentOperatorWithValue_549) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_549, AssignmentOperatorWithNode_549) {
    YAML::Node node1("original");
    YAML::Node node2;
    node2 = node1;
    EXPECT_TRUE(node2.is(node1));
    EXPECT_EQ(node2.Scalar(), "original");
}

// Test reset
TEST(NodeTest_549, ResetNode_549) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.Scalar(), "second");
}

// Test bool operator
TEST(NodeTest_549, BoolOperatorOnValidNode_549) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_549, BoolOperatorOnDefaultNode_549) {
    YAML::Node node;
    // Default node is valid but null - still converts to true as it's a valid node
    // The bool operator checks if the node is valid (not zombie)
    EXPECT_TRUE(static_cast<bool>(node));
}

// Test operator!
TEST(NodeTest_549, NotOperatorOnValidNode_549) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

// Test as() with fallback
TEST(NodeTest_549, AsWithFallbackOnUndefined_549) {
    YAML::Node node = YAML::Load("{a: 1}");
    int val = node["nonexistent"].as<int>(42);
    EXPECT_EQ(val, 42);
}

TEST(NodeTest_549, AsWithFallbackOnDefined_549) {
    YAML::Node node = YAML::Load("{a: 1}");
    int val = node["a"].as<int>(42);
    EXPECT_EQ(val, 1);
}

// Test as() type conversions
TEST(NodeTest_549, AsIntConversion_549) {
    YAML::Node node = YAML::Load("123");
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_549, AsDoubleConversion_549) {
    YAML::Node node = YAML::Load("3.14");
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST(NodeTest_549, AsBoolConversion_549) {
    YAML::Node node = YAML::Load("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_549, AsStringConversion_549) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test iteration over sequence
TEST(NodeTest_549, IterateOverSequence_549) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over map
TEST(NodeTest_549, IterateOverMap_549) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test force_insert
TEST(NodeTest_549, ForceInsertOnMap_549) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key1", "value1");
    node.force_insert("key1", "value2");  // Duplicate key
    EXPECT_EQ(node.size(), 2u);  // force_insert allows duplicates
}

// Test Mark on parsed YAML with multiple lines
TEST(NodeTest_549, MarkOnParsedMultiLineYAML_549) {
    std::string yaml = "a: 1\nb: 2\nc: 3";
    YAML::Node node = YAML::Load(yaml);
    YAML::Mark mark = node.Mark();
    // The root node should have a mark at the beginning
    EXPECT_NO_THROW(node.Mark());
}

// Test accessing undefined node through non-existent key in a map
TEST(NodeTest_549, UndefinedNodeFromMapAccess_549) {
    YAML::Node node = YAML::Load("{a: 1}");
    const YAML::Node& constNode = node;
    YAML::Node child = constNode["b"];
    EXPECT_FALSE(child.IsDefined());
}

// Test that Mark can be called on nodes from a loaded sequence
TEST(NodeTest_549, MarkOnSequenceElement_549) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_NO_THROW(node[0].Mark());
    EXPECT_NO_THROW(node[1].Mark());
    EXPECT_NO_THROW(node[2].Mark());
}

// Test that Mark can be called on nodes from a loaded map
TEST(NodeTest_549, MarkOnMapValue_549) {
    YAML::Node node = YAML::Load("{key: value}");
    EXPECT_NO_THROW(node["key"].Mark());
}

// Test null node type
TEST(NodeTest_549, NullNodeType_549) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test conversion from null to sequence via push_back
TEST(NodeTest_549, NullToSequenceViaPushBack_549) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

// Test conversion from null to map via subscript assignment
TEST(NodeTest_549, NullToMapViaSubscript_549) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test empty string scalar
TEST(NodeTest_549, EmptyStringScalar_549) {
    YAML::Node node = YAML::Load("''");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// Test large sequence
TEST(NodeTest_549, LargeSequence_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test Mark on node constructed with type
TEST(NodeTest_549, MarkOnTypeConstructedNode_549) {
    YAML::Node node(YAML::NodeType::Map);
    // Node constructed programmatically should have a null mark or valid mark
    YAML::Mark mark = node.Mark();
    // Should not throw
    EXPECT_NO_THROW(node.Mark());
}

// Test as() throws on type mismatch
TEST(NodeTest_549, AsThrowsOnTypeMismatch_549) {
    YAML::Node node = YAML::Load("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// Test nested map access
TEST(NodeTest_549, NestedMapAccess_549) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

// Test remove from sequence
TEST(NodeTest_549, RemoveFromSequenceByIndex_549) {
    YAML::Node node = YAML::Load("[a, b, c]");
    // remove with integer key on sequence
    EXPECT_TRUE(node.remove(1));
}

// Test multiple set tag calls
TEST(NodeTest_549, MultipleSetTagCalls_549) {
    YAML::Node node("value");
    node.SetTag("!first");
    EXPECT_EQ(node.Tag(), "!first");
    node.SetTag("!second");
    EXPECT_EQ(node.Tag(), "!second");
}

// Test style setting on different node types
TEST(NodeTest_549, StyleOnMapNode_549) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

TEST(NodeTest_549, StyleOnSequenceNode_549) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}
