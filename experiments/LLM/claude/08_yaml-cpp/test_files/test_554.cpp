#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor creates a valid Null node
TEST(NodeTest_554, DefaultConstructorCreatesNullNode_554) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test constructing with a scalar value
TEST(NodeTest_554, ScalarConstructor_554) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test constructing with explicit type
TEST(NodeTest_554, ExplicitTypeConstructorScalar_554) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTest_554, ExplicitTypeConstructorSequence_554) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_554, ExplicitTypeConstructorMap_554) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_554, ExplicitTypeConstructorNull_554) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

// Test as<string> for scalar node
TEST(NodeAsTest_554, AsStringFromScalar_554) {
    YAML::Node node("world");
    EXPECT_EQ(node.as<std::string>(), "world");
}

// Test as<string> for null node returns "null"
TEST(NodeAsTest_554, AsStringFromNullReturnsNull_554) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>(), "null");
}

// Test as<int> from scalar
TEST(NodeAsTest_554, AsIntFromScalar_554) {
    YAML::Node node("42");
    EXPECT_EQ(node.as<int>(), 42);
}

// Test as<double> from scalar
TEST(NodeAsTest_554, AsDoubleFromScalar_554) {
    YAML::Node node("3.14");
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

// Test as<bool> from scalar
TEST(NodeAsTest_554, AsBoolFromScalar_554) {
    YAML::Node nodeTrue("true");
    EXPECT_TRUE(nodeTrue.as<bool>());

    YAML::Node nodeFalse("false");
    EXPECT_FALSE(nodeFalse.as<bool>());
}

// Test as<string> with fallback on undefined node
TEST(NodeAsTest_554, AsStringWithFallbackOnUndefined_554) {
    YAML::Node node;
    YAML::Node child = node["nonexistent"];
    EXPECT_EQ(child.as<std::string>("default_value"), "default_value");
}

// Test as<int> with fallback
TEST(NodeAsTest_554, AsIntWithFallback_554) {
    YAML::Node node;
    YAML::Node child = node["nonexistent"];
    EXPECT_EQ(child.as<int>(99), 99);
}

// Test as<string> throws on sequence node (non-scalar, non-null, non-undefined)
TEST(NodeAsTest_554, AsStringThrowsOnSequenceNode_554) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    EXPECT_THROW(node.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

// Test as<string> throws on map node
TEST(NodeAsTest_554, AsStringThrowsOnMapNode_554) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    EXPECT_THROW(node.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

// Test IsDefined
TEST(NodeTest_554, IsDefinedForValidNode_554) {
    YAML::Node node("test");
    EXPECT_TRUE(node.IsDefined());
}

// Test copy constructor
TEST(NodeTest_554, CopyConstructor_554) {
    YAML::Node original("original");
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "original");
}

// Test operator bool
TEST(NodeTest_554, OperatorBool_554) {
    YAML::Node defined("test");
    EXPECT_TRUE(static_cast<bool>(defined));

    YAML::Node null;
    // Null node is still "valid" but evaluates to false
    EXPECT_FALSE(static_cast<bool>(null));
}

// Test operator!
TEST(NodeTest_554, OperatorNot_554) {
    YAML::Node node("test");
    EXPECT_FALSE(!node);

    YAML::Node null;
    EXPECT_TRUE(!null);
}

// Test IsNull, IsScalar, IsSequence, IsMap
TEST(NodeTest_554, TypeCheckers_554) {
    YAML::Node nullNode;
    EXPECT_TRUE(nullNode.IsNull());
    EXPECT_FALSE(nullNode.IsScalar());
    EXPECT_FALSE(nullNode.IsSequence());
    EXPECT_FALSE(nullNode.IsMap());

    YAML::Node scalarNode("hello");
    EXPECT_FALSE(scalarNode.IsNull());
    EXPECT_TRUE(scalarNode.IsScalar());
    EXPECT_FALSE(scalarNode.IsSequence());
    EXPECT_FALSE(scalarNode.IsMap());
}

// Test sequence operations
TEST(NodeTest_554, SequencePushBackAndSize_554) {
    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_EQ(seq.size(), 0u);

    seq.push_back("item1");
    seq.push_back("item2");
    seq.push_back("item3");
    EXPECT_EQ(seq.size(), 3u);
}

// Test sequence iteration
TEST(NodeTest_554, SequenceIteration_554) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(3);

    int sum = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(sum, 6);
}

// Test map operations
TEST(NodeTest_554, MapInsertAndAccess_554) {
    YAML::Node map(YAML::NodeType::Map);
    map["key1"] = "value1";
    map["key2"] = "value2";

    EXPECT_EQ(map["key1"].as<std::string>(), "value1");
    EXPECT_EQ(map["key2"].as<std::string>(), "value2");
    EXPECT_EQ(map.size(), 2u);
}

// Test map remove
TEST(NodeTest_554, MapRemove_554) {
    YAML::Node map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    EXPECT_TRUE(map.remove("key1"));
    EXPECT_EQ(map.size(), 1u);
    EXPECT_FALSE(map["key1"].IsDefined());
}

// Test remove nonexistent key
TEST(NodeTest_554, MapRemoveNonexistent_554) {
    YAML::Node map;
    map["key1"] = "value1";
    EXPECT_FALSE(map.remove("nonexistent"));
}

// Test assignment operator
TEST(NodeTest_554, AssignmentOperator_554) {
    YAML::Node node;
    node = "assigned_value";
    EXPECT_EQ(node.as<std::string>(), "assigned_value");
}

// Test node assignment from another node
TEST(NodeTest_554, NodeAssignment_554) {
    YAML::Node original("original");
    YAML::Node copy;
    copy = original;
    EXPECT_EQ(copy.as<std::string>(), "original");
}

// Test reset
TEST(NodeTest_554, Reset_554) {
    YAML::Node node("initial");
    YAML::Node other("other");
    node.reset(other);
    EXPECT_EQ(node.as<std::string>(), "other");
}

// Test is() - same node identity
TEST(NodeTest_554, IsSameNode_554) {
    YAML::Node node("test");
    YAML::Node copy = node;
    EXPECT_TRUE(node.is(copy));

    YAML::Node different("test");
    EXPECT_FALSE(node.is(different));
}

// Test SetTag and Tag
TEST(NodeTest_554, TagOperations_554) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

// Test SetStyle and Style
TEST(NodeTest_554, StyleOperations_554) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(1);
    seq.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(seq.Style(), YAML::EmitterStyle::Flow);
}

// Test sequence subscript operator with integer index
TEST(NodeTest_554, SequenceSubscriptByIndex_554) {
    YAML::Node seq;
    seq.push_back("first");
    seq.push_back("second");
    seq.push_back("third");

    EXPECT_EQ(seq[0].as<std::string>(), "first");
    EXPECT_EQ(seq[1].as<std::string>(), "second");
    EXPECT_EQ(seq[2].as<std::string>(), "third");
}

// Test node constructed from integer
TEST(NodeTest_554, IntegerConstructor_554) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
    EXPECT_TRUE(node.IsScalar());
}

// Test node constructed from boolean
TEST(NodeTest_554, BooleanConstructor_554) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

// Test force_insert on map
TEST(NodeTest_554, ForceInsert_554) {
    YAML::Node map;
    map["key"] = "value1";
    map.force_insert("key", "value2");
    // force_insert adds duplicate keys; size should be 2
    EXPECT_EQ(map.size(), 2u);
}

// Test empty sequence size
TEST(NodeTest_554, EmptySequenceSize_554) {
    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_EQ(seq.size(), 0u);
}

// Test empty map size
TEST(NodeTest_554, EmptyMapSize_554) {
    YAML::Node map(YAML::NodeType::Map);
    EXPECT_EQ(map.size(), 0u);
}

// Test as<string> with fallback on null returns "null" (no fallback used since node is valid)
TEST(NodeAsTest_554, AsStringWithFallbackOnNull_554) {
    YAML::Node node;
    // Null node should return "null" not the fallback, since it's a valid node
    EXPECT_EQ(node.as<std::string>("fallback"), "null");
}

// Test as<int> with fallback on null node
TEST(NodeAsTest_554, AsIntWithFallbackOnNull_554) {
    YAML::Node node;
    // Null node - conversion to int should fail and use fallback
    EXPECT_EQ(node.as<int>(123), 123);
}

// Test that accessing nonexistent key in const map returns undefined
TEST(NodeTest_554, ConstMapNonexistentKeyUndefined_554) {
    YAML::Node map;
    map["exists"] = "value";
    const YAML::Node& constMap = map;
    EXPECT_FALSE(constMap["nonexistent"].IsDefined());
}

// Test push_back with Node
TEST(NodeTest_554, PushBackNode_554) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node item("item");
    seq.push_back(item);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "item");
}

// Test map iteration
TEST(NodeTest_554, MapIteration_554) {
    YAML::Node map;
    map["a"] = 1;
    map["b"] = 2;

    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test Scalar() on non-scalar throws or returns empty
TEST(NodeTest_554, ScalarOnScalarNode_554) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

// Test constructing node from float
TEST(NodeTest_554, FloatConstructor_554) {
    YAML::Node node(3.14);
    EXPECT_NEAR(node.as<double>(), 3.14, 0.01);
}

// Test as with fallback on scalar (fallback not used)
TEST(NodeAsTest_554, AsStringWithFallbackOnScalar_554) {
    YAML::Node node("actual");
    EXPECT_EQ(node.as<std::string>("fallback"), "actual");
}

// Test remove with Node key
TEST(NodeTest_554, RemoveWithNodeKey_554) {
    YAML::Node map;
    map["key1"] = "val1";
    map["key2"] = "val2";

    YAML::Node key("key1");
    EXPECT_TRUE(map.remove(key));
    EXPECT_EQ(map.size(), 1u);
}

// Test that undefined node's as<string>() throws InvalidNode
TEST(NodeAsTest_554, AsStringThrowsOnUndefinedNode_554) {
    YAML::Node map;
    map["exists"] = "value";
    const YAML::Node& constMap = map;
    YAML::Node undefined = constMap["nonexistent"];
    EXPECT_THROW(undefined.as<std::string>(), YAML::InvalidNode);
}

// Test Mark on a programmatically constructed node
TEST(NodeTest_554, MarkOnConstructedNode_554) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // Programmatically constructed nodes typically have null marks
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// Test loading from YAML string and accessing
TEST(NodeTest_554, LoadAndAccess_554) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

// Test loading map from YAML string
TEST(NodeTest_554, LoadMapAndAccess_554) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

// Test nested structures
TEST(NodeTest_554, NestedStructure_554) {
    YAML::Node node = YAML::Load("{list: [1, 2, 3]}");
    EXPECT_TRUE(node["list"].IsSequence());
    EXPECT_EQ(node["list"].size(), 3u);
    EXPECT_EQ(node["list"][0].as<int>(), 1);
}
