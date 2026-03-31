#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <sstream>

// Test fixture for YAML::Node tests
class NodeTest_672 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(NodeTest_672, DefaultConstructorCreatesNullNode_672) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST_F(NodeTest_672, ConstructWithSequenceType_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST_F(NodeTest_672, ConstructWithMapType_672) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

TEST_F(NodeTest_672, ConstructWithScalarType_672) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST_F(NodeTest_672, ConstructWithStringValue_672) {
    YAML::Node node("Hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "Hello");
}

TEST_F(NodeTest_672, ConstructWithIntValue_672) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_672, ConstructWithDoubleValue_672) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST_F(NodeTest_672, ConstructWithBoolValue_672) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_TRUE(node.as<bool>());
}

// ==================== Copy Constructor Tests ====================

TEST_F(NodeTest_672, CopyConstructorSharesData_672) {
    YAML::Node original;
    original = "test";
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "test");
    EXPECT_TRUE(copy.is(original));
}

// ==================== Assignment Tests ====================

TEST_F(NodeTest_672, AssignStringToNode_672) {
    YAML::Node node;
    node = "Hello, World";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "Hello, World");
}

TEST_F(NodeTest_672, AssignIntToNode_672) {
    YAML::Node node;
    node = 123;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 123);
}

TEST_F(NodeTest_672, AssignNodeToNode_672) {
    YAML::Node a;
    a = "value_a";
    YAML::Node b;
    b = a;
    EXPECT_EQ(b.as<std::string>(), "value_a");
}

TEST_F(NodeTest_672, AssignOverwritesPreviousValue_672) {
    YAML::Node node;
    node = "first";
    EXPECT_EQ(node.as<std::string>(), "first");
    node = "second";
    EXPECT_EQ(node.as<std::string>(), "second");
}

TEST_F(NodeTest_672, AssignScalarOverwritesSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node = "scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "scalar");
}

// ==================== Type Check Tests ====================

TEST_F(NodeTest_672, IsNullForDefaultNode_672) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_672, IsScalarForStringNode_672) {
    YAML::Node node("test");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST_F(NodeTest_672, BoolOperatorOnDefinedNode_672) {
    YAML::Node node("test");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_672, IsDefined_672) {
    YAML::Node node("test");
    EXPECT_TRUE(node.IsDefined());
}

// ==================== Scalar Tests ====================

TEST_F(NodeTest_672, ScalarReturnsStringValue_672) {
    YAML::Node node("hello");
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST_F(NodeTest_672, AsStringConversion_672) {
    YAML::Node node("world");
    EXPECT_EQ(node.as<std::string>(), "world");
}

TEST_F(NodeTest_672, AsIntConversion_672) {
    YAML::Node node(42);
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(NodeTest_672, AsWithFallback_672) {
    YAML::Node node;
    EXPECT_EQ(node.as<std::string>("fallback"), "fallback");
}

TEST_F(NodeTest_672, AsIntWithFallback_672) {
    YAML::Node node;
    EXPECT_EQ(node.as<int>(99), 99);
}

// ==================== Sequence Tests ====================

TEST_F(NodeTest_672, PushBackCreatesSequence_672) {
    YAML::Node node;
    node.push_back("zero");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "zero");
}

TEST_F(NodeTest_672, PushBackMultipleElements_672) {
    YAML::Node node;
    node.push_back("zero");
    node.push_back("one");
    node.push_back("two");
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "zero");
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

TEST_F(NodeTest_672, SequenceIndexAccess_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST_F(NodeTest_672, SequenceAssignByIndex_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node[0] = "zero";
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node[0].as<std::string>(), "zero");
}

TEST_F(NodeTest_672, SequenceGapFillsWithNull_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node[0] = 0;
    node[2] = "two";
    EXPECT_EQ(node.size(), 3u);
    EXPECT_TRUE(node[1].IsNull());
}

TEST_F(NodeTest_672, SequenceSizeAfterPushBack_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back(1);
    EXPECT_EQ(node.size(), 1u);
    node.push_back(2);
    EXPECT_EQ(node.size(), 2u);
}

// ==================== Map Tests ====================

TEST_F(NodeTest_672, MapAccessByStringKey_672) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_672, MapAccessByIntKey_672) {
    YAML::Node node;
    node[3] = 1;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[3].as<int>(), 1);
}

TEST_F(NodeTest_672, MapMultipleKeys_672) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

TEST_F(NodeTest_672, MapRemoveKey_672) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_EQ(node.size(), 2u);
    bool removed = node.remove("key1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_672, MapRemoveNonExistentKey_672) {
    YAML::Node node;
    node["key"] = "value";
    bool removed = node.remove("nonexistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_672, MapWithNodeKey_672) {
    YAML::Node root;
    YAML::Node key;
    key["key"] = "value";
    root[key] = "mapped";
    EXPECT_EQ(root[key].as<std::string>(), "mapped");
}

// ==================== Alias / is() Tests ====================

TEST_F(NodeTest_672, IsReturnsTrueForSameNode_672) {
    YAML::Node a;
    a = "test";
    YAML::Node b = a;
    EXPECT_TRUE(a.is(b));
}

TEST_F(NodeTest_672, IsReturnsFalseForDifferentNodes_672) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

TEST_F(NodeTest_672, AliasModificationReflected_672) {
    YAML::Node root(YAML::NodeType::Sequence);
    root.push_back("hello");
    YAML::Node alias = root;
    alias[0] = "world";
    EXPECT_EQ(root[0].as<std::string>(), "world");
}

TEST_F(NodeTest_672, SequenceAliasElements_672) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq[0] = "zero";
    seq[1] = seq[0];
    EXPECT_TRUE(seq[0].is(seq[1]));
    seq[1] = "one";
    // Both should be "one" since they are aliased
    EXPECT_EQ(seq[0].as<std::string>(), "one");
}

// ==================== Reset Tests ====================

TEST_F(NodeTest_672, ResetWithAnotherNode_672) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_EQ(a.as<std::string>(), "second");
    EXPECT_TRUE(a.is(b));
}

// ==================== Tag Tests ====================

TEST_F(NodeTest_672, SetAndGetTag_672) {
    YAML::Node node("value");
    node.SetTag("!mytag");
    EXPECT_EQ(node.Tag(), "!mytag");
}

TEST_F(NodeTest_672, DefaultTagIsEmpty_672) {
    YAML::Node node("value");
    EXPECT_TRUE(node.Tag().empty() || node.Tag() == "?");
}

// ==================== Style Tests ====================

TEST_F(NodeTest_672, SetAndGetStyle_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeTest_672, SetBlockStyle_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// ==================== Iterator Tests ====================

TEST_F(NodeTest_672, IterateOverSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

TEST_F(NodeTest_672, IterateOverMap_672) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST_F(NodeTest_672, RangeBasedForSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    
    std::vector<int> values;
    for (const auto& item : node) {
        values.push_back(item.as<int>());
    }
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// ==================== Size Tests ====================

TEST_F(NodeTest_672, SizeOfEmptySequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_672, SizeOfEmptyMap_672) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_672, SizeOfNullNode_672) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(NodeTest_672, SizeOfScalarNode_672) {
    YAML::Node node("hello");
    EXPECT_EQ(node.size(), 0u);
}

// ==================== Auto-construct Tests ====================

TEST_F(NodeTest_672, NullNodeAutoConstructsSequenceWithIntIndex_672) {
    // When using integer index on null node via push_back or sequence context
    YAML::Node node;
    node[0] = 1;
    // The behavior depends on implementation - indexing null node with int
    // could auto-construct a sequence
    EXPECT_TRUE(node.IsDefined());
}

TEST_F(NodeTest_672, NullNodeAutoConstructsMapWithStringKey_672) {
    YAML::Node node;
    node["key"] = 5;
    EXPECT_TRUE(node.IsMap());
}

// ==================== force_insert Tests ====================

TEST_F(NodeTest_672, ForceInsertIntoMap_672) {
    YAML::Node node;
    node["existing"] = "value";
    node.force_insert("forced_key", "forced_value");
    EXPECT_TRUE(node.IsMap());
}

// ==================== Complex Scenarios ====================

TEST_F(NodeTest_672, SelfReferenceInSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node[0] = node;
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeTest_672, NestedSequences_672) {
    YAML::Node root(YAML::NodeType::Sequence);
    root[0] = "hi";
    YAML::Node inner(YAML::NodeType::Sequence);
    inner.push_back("bye");
    root[1] = inner;
    EXPECT_EQ(root[0].as<std::string>(), "hi");
    EXPECT_TRUE(root[1].IsSequence());
    EXPECT_EQ(root[1][0].as<std::string>(), "bye");
}

TEST_F(NodeTest_672, NestedMaps_672) {
    YAML::Node root;
    root["outer"]["inner"] = "value";
    EXPECT_TRUE(root.IsMap());
    EXPECT_TRUE(root["outer"].IsMap());
    EXPECT_EQ(root["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(NodeTest_672, SubnodeRetainedAfterRootReassignment_672) {
    YAML::Node root;
    root.push_back("zero");
    root.push_back("one");
    root.push_back("two");
    YAML::Node two = root[2];
    root = "scalar";
    EXPECT_EQ(two.as<std::string>(), "two");
    EXPECT_TRUE(root.IsScalar());
}

TEST_F(NodeTest_672, OverwriteSelfReferenceWithScalar_672) {
    YAML::Node root(YAML::NodeType::Sequence);
    root[0] = root;
    root[0] = 5;
    EXPECT_EQ(root[0].as<int>(), 5);
}

// ==================== YAML Load/Dump Tests ====================

TEST_F(NodeTest_672, LoadSimpleScalar_672) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(NodeTest_672, LoadSimpleSequence_672) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(NodeTest_672, LoadSimpleMap_672) {
    YAML::Node node = YAML::Load("{key: value}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_672, LoadNull_672) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeTest_672, LoadNestedStructure_672) {
    std::string yaml = "root:\n  child1: value1\n  child2: value2";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["root"]["child1"].as<std::string>(), "value1");
    EXPECT_EQ(node["root"]["child2"].as<std::string>(), "value2");
}

TEST_F(NodeTest_672, LoadSequenceOfMaps_672) {
    std::string yaml = "- name: Alice\n- name: Bob";
    YAML::Node node = YAML::Load(yaml);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[1]["name"].as<std::string>(), "Bob");
}

TEST_F(NodeTest_672, EmitNode_672) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Emitter emitter;
    emitter << node;
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ==================== Edge Cases ====================

TEST_F(NodeTest_672, EmptyStringScalar_672) {
    YAML::Node node("");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(NodeTest_672, LargeSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(NodeTest_672, AccessUndefinedMapKey_672) {
    YAML::Node node;
    node["key"] = "value";
    // Accessing a non-existent key should return an undefined node
    YAML::Node missing = node["nonexistent"];
    EXPECT_FALSE(missing.IsDefined());
}

TEST_F(NodeTest_672, ConvertBoolFromString_672) {
    YAML::Node node = YAML::Load("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(NodeTest_672, ConvertBoolFalseFromString_672) {
    YAML::Node node = YAML::Load("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(NodeTest_672, RemoveFromSequence_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    // Remove by value/index
    bool removed = node.remove(1);
    EXPECT_TRUE(removed);
}

TEST_F(NodeTest_672, CloneNode_672) {
    YAML::Node original;
    original["key"] = "value";
    YAML::Node cloned = Clone(original);
    EXPECT_FALSE(cloned.is(original));
    EXPECT_EQ(cloned["key"].as<std::string>(), "value");
}

TEST_F(NodeTest_672, CloneIndependence_672) {
    YAML::Node original;
    original["key"] = "value";
    YAML::Node cloned = Clone(original);
    cloned["key"] = "modified";
    EXPECT_EQ(original["key"].as<std::string>(), "value");
    EXPECT_EQ(cloned["key"].as<std::string>(), "modified");
}

TEST_F(NodeTest_672, NullNodeBoolOperator_672) {
    YAML::Node node;
    // A null node is "valid" but null
    // The bool operator checks if it's defined
    EXPECT_FALSE(!node);
}

TEST_F(NodeTest_672, LoadInvalidYamlThrows_672) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: ]{"), YAML::Exception);
}

TEST_F(NodeTest_672, AsThrowsOnTypeMismatch_672) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::Exception);
}

TEST_F(NodeTest_672, SequenceBeginEndEmpty_672) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_672, MapBeginEndEmpty_672) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

TEST_F(NodeTest_672, MapIteratorAccessKeyValue_672) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;
    
    bool foundAlpha = false;
    bool foundBeta = false;
    for (auto it = node.begin(); it != node.end(); ++it) {
        std::string key = it->first.as<std::string>();
        if (key == "alpha") {
            EXPECT_EQ(it->second.as<int>(), 1);
            foundAlpha = true;
        } else if (key == "beta") {
            EXPECT_EQ(it->second.as<int>(), 2);
            foundBeta = true;
        }
    }
    EXPECT_TRUE(foundAlpha);
    EXPECT_TRUE(foundBeta);
}

TEST_F(NodeTest_672, PushBackNodeValue_672) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node val("hello");
    seq.push_back(val);
    EXPECT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST_F(NodeTest_672, SequenceTypeConstructedExplicitly_672) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq[3] = 1;
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq.size(), 4u);
    EXPECT_TRUE(seq[0].IsNull());
    EXPECT_TRUE(seq[1].IsNull());
    EXPECT_TRUE(seq[2].IsNull());
    EXPECT_EQ(seq[3].as<int>(), 1);
}

TEST_F(NodeTest_672, NullNodeIndexWithIntCreatesMap_672) {
    YAML::Node map;
    map[3] = 1;
    // Indexing a null node with an int creates a map (not a sequence)
    EXPECT_TRUE(map.IsMap());
    EXPECT_EQ(map[3].as<int>(), 1);
}
