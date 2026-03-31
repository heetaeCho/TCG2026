#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test fixture for Node tests
class NodeTest_566 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== size() tests ====================

TEST_F(NodeTest_566, DefaultNodeSizeIsZero_566) {
    YAML::Node node;
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, NullNodeSizeIsZero_566) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, ScalarNodeSizeIsZero_566) {
    YAML::Node node("hello");
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, SequenceNodeSizeReflectsElements_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_EQ(3u, node.size());
}

TEST_F(NodeTest_566, MapNodeSizeReflectsEntries_566) {
    YAML::Node node(YAML::NodeType::Map);
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(2u, node.size());
}

TEST_F(NodeTest_566, EmptySequenceNodeSizeIsZero_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, EmptyMapNodeSizeIsZero_566) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, SequenceSizeAfterPushBack_566) {
    YAML::Node node;
    node.push_back("a");
    EXPECT_EQ(1u, node.size());
    node.push_back("b");
    EXPECT_EQ(2u, node.size());
}

TEST_F(NodeTest_566, InvalidNodeSizeThrows_566) {
    YAML::Node validNode;
    // Accessing a non-existent key on a map returns an invalid/zombie node
    YAML::Node mapNode(YAML::NodeType::Map);
    mapNode["existing"] = "value";
    // A const access to a non-existent key returns an undefined node
    const YAML::Node& constMap = mapNode;
    YAML::Node missing = constMap["nonexistent"];
    // The node should not be defined
    EXPECT_FALSE(missing.IsDefined());
}

// ==================== Type and predicate tests ====================

TEST_F(NodeTest_566, DefaultNodeTypeIsNull_566) {
    YAML::Node node;
    EXPECT_EQ(YAML::NodeType::Null, node.Type());
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_566, ScalarNodeTypeIsScalar_566) {
    YAML::Node node("test");
    EXPECT_EQ(YAML::NodeType::Scalar, node.Type());
    EXPECT_TRUE(node.IsScalar());
}

TEST_F(NodeTest_566, SequenceNodeTypeIsSequence_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(YAML::NodeType::Sequence, node.Type());
    EXPECT_TRUE(node.IsSequence());
}

TEST_F(NodeTest_566, MapNodeTypeIsMap_566) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(YAML::NodeType::Map, node.Type());
    EXPECT_TRUE(node.IsMap());
}

// ==================== Scalar tests ====================

TEST_F(NodeTest_566, ScalarValueIsCorrect_566) {
    YAML::Node node("hello world");
    EXPECT_EQ("hello world", node.Scalar());
}

TEST_F(NodeTest_566, NodeAsStringReturnsScalar_566) {
    YAML::Node node("42");
    EXPECT_EQ("42", node.as<std::string>());
}

TEST_F(NodeTest_566, NodeAsIntConverts_566) {
    YAML::Node node("42");
    EXPECT_EQ(42, node.as<int>());
}

TEST_F(NodeTest_566, NodeAsDoubleConverts_566) {
    YAML::Node node("3.14");
    EXPECT_NEAR(3.14, node.as<double>(), 0.001);
}

TEST_F(NodeTest_566, NodeAsBoolConverts_566) {
    YAML::Node node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_566, NodeAsWithFallback_566) {
    YAML::Node node;
    EXPECT_EQ(99, node.as<int>(99));
}

TEST_F(NodeTest_566, NodeAsWithFallbackOnUndefined_566) {
    YAML::Node mapNode(YAML::NodeType::Map);
    mapNode["key"] = "value";
    const YAML::Node& constMap = mapNode;
    YAML::Node missing = constMap["nonexistent"];
    EXPECT_EQ("default", missing.as<std::string>("default"));
}

// ==================== Assignment and operator= tests ====================

TEST_F(NodeTest_566, AssignScalarToNode_566) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("hello", node.Scalar());
}

TEST_F(NodeTest_566, AssignIntToNode_566) {
    YAML::Node node;
    node = 42;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(42, node.as<int>());
}

TEST_F(NodeTest_566, CopyConstructorSharesIdentity_566) {
    YAML::Node node;
    node = "test";
    YAML::Node copy(node);
    EXPECT_TRUE(copy.is(node));
    EXPECT_EQ("test", copy.Scalar());
}

TEST_F(NodeTest_566, AssignNodeToNode_566) {
    YAML::Node a;
    a = "hello";
    YAML::Node b;
    b = a;
    EXPECT_TRUE(b.is(a));
}

// ==================== reset tests ====================

TEST_F(NodeTest_566, ResetChangesIdentity_566) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ("second", a.Scalar());
}

// ==================== Tag tests ====================

TEST_F(NodeTest_566, SetAndGetTag_566) {
    YAML::Node node("value");
    node.SetTag("!custom");
    EXPECT_EQ("!custom", node.Tag());
}

// ==================== Style tests ====================

TEST_F(NodeTest_566, SetAndGetStyle_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// ==================== Sequence operations ====================

TEST_F(NodeTest_566, PushBackCreatesSequence_566) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(2u, node.size());
    EXPECT_EQ("first", node[0].as<std::string>());
    EXPECT_EQ("second", node[1].as<std::string>());
}

TEST_F(NodeTest_566, SequenceIterator_566) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(6, sum);
}

TEST_F(NodeTest_566, SequenceAccessByIndex_566) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    EXPECT_EQ("a", node[0].as<std::string>());
    EXPECT_EQ("b", node[1].as<std::string>());
    EXPECT_EQ("c", node[2].as<std::string>());
}

// ==================== Map operations ====================

TEST_F(NodeTest_566, MapInsertAndAccess_566) {
    YAML::Node node;
    node["name"] = "John";
    node["age"] = 30;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(2u, node.size());
    EXPECT_EQ("John", node["name"].as<std::string>());
    EXPECT_EQ(30, node["age"].as<int>());
}

TEST_F(NodeTest_566, MapRemoveByKey_566) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(3u, node.size());
    EXPECT_TRUE(node.remove("b"));
    EXPECT_EQ(2u, node.size());
}

TEST_F(NodeTest_566, MapRemoveNonExistentKey_566) {
    YAML::Node node;
    node["a"] = 1;
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(1u, node.size());
}

TEST_F(NodeTest_566, MapIterator_566) {
    YAML::Node node;
    node["x"] = 10;
    node["y"] = 20;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
        EXPECT_TRUE(it->first.IsScalar());
        EXPECT_TRUE(it->second.IsScalar());
    }
    EXPECT_EQ(2, count);
}

TEST_F(NodeTest_566, ForceInsertOnMap_566) {
    YAML::Node node;
    node["key"] = "value1";
    node.force_insert("key", "value2");
    // force_insert allows duplicate keys, so size increases
    EXPECT_EQ(2u, node.size());
}

// ==================== IsDefined tests ====================

TEST_F(NodeTest_566, DefaultNodeIsDefined_566) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_566, ScalarNodeIsDefined_566) {
    YAML::Node node("hello");
    EXPECT_TRUE(node.IsDefined());
}

// ==================== Bool conversion tests ====================

TEST_F(NodeTest_566, NullNodeBoolConversionFalse_566) {
    YAML::Node node;
    EXPECT_FALSE(static_cast<bool>(node));
    EXPECT_TRUE(!node);
}

TEST_F(NodeTest_566, ScalarNodeBoolConversionTrue_566) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_566, SequenceNodeBoolConversionTrue_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    EXPECT_TRUE(static_cast<bool>(node));
}

// ==================== is() tests ====================

TEST_F(NodeTest_566, SameNodeIsTrue_566) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST_F(NodeTest_566, DifferentNodesIsNotTrue_566) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// ==================== YAML parsing and size ====================

TEST_F(NodeTest_566, ParsedSequenceSizeIsCorrect_566) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(5u, node.size());
}

TEST_F(NodeTest_566, ParsedMapSizeIsCorrect_566) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(3u, node.size());
}

TEST_F(NodeTest_566, ParsedNestedStructureSize_566) {
    YAML::Node node = YAML::Load("{a: [1,2], b: [3,4,5]}");
    EXPECT_EQ(2u, node.size());
    EXPECT_EQ(2u, node["a"].size());
    EXPECT_EQ(3u, node["b"].size());
}

TEST_F(NodeTest_566, ParsedScalarSizeIsZero_566) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(0u, node.size());
}

// ==================== Edge cases ====================

TEST_F(NodeTest_566, EmptyStringScalar_566) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ("", node.Scalar());
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, LargeSequenceSize_566) {
    YAML::Node node(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(1000u, node.size());
}

TEST_F(NodeTest_566, MapWithNodeKey_566) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(1u, node.size());
    EXPECT_EQ("myvalue", node[key].as<std::string>());
}

TEST_F(NodeTest_566, RemoveByNodeKey_566) {
    YAML::Node node;
    YAML::Node key("mykey");
    node[key] = "myvalue";
    EXPECT_EQ(1u, node.size());
    EXPECT_TRUE(node.remove(key));
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, ConstNodeAccessDoesNotModify_566) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    const YAML::Node& constNode = node;
    EXPECT_EQ(2u, constNode.size());
    YAML::Node val = constNode["a"];
    EXPECT_EQ(1, val.as<int>());
    // Size should not change after const access
    EXPECT_EQ(2u, constNode.size());
}

TEST_F(NodeTest_566, ConstNodeAccessNonExistentKey_566) {
    YAML::Node node;
    node["a"] = 1;
    const YAML::Node& constNode = node;
    YAML::Node missing = constNode["nonexistent"];
    EXPECT_FALSE(missing.IsDefined());
    // Original size should not change
    EXPECT_EQ(1u, constNode.size());
}

TEST_F(NodeTest_566, UndefinedNodeSizeIsZero_566) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_EQ(0u, node.size());
}

TEST_F(NodeTest_566, OverwriteMapEntry_566) {
    YAML::Node node;
    node["key"] = "value1";
    EXPECT_EQ(1u, node.size());
    node["key"] = "value2";
    EXPECT_EQ(1u, node.size());
    EXPECT_EQ("value2", node["key"].as<std::string>());
}

TEST_F(NodeTest_566, PushBackNodeToSequence_566) {
    YAML::Node seq;
    YAML::Node child;
    child["nested"] = "value";
    seq.push_back(child);
    EXPECT_EQ(1u, seq.size());
    EXPECT_TRUE(seq[0].IsMap());
    EXPECT_EQ("value", seq[0]["nested"].as<std::string>());
}

TEST_F(NodeTest_566, MarkOnDefaultNode_566) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    // Default mark should be null mark
    EXPECT_EQ(0, mark.line);
    EXPECT_EQ(0, mark.column);
}
