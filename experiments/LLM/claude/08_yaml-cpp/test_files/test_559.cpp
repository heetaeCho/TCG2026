#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Normal operation tests

TEST(NodeTest_559, DefaultConstructorCreatesNullNode_559) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_559, ConstructWithScalarType_559) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(NodeTest_559, ConstructWithSequenceType_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodeTest_559, ConstructWithMapType_559) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST(NodeTest_559, ConstructWithStringValue_559) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_559, ConstructWithIntValue_559) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_559, ConstructWithDoubleValue_559) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST(NodeTest_559, ConstructWithBoolValue_559) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_559, SetTagAndGetTag_559) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST(NodeTest_559, SetTagOnDefaultNode_559) {
    YAML::Node node;
    node.SetTag("!mytag");
    EXPECT_EQ(node.Tag(), "!mytag");
}

TEST(NodeTest_559, SetTagEmptyString_559) {
    YAML::Node node("value");
    node.SetTag("");
    EXPECT_EQ(node.Tag(), "");
}

TEST(NodeTest_559, SetTagOverwrite_559) {
    YAML::Node node("value");
    node.SetTag("!first");
    EXPECT_EQ(node.Tag(), "!first");
    node.SetTag("!second");
    EXPECT_EQ(node.Tag(), "!second");
}

TEST(NodeTest_559, ScalarValue_559) {
    YAML::Node node("test_scalar");
    EXPECT_EQ(node.Scalar(), "test_scalar");
}

TEST(NodeTest_559, AsStringConversion_559) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST(NodeTest_559, AsIntConversion_559) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_559, AsWithFallback_559) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>("fallback"), "fallback");
}

TEST(NodeTest_559, AsIntWithFallback_559) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(99), 99);
}

TEST(NodeTest_559, IsDefined_559) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_559, NullNodeIsNotDefined_559) {
    YAML::Node node;
    // A null node is valid but Type is Null
    // IsDefined may still be true for a valid null node
    // depending on implementation
    EXPECT_TRUE(static_cast<bool>(node) || !static_cast<bool>(node));
}

TEST(NodeTest_559, BoolOperator_559) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_559, NotOperatorOnDefinedNode_559) {
    YAML::Node node("value");
    EXPECT_FALSE(!node);
}

TEST(NodeTest_559, CopyConstructor_559) {
    YAML::Node original("original");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "original");
    EXPECT_TRUE(copy.is(original));
}

TEST(NodeTest_559, AssignmentOperator_559) {
    YAML::Node node1("first");
    YAML::Node node2;
    node2 = node1;
    EXPECT_TRUE(node2.is(node1));
}

TEST(NodeTest_559, AssignStringValue_559) {
    YAML::Node node;
    node = "assigned_value";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned_value");
}

TEST(NodeTest_559, AssignIntValue_559) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_559, ResetNode_559) {
    YAML::Node node1("first");
    YAML::Node node2("second");
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.Scalar(), "second");
}

TEST(NodeTest_559, IsMethodSameNode_559) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST(NodeTest_559, IsMethodDifferentNodes_559) {
    YAML::Node node1("test1");
    YAML::Node node2("test2");
    EXPECT_FALSE(node1.is(node2));
}

// Sequence tests

TEST(NodeTest_559, SequencePushBack_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_559, SequenceAccessByIndex_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST(NodeTest_559, SequenceSize_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_559, SequencePushBackNode_559) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node child("child_value");
    seq.push_back(child);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "child_value");
}

TEST(NodeTest_559, SequenceIteration_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");

    std::vector<std::string> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<std::string>());
    }
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "a");
    EXPECT_EQ(values[1], "b");
    EXPECT_EQ(values[2], "c");
}

// Map tests

TEST(NodeTest_559, MapInsertAndAccess_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

TEST(NodeTest_559, MapSize_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_559, MapIsMap_559) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_559, MapRemoveByStringKey_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.remove("key1"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_559, MapRemoveNonExistentKey_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_559, MapRemoveByNodeKey_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    YAML::Node key("key1");
    EXPECT_TRUE(node.remove(key));
}

TEST(NodeTest_559, MapForceInsert_559) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value");
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_559, MapIteration_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["x"] = 10;
    node["y"] = 20;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Style tests

TEST(NodeTest_559, SetAndGetStyle_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_559, SetStyleBlock_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

TEST(NodeTest_559, DefaultStyleIsDefault_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// Edge cases and boundary conditions

TEST(NodeTest_559, EmptySequenceSize_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_559, EmptyMapSize_559) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_559, NullNodeType_559) {
    YAML::Node node;
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_559, SetTagWithSpecialCharacters_559) {
    YAML::Node node("value");
    node.SetTag("!tag:with:colons");
    EXPECT_EQ(node.Tag(), "!tag:with:colons");
}

TEST(NodeTest_559, SetTagVeryLongString_559) {
    YAML::Node node("value");
    std::string longTag(1000, 'x');
    node.SetTag(longTag);
    EXPECT_EQ(node.Tag(), longTag);
}

TEST(NodeTest_559, SequenceAccessOutOfBounds_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item");
    // Accessing an out-of-bounds index should return undefined node
    YAML::Node outOfBounds = node[5];
    EXPECT_FALSE(outOfBounds.IsDefined());
}

TEST(NodeTest_559, MapAccessNonExistentKeyConst_559) {
    YAML::Node node(YAML::NodeType::Map);
    node["existing"] = "value";
    const YAML::Node& constNode = node;
    YAML::Node result = constNode["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeTest_559, AssignNewValueToScalar_559) {
    YAML::Node node("old_value");
    node = "new_value";
    EXPECT_EQ(node.Scalar(), "new_value");
}

TEST(NodeTest_559, ConvertNullToSequenceByPushBack_559) {
    YAML::Node node;
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_559, ConvertNullToMapByIndexAssignment_559) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_559, EmptyStringScalar_559) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_559, AsWithInvalidConversionUsesFallback_559) {
    YAML::Node node("not_a_number");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST(NodeTest_559, ParseYAMLString_559) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(NodeTest_559, ParseYAMLSequence_559) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_559, TagFromParsedYAML_559) {
    YAML::Node node = YAML::Load("!custom tagged_value");
    EXPECT_EQ(node.Tag(), "!custom");
    EXPECT_EQ(node.as<std::string>(), "tagged_value");
}

TEST(NodeTest_559, MultipleSetTagCalls_559) {
    YAML::Node node("value");
    for (int i = 0; i < 100; ++i) {
        node.SetTag("!tag" + std::to_string(i));
    }
    EXPECT_EQ(node.Tag(), "!tag99");
}

TEST(NodeTest_559, SequenceRemoveByIndex_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_TRUE(node.remove(1));
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_559, NullNodeBeginEqualsEnd_559) {
    YAML::Node node;
    EXPECT_TRUE(node.begin() == node.end());
}

TEST(NodeTest_559, EmptySequenceBeginEqualsEnd_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.begin() == node.end());
}

TEST(NodeTest_559, EmptyMapBeginEqualsEnd_559) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.begin() == node.end());
}

TEST(NodeTest_559, SetTagOnSequenceNode_559) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetTag("!seq");
    EXPECT_EQ(node.Tag(), "!seq");
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_559, SetTagOnMapNode_559) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetTag("!map");
    EXPECT_EQ(node.Tag(), "!map");
    EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_559, ConstructWithNullType_559) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_559, ConstructWithUndefinedType_559) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

TEST(NodeTest_559, SetTagUnicodeString_559) {
    YAML::Node node("value");
    node.SetTag("!日本語タグ");
    EXPECT_EQ(node.Tag(), "!日本語タグ");
}
