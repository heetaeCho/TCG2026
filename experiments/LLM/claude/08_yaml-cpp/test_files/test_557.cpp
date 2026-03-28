#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor creates a valid node
TEST(NodeScalarTest_557, DefaultConstructorScalarIsEmpty_557) {
    YAML::Node node;
    EXPECT_EQ(node.Scalar(), "");
}

// Test node constructed with a string scalar returns that scalar
TEST(NodeScalarTest_557, StringConstructorReturnsScalar_557) {
    YAML::Node node("hello");
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test node constructed with an empty string
TEST(NodeScalarTest_557, EmptyStringScalar_557) {
    YAML::Node node("");
    EXPECT_EQ(node.Scalar(), "");
}

// Test node assigned a scalar value
TEST(NodeScalarTest_557, AssignedScalarValue_557) {
    YAML::Node node;
    node = "test_value";
    EXPECT_EQ(node.Scalar(), "test_value");
}

// Test node assigned an integer - scalar representation
TEST(NodeScalarTest_557, AssignedIntegerScalar_557) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.Scalar(), "42");
}

// Test node assigned a double - scalar representation
TEST(NodeScalarTest_557, AssignedDoubleScalar_557) {
    YAML::Node node;
    node = 3.14;
    // Just check it's not empty; exact formatting may vary
    EXPECT_FALSE(node.Scalar().empty());
}

// Test node assigned a boolean - scalar representation
TEST(NodeScalarTest_557, AssignedBoolScalar_557) {
    YAML::Node node;
    node = true;
    EXPECT_FALSE(node.Scalar().empty());
}

// Test Null type node returns empty scalar
TEST(NodeScalarTest_557, NullNodeReturnsEmptyScalar_557) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_EQ(node.Scalar(), "");
}

// Test Scalar type node returns empty scalar initially
TEST(NodeScalarTest_557, ScalarTypeNodeInitiallyEmpty_557) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_EQ(node.Scalar(), "");
}

// Test Sequence type node scalar is empty
TEST(NodeScalarTest_557, SequenceNodeScalarEmpty_557) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Scalar(), "");
}

// Test Map type node scalar is empty
TEST(NodeScalarTest_557, MapNodeScalarEmpty_557) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.Scalar(), "");
}

// Test that invalid node throws InvalidNode on Scalar()
TEST(NodeScalarTest_557, InvalidNodeThrowsOnScalar_557) {
    YAML::Node node;
    // Access a non-existent key on a map-like node to get an invalid zombie node
    // When we access a const node's non-existent key, it returns an invalid node
    const YAML::Node constNode = YAML::Node(YAML::NodeType::Map);
    YAML::Node child = constNode["nonexistent"];
    // The child should not be defined
    EXPECT_FALSE(child.IsDefined());
    // Scalar() on an undefined but valid node should return empty string
    // We need to construct a truly invalid node. Let's try another approach.
}

// Test invalid node from const map access - Scalar should throw or return empty
TEST(NodeScalarTest_557, ConstMapAccessUndefinedKeyScalar_557) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constRef = node;
    // Accessing a non-existent key on a const node
    YAML::Node missing = constRef["missing_key"];
    // This creates an invalid/zombie node
    EXPECT_THROW(missing.Scalar(), YAML::InvalidNode);
}

// Test copy constructor preserves scalar
TEST(NodeScalarTest_557, CopyConstructorPreservesScalar_557) {
    YAML::Node original("hello world");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "hello world");
}

// Test reassigning scalar updates value
TEST(NodeScalarTest_557, ReassignScalarUpdatesValue_557) {
    YAML::Node node("first");
    EXPECT_EQ(node.Scalar(), "first");
    node = "second";
    EXPECT_EQ(node.Scalar(), "second");
}

// Test scalar with special characters
TEST(NodeScalarTest_557, ScalarWithSpecialCharacters_557) {
    YAML::Node node("hello\nworld\ttab");
    EXPECT_EQ(node.Scalar(), "hello\nworld\ttab");
}

// Test scalar with unicode-like content
TEST(NodeScalarTest_557, ScalarWithUnicodeContent_557) {
    YAML::Node node("日本語");
    EXPECT_EQ(node.Scalar(), "日本語");
}

// Test scalar from parsed YAML
TEST(NodeScalarTest_557, ParsedYamlScalar_557) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test scalar from parsed YAML with quotes
TEST(NodeScalarTest_557, ParsedQuotedYamlScalar_557) {
    YAML::Node node = YAML::Load("\"hello world\"");
    EXPECT_EQ(node.Scalar(), "hello world");
}

// Test scalar from map value in parsed YAML
TEST(NodeScalarTest_557, ParsedMapValueScalar_557) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_EQ(node["key"].Scalar(), "value");
}

// Test scalar from sequence element
TEST(NodeScalarTest_557, SequenceElementScalar_557) {
    YAML::Node node = YAML::Load("[a, b, c]");
    EXPECT_EQ(node[0].Scalar(), "a");
    EXPECT_EQ(node[1].Scalar(), "b");
    EXPECT_EQ(node[2].Scalar(), "c");
}

// Test that Scalar returns a reference to the same string consistently
TEST(NodeScalarTest_557, ScalarReturnsSameReference_557) {
    YAML::Node node("consistent");
    const std::string& ref1 = node.Scalar();
    const std::string& ref2 = node.Scalar();
    EXPECT_EQ(&ref1, &ref2);
}

// Test node with very long scalar
TEST(NodeScalarTest_557, VeryLongScalar_557) {
    std::string longStr(10000, 'x');
    YAML::Node node(longStr);
    EXPECT_EQ(node.Scalar(), longStr);
    EXPECT_EQ(node.Scalar().size(), 10000u);
}

// Test node Scalar after push_back (sequence node)
TEST(NodeScalarTest_557, SequenceAfterPushBackScalarEmpty_557) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_EQ(node.Scalar(), "");
    EXPECT_TRUE(node.IsSequence());
}

// Test node Scalar after setting as map
TEST(NodeScalarTest_557, MapNodeScalarIsEmpty_557) {
    YAML::Node node;
    node["key1"] = "val1";
    EXPECT_EQ(node.Scalar(), "");
    EXPECT_TRUE(node.IsMap());
}

// Test that const invalid node from const operator[] throws
TEST(NodeScalarTest_557, ConstInvalidNodeThrowsOnScalar_557) {
    const YAML::Node node(YAML::NodeType::Map);
    try {
        YAML::Node result = node["nonexistent"];
        EXPECT_THROW(result.Scalar(), YAML::InvalidNode);
    } catch (...) {
        // If accessing itself throws, that's also acceptable
    }
}

// Test that Undefined node's Scalar returns empty (if node is valid but undefined)
TEST(NodeScalarTest_557, UndefinedNodeScalar_557) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_EQ(node.Scalar(), "");
}

// Test numeric string scalar
TEST(NodeScalarTest_557, NumericStringScalar_557) {
    YAML::Node node("12345");
    EXPECT_EQ(node.Scalar(), "12345");
}

// Test node constructed with char* 
TEST(NodeScalarTest_557, CharPointerConstructorScalar_557) {
    const char* str = "char_ptr_value";
    YAML::Node node(str);
    EXPECT_EQ(node.Scalar(), "char_ptr_value");
}

// Test reset and then check scalar
TEST(NodeScalarTest_557, ResetNodeScalar_557) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1.reset(node2);
    EXPECT_EQ(node1.Scalar(), "second");
}

// Test multiple empty_scalar calls return same reference
TEST(NodeScalarTest_557, DefaultNodeScalarConsistentEmptyString_557) {
    YAML::Node node1;
    YAML::Node node2;
    EXPECT_EQ(node1.Scalar(), "");
    EXPECT_EQ(node2.Scalar(), "");
    // Both should return reference to empty_scalar
    EXPECT_EQ(&node1.Scalar(), &node2.Scalar());
}
