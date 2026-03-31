#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// Test default constructor creates a valid, undefined node
TEST(YAMLNodeTest_195, DefaultConstructor_CreatesUndefinedNode_195) {
    YAML::Node node;
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test explicit bool conversion for undefined node
TEST(YAMLNodeTest_195, BoolConversion_UndefinedNodeIsFalse_195) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
}

// Test constructor with NodeType::Null
TEST(YAMLNodeTest_195, NullTypeConstructor_195) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test constructor with NodeType::Scalar
TEST(YAMLNodeTest_195, ScalarTypeConstructor_195) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

// Test constructor with NodeType::Sequence
TEST(YAMLNodeTest_195, SequenceTypeConstructor_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

// Test constructor with NodeType::Map
TEST(YAMLNodeTest_195, MapTypeConstructor_195) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

// Test constructor with string value
TEST(YAMLNodeTest_195, StringConstructor_195) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test constructor with int value
TEST(YAMLNodeTest_195, IntConstructor_195) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test constructor with double value
TEST(YAMLNodeTest_195, DoubleConstructor_195) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

// Test constructor with bool value
TEST(YAMLNodeTest_195, BoolConstructor_195) {
    YAML::Node nodeTrue(true);
    EXPECT_TRUE(nodeTrue.as<bool>());

    YAML::Node nodeFalse(false);
    EXPECT_FALSE(nodeFalse.as<bool>());
}

// Test constructor with const char*
TEST(YAMLNodeTest_195, CStringConstructor_195) {
    YAML::Node node("hello world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test copy constructor
TEST(YAMLNodeTest_195, CopyConstructor_195) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test");
    EXPECT_TRUE(copy.is(original));
}

// Test assignment operator with scalar value
TEST(YAMLNodeTest_195, AssignmentOperatorScalar_195) {
    YAML::Node node;
    node = "assigned";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "assigned");
}

// Test assignment operator with int
TEST(YAMLNodeTest_195, AssignmentOperatorInt_195) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(node.as<int>(), 100);
}

// Test assignment operator with another node
TEST(YAMLNodeTest_195, AssignmentOperatorNode_195) {
    YAML::Node source("source_value");
    YAML::Node target;
    target = source;
    EXPECT_TRUE(target.is(source));
    EXPECT_EQ(target.as<std::string>(), "source_value");
}

// Test IsNull
TEST(YAMLNodeTest_195, IsNull_195) {
    YAML::Node node;
    // Default node is Null type
    EXPECT_TRUE(node.IsNull());
    node = "value";
    EXPECT_FALSE(node.IsNull());
}

// Test IsScalar
TEST(YAMLNodeTest_195, IsScalar_195) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());

    YAML::Node seqNode(YAML::NodeType::Sequence);
    EXPECT_FALSE(seqNode.IsScalar());
}

// Test IsSequence
TEST(YAMLNodeTest_195, IsSequence_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());

    YAML::Node scalarNode("test");
    EXPECT_FALSE(scalarNode.IsSequence());
}

// Test IsMap
TEST(YAMLNodeTest_195, IsMap_195) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());

    YAML::Node scalarNode("test");
    EXPECT_FALSE(scalarNode.IsMap());
}

// Test Scalar() returns correct value
TEST(YAMLNodeTest_195, Scalar_195) {
    YAML::Node node("hello");
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test as<T>() with string
TEST(YAMLNodeTest_195, AsString_195) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test as<T>() with int
TEST(YAMLNodeTest_195, AsInt_195) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

// Test as<T>() with float
TEST(YAMLNodeTest_195, AsFloat_195) {
    YAML::Node node(2.5f);
    EXPECT_FLOAT_EQ(node.as<float>(), 2.5f);
}

// Test as<T>() with bool
TEST(YAMLNodeTest_195, AsBool_195) {
    YAML::Node nodeTrue("true");
    EXPECT_TRUE(nodeTrue.as<bool>());

    YAML::Node nodeFalse("false");
    EXPECT_FALSE(nodeFalse.as<bool>());
}

// Test as<T>() with fallback
TEST(YAMLNodeTest_195, AsWithFallback_195) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>("fallback"), "fallback");
    EXPECT_EQ(node.as<int>(99), 99);
}

// Test as<T>() with fallback when value exists
TEST(YAMLNodeTest_195, AsWithFallbackValueExists_195) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(99), 42);
}

// Test as<T>() throws on bad conversion
TEST(YAMLNodeTest_195, AsThrowsOnBadConversion_195) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

// Test Tag and SetTag
TEST(YAMLNodeTest_195, TagAndSetTag_195) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

// Test Style and SetStyle
TEST(YAMLNodeTest_195, StyleAndSetStyle_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);

    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// Test sequence push_back and size
TEST(YAMLNodeTest_195, SequencePushBackAndSize_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);

    node.push_back("first");
    EXPECT_EQ(node.size(), 1u);

    node.push_back("second");
    EXPECT_EQ(node.size(), 2u);

    node.push_back("third");
    EXPECT_EQ(node.size(), 3u);
}

// Test sequence push_back with Node
TEST(YAMLNodeTest_195, SequencePushBackNode_195) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node elem("element");
    seq.push_back(elem);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "element");
}

// Test sequence push_back with different types
TEST(YAMLNodeTest_195, SequencePushBackDifferentTypes_195) {
    YAML::Node node;
    node.push_back(1);
    node.push_back("two");
    node.push_back(3.0);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<std::string>(), "two");
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.0);
}

// Test sequence indexing with int
TEST(YAMLNodeTest_195, SequenceIndexing_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");

    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

// Test map operator[] with string key
TEST(YAMLNodeTest_195, MapOperatorBracket_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";

    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
    EXPECT_EQ(node.size(), 2u);
}

// Test map operator[] with Node key
TEST(YAMLNodeTest_195, MapOperatorBracketWithNodeKey_195) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

// Test map size
TEST(YAMLNodeTest_195, MapSize_195) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);

    node["a"] = 1;
    EXPECT_EQ(node.size(), 1u);

    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
}

// Test remove from map by key string
TEST(YAMLNodeTest_195, RemoveFromMap_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node.size(), 2u);

    EXPECT_TRUE(node.remove("key1"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["key1"].IsDefined());
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// Test remove non-existent key
TEST(YAMLNodeTest_195, RemoveNonExistentKey_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

// Test remove with Node key
TEST(YAMLNodeTest_195, RemoveWithNodeKey_195) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("key1");
    node[key] = "value1";
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(node.size(), 0u);
}

// Test is() method - same node
TEST(YAMLNodeTest_195, IsSameNode_195) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

// Test is() method - different nodes
TEST(YAMLNodeTest_195, IsDifferentNode_195) {
    YAML::Node node1("test");
    YAML::Node node2("test");
    EXPECT_FALSE(node1.is(node2));
}

// Test reset
TEST(YAMLNodeTest_195, Reset_195) {
    YAML::Node node1("original");
    YAML::Node node2("replacement");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.as<std::string>(), "replacement");
}

// Test begin/end iteration on sequence
TEST(YAMLNodeTest_195, SequenceIteration_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

// Test begin/end iteration on map
TEST(YAMLNodeTest_195, MapIteration_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["a"] = 1;
    node["b"] = 2;

    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// Test range-based for loop on sequence
TEST(YAMLNodeTest_195, RangeBasedForSequence_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("x");
    node.push_back("y");

    std::vector<std::string> values;
    for (const auto& item : node) {
        values.push_back(item.as<std::string>());
    }
    ASSERT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], "x");
    EXPECT_EQ(values[1], "y");
}

// Test operator! for undefined node
TEST(YAMLNodeTest_195, OperatorNot_UndefinedNode_195) {
    YAML::Node node;
    EXPECT_TRUE(!node);
}

// Test operator! for defined node
TEST(YAMLNodeTest_195, OperatorNot_DefinedNode_195) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

// Test explicit bool for defined node
TEST(YAMLNodeTest_195, BoolConversion_DefinedNode_195) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

// Test size of empty sequence
TEST(YAMLNodeTest_195, EmptySequenceSize_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

// Test size of empty map
TEST(YAMLNodeTest_195, EmptyMapSize_195) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

// Test force_insert
TEST(YAMLNodeTest_195, ForceInsert_195) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value");
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test force_insert allows duplicate keys
TEST(YAMLNodeTest_195, ForceInsertDuplicateKeys_195) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert should add both, so size should be 2
    EXPECT_EQ(node.size(), 2u);
}

// Test converting null node to sequence by push_back
TEST(YAMLNodeTest_195, NullToSequenceViaPushBack_195) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

// Test converting null node to map by operator[]
TEST(YAMLNodeTest_195, NullToMapViaOperatorBracket_195) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test reassigning scalar to different type
TEST(YAMLNodeTest_195, ReassignScalarToDifferentType_195) {
    YAML::Node node("string_value");
    EXPECT_TRUE(node.IsScalar());
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

// Test accessing non-existent map key returns undefined
TEST(YAMLNodeTest_195, NonExistentMapKeyReturnsUndefined_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["exists"] = "yes";
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["missing"].IsDefined());
}

// Test YAML::Load with scalar
TEST(YAMLNodeTest_195, LoadScalar_195) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test YAML::Load with sequence
TEST(YAMLNodeTest_195, LoadSequence_195) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

// Test YAML::Load with map
TEST(YAMLNodeTest_195, LoadMap_195) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

// Test YAML::Load with null
TEST(YAMLNodeTest_195, LoadNull_195) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

// Test YAML::Load with empty string throws
TEST(YAMLNodeTest_195, LoadEmptyString_195) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

// Test nested map access
TEST(YAMLNodeTest_195, NestedMapAccess_195) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

// Test nested sequence
TEST(YAMLNodeTest_195, NestedSequence_195) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[0][1].as<int>(), 2);
    EXPECT_EQ(node[1][0].as<int>(), 3);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// Test Mark() returns a mark
TEST(YAMLNodeTest_195, MarkReturnsValidMark_195) {
    YAML::Node node = YAML::Load("test");
    YAML::Mark mark = node.Mark();
    // Just verify we can call it without crashing
    // Default mark values are implementation-defined
    EXPECT_GE(mark.line, 0);
    EXPECT_GE(mark.column, 0);
}

// Test as<std::string> for integer scalar
TEST(YAMLNodeTest_195, IntScalarAsString_195) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<std::string>(), "42");
}

// Test empty scalar
TEST(YAMLNodeTest_195, EmptyScalar_195) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// Test overwriting map value
TEST(YAMLNodeTest_195, OverwriteMapValue_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "original";
    EXPECT_EQ(node["key"].as<std::string>(), "original");
    node["key"] = "updated";
    EXPECT_EQ(node["key"].as<std::string>(), "updated");
    EXPECT_EQ(node.size(), 1u);
}

// Test large sequence
TEST(YAMLNodeTest_195, LargeSequence_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), static_cast<std::size_t>(count));
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test sequence with mixed types
TEST(YAMLNodeTest_195, SequenceMixedTypes_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back("hello");
    node.push_back(true);
    node.push_back(3.14);

    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_EQ(node[2].as<bool>(), true);
    EXPECT_DOUBLE_EQ(node[3].as<double>(), 3.14);
}

// Test IsDefined on a defined node
TEST(YAMLNodeTest_195, IsDefinedOnDefinedNode_195) {
    YAML::Node node("defined");
    EXPECT_TRUE(node.IsDefined());
}

// Test IsDefined on null type node
TEST(YAMLNodeTest_195, IsDefinedOnNullTypeNode_195) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsDefined());
}

// Test SetStyle on default style
TEST(YAMLNodeTest_195, DefaultStyle_195) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// Test self-assignment
TEST(YAMLNodeTest_195, SelfAssignment_195) {
    YAML::Node node("value");
    node = node;
    EXPECT_EQ(node.as<std::string>(), "value");
}

// Test clone behavior (reset creates alias, not clone)
TEST(YAMLNodeTest_195, ResetCreatesAlias_195) {
    YAML::Node node1("original");
    YAML::Node node2("other");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    // Modifying node2 should be reflected in node1 since they alias
    node2 = "modified";
    EXPECT_EQ(node1.as<std::string>(), "modified");
}

// Test YAML::Load with bad YAML throws
TEST(YAMLNodeTest_195, LoadBadYAMLThrows_195) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: ["), YAML::ParserException);
}

// Test node with special characters in scalar
TEST(YAMLNodeTest_195, SpecialCharactersInScalar_195) {
    YAML::Node node("hello\nworld\ttab");
    EXPECT_EQ(node.as<std::string>(), "hello\nworld\ttab");
}

// Test that accessing undefined key via const operator[] doesn't create entry
TEST(YAMLNodeTest_195, ConstOperatorBracketDoesNotCreate_195) {
    YAML::Node node(YAML::NodeType::Map);
    node["existing"] = "value";
    const YAML::Node& constRef = node;
    YAML::Node result = constRef["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
    EXPECT_EQ(node.size(), 1u);  // Should still be 1
}
