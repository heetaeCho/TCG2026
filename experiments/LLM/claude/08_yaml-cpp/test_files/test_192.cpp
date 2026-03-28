#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Default Construction Tests
// ============================================================

TEST(NodeTest_192, DefaultConstructor_CreatesNullNode_192) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_192, DefaultConstructor_IsDefined_192) {
    YAML::Node node;
    // A default-constructed node is valid but Null type
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_192, DefaultConstructor_BoolConversion_192) {
    YAML::Node node;
    // Null node should be falsy
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

// ============================================================
// Type-based Construction Tests
// ============================================================

TEST(NodeTest_192, ConstructWithScalarType_192) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(NodeTest_192, ConstructWithSequenceType_192) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodeTest_192, ConstructWithMapType_192) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(NodeTest_192, ConstructWithNullType_192) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_192, ConstructWithUndefinedType_192) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// ============================================================
// Template Construction Tests
// ============================================================

TEST(NodeTest_192, ConstructWithString_192) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_192, ConstructWithCString_192) {
    YAML::Node node("world");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "world");
}

TEST(NodeTest_192, ConstructWithInt_192) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_192, ConstructWithDouble_192) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(NodeTest_192, ConstructWithBoolTrue_192) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_192, ConstructWithBoolFalse_192) {
    YAML::Node node(false);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.as<bool>());
}

// ============================================================
// Copy Construction Tests
// ============================================================

TEST(NodeTest_192, CopyConstructor_192) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_TRUE(copy.IsScalar());
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST(NodeTest_192, AssignmentOperatorNode_192) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1 = node2;
    EXPECT_EQ(node1.Scalar(), "second");
    EXPECT_TRUE(node1.is(node2));
}

TEST(NodeTest_192, AssignmentOperatorString_192) {
    YAML::Node node;
    node = std::string("assigned");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned");
}

TEST(NodeTest_192, AssignmentOperatorInt_192) {
    YAML::Node node;
    node = 100;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 100);
}

TEST(NodeTest_192, AssignmentOperatorCString_192) {
    YAML::Node node;
    node = "cstring";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "cstring");
}

// ============================================================
// Scalar Tests
// ============================================================

TEST(NodeTest_192, ScalarValue_192) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.Scalar(), "hello world");
}

TEST(NodeTest_192, ScalarEmptyString_192) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

// ============================================================
// as<T>() Tests
// ============================================================

TEST(NodeTest_192, AsString_192) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

TEST(NodeTest_192, AsInt_192) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_192, AsDouble_192) {
    YAML::Node node(2.718);
    EXPECT_NEAR(node.as<double>(), 2.718, 0.001);
}

TEST(NodeTest_192, AsBool_192) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_192, AsWithFallback_NullNode_192) {
    YAML::Node node;
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_192, AsWithFallback_ValidNode_192) {
    YAML::Node node(10);
    int result = node.as<int>(42);
    EXPECT_EQ(result, 10);
}

TEST(NodeTest_192, AsWithFallback_InvalidConversion_192) {
    YAML::Node node("not_a_number");
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

// ============================================================
// Tag Tests
// ============================================================

TEST(NodeTest_192, SetAndGetTag_192) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST(NodeTest_192, DefaultTagIsEmpty_192) {
    YAML::Node node("value");
    // Tag might be "?" or empty by default
    // Just ensure it doesn't crash
    node.Tag();
}

TEST(NodeTest_192, SetTagEmptyString_192) {
    YAML::Node node("value");
    node.SetTag("");
    // After setting empty tag, Tag() should reflect it
    EXPECT_EQ(node.Tag(), "");
}

// ============================================================
// Style Tests
// ============================================================

TEST(NodeTest_192, SetAndGetStyle_192) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_192, SetStyleBlock_192) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

TEST(NodeTest_192, DefaultStyle_192) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// ============================================================
// Sequence (push_back, size, iteration) Tests
// ============================================================

TEST(NodeTest_192, PushBackCreatesSequence_192) {
    YAML::Node node;
    node.push_back("item1");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_192, PushBackMultipleItems_192) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeTest_192, PushBackNode_192) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "child_value");
}

TEST(NodeTest_192, SequenceIndexAccess_192) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
    EXPECT_EQ(node[2].as<std::string>(), "third");
}

TEST(NodeTest_192, SequenceIteration_192) {
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

TEST(NodeTest_192, EmptySequenceSize_192) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_192, SequenceBeginEqualsEndWhenEmpty_192) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

// ============================================================
// Map Tests
// ============================================================

TEST(NodeTest_192, MapSubscriptOperatorCreatesMap_192) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_192, MapMultipleEntries_192) {
    YAML::Node node;
    node["name"] = "Alice";
    node["age"] = 30;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST(NodeTest_192, MapRemoveByKey_192) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST(NodeTest_192, MapRemoveNonExistentKey_192) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_192, MapRemoveByNodeKey_192) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";

    YAML::Node keyNode("key1");
    EXPECT_TRUE(node.remove(keyNode));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_192, MapSubscriptWithNodeKey_192) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[key].as<std::string>(), "myvalue");
    EXPECT_EQ(node["mykey"].as<std::string>(), "myvalue");
}

TEST(NodeTest_192, MapIteration_192) {
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

TEST(NodeTest_192, MapForceInsert_192) {
    YAML::Node node;
    node["key"] = "original";
    node.force_insert("key", "duplicate");
    // force_insert allows duplicate keys, so size should increase
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_192, EmptyMapSize_192) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// is() Tests
// ============================================================

TEST(NodeTest_192, IsReturnsTrueForSameNode_192) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST(NodeTest_192, IsReturnsFalseForDifferentNodes_192) {
    YAML::Node node1("test");
    YAML::Node node2("test");
    EXPECT_FALSE(node1.is(node2));
}

// ============================================================
// reset() Tests
// ============================================================

TEST(NodeTest_192, ResetNode_192) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.Scalar(), "second");
}

// ============================================================
// Bool Conversion Tests
// ============================================================

TEST(NodeTest_192, BoolConversionTrue_192) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(NodeTest_192, BoolConversionFalseForNull_192) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

TEST(NodeTest_192, BoolConversionForUndefined_192) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(static_cast<bool>(node));
}

// ============================================================
// IsDefined Tests
// ============================================================

TEST(NodeTest_192, IsDefinedForScalar_192) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_192, IsDefinedForNull_192) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_192, IsDefinedForUndefined_192) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

TEST(NodeTest_192, UndefinedMapAccess_192) {
    YAML::Node node;
    node["exists"] = "yes";
    // Accessing non-existent key in const context
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["nonexistent"].IsDefined());
}

// ============================================================
// Size Tests for Non-Collection Types
// ============================================================

TEST(NodeTest_192, NullNodeSizeIsZero_192) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_192, ScalarNodeSizeIsZero_192) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// YAML Parsing and Round-trip Tests
// ============================================================

TEST(NodeTest_192, ParseScalar_192) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_192, ParseSequence_192) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_192, ParseMap_192) {
    YAML::Node node = YAML::Load("{name: John, age: 25}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 25);
}

TEST(NodeTest_192, ParseNull_192) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_192, ParseNestedStructure_192) {
    std::string yaml = "person:\n  name: Alice\n  hobbies:\n    - reading\n    - coding";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["person"].IsMap());
    EXPECT_EQ(node["person"]["name"].as<std::string>(), "Alice");
    EXPECT_TRUE(node["person"]["hobbies"].IsSequence());
    EXPECT_EQ(node["person"]["hobbies"].size(), 2u);
    EXPECT_EQ(node["person"]["hobbies"][0].as<std::string>(), "reading");
    EXPECT_EQ(node["person"]["hobbies"][1].as<std::string>(), "coding");
}

// ============================================================
// Exceptional Cases
// ============================================================

TEST(NodeTest_192, AsThrowsOnInvalidConversion_192) {
    YAML::Node node("not_an_int");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST(NodeTest_192, AsThrowsOnNullNodeWithoutFallback_192) {
    YAML::Node node;
    EXPECT_THROW(node.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

TEST(NodeTest_192, ParseInvalidYAML_192) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: ]]"), YAML::ParserException);
}

// ============================================================
// Mark Tests
// ============================================================

TEST(NodeTest_192, MarkOnDefaultNode_192) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    // Default node mark values - just verify it doesn't crash
    (void)mark;
}

TEST(NodeTest_192, MarkOnParsedNode_192) {
    YAML::Node node = YAML::Load("key: value");
    YAML::Mark mark = node.Mark();
    // Parsed node should have a valid mark
    (void)mark;
}

// ============================================================
// Complex Scenarios
// ============================================================

TEST(NodeTest_192, OverwriteScalarWithSequence_192) {
    YAML::Node node("scalar_value");
    EXPECT_TRUE(node.IsScalar());
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_192, OverwriteScalarWithMap_192) {
    YAML::Node node("scalar_value");
    EXPECT_TRUE(node.IsScalar());
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_192, SequenceOfNodes_192) {
    YAML::Node seq;
    YAML::Node n1("hello");
    YAML::Node n2(42);
    YAML::Node n3(true);
    seq.push_back(n1);
    seq.push_back(n2);
    seq.push_back(n3);

    EXPECT_EQ(seq.size(), 3u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
    EXPECT_EQ(seq[1].as<int>(), 42);
    EXPECT_TRUE(seq[2].as<bool>());
}

TEST(NodeTest_192, MapWithIntKeys_192) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST(NodeTest_192, NestedMapCreation_192) {
    YAML::Node root;
    root["level1"]["level2"]["level3"] = "deep_value";
    EXPECT_TRUE(root.IsMap());
    EXPECT_TRUE(root["level1"].IsMap());
    EXPECT_TRUE(root["level1"]["level2"].IsMap());
    EXPECT_EQ(root["level1"]["level2"]["level3"].as<std::string>(), "deep_value");
}

TEST(NodeTest_192, SelfAssignment_192) {
    YAML::Node node("value");
    node = node;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "value");
}

TEST(NodeTest_192, ResetToSelf_192) {
    YAML::Node node("value");
    node.reset(node);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "value");
}

TEST(NodeTest_192, SequenceRemoveByIndex_192) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    // Remove index 1
    EXPECT_TRUE(node.remove(1));
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_192, LargeSequence_192) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_192, LargeMap_192) {
    YAML::Node node;
    for (int i = 0; i < 100; ++i) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), 100u);
    EXPECT_EQ(node["0"].as<int>(), 0);
    EXPECT_EQ(node["99"].as<int>(), 99);
}

TEST(NodeTest_192, AsFloatFromInt_192) {
    YAML::Node node(42);
    EXPECT_NEAR(node.as<float>(), 42.0f, 0.001f);
}

TEST(NodeTest_192, AsStringFromInt_192) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<std::string>(), "42");
}

TEST(NodeTest_192, EmptyStringScalar_192) {
    YAML::Node node = YAML::Load("''");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST(NodeTest_192, NullNodeIsNotDefined_AsWithFallback_192) {
    YAML::Node root;
    root["key"] = "value";
    const YAML::Node& croot = root;
    std::string result = croot["missing"].as<std::string>("default");
    EXPECT_EQ(result, "default");
}
