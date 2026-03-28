#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// Test fixture
class NodeTest_555 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(NodeTest_555, DefaultConstructor_CreatesNullNode_555) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_555, ConstructWithScalarType_555) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_555, ConstructWithSequenceType_555) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_555, ConstructWithMapType_555) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
}

TEST_F(NodeTest_555, ConstructWithStringValue_555) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_555, ConstructWithIntValue_555) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_555, ConstructWithDoubleValue_555) {
    YAML::Node node(3.14);
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST_F(NodeTest_555, ConstructWithBoolValue_555) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_555, CopyConstructor_555) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test");
}

// ==================== Type Query Tests ====================

TEST_F(NodeTest_555, IsNull_DefaultNode_555) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_555, IsScalar_StringNode_555) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_555, IsSequence_AfterPushBack_555) {
    YAML::Node node;
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_555, IsMap_AfterSubscript_555) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

// ==================== Bool Operator Tests ====================

TEST_F(NodeTest_555, BoolOperator_ValidNode_555) {
    YAML::Node node("test");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_555, BoolOperator_NullNode_555) {
    YAML::Node node;
    // A null node is valid but not defined in some contexts
    // The bool operator checks for defined-ness
    // Default constructed node should be valid
}

// ==================== as<T>() Tests ====================

TEST_F(NodeTest_555, AsString_555) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(NodeTest_555, AsInt_555) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST_F(NodeTest_555, AsDouble_555) {
    YAML::Node node(2.718);
    EXPECT_DOUBLE_EQ(node.as<double>(), 2.718);
}

TEST_F(NodeTest_555, AsBool_True_555) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_555, AsBool_False_555) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_555, AsFloat_555) {
    YAML::Node node(1.5f);
    EXPECT_FLOAT_EQ(node.as<float>(), 1.5f);
}

TEST_F(NodeTest_555, AsWithFallback_ValidNode_555) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(99), 42);
}

TEST_F(NodeTest_555, AsWithFallback_NullNode_555) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(99), 99);
}

TEST_F(NodeTest_555, AsWithFallback_UndefinedNode_555) {
    YAML::Node node;
    // Accessing a non-existent key returns an undefined node
    YAML::Node child = node["nonexistent"];
    EXPECT_EQ(child.as<std::string>("default_val"), "default_val");
}

// ==================== Scalar Tests ====================

TEST_F(NodeTest_555, Scalar_ReturnsValue_555) {
    YAML::Node node("scalar_value");
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

TEST_F(NodeTest_555, Scalar_EmptyString_555) {
    YAML::Node node(std::string(""));
    EXPECT_EQ(node.Scalar(), "");
}

// ==================== Tag Tests ====================

TEST_F(NodeTest_555, SetAndGetTag_555) {
    YAML::Node node("value");
    node.SetTag("!custom_tag");
    EXPECT_EQ(node.Tag(), "!custom_tag");
}

TEST_F(NodeTest_555, DefaultTag_555) {
    YAML::Node node("value");
    // Default tag should be "?" or empty depending on implementation
    std::string tag = node.Tag();
    EXPECT_TRUE(tag == "?" || tag.empty() || tag == "!");
}

// ==================== Style Tests ====================

TEST_F(NodeTest_555, SetAndGetStyle_555) {
    YAML::Node node;
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_555, SetBlockStyle_555) {
    YAML::Node node;
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ==================== Sequence Tests ====================

TEST_F(NodeTest_555, PushBack_CreatesSequence_555) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_555, PushBack_StringValues_555) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
}

TEST_F(NodeTest_555, PushBack_NodeValue_555) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "child_value");
}

TEST_F(NodeTest_555, SequenceAccessByIndex_555) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST_F(NodeTest_555, SequenceIteration_555) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(sum, 6);
}

TEST_F(NodeTest_555, SequenceRangeFor_555) {
    YAML::Node node;
    node.push_back("x");
    node.push_back("y");

    std::vector<std::string> items;
    for (const auto& item : node) {
        items.push_back(item.as<std::string>());
    }
    EXPECT_EQ(items.size(), 2u);
    EXPECT_EQ(items[0], "x");
    EXPECT_EQ(items[1], "y");
}

// ==================== Map Tests ====================

TEST_F(NodeTest_555, MapSubscript_CreatesMap_555) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_555, MapAccess_StringKeys_555) {
    YAML::Node node;
    node["name"] = "Alice";
    node["age"] = 30;
    EXPECT_EQ(node["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST_F(NodeTest_555, MapAccess_IntKeys_555) {
    YAML::Node node;
    node[1] = "one";
    node[2] = "two";
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST_F(NodeTest_555, MapAccess_NonexistentKey_Const_555) {
    YAML::Node node;
    node["existing"] = "value";
    const YAML::Node& constNode = node;
    YAML::Node result = constNode["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST_F(NodeTest_555, MapIteration_555) {
    YAML::Node node;
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

// ==================== Size Tests ====================

TEST_F(NodeTest_555, Size_NullNode_555) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_555, Size_ScalarNode_555) {
    YAML::Node node("value");
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_555, Size_SequenceNode_555) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeTest_555, Size_MapNode_555) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

// ==================== Remove Tests ====================

TEST_F(NodeTest_555, Remove_MapKey_555) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_TRUE(node.remove("a"));
    EXPECT_EQ(node.size(), 1u);
    EXPECT_FALSE(node["a"].IsDefined());
}

TEST_F(NodeTest_555, Remove_NonexistentKey_555) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_555, Remove_WithNodeKey_555) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Node keyNode("key");
    EXPECT_TRUE(node.remove(keyNode));
    EXPECT_EQ(node.size(), 0u);
}

// ==================== Assignment Tests ====================

TEST_F(NodeTest_555, AssignString_555) {
    YAML::Node node;
    node = "assigned_value";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "assigned_value");
}

TEST_F(NodeTest_555, AssignInt_555) {
    YAML::Node node;
    node = 42;
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_555, AssignNode_555) {
    YAML::Node src("source");
    YAML::Node dest;
    dest = src;
    EXPECT_EQ(dest.as<std::string>(), "source");
}

TEST_F(NodeTest_555, AssignOverwrite_555) {
    YAML::Node node("initial");
    node = "overwritten";
    EXPECT_EQ(node.as<std::string>(), "overwritten");
}

// ==================== Reset Tests ====================

TEST_F(NodeTest_555, Reset_555) {
    YAML::Node node("original");
    YAML::Node other("replacement");
    node.reset(other);
    EXPECT_EQ(node.as<std::string>(), "replacement");
}

// ==================== is() Tests ====================

TEST_F(NodeTest_555, Is_SameNode_555) {
    YAML::Node node("value");
    YAML::Node alias = node;
    EXPECT_TRUE(node.is(alias));
}

TEST_F(NodeTest_555, Is_DifferentNode_555) {
    YAML::Node node1("value");
    YAML::Node node2("value");
    EXPECT_FALSE(node1.is(node2));
}

// ==================== IsDefined Tests ====================

TEST_F(NodeTest_555, IsDefined_ValidNode_555) {
    YAML::Node node("value");
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_555, IsDefined_NullNode_555) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_555, IsDefined_UndefinedChild_555) {
    YAML::Node node;
    node["a"] = 1;
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["nonexistent"].IsDefined());
}

// ==================== ForceInsert Tests ====================

TEST_F(NodeTest_555, ForceInsert_555) {
    YAML::Node node;
    node.force_insert("key1", "value1");
    node.force_insert("key1", "value2"); // force_insert allows duplicate keys
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
}

// ==================== YAML Parsing and as<T>() Tests ====================

TEST_F(NodeTest_555, ParseAndAccessScalar_555) {
    YAML::Node node = YAML::Load("42");
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_555, ParseAndAccessSequence_555) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_555, ParseAndAccessMap_555) {
    YAML::Node node = YAML::Load("{name: John, age: 25}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 25);
}

TEST_F(NodeTest_555, ParseNull_555) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_555, ParseBoolTrue_555) {
    YAML::Node node = YAML::Load("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_555, ParseBoolFalse_555) {
    YAML::Node node = YAML::Load("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_555, ParseNestedMap_555) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(NodeTest_555, ParseNestedSequence_555) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    EXPECT_EQ(node[0][0].as<int>(), 1);
    EXPECT_EQ(node[0][1].as<int>(), 2);
    EXPECT_EQ(node[1][0].as<int>(), 3);
    EXPECT_EQ(node[1][1].as<int>(), 4);
}

// ==================== Exception Tests ====================

TEST_F(NodeTest_555, AsThrowsOnTypeMismatch_555) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::Exception);
}

TEST_F(NodeTest_555, AsVectorFromSequence_555) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4]");
    auto vec = node.as<std::vector<int>>();
    EXPECT_EQ(vec.size(), 4u);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[3], 4);
}

TEST_F(NodeTest_555, AsMapFromMap_555) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    auto m = node.as<std::map<std::string, int>>();
    EXPECT_EQ(m.size(), 2u);
    EXPECT_EQ(m["a"], 1);
    EXPECT_EQ(m["b"], 2);
}

// ==================== Empty Sequence / Map Tests ====================

TEST_F(NodeTest_555, EmptySequence_555) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_555, EmptyMap_555) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// ==================== Complex Values ====================

TEST_F(NodeTest_555, StringWithSpaces_555) {
    YAML::Node node("hello world with spaces");
    EXPECT_EQ(node.as<std::string>(), "hello world with spaces");
}

TEST_F(NodeTest_555, EmptyStringScalar_555) {
    YAML::Node node(std::string(""));
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(NodeTest_555, LargeSequence_555) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(NodeTest_555, OverwriteMapValue_555) {
    YAML::Node node;
    node["key"] = "value1";
    node["key"] = "value2";
    EXPECT_EQ(node["key"].as<std::string>(), "value2");
    EXPECT_EQ(node.size(), 1u);
}

// ==================== Multiline / Block YAML ====================

TEST_F(NodeTest_555, ParseBlockStyleYAML_555) {
    std::string yaml = R"(
name: Alice
age: 30
hobbies:
  - reading
  - coding
)";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node["age"].as<int>(), 30);
    EXPECT_TRUE(node["hobbies"].IsSequence());
    EXPECT_EQ(node["hobbies"].size(), 2u);
    EXPECT_EQ(node["hobbies"][0].as<std::string>(), "reading");
    EXPECT_EQ(node["hobbies"][1].as<std::string>(), "coding");
}

// ==================== Mark Tests ====================

TEST_F(NodeTest_555, Mark_DefaultNode_555) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // Default constructed node mark is typically line 0, column 0
    // Just test it doesn't crash
    (void)mark;
}

// ==================== NegativeInt and Special Numeric ====================

TEST_F(NodeTest_555, NegativeInt_555) {
    YAML::Node node(-42);
    EXPECT_EQ(node.as<int>(), -42);
}

TEST_F(NodeTest_555, ZeroValue_555) {
    YAML::Node node(0);
    EXPECT_EQ(node.as<int>(), 0);
}

TEST_F(NodeTest_555, LargeInt_555) {
    YAML::Node node(2147483647);
    EXPECT_EQ(node.as<int>(), 2147483647);
}

// ==================== Type Conversion from Parse ====================

TEST_F(NodeTest_555, ParseStringAsString_555) {
    YAML::Node node = YAML::Load("\"123\"");
    EXPECT_EQ(node.as<std::string>(), "123");
}

TEST_F(NodeTest_555, ParseFloatingPoint_555) {
    YAML::Node node = YAML::Load("3.14159");
    EXPECT_NEAR(node.as<double>(), 3.14159, 0.00001);
}

// ==================== Begin/End on Non-Collection ====================

TEST_F(NodeTest_555, BeginEndOnScalar_555) {
    YAML::Node node("scalar");
    // begin and end should be equal on scalar
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_555, BeginEndOnNull_555) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}
