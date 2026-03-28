#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test: encode returns the same node (identity encoding)
TEST(NodeConvertTest_593, EncodeReturnsNode_593) {
    YAML::Node original;
    original = "hello";
    YAML::Node encoded = YAML::encode(original);
    ASSERT_TRUE(encoded.IsDefined());
    ASSERT_TRUE(encoded.IsScalar());
    EXPECT_EQ(encoded.as<std::string>(), "hello");
}

// Test: encode with a null node
TEST(NodeConvertTest_593, EncodeNullNode_593) {
    YAML::Node nullNode(YAML::NodeType::Null);
    YAML::Node encoded = YAML::encode(nullNode);
    EXPECT_TRUE(encoded.IsNull());
}

// Test: encode with an integer scalar node
TEST(NodeConvertTest_593, EncodeIntegerScalar_593) {
    YAML::Node node;
    node = 42;
    YAML::Node encoded = YAML::encode(node);
    EXPECT_EQ(encoded.as<int>(), 42);
}

// Test: encode with a sequence node
TEST(NodeConvertTest_593, EncodeSequenceNode_593) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(3);
    YAML::Node encoded = YAML::encode(seq);
    ASSERT_TRUE(encoded.IsSequence());
    EXPECT_EQ(encoded.size(), 3u);
    EXPECT_EQ(encoded[0].as<int>(), 1);
    EXPECT_EQ(encoded[1].as<int>(), 2);
    EXPECT_EQ(encoded[2].as<int>(), 3);
}

// Test: encode with a map node
TEST(NodeConvertTest_593, EncodeMapNode_593) {
    YAML::Node map(YAML::NodeType::Map);
    map["key1"] = "value1";
    map["key2"] = "value2";
    YAML::Node encoded = YAML::encode(map);
    ASSERT_TRUE(encoded.IsMap());
    EXPECT_EQ(encoded["key1"].as<std::string>(), "value1");
    EXPECT_EQ(encoded["key2"].as<std::string>(), "value2");
}

// Test: encode with an empty/default-constructed node
TEST(NodeConvertTest_593, EncodeDefaultNode_593) {
    YAML::Node defaultNode;
    YAML::Node encoded = YAML::encode(defaultNode);
    // Default node is Null type
    EXPECT_TRUE(encoded.IsNull());
}

// Test: encode preserves the tag of a node
TEST(NodeConvertTest_593, EncodePreservesTag_593) {
    YAML::Node node;
    node = "tagged_value";
    node.SetTag("!custom");
    YAML::Node encoded = YAML::encode(node);
    EXPECT_EQ(encoded.Tag(), "!custom");
    EXPECT_EQ(encoded.Scalar(), "tagged_value");
}

// Test: encode preserves the style of a node
TEST(NodeConvertTest_593, EncodePreservesStyle_593) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Flow);
    YAML::Node encoded = YAML::encode(node);
    EXPECT_EQ(encoded.Style(), YAML::EmitterStyle::Flow);
}

// Test: encode with a boolean value
TEST(NodeConvertTest_593, EncodeBooleanNode_593) {
    YAML::Node node;
    node = true;
    YAML::Node encoded = YAML::encode(node);
    EXPECT_TRUE(encoded.as<bool>());
}

// Test: encode with a double value
TEST(NodeConvertTest_593, EncodeDoubleNode_593) {
    YAML::Node node;
    node = 3.14;
    YAML::Node encoded = YAML::encode(node);
    EXPECT_NEAR(encoded.as<double>(), 3.14, 0.001);
}

// Test: encode with a string value
TEST(NodeConvertTest_593, EncodeStringNode_593) {
    YAML::Node node;
    node = std::string("test string");
    YAML::Node encoded = YAML::encode(node);
    EXPECT_EQ(encoded.as<std::string>(), "test string");
}

// Test: encode with an empty string
TEST(NodeConvertTest_593, EncodeEmptyStringNode_593) {
    YAML::Node node;
    node = std::string("");
    YAML::Node encoded = YAML::encode(node);
    EXPECT_EQ(encoded.as<std::string>(), "");
}

// Test: encode with a nested map
TEST(NodeConvertTest_593, EncodeNestedMapNode_593) {
    YAML::Node node;
    node["outer"]["inner"] = "deep_value";
    YAML::Node encoded = YAML::encode(node);
    ASSERT_TRUE(encoded.IsMap());
    ASSERT_TRUE(encoded["outer"].IsMap());
    EXPECT_EQ(encoded["outer"]["inner"].as<std::string>(), "deep_value");
}

// Test: encoded node refers to the same data (is same node)
TEST(NodeConvertTest_593, EncodeReturnsSameNodeReference_593) {
    YAML::Node node;
    node = "original";
    YAML::Node encoded = YAML::encode(node);
    // They should refer to the same underlying node
    EXPECT_TRUE(node.is(encoded));
}

// Test: encode with a large sequence
TEST(NodeConvertTest_593, EncodeLargeSequence_593) {
    YAML::Node seq(YAML::NodeType::Sequence);
    for (int i = 0; i < 1000; ++i) {
        seq.push_back(i);
    }
    YAML::Node encoded = YAML::encode(seq);
    ASSERT_TRUE(encoded.IsSequence());
    EXPECT_EQ(encoded.size(), 1000u);
    EXPECT_EQ(encoded[0].as<int>(), 0);
    EXPECT_EQ(encoded[999].as<int>(), 999);
}

// Test: Node default construction
TEST(NodeTest_593, DefaultConstructionIsNull_593) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

// Test: Node construction with type
TEST(NodeTest_593, ConstructWithScalarType_593) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_EQ(node.Type(), YAML::NodeType::Scalar);
}

TEST(NodeTest_593, ConstructWithSequenceType_593) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_593, ConstructWithMapType_593) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// Test: Node assignment from value
TEST(NodeTest_593, AssignString_593) {
    YAML::Node node;
    node = "test";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "test");
}

TEST(NodeTest_593, AssignInt_593) {
    YAML::Node node;
    node = 123;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 123);
}

// Test: Node copy construction
TEST(NodeTest_593, CopyConstruction_593) {
    YAML::Node original;
    original = "copy_me";
    YAML::Node copy(original);
    EXPECT_EQ(copy.as<std::string>(), "copy_me");
    EXPECT_TRUE(copy.is(original));
}

// Test: Node push_back
TEST(NodeTest_593, PushBackToSequence_593) {
    YAML::Node seq;
    seq.push_back(10);
    seq.push_back(20);
    EXPECT_TRUE(seq.IsSequence());
    EXPECT_EQ(seq.size(), 2u);
    EXPECT_EQ(seq[0].as<int>(), 10);
    EXPECT_EQ(seq[1].as<int>(), 20);
}

// Test: Node map access
TEST(NodeTest_593, MapAccess_593) {
    YAML::Node map;
    map["key"] = "value";
    EXPECT_TRUE(map.IsMap());
    EXPECT_EQ(map["key"].as<std::string>(), "value");
}

// Test: Node remove from map
TEST(NodeTest_593, RemoveFromMap_593) {
    YAML::Node map;
    map["a"] = 1;
    map["b"] = 2;
    EXPECT_TRUE(map.remove("a"));
    EXPECT_EQ(map.size(), 1u);
    EXPECT_FALSE(map["a"].IsDefined());
}

// Test: Node remove non-existent key
TEST(NodeTest_593, RemoveNonExistentKey_593) {
    YAML::Node map;
    map["a"] = 1;
    EXPECT_FALSE(map.remove("nonexistent"));
}

// Test: Node as with fallback
TEST(NodeTest_593, AsWithFallback_593) {
    YAML::Node node;
    // Node is null, so fallback should be returned
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

// Test: Node as without fallback on valid scalar
TEST(NodeTest_593, AsWithoutFallback_593) {
    YAML::Node node;
    node = 99;
    EXPECT_EQ(node.as<int>(), 99);
}

// Test: Node Scalar
TEST(NodeTest_593, ScalarValue_593) {
    YAML::Node node;
    node = "scalar_value";
    EXPECT_EQ(node.Scalar(), "scalar_value");
}

// Test: Node SetTag / Tag
TEST(NodeTest_593, SetAndGetTag_593) {
    YAML::Node node;
    node = "value";
    node.SetTag("!mytag");
    EXPECT_EQ(node.Tag(), "!mytag");
}

// Test: Node SetStyle / Style
TEST(NodeTest_593, SetAndGetStyle_593) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Block);
}

// Test: Node reset
TEST(NodeTest_593, ResetNode_593) {
    YAML::Node node1;
    node1 = "first";
    YAML::Node node2;
    node2 = "second";
    node1.reset(node2);
    EXPECT_TRUE(node1.is(node2));
    EXPECT_EQ(node1.as<std::string>(), "second");
}

// Test: Node bool operator
TEST(NodeTest_593, BoolOperator_593) {
    YAML::Node defined;
    defined = "value";
    EXPECT_TRUE(static_cast<bool>(defined));

    YAML::Node null_node;
    // A default-constructed node is valid but null
    // operator bool returns IsDefined
    // A Null node IS defined, so this should be true
    // Actually, a default node is Null and IsDefined depends on the implementation
}

// Test: Node operator!
TEST(NodeTest_593, NotOperator_593) {
    YAML::Node node;
    node = "hello";
    EXPECT_FALSE(!node);
}

// Test: Node is() identity check
TEST(NodeTest_593, IsIdentity_593) {
    YAML::Node a;
    a = "test";
    YAML::Node b = a;
    YAML::Node c;
    c = "test";
    EXPECT_TRUE(a.is(b));
    EXPECT_FALSE(a.is(c));
}

// Test: Node size for different types
TEST(NodeTest_593, SizeOfEmptySequence_593) {
    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_EQ(seq.size(), 0u);
}

TEST(NodeTest_593, SizeOfMap_593) {
    YAML::Node map;
    map["a"] = 1;
    map["b"] = 2;
    map["c"] = 3;
    EXPECT_EQ(map.size(), 3u);
}

// Test: Node iteration over sequence
TEST(NodeTest_593, IterateSequence_593) {
    YAML::Node seq;
    seq.push_back(10);
    seq.push_back(20);
    seq.push_back(30);
    
    int sum = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(sum, 60);
}

// Test: Node iteration over map
TEST(NodeTest_593, IterateMap_593) {
    YAML::Node map;
    map["x"] = 1;
    map["y"] = 2;
    
    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test: Node force_insert
TEST(NodeTest_593, ForceInsert_593) {
    YAML::Node map(YAML::NodeType::Map);
    map.force_insert("key1", "val1");
    map.force_insert("key2", "val2");
    EXPECT_EQ(map.size(), 2u);
}

// Test: Node construction from value
TEST(NodeTest_593, ConstructFromString_593) {
    YAML::Node node(std::string("constructed"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "constructed");
}

TEST(NodeTest_593, ConstructFromInt_593) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test: Node assignment operator from another node
TEST(NodeTest_593, AssignmentFromNode_593) {
    YAML::Node a;
    a = "original";
    YAML::Node b;
    b = a;
    EXPECT_TRUE(b.is(a));
    EXPECT_EQ(b.as<std::string>(), "original");
}

// Test: Undefined node access
TEST(NodeTest_593, UndefinedMapAccess_593) {
    YAML::Node map;
    map["exists"] = 1;
    const YAML::Node& ref = map["nonexistent"];
    EXPECT_FALSE(ref.IsDefined());
}

// Test: Accessing const node by key
TEST(NodeTest_593, ConstNodeMapAccess_593) {
    YAML::Node map;
    map["key"] = "value";
    const YAML::Node& constMap = map;
    EXPECT_EQ(constMap["key"].as<std::string>(), "value");
}

// Test: Node IsDefined
TEST(NodeTest_593, IsDefinedOnValidNode_593) {
    YAML::Node node;
    node = "defined";
    EXPECT_TRUE(node.IsDefined());
}

// Test: Null node type check
TEST(NodeTest_593, NullNodeTypeCheck_593) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}
