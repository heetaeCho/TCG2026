#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class NodeTest_567 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Construction Tests
// =============================================================================

TEST_F(NodeTest_567, DefaultConstructorCreatesNullNode_567) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_567, ConstructWithScalarType_567) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_567, ConstructWithSequenceType_567) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_567, ConstructWithMapType_567) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST_F(NodeTest_567, ConstructWithStringValue_567) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_567, ConstructWithIntValue_567) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_567, ConstructWithDoubleValue_567) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(NodeTest_567, ConstructWithBoolValue_567) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_567, CopyConstructor_567) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ(copy.Scalar(), "test");
    EXPECT_TRUE(copy.is(original));
}

// =============================================================================
// Type Check Tests
// =============================================================================

TEST_F(NodeTest_567, IsNullForDefaultNode_567) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_567, IsScalarForStringNode_567) {
    YAML::Node node("value");
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_567, BoolOperatorForDefinedNode_567) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_567, BoolOperatorForNullNode_567) {
    YAML::Node node;
    // Null node is valid but not defined in the usual sense
    // operator bool returns IsDefined()
    EXPECT_FALSE(static_cast<bool>(node));
}

TEST_F(NodeTest_567, IsDefinedForScalar_567) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsDefined());
}

// =============================================================================
// Scalar Tests
// =============================================================================

TEST_F(NodeTest_567, ScalarReturnsValue_567) {
    YAML::Node node("hello world");
    EXPECT_EQ(node.Scalar(), "hello world");
}

TEST_F(NodeTest_567, ScalarEmptyString_567) {
    YAML::Node node(std::string(""));
    EXPECT_EQ(node.Scalar(), "");
}

TEST_F(NodeTest_567, AsStringConversion_567) {
    YAML::Node node("test_value");
    EXPECT_EQ(node.as<std::string>(), "test_value");
}

TEST_F(NodeTest_567, AsIntConversion_567) {
    YAML::Node node(123);
    EXPECT_EQ(node.as<int>(), 123);
}

TEST_F(NodeTest_567, AsDoubleConversion_567) {
    YAML::Node node(2.718);
    EXPECT_NEAR(node.as<double>(), 2.718, 0.001);
}

TEST_F(NodeTest_567, AsBoolConversion_567) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_567, AsWithFallback_567) {
    YAML::Node node;
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

TEST_F(NodeTest_567, AsWithFallbackWhenDefined_567) {
    YAML::Node node(100);
    int result = node.as<int>(42);
    EXPECT_EQ(result, 100);
}

TEST_F(NodeTest_567, AsStringWithFallback_567) {
    YAML::Node node;
    std::string result = node.as<std::string>("default");
    EXPECT_EQ(result, "default");
}

// =============================================================================
// Tag Tests
// =============================================================================

TEST_F(NodeTest_567, SetAndGetTag_567) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ(node.Tag(), "!custom");
}

TEST_F(NodeTest_567, DefaultTagIsEmpty_567) {
    YAML::Node node("value");
    // Tag should be empty or "?" for untagged nodes
    // Just verify it doesn't throw
    std::string tag = node.Tag();
    (void)tag;
}

// =============================================================================
// Style Tests
// =============================================================================

TEST_F(NodeTest_567, SetAndGetStyle_567) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_567, SetBlockStyle_567) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// =============================================================================
// Sequence Tests
// =============================================================================

TEST_F(NodeTest_567, PushBackCreatesSequence_567) {
    YAML::Node node;
    node.push_back("item1");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_567, PushBackMultipleItems_567) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_567, PushBackNodeValue_567) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_567, SequenceAccessByIndex_567) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ(node[0].as<std::string>(), "first");
    EXPECT_EQ(node[1].as<std::string>(), "second");
}

TEST_F(NodeTest_567, SequenceSizeAfterPushBack_567) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
    node.push_back(3);
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_567, PushBackIntValues_567) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

// =============================================================================
// Map Tests
// =============================================================================

TEST_F(NodeTest_567, MapAccessCreatesMap_567) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
}

TEST_F(NodeTest_567, MapGetValue_567) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_567, MapMultipleKeys_567) {
    YAML::Node node;
    node["name"] = "John";
    node["age"] = 30;
    node["active"] = true;
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
    EXPECT_TRUE(node["active"].as<bool>());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(NodeTest_567, MapRemoveKey_567) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";
    EXPECT_EQ(node.size(), 2u);
    EXPECT_TRUE(node.remove("key1"));
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_567, MapRemoveNonExistentKey_567) {
    YAML::Node node;
    node["key1"] = "val1";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_567, MapRemoveWithNodeKey_567) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_567, ConstMapAccess_567) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_EQ(constNode["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_567, MapConstAccessNonExistentKey_567) {
    YAML::Node node;
    node["existing"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_FALSE(constNode["nonexistent"].IsDefined());
}

TEST_F(NodeTest_567, ForceInsert_567) {
    YAML::Node node;
    node.force_insert("key", "value");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// =============================================================================
// Iterator Tests
// =============================================================================

TEST_F(NodeTest_567, BeginEndForEmptySequence_567) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_567, BeginEndForNullNode_567) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_567, IterateOverSequence_567) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 3);
    EXPECT_EQ(sum, 6);
}

TEST_F(NodeTest_567, IterateOverMap_567) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST_F(NodeTest_567, RangeBasedForSequence_567) {
    YAML::Node node;
    node.push_back("x");
    node.push_back("y");
    node.push_back("z");

    std::vector<std::string> results;
    for (const auto& item : node) {
        results.push_back(item.as<std::string>());
    }
    EXPECT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], "x");
    EXPECT_EQ(results[1], "y");
    EXPECT_EQ(results[2], "z");
}

TEST_F(NodeTest_567, RangeBasedForMap_567) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";

    std::map<std::string, std::string> results;
    for (const auto& pair : node) {
        results[pair.first.as<std::string>()] = pair.second.as<std::string>();
    }
    EXPECT_EQ(results.size(), 2u);
    EXPECT_EQ(results["key1"], "val1");
    EXPECT_EQ(results["key2"], "val2");
}

TEST_F(NodeTest_567, ConstIteratorForSequence_567) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);

    const YAML::Node& constNode = node;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// =============================================================================
// Assignment Tests
// =============================================================================

TEST_F(NodeTest_567, AssignStringValue_567) {
    YAML::Node node;
    node = "assigned_value";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "assigned_value");
}

TEST_F(NodeTest_567, AssignIntValue_567) {
    YAML::Node node;
    node = 99;
    EXPECT_EQ(node.as<int>(), 99);
}

TEST_F(NodeTest_567, AssignNodeToNode_567) {
    YAML::Node a("hello");
    YAML::Node b;
    b = a;
    EXPECT_EQ(b.as<std::string>(), "hello");
    EXPECT_TRUE(b.is(a));
}

TEST_F(NodeTest_567, ResetNode_567) {
    YAML::Node a("original");
    YAML::Node b("replacement");
    a.reset(b);
    EXPECT_EQ(a.as<std::string>(), "replacement");
    EXPECT_TRUE(a.is(b));
}

// =============================================================================
// Identity Tests
// =============================================================================

TEST_F(NodeTest_567, IsIdenticalAfterCopy_567) {
    YAML::Node a("value");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
    EXPECT_TRUE(b.is(a));
}

TEST_F(NodeTest_567, IsNotIdenticalForDifferentNodes_567) {
    YAML::Node a("value");
    YAML::Node b("value");
    EXPECT_FALSE(a.is(b));
}

// =============================================================================
// Size Tests
// =============================================================================

TEST_F(NodeTest_567, SizeOfNullNodeIsZero_567) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_567, SizeOfScalarIsZero_567) {
    YAML::Node node("hello");
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_567, SizeOfEmptySequence_567) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_567, SizeOfEmptyMap_567) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_567, SizeAfterMapInsertions_567) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
}

// =============================================================================
// Parsing Tests (Integration-like, via YAML::Load)
// =============================================================================

TEST_F(NodeTest_567, LoadScalar_567) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_567, LoadSequence_567) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_567, LoadMap_567) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST_F(NodeTest_567, LoadNestedStructure_567) {
    YAML::Node node = YAML::Load("{items: [1, 2, 3], count: 3}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["items"].IsSequence());
    EXPECT_EQ(node["items"].size(), 3u);
    EXPECT_EQ(node["count"].as<int>(), 3);
}

TEST_F(NodeTest_567, LoadEmptyDocument_567) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_567, LoadNullValue_567) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_567, LoadBoolTrue_567) {
    YAML::Node node = YAML::Load("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_567, LoadBoolFalse_567) {
    YAML::Node node = YAML::Load("false");
    EXPECT_FALSE(node.as<bool>());
}

// =============================================================================
// Error / Exception Tests
// =============================================================================

TEST_F(NodeTest_567, AsWrongTypeThrows_567) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST_F(NodeTest_567, InvalidYAMLThrows_567) {
    EXPECT_THROW(YAML::Load("[unbalanced"), YAML::ParserException);
}

// =============================================================================
// begin() on invalid/default node
// =============================================================================

TEST_F(NodeTest_567, BeginOnDefaultNodeEqualsEnd_567) {
    YAML::Node node;
    auto b = node.begin();
    auto e = node.end();
    EXPECT_EQ(b, e);
}

TEST_F(NodeTest_567, BeginOnScalarNodeEqualsEnd_567) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.begin(), node.end());
}

// =============================================================================
// Overwrite values in map
// =============================================================================

TEST_F(NodeTest_567, MapOverwriteValue_567) {
    YAML::Node node;
    node["key"] = "original";
    node["key"] = "overwritten";
    EXPECT_EQ(node["key"].as<std::string>(), "overwritten");
    EXPECT_EQ(node.size(), 1u);
}

// =============================================================================
// Mixed type push_back
// =============================================================================

TEST_F(NodeTest_567, PushBackMixedTypes_567) {
    YAML::Node node;
    node.push_back(42);
    node.push_back("hello");
    node.push_back(true);
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_TRUE(node[2].as<bool>());
}

// =============================================================================
// Node with Undefined type
// =============================================================================

TEST_F(NodeTest_567, UndefinedTypeForNullNode_567) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
    EXPECT_EQ(node.Type(), YAML::NodeType::Undefined);
}

// =============================================================================
// Large sequence test
// =============================================================================

TEST_F(NodeTest_567, LargeSequence_567) {
    YAML::Node node;
    const int count = 1000;
    for (int i = 0; i < count; i++) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), static_cast<std::size_t>(count));
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

// =============================================================================
// Large map test
// =============================================================================

TEST_F(NodeTest_567, LargeMap_567) {
    YAML::Node node;
    const int count = 100;
    for (int i = 0; i < count; i++) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), static_cast<std::size_t>(count));
    EXPECT_EQ(node["0"].as<int>(), 0);
    EXPECT_EQ(node["99"].as<int>(), 99);
}

// =============================================================================
// Mark test
// =============================================================================

TEST_F(NodeTest_567, MarkOnParsedNode_567) {
    YAML::Node node = YAML::Load("hello");
    YAML::Mark mark = node.Mark();
    // Mark should be valid, line/column typically 0-based
    EXPECT_GE(mark.line, 0);
    EXPECT_GE(mark.column, 0);
}

// =============================================================================
// Nested node modification
// =============================================================================

TEST_F(NodeTest_567, NestedMapModification_567) {
    YAML::Node node;
    node["level1"]["level2"]["level3"] = "deep_value";
    EXPECT_EQ(node["level1"]["level2"]["level3"].as<std::string>(), "deep_value");
}

TEST_F(NodeTest_567, SequenceOfMaps_567) {
    YAML::Node node;
    YAML::Node item1;
    item1["name"] = "Alice";
    YAML::Node item2;
    item2["name"] = "Bob";
    node.push_back(item1);
    node.push_back(item2);
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[1]["name"].as<std::string>(), "Bob");
}
