#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor
TEST(NodeTest_685, DefaultConstructor_685) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test constructor with NodeType::Null
TEST(NodeTest_685, ConstructWithNullType_685) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test constructor with NodeType::Scalar
TEST(NodeTest_685, ConstructWithScalarType_685) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

// Test constructor with NodeType::Sequence
TEST(NodeTest_685, ConstructWithSequenceType_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

// Test constructor with NodeType::Map
TEST(NodeTest_685, ConstructWithMapType_685) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

// Test constructor with NodeType::Undefined
TEST(NodeTest_685, ConstructWithUndefinedType_685) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// Test template constructor with string
TEST(NodeTest_685, ConstructWithString_685) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test template constructor with int
TEST(NodeTest_685, ConstructWithInt_685) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test template constructor with double
TEST(NodeTest_685, ConstructWithDouble_685) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

// Test template constructor with bool
TEST(NodeTest_685, ConstructWithBool_685) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// Test copy constructor
TEST(NodeTest_685, CopyConstructor_685) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// Test IsDefined for defined node
TEST(NodeTest_685, IsDefinedForDefinedNode_685) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

// Test bool operator
TEST(NodeTest_685, BoolOperatorForDefinedNode_685) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

// Test bool operator for null node
TEST(NodeTest_685, BoolOperatorForNullNode_685) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
}

// Test not operator for null node
TEST(NodeTest_685, NotOperatorForNullNode_685) {
    YAML::Node node;
    EXPECT_TRUE(!node);
}

// Test not operator for defined node
TEST(NodeTest_685, NotOperatorForDefinedNode_685) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

// Test Scalar() on scalar node
TEST(NodeTest_685, ScalarValue_685) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.Scalar(), "hello world");
}

// Test as<string>
TEST(NodeTest_685, AsString_685) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

// Test as<int>
TEST(NodeTest_685, AsInt_685) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

// Test as with fallback when conversion fails
TEST(NodeTest_685, AsWithFallback_685) {
    YAML::Node node;
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

// Test as with fallback when conversion succeeds
TEST(NodeTest_685, AsWithFallbackSucceeds_685) {
    YAML::Node node(100);
    int result = node.as<int>(42);
    EXPECT_EQ(result, 100);
}

// Test Tag
TEST(NodeTest_685, SetAndGetTag_685) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

// Test Style
TEST(NodeTest_685, SetAndGetStyle_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test SetStyle Block
TEST(NodeTest_685, SetStyleBlock_685) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// Test is() with same node
TEST(NodeTest_685, IsSameNode_685) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

// Test is() with different nodes
TEST(NodeTest_685, IsDifferentNode_685) {
    YAML::Node node1("test1");
    YAML::Node node2("test2");
    EXPECT_FALSE(node1.is(node2));
}

// Test assignment operator with value
TEST(NodeTest_685, AssignmentWithValue_685) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test assignment operator with int
TEST(NodeTest_685, AssignmentWithInt_685) {
    YAML::Node node;
    node = 42;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test assignment operator with another node
TEST(NodeTest_685, AssignmentWithNode_685) {
    YAML::Node node1("original");
    YAML::Node node2;
    node2 = node1;
    EXPECT_TRUE(node2.is(node1));
    EXPECT_EQ(node2.Scalar(), "original");
}

// Test reset
TEST(NodeTest_685, Reset_685) {
    YAML::Node node1("original");
    YAML::Node node2("replacement");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
}

// Test sequence push_back
TEST(NodeTest_685, SequencePushBack_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.IsSequence());
}

// Test sequence push_back with node
TEST(NodeTest_685, SequencePushBackNode_685) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node item("value");
    seq.push_back(item);
    EXPECT_EQ(seq.size(), 1u);
}

// Test sequence size
TEST(NodeTest_685, SequenceSize_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
}

// Test sequence access by index
TEST(NodeTest_685, SequenceAccessByIndex_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
    EXPECT_EQ(node[2].as<std::string>(), "third");
}

// Test sequence iteration
TEST(NodeTest_685, SequenceIteration_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test map operator[]
TEST(NodeTest_685, MapAccessByKey_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// Test map size
TEST(NodeTest_685, MapSize_685) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
    node["key1"] = "value1";
    EXPECT_EQ(node.size(), 1u);
    node["key2"] = "value2";
    EXPECT_EQ(node.size(), 2u);
}

// Test map iteration
TEST(NodeTest_685, MapIteration_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["a"] = 1;
    node["b"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test remove from map
TEST(NodeTest_685, MapRemoveByKey_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node.size(), 2u);
    
    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

// Test remove non-existent key from map
TEST(NodeTest_685, MapRemoveNonExistentKey_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

// Test remove with Node key
TEST(NodeTest_685, MapRemoveByNodeKey_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    
    YAML::Node key("key1");
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

// Test force_insert
TEST(NodeTest_685, ForceInsert_685) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key1", "value1");
    node.force_insert("key2", "value2");
    EXPECT_EQ(node.size(), 2u);
}

// Test null node size
TEST(NodeTest_685, NullNodeSize_685) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// Test scalar node size
TEST(NodeTest_685, ScalarNodeSize_685) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// Test const operator[] on map
TEST(NodeTest_685, ConstMapAccess_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode["key"].as<std::string>(), "value");
}

// Test accessing non-existent key in map (const)
TEST(NodeTest_685, ConstMapAccessNonExistent_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["nonexistent"].IsDefined());
}

// Test IsNull
TEST(NodeTest_685, IsNull_685) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    
    node = "value";
    EXPECT_FALSE(node.IsNull());
}

// Test IsScalar
TEST(NodeTest_685, IsScalar_685) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    
    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_FALSE(seq.IsScalar());
}

// Test IsSequence
TEST(NodeTest_685, IsSequence_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    
    YAML::Node scalar("test");
    EXPECT_FALSE(scalar.IsSequence());
}

// Test IsMap
TEST(NodeTest_685, IsMap_685) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    
    YAML::Node scalar("test");
    EXPECT_FALSE(scalar.IsMap());
}

// Test empty sequence begin == end
TEST(NodeTest_685, EmptySequenceBeginEqualsEnd_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test empty map begin == end
TEST(NodeTest_685, EmptyMapBeginEqualsEnd_685) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

// Test push_back with various types
TEST(NodeTest_685, PushBackVariousTypes_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back("string");
    node.push_back(3.14);
    node.push_back(true);
    EXPECT_EQ(node.size(), 4u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<std::string>(), "string");
    EXPECT_NEAR(node[2].as<double>(), 3.14, 0.001);
    EXPECT_EQ(node[3].as<bool>(), true);
}

// Test nested map
TEST(NodeTest_685, NestedMap_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["outer"]["inner"] = "value";
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

// Test nested sequence
TEST(NodeTest_685, NestedSequence_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    YAML::Node inner(YAML::NodeType::Sequence);
    inner.push_back(1);
    inner.push_back(2);
    node.push_back(inner);
    
    EXPECT_EQ(node.size(), 1u);
    EXPECT_TRUE(node[0].IsSequence());
    EXPECT_EQ(node[0].size(), 2u);
}

// Test Scalar on null node returns empty
TEST(NodeTest_685, ScalarOnNullNode_685) {
    YAML::Node node;
    EXPECT_EQ(node.Scalar(), "");
}

// Test empty string scalar
TEST(NodeTest_685, EmptyStringScalar_685) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// Test overwriting map value
TEST(NodeTest_685, OverwriteMapValue_685) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "old_value";
    node["key"] = "new_value";
    EXPECT_EQ(node["key"].as<std::string>(), "new_value");
    EXPECT_EQ(node.size(), 1u);
}

// Test as<string> with fallback on undefined
TEST(NodeTest_685, AsStringFallbackOnUndefined_685) {
    YAML::Node node;
    std::string result = node.as<std::string>("fallback");
    EXPECT_EQ(result, "fallback");
}

// Test constructor with const char*
TEST(NodeTest_685, ConstructWithConstCharPtr_685) {
    YAML::Node node("const char ptr");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "const char ptr");
}

// Test assignment to self
TEST(NodeTest_685, SelfAssignment_685) {
    YAML::Node node("test");
    node = node;
    EXPECT_EQ(node.Scalar(), "test");
}

// Test Mark on new node
TEST(NodeTest_685, MarkOnNewNode_685) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // Mark should exist but values are implementation-defined for programmatically created nodes
    // Just verify it doesn't crash
    (void)mark;
}

// Test push_back transforms null to sequence
TEST(NodeTest_685, PushBackTransformsNullToSequence_685) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

// Test operator[] transforms null to map
TEST(NodeTest_685, SubscriptTransformsNullToMap_685) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
}

// Test large sequence
TEST(NodeTest_685, LargeSequence_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test Tag on fresh node
TEST(NodeTest_685, TagOnFreshNode_685) {
    YAML::Node node("value");
    // Fresh programmatic nodes should have some default tag behavior
    std::string tag = node.Tag();
    // Just ensure it doesn't crash; tag may be empty or "?"
    (void)tag;
}

// Test Style on fresh node
TEST(NodeTest_685, StyleOnFreshNode_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    YAML::EmitterStyle::value style = node.Style();
    // Default style
    (void)style;
}

// Test as<bool> conversion
TEST(NodeTest_685, AsBoolConversion_685) {
    YAML::Node trueNode("true");
    EXPECT_EQ(trueNode.as<bool>(), true);
    
    YAML::Node falseNode("false");
    EXPECT_EQ(falseNode.as<bool>(), false);
}

// Test as<float>
TEST(NodeTest_685, AsFloat_685) {
    YAML::Node node(2.5f);
    EXPECT_NEAR(node.as<float>(), 2.5f, 0.001f);
}

// Test map with int keys
TEST(NodeTest_685, MapWithIntKeys_685) {
    YAML::Node node(YAML::NodeType::Map);
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
    EXPECT_EQ(node.size(), 2u);
}

// Test map with Node key
TEST(NodeTest_685, MapWithNodeKey_685) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

// Test force_insert allows duplicate keys
TEST(NodeTest_685, ForceInsertDuplicateKeys_685) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert should insert regardless of duplicate key
    EXPECT_EQ(node.size(), 2u);
}

// Test assignment changes type
TEST(NodeTest_685, AssignmentChangesType_685) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    node = "scalar_value";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

// Test as with negative int
TEST(NodeTest_685, AsNegativeInt_685) {
    YAML::Node node(-42);
    EXPECT_EQ(node.as<int>(), -42);
}

// Test as with zero
TEST(NodeTest_685, AsZero_685) {
    YAML::Node node(0);
    EXPECT_EQ(node.as<int>(), 0);
}
