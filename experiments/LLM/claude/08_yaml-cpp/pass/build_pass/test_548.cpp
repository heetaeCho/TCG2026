#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default constructor creates a defined node
TEST(NodeTest_548, DefaultConstructorIsDefined_548) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

// Test default constructor creates a Null type node
TEST(NodeTest_548, DefaultConstructorIsNull_548) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test explicit type constructor - Scalar
TEST(NodeTest_548, ScalarTypeConstructor_548) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
}

// Test explicit type constructor - Sequence
TEST(NodeTest_548, SequenceTypeConstructor_548) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsSequence());
}

// Test explicit type constructor - Map
TEST(NodeTest_548, MapTypeConstructor_548) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsMap());
}

// Test explicit type constructor - Null
TEST(NodeTest_548, NullTypeConstructor_548) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsNull());
}

// Test explicit type constructor - Undefined
TEST(NodeTest_548, UndefinedTypeConstructor_548) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// Test constructing from a string value
TEST(NodeTest_548, StringValueConstructor_548) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

// Test constructing from an integer value
TEST(NodeTest_548, IntValueConstructor_548) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test constructing from a double value
TEST(NodeTest_548, DoubleValueConstructor_548) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
}

// Test constructing from a bool value
TEST(NodeTest_548, BoolValueConstructor_548) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// Test copy constructor
TEST(NodeTest_548, CopyConstructor_548) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_TRUE(copy.IsDefined());
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// Test bool conversion operator for valid node
TEST(NodeTest_548, BoolOperatorTrue_548) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
}

// Test bool conversion operator for null node
TEST(NodeTest_548, BoolOperatorNull_548) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
}

// Test negation operator for null node
TEST(NodeTest_548, NegationOperatorNull_548) {
    YAML::Node node;
    EXPECT_TRUE(!node);
}

// Test negation operator for valid node
TEST(NodeTest_548, NegationOperatorValid_548) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

// Test Scalar() returns correct value
TEST(NodeTest_548, ScalarReturnsValue_548) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.Scalar(), "test_value");
}

// Test as<T>() conversion for string
TEST(NodeTest_548, AsString_548) {
    YAML::Node node("hello");
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test as<T>() conversion for int
TEST(NodeTest_548, AsInt_548) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

// Test as<T>() conversion for double
TEST(NodeTest_548, AsDouble_548) {
    YAML::Node node(2.5);
    EXPECT_DOUBLE_EQ(node.as<double>(), 2.5);
}

// Test as<T>() conversion for bool
TEST(NodeTest_548, AsBool_548) {
    YAML::Node node(false);
    EXPECT_EQ(node.as<bool>(), false);
}

// Test as<T, S>() with fallback when conversion fails
TEST(NodeTest_548, AsFallback_548) {
    YAML::Node node;
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

// Test as<T, S>() with fallback when conversion succeeds
TEST(NodeTest_548, AsFallbackNotUsed_548) {
    YAML::Node node(10);
    int result = node.as<int>(42);
    EXPECT_EQ(result, 10);
}

// Test assignment operator with value
TEST(NodeTest_548, AssignmentOperatorValue_548) {
    YAML::Node node;
    node = "assigned";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned");
}

// Test assignment operator with int
TEST(NodeTest_548, AssignmentOperatorInt_548) {
    YAML::Node node;
    node = 99;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 99);
}

// Test assignment operator with another node
TEST(NodeTest_548, AssignmentOperatorNode_548) {
    YAML::Node a("source");
    YAML::Node b;
    b = a;
    EXPECT_EQ(b.Scalar(), "source");
    EXPECT_TRUE(b.is(a));
}

// Test reset
TEST(NodeTest_548, Reset_548) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.Scalar(), "second");
}

// Test is() returns true for same node
TEST(NodeTest_548, IsSameNode_548) {
    YAML::Node a("test");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

// Test is() returns false for different nodes
TEST(NodeTest_548, IsDifferentNode_548) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// Test Tag and SetTag
TEST(NodeTest_548, SetAndGetTag_548) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

// Test Style and SetStyle
TEST(NodeTest_548, SetAndGetStyle_548) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test sequence - push_back and size
TEST(NodeTest_548, SequencePushBackAndSize_548) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// Test sequence - push_back with Node
TEST(NodeTest_548, SequencePushBackNode_548) {
    YAML::Node seq;
    YAML::Node child("item");
    seq.push_back(child);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq.size(), 1u);
}

// Test sequence - access by index
TEST(NodeTest_548, SequenceAccessByIndex_548) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

// Test sequence - begin and end iteration
TEST(NodeTest_548, SequenceIteration_548) {
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

// Test map - operator[] with string key
TEST(NodeTest_548, MapAccessByStringKey_548) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test map - multiple keys
TEST(NodeTest_548, MapMultipleKeys_548) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

// Test map - access by Node key
TEST(NodeTest_548, MapAccessByNodeKey_548) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
}

// Test map - remove by string key
TEST(NodeTest_548, MapRemoveByStringKey_548) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";
    EXPECT_EQ(node.size(), 2u);
    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

// Test map - remove non-existent key
TEST(NodeTest_548, MapRemoveNonExistentKey_548) {
    YAML::Node node;
    node["key1"] = "val1";
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

// Test map - remove by Node key
TEST(NodeTest_548, MapRemoveByNodeKey_548) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(node.size(), 1u);
    bool removed = node.remove(key);
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 0u);
}

// Test force_insert
TEST(NodeTest_548, ForceInsert_548) {
    YAML::Node node;
    node["key"] = "value1";
    node.force_insert("key", "value2");
    // force_insert should allow duplicate keys, increasing size
    EXPECT_EQ(node.size(), 2u);
}

// Test size of null/empty node
TEST(NodeTest_548, SizeOfNullNode_548) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

// Test size of scalar node
TEST(NodeTest_548, SizeOfScalarNode_548) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// Test IsDefined for undefined node from non-existent map key (const access)
TEST(NodeTest_548, UndefinedFromConstMapAccess_548) {
    YAML::Node node;
    node["existing"] = "value";
    const YAML::Node& cnode = node;
    YAML::Node result = cnode["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

// Test accessing non-existent key on const node returns undefined
TEST(NodeTest_548, ConstAccessNonExistentKey_548) {
    const YAML::Node node = YAML::Load("key: value");
    YAML::Node missing = node["missing"];
    EXPECT_FALSE(missing.IsDefined());
}

// Test YAML::Load with scalar
TEST(NodeTest_548, LoadScalar_548) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test YAML::Load with sequence
TEST(NodeTest_548, LoadSequence_548) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

// Test YAML::Load with map
TEST(NodeTest_548, LoadMap_548) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

// Test YAML::Load with null
TEST(NodeTest_548, LoadNull_548) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

// Test nested map access
TEST(NodeTest_548, NestedMapAccess_548) {
    YAML::Node node = YAML::Load("outer:\n  inner: value");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

// Test nested sequence access
TEST(NodeTest_548, NestedSequenceAccess_548) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[0][1].as<int>(), 2);
    EXPECT_EQ(node[1][0].as<int>(), 3);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// Test map iteration
TEST(NodeTest_548, MapIteration_548) {
    YAML::Node node = YAML::Load("{x: 10, y: 20}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test empty sequence size
TEST(NodeTest_548, EmptySequenceSize_548) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test empty map size
TEST(NodeTest_548, EmptyMapSize_548) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// Test as<T>() throws for invalid conversion
TEST(NodeTest_548, AsThrowsOnInvalidConversion_548) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::BadConversion);
}

// Test as<T>() on undefined node throws
TEST(NodeTest_548, AsThrowsOnUndefinedNode_548) {
    const YAML::Node node = YAML::Load("key: value");
    YAML::Node missing = node["missing"];
    EXPECT_THROW(missing.as<std::string>(), YAML::Exception);
}

// Test Mark returns valid mark
TEST(NodeTest_548, MarkReturnsValidMark_548) {
    YAML::Node node = YAML::Load("hello");
    YAML::Mark mark = node.Mark();
    // Just verify it doesn't throw; mark values are implementation-dependent
    (void)mark;
}

// Test overwriting a scalar value
TEST(NodeTest_548, OverwriteScalarValue_548) {
    YAML::Node node("original");
    node = "modified";
    EXPECT_EQ(node.as<std::string>(), "modified");
}

// Test changing node type from scalar to sequence
TEST(NodeTest_548, ChangeTypeScalarToSequence_548) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
}

// Test changing node type from scalar to map
TEST(NodeTest_548, ChangeTypeScalarToMap_548) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

// Test IsDefined returns true for constructed scalar node
TEST(NodeTest_548, IsDefinedTrueForScalar_548) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsDefined());
}

// Test IsNull, IsScalar, IsSequence, IsMap are mutually exclusive
TEST(NodeTest_548, TypeChecksMutuallyExclusive_548) {
    YAML::Node scalar("val");
    EXPECT_TRUE(scalar.IsScalar());
    EXPECT_FALSE(scalar.IsNull());
    EXPECT_FALSE(scalar.IsSequence());
    EXPECT_FALSE(scalar.IsMap());

    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_FALSE(seq.IsScalar());
    EXPECT_FALSE(seq.IsNull());
    EXPECT_FALSE(seq.IsMap());

    YAML::Node map(YAML::NodeType::Map);
    EXPECT_TRUE(map.IsMap());
    EXPECT_FALSE(map.IsScalar());
    EXPECT_FALSE(map.IsNull());
    EXPECT_FALSE(map.IsSequence());

    YAML::Node null;
    EXPECT_TRUE(null.IsNull());
    EXPECT_FALSE(null.IsScalar());
    EXPECT_FALSE(null.IsSequence());
    EXPECT_FALSE(null.IsMap());
}

// Test default style
TEST(NodeTest_548, DefaultStyleIsDefault_548) {
    YAML::Node node("value");
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// Test SetStyle Block
TEST(NodeTest_548, SetStyleBlock_548) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// Test large sequence
TEST(NodeTest_548, LargeSequence_548) {
    YAML::Node node;
    for (int i = 0; i < 1000; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// Test that accessing the same key twice returns the same value
TEST(NodeTest_548, MapAccessSameKeyTwice_548) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_EQ(node["key"].as<std::string>(), "value");
    EXPECT_EQ(node["key"].as<std::string>(), "value");
    EXPECT_EQ(node.size(), 1u);
}

// Test Tag is empty by default
TEST(NodeTest_548, TagEmptyByDefault_548) {
    YAML::Node node("value");
    EXPECT_EQ(node.Tag(), "?");
}

// Test YAML::Load with tagged value
TEST(NodeTest_548, LoadTaggedValue_548) {
    YAML::Node node = YAML::Load("!mytag value");
    EXPECT_EQ(node.Tag(), "!mytag");
    EXPECT_EQ(node.as<std::string>(), "value");
}

// Test exception on YAML parse error
TEST(NodeTest_548, LoadInvalidYAMLThrows_548) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: :::"), YAML::Exception);
}

// Test constructor from const char*
TEST(NodeTest_548, ConstructFromConstCharPtr_548) {
    YAML::Node node("hello world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello world");
}

// Test assigning empty string
TEST(NodeTest_548, AssignEmptyString_548) {
    YAML::Node node;
    node = "";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// Test sequence with mixed types
TEST(NodeTest_548, SequenceMixedTypes_548) {
    YAML::Node node;
    node.push_back(1);
    node.push_back("two");
    node.push_back(3.0);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<std::string>(), "two");
    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.0);
}

// Test map with integer keys
TEST(NodeTest_548, MapWithIntegerKeys_548) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}
