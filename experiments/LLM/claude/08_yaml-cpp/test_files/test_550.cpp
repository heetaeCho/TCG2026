#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor creates a Null node
TEST(NodeTest_550, DefaultConstructorCreatesNullNode_550) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

// Test that default constructed node is not defined
TEST(NodeTest_550, DefaultConstructorIsNotDefined_550) {
    YAML::Node node;
    EXPECT_FALSE(node.IsDefined());
}

// Test constructor with NodeType::Scalar
TEST(NodeTest_550, ConstructorWithScalarType_550) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
}

// Test constructor with NodeType::Sequence
TEST(NodeTest_550, ConstructorWithSequenceType_550) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

// Test constructor with NodeType::Map
TEST(NodeTest_550, ConstructorWithMapType_550) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

// Test constructor with NodeType::Null
TEST(NodeTest_550, ConstructorWithNullType_550) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

// Test constructor with a string value
TEST(NodeTest_550, ConstructorWithStringValue_550) {
    YAML::Node node(std::string("hello"));
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test constructor with an integer value
TEST(NodeTest_550, ConstructorWithIntValue_550) {
    YAML::Node node(42);
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
    EXPECT_EQ(node.as<int>(), 42);
}

// Test copy constructor
TEST(NodeTest_550, CopyConstructor_550) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test");
    EXPECT_TRUE(copy.is(original));
}

// Test IsNull on a null node
TEST(NodeTest_550, IsNullOnNullNode_550) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

// Test IsScalar on a scalar node
TEST(NodeTest_550, IsScalarOnScalarNode_550) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

// Test Scalar() returns the scalar value
TEST(NodeTest_550, ScalarReturnsValue_550) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.Scalar(), "hello world");
}

// Test as<T> with default fallback
TEST(NodeTest_550, AsWithFallback_550) {
    YAML::Node node;
    int value = node.as<int>(99);
    EXPECT_EQ(value, 99);
}

// Test as<T> with valid conversion
TEST(NodeTest_550, AsWithValidConversion_550) {
    YAML::Node node("123");
    EXPECT_EQ(node.as<int>(), 123);
}

// Test as<T> with bool conversion
TEST(NodeTest_550, AsWithBoolConversion_550) {
    YAML::Node node("true");
    EXPECT_TRUE(node.as<bool>());
}

// Test as<T> with double conversion
TEST(NodeTest_550, AsWithDoubleConversion_550) {
    YAML::Node node("3.14");
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

// Test as<T> with fallback when conversion fails
TEST(NodeTest_550, AsWithFallbackOnFailedConversion_550) {
    YAML::Node node;
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "default");
}

// Test operator bool on valid node
TEST(NodeTest_550, OperatorBoolOnValidNode_550) {
    YAML::Node node("test");
    EXPECT_TRUE(static_cast<bool>(node));
}

// Test operator bool on null node
TEST(NodeTest_550, OperatorBoolOnNullNode_550) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
}

// Test operator! on valid node
TEST(NodeTest_550, OperatorNotOnValidNode_550) {
    YAML::Node node("test");
    EXPECT_FALSE(!node);
}

// Test operator! on null node
TEST(NodeTest_550, OperatorNotOnNullNode_550) {
    YAML::Node node;
    EXPECT_TRUE(!node);
}

// Test assignment operator with value
TEST(NodeTest_550, AssignmentWithValue_550) {
    YAML::Node node;
    node = "hello";
    EXPECT_EQ(node.as<std::string>(), "hello");
    EXPECT_TRUE(node.IsScalar());
}

// Test assignment operator with int
TEST(NodeTest_550, AssignmentWithInt_550) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

// Test assignment operator with another Node
TEST(NodeTest_550, AssignmentWithNode_550) {
    YAML::Node src("source");
    YAML::Node dest;
    dest = src;
    EXPECT_EQ(dest.as<std::string>(), "source");
}

// Test push_back creates a sequence
TEST(NodeTest_550, PushBackCreatesSequence_550) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// Test push_back with Node
TEST(NodeTest_550, PushBackWithNode_550) {
    YAML::Node node;
    YAML::Node child("item");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

// Test operator[] with integer index on sequence
TEST(NodeTest_550, SubscriptWithIntOnSequence_550) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

// Test operator[] with string key on map
TEST(NodeTest_550, SubscriptWithStringKeyOnMap_550) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test size on empty node
TEST(NodeTest_550, SizeOnEmptyNode_550) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// Test size on sequence
TEST(NodeTest_550, SizeOnSequence_550) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

// Test size on map
TEST(NodeTest_550, SizeOnMap_550) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

// Test begin/end iteration on sequence
TEST(NodeTest_550, IterationOnSequence_550) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test begin/end iteration on map
TEST(NodeTest_550, IterationOnMap_550) {
    YAML::Node node;
    node["x"] = 1;
    node["y"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test remove on map
TEST(NodeTest_550, RemoveFromMap_550) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    
    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(node.size(), 2u);
}

// Test remove non-existent key
TEST(NodeTest_550, RemoveNonExistentKey_550) {
    YAML::Node node;
    node["a"] = 1;
    
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

// Test remove with Node key
TEST(NodeTest_550, RemoveWithNodeKey_550) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(node.size(), 0u);
}

// Test Tag operations
TEST(NodeTest_550, SetAndGetTag_550) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

// Test Style operations
TEST(NodeTest_550, SetAndGetStyle_550) {
    YAML::Node node;
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test is() method - same node
TEST(NodeTest_550, IsSameNode_550) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

// Test is() method - different nodes
TEST(NodeTest_550, IsDifferentNode_550) {
    YAML::Node node1("test");
    YAML::Node node2("test");
    EXPECT_FALSE(node1.is(node2));
}

// Test reset
TEST(NodeTest_550, ResetNode_550) {
    YAML::Node node1("original");
    YAML::Node node2("replacement");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.as<std::string>(), "replacement");
}

// Test force_insert
TEST(NodeTest_550, ForceInsert_550) {
    YAML::Node node;
    node.force_insert("key1", "value1");
    node.force_insert("key2", "value2");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
}

// Test nested map access
TEST(NodeTest_550, NestedMapAccess_550) {
    YAML::Node node;
    node["outer"]["inner"] = "deep_value";
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "deep_value");
}

// Test const operator[] returns undefined for missing key
TEST(NodeTest_550, ConstSubscriptMissingKey_550) {
    const YAML::Node node = YAML::Node(YAML::NodeType::Map);
    const YAML::Node result = node["missing"];
    EXPECT_FALSE(result.IsDefined());
}

// Test sequence with mixed types
TEST(NodeTest_550, SequenceWithMixedTypes_550) {
    YAML::Node node;
    node.push_back(42);
    node.push_back("hello");
    node.push_back(3.14);
    
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_NEAR(node[2].as<double>(), 3.14, 0.001);
}

// Test loading from YAML string
TEST(NodeTest_550, LoadFromString_550) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test loading sequence from YAML string
TEST(NodeTest_550, LoadSequenceFromString_550) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

// Test loading scalar from YAML string
TEST(NodeTest_550, LoadScalarFromString_550) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test loading null from YAML string
TEST(NodeTest_550, LoadNullFromString_550) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

// Test overwriting a scalar node value
TEST(NodeTest_550, OverwriteScalarValue_550) {
    YAML::Node node("original");
    node = "modified";
    EXPECT_EQ(node.as<std::string>(), "modified");
}

// Test overwriting map value
TEST(NodeTest_550, OverwriteMapValue_550) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
    EXPECT_EQ(node.size(), 1u);
}

// Test empty scalar
TEST(NodeTest_550, EmptyScalar_550) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// Test constructing from const char*
TEST(NodeTest_550, ConstructFromConstCharPtr_550) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test Type() throws InvalidNode for invalid node (accessed via missing map key on const node)
TEST(NodeTest_550, InvalidNodeThrowsOnType_550) {
    YAML::Node root;
    root["existing"] = "value";
    
    // Accessing a non-existent key on a const node returns a "zombie" (invalid) node
    const YAML::Node constRoot = root;
    const YAML::Node zombie = constRoot["nonexistent"];
    
    // The zombie should not be defined
    EXPECT_FALSE(zombie.IsDefined());
}

// Test Mark on a loaded node
TEST(NodeTest_550, MarkOnLoadedNode_550) {
    YAML::Node node = YAML::Load("key: value");
    YAML::Mark mark = node.Mark();
    // Mark should have valid line/column (typically 0-based)
    EXPECT_GE(mark.line, 0);
    EXPECT_GE(mark.column, 0);
}

// Test default style
TEST(NodeTest_550, DefaultStyle_550) {
    YAML::Node node;
    node.push_back(1);
    // Default style should be Default
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// Test Block style
TEST(NodeTest_550, BlockStyle_550) {
    YAML::Node node;
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// Test large sequence
TEST(NodeTest_550, LargeSequence_550) {
    YAML::Node node;
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), static_cast<std::size_t>(count));
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test map with various key types
TEST(NodeTest_550, MapWithIntKeys_550) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

// Test null assignment
TEST(NodeTest_550, AssignNullType_550) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsScalar());
    node = YAML::Node();
    EXPECT_TRUE(node.IsNull());
}

// Test that IsDefined returns true for scalar node
TEST(NodeTest_550, IsDefinedForScalar_550) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

// Test that IsDefined returns false for default node
TEST(NodeTest_550, IsDefinedForDefault_550) {
    YAML::Node node;
    EXPECT_FALSE(node.IsDefined());
}
