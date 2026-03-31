#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <sstream>

// ============================================================
// Tests for YAML::Node
// ============================================================

// --- Default Construction ---

TEST(NodeTest_565, DefaultConstructionIsNull_565) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_565, DefaultConstructionTypeIsNull_565) {
    YAML::Node node;
    EXPECT_EQ(YAML::NodeType::Null, node.Type());
}

TEST(NodeTest_565, DefaultConstructionIsDefined_565) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_565, DefaultConstructionBoolConversion_565) {
    YAML::Node node;
    // A null node should convert to false
    EXPECT_FALSE(static_cast<bool>(node));
}

// --- Construction with Type ---

TEST(NodeTest_565, ConstructScalarType_565) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(YAML::NodeType::Scalar, node.Type());
}

TEST(NodeTest_565, ConstructSequenceType_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(YAML::NodeType::Sequence, node.Type());
}

TEST(NodeTest_565, ConstructMapType_565) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(YAML::NodeType::Map, node.Type());
}

// --- Construction with Value ---

TEST(NodeTest_565, ConstructWithString_565) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("hello", node.Scalar());
}

TEST(NodeTest_565, ConstructWithInt_565) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(42, node.as<int>());
}

TEST(NodeTest_565, ConstructWithDouble_565) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_NEAR(3.14, node.as<double>(), 0.001);
}

TEST(NodeTest_565, ConstructWithBool_565) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

// --- Copy Construction ---

TEST(NodeTest_565, CopyConstruction_565) {
    YAML::Node original("test");
    YAML::Node copy(original);
    EXPECT_EQ("test", copy.Scalar());
    EXPECT_TRUE(copy.is(original));
}

// --- Assignment ---

TEST(NodeTest_565, AssignString_565) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("hello", node.Scalar());
}

TEST(NodeTest_565, AssignInt_565) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(100, node.as<int>());
}

TEST(NodeTest_565, AssignNode_565) {
    YAML::Node a("value_a");
    YAML::Node b;
    b = a;
    EXPECT_TRUE(b.is(a));
    EXPECT_EQ("value_a", b.Scalar());
}

// --- as<T>() ---

TEST(NodeTest_565, AsInt_565) {
    YAML::Node node(42);
    EXPECT_EQ(42, node.as<int>());
}

TEST(NodeTest_565, AsString_565) {
    YAML::Node node("hello world");
    EXPECT_EQ("hello world", node.as<std::string>());
}

TEST(NodeTest_565, AsWithFallback_565) {
    YAML::Node node;
    int result = node.as<int>(99);
    EXPECT_EQ(99, result);
}

TEST(NodeTest_565, AsBoolTrue_565) {
    YAML::Node node(true);
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_565, AsBoolFalse_565) {
    YAML::Node node(false);
    EXPECT_FALSE(node.as<bool>());
}

TEST(NodeTest_565, AsDoubleWithFallback_565) {
    YAML::Node node;
    double result = node.as<double>(1.5);
    EXPECT_DOUBLE_EQ(1.5, result);
}

// --- Scalar ---

TEST(NodeTest_565, ScalarReturnsValue_565) {
    YAML::Node node("my_scalar");
    EXPECT_EQ("my_scalar", node.Scalar());
}

TEST(NodeTest_565, ScalarOnNonScalarReturnsEmpty_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ("", node.Scalar());
}

// --- Tag ---

TEST(NodeTest_565, SetAndGetTag_565) {
    YAML::Node node("value");
    node.SetTag("!mytag");
    EXPECT_EQ("!mytag", node.Tag());
}

TEST(NodeTest_565, DefaultTagEmpty_565) {
    YAML::Node node("value");
    EXPECT_EQ("?", node.Tag());
}

// --- Style ---

TEST(NodeTest_565, SetAndGetStyle_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// --- Sequence Operations ---

TEST(NodeTest_565, PushBackCreatesSequence_565) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(3u, node.size());
}

TEST(NodeTest_565, PushBackNode_565) {
    YAML::Node node;
    YAML::Node child("child");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(1u, node.size());
}

TEST(NodeTest_565, SequenceAccessByIndex_565) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_EQ("first", node[0].as<std::string>());
    EXPECT_EQ("second", node[1].as<std::string>());
}

TEST(NodeTest_565, SequenceIteration_565) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(3u, values.size());
    EXPECT_EQ(10, values[0]);
    EXPECT_EQ(20, values[1]);
    EXPECT_EQ(30, values[2]);
}

// --- Map Operations ---

TEST(NodeTest_565, MapInsertAndAccess_565) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ("value1", node["key1"].as<std::string>());
    EXPECT_EQ("value2", node["key2"].as<std::string>());
}

TEST(NodeTest_565, MapSize_565) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_EQ(2u, node.size());
}

TEST(NodeTest_565, MapRemoveKey_565) {
    YAML::Node node;
    node["key1"] = "val1";
    node["key2"] = "val2";
    EXPECT_TRUE(node.remove("key1"));
    EXPECT_EQ(1u, node.size());
    EXPECT_FALSE(node["key1"].IsDefined());
}

TEST(NodeTest_565, MapRemoveNonExistentKey_565) {
    YAML::Node node;
    node["key1"] = "val1";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(1u, node.size());
}

TEST(NodeTest_565, MapRemoveByNodeKey_565) {
    YAML::Node node;
    node["key1"] = "val1";
    YAML::Node key("key1");
    EXPECT_TRUE(node.remove(key));
    EXPECT_FALSE(node["key1"].IsDefined());
}

TEST(NodeTest_565, MapIterationKeysAndValues_565) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;

    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(2u, result.size());
    EXPECT_EQ(1, result["alpha"]);
    EXPECT_EQ(2, result["beta"]);
}

TEST(NodeTest_565, ForceInsert_565) {
    YAML::Node node;
    node.force_insert("key", "value");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ("value", node["key"].as<std::string>());
}

// --- size() ---

TEST(NodeTest_565, SizeOfNullNode_565) {
    YAML::Node node;
    EXPECT_EQ(0u, node.size());
}

TEST(NodeTest_565, SizeOfScalarNode_565) {
    YAML::Node node("scalar");
    EXPECT_EQ(0u, node.size());
}

TEST(NodeTest_565, SizeOfEmptySequence_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(0u, node.size());
}

TEST(NodeTest_565, SizeOfEmptyMap_565) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(0u, node.size());
}

// --- is() ---

TEST(NodeTest_565, IsReturnsTrueForSameNode_565) {
    YAML::Node a("test");
    YAML::Node b(a);
    EXPECT_TRUE(a.is(b));
}

TEST(NodeTest_565, IsReturnsFalseForDifferentNodes_565) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// --- reset() ---

TEST(NodeTest_565, ResetMakesNodesEqual_565) {
    YAML::Node a("first");
    YAML::Node b("second");
    EXPECT_FALSE(a.is(b));
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ("second", a.Scalar());
}

TEST(NodeTest_565, ResetToSelf_565) {
    YAML::Node a("value");
    a.reset(a);
    EXPECT_EQ("value", a.Scalar());
}

// --- Boolean operators ---

TEST(NodeTest_565, OperatorBoolDefinedNode_565) {
    YAML::Node node("hello");
    EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_565, OperatorNotNullNode_565) {
    YAML::Node node;
    EXPECT_TRUE(!node);
}

TEST(NodeTest_565, OperatorNotDefinedNode_565) {
    YAML::Node node("hello");
    EXPECT_FALSE(!node);
}

// --- Type checks ---

TEST(NodeTest_565, IsNullForNullNode_565) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_565, IsScalarForScalarNode_565) {
    YAML::Node node("scalar");
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_565, IsSequenceForSequenceNode_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_565, IsMapForMapNode_565) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_TRUE(node.IsMap());
}

// --- Undefined node ---

TEST(NodeTest_565, UndefinedNodeFromNonExistentKey_565) {
    YAML::Node node(YAML::NodeType::Map);
    const YAML::Node& constNode = node;
    YAML::Node child = constNode["nonexistent"];
    EXPECT_FALSE(child.IsDefined());
}

// --- Parsing YAML ---

TEST(NodeTest_565, ParseScalar_565) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("hello", node.as<std::string>());
}

TEST(NodeTest_565, ParseSequence_565) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(3u, node.size());
    EXPECT_EQ(1, node[0].as<int>());
    EXPECT_EQ(2, node[1].as<int>());
    EXPECT_EQ(3, node[2].as<int>());
}

TEST(NodeTest_565, ParseMap_565) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(2u, node.size());
    EXPECT_EQ(1, node["a"].as<int>());
    EXPECT_EQ(2, node["b"].as<int>());
}

TEST(NodeTest_565, ParseNestedMap_565) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ("value", node["outer"]["inner"].as<std::string>());
}

TEST(NodeTest_565, ParseNull_565) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_565, ParseEmptyDocument_565) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

// --- Edge cases ---

TEST(NodeTest_565, EmptyStringScalar_565) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("", node.Scalar());
}

TEST(NodeTest_565, LargeSequence_565) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(1000u, node.size());
    EXPECT_EQ(0, node[0].as<int>());
    EXPECT_EQ(999, node[999].as<int>());
}

TEST(NodeTest_565, OverwriteMapValue_565) {
    YAML::Node node;
    node["key"] = "old_value";
    node["key"] = "new_value";
    EXPECT_EQ("new_value", node["key"].as<std::string>());
    EXPECT_EQ(1u, node.size());
}

TEST(NodeTest_565, AssignDifferentTypesOverwrite_565) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
    node.push_back(1);
    EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_565, ConstNodeAccess_565) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node& constNode = node;
    EXPECT_EQ("value", constNode["key"].as<std::string>());
}

// --- Mark ---

TEST(NodeTest_565, MarkOnCreatedNode_565) {
    YAML::Node node("test");
    YAML::Mark mark = node.Mark();
    // Programmatically created nodes typically have null marks
    // Just verify it doesn't throw
    (void)mark;
}

// --- Mixed types ---

TEST(NodeTest_565, SequenceOfMaps_565) {
    YAML::Node node = YAML::Load("[{a: 1}, {b: 2}]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(2u, node.size());
    EXPECT_EQ(1, node[0]["a"].as<int>());
    EXPECT_EQ(2, node[1]["b"].as<int>());
}

TEST(NodeTest_565, MapOfSequences_565) {
    YAML::Node node = YAML::Load("{x: [1, 2], y: [3, 4]}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["x"].IsSequence());
    EXPECT_TRUE(node["y"].IsSequence());
    EXPECT_EQ(1, node["x"][0].as<int>());
    EXPECT_EQ(4, node["y"][1].as<int>());
}

// --- Reset with InvalidNode (error case) ---

TEST(NodeTest_565, ResetValidNodes_565) {
    YAML::Node a("a_value");
    YAML::Node b("b_value");
    EXPECT_NO_THROW(a.reset(b));
    EXPECT_EQ("b_value", a.Scalar());
}

// --- begin/end on empty collections ---

TEST(NodeTest_565, BeginEqualsEndForEmptySequence_565) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST(NodeTest_565, BeginEqualsEndForEmptyMap_565) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

// --- as<T>() failure ---

TEST(NodeTest_565, AsThrowsOnBadConversion_565) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::BadConversion);
}

TEST(NodeTest_565, AsWithFallbackNoThrow_565) {
    YAML::Node node("not_a_number");
    int result = node.as<int>(42);
    EXPECT_EQ(42, result);
}

// --- Multiple push_back of nodes ---

TEST(NodeTest_565, PushBackMultipleNodes_565) {
    YAML::Node seq;
    YAML::Node a("a");
    YAML::Node b("b");
    seq.push_back(a);
    seq.push_back(b);
    EXPECT_EQ(2u, seq.size());
    EXPECT_EQ("a", seq[0].as<std::string>());
    EXPECT_EQ("b", seq[1].as<std::string>());
}

// --- Chained map access ---

TEST(NodeTest_565, ChainedMapAccessCreatesIntermediateNodes_565) {
    YAML::Node node;
    node["level1"]["level2"]["level3"] = "deep";
    EXPECT_EQ("deep", node["level1"]["level2"]["level3"].as<std::string>());
}

// --- Force insert duplicate keys ---

TEST(NodeTest_565, ForceInsertDuplicateKeys_565) {
    YAML::Node node;
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    // force_insert allows duplicate keys, so size should be 2
    EXPECT_EQ(2u, node.size());
}
