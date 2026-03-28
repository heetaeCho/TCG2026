#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <sstream>

namespace {

// Test fixture for Clone tests
class CloneTest_508 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test cloning a Null node
TEST_F(CloneTest_508, CloneNullNode_508) {
    YAML::Node node;
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsNull());
    EXPECT_EQ(cloned.Type(), YAML::NodeType::Null);
}

// Test cloning a scalar node with string value
TEST_F(CloneTest_508, CloneScalarStringNode_508) {
    YAML::Node node("hello");
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_EQ(cloned.as<std::string>(), "hello");
}

// Test cloning a scalar node with integer value
TEST_F(CloneTest_508, CloneScalarIntNode_508) {
    YAML::Node node(42);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_EQ(cloned.as<int>(), 42);
}

// Test cloning a scalar node with floating point value
TEST_F(CloneTest_508, CloneScalarDoubleNode_508) {
    YAML::Node node(3.14);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_DOUBLE_EQ(cloned.as<double>(), 3.14);
}

// Test cloning a boolean scalar node
TEST_F(CloneTest_508, CloneScalarBoolNode_508) {
    YAML::Node node(true);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_EQ(cloned.as<bool>(), true);
}

// Test cloning a sequence node
TEST_F(CloneTest_508, CloneSequenceNode_508) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsSequence());
    EXPECT_EQ(cloned.size(), 3u);
    EXPECT_EQ(cloned[0].as<int>(), 1);
    EXPECT_EQ(cloned[1].as<int>(), 2);
    EXPECT_EQ(cloned[2].as<int>(), 3);
}

// Test cloning a map node
TEST_F(CloneTest_508, CloneMapNode_508) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsMap());
    EXPECT_EQ(cloned.size(), 2u);
    EXPECT_EQ(cloned["key1"].as<std::string>(), "value1");
    EXPECT_EQ(cloned["key2"].as<std::string>(), "value2");
}

// Test that cloned node is independent from original (deep copy)
TEST_F(CloneTest_508, ClonedNodeIsIndependent_508) {
    YAML::Node node;
    node["key"] = "original";
    
    YAML::Node cloned = YAML::Clone(node);
    cloned["key"] = "modified";
    
    EXPECT_EQ(node["key"].as<std::string>(), "original");
    EXPECT_EQ(cloned["key"].as<std::string>(), "modified");
}

// Test that cloned sequence is independent from original
TEST_F(CloneTest_508, ClonedSequenceIsIndependent_508) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    
    YAML::Node cloned = YAML::Clone(node);
    cloned.push_back("c");
    
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(cloned.size(), 3u);
}

// Test cloning an empty sequence
TEST_F(CloneTest_508, CloneEmptySequence_508) {
    YAML::Node node(YAML::NodeType::Sequence);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsSequence());
    EXPECT_EQ(cloned.size(), 0u);
}

// Test cloning an empty map
TEST_F(CloneTest_508, CloneEmptyMap_508) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsMap());
    EXPECT_EQ(cloned.size(), 0u);
}

// Test cloning nested structures (map containing sequence)
TEST_F(CloneTest_508, CloneNestedMapWithSequence_508) {
    YAML::Node node;
    node["list"].push_back(1);
    node["list"].push_back(2);
    node["name"] = "test";
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsMap());
    EXPECT_TRUE(cloned["list"].IsSequence());
    EXPECT_EQ(cloned["list"].size(), 2u);
    EXPECT_EQ(cloned["list"][0].as<int>(), 1);
    EXPECT_EQ(cloned["list"][1].as<int>(), 2);
    EXPECT_EQ(cloned["name"].as<std::string>(), "test");
}

// Test cloning nested structures (sequence containing maps)
TEST_F(CloneTest_508, CloneNestedSequenceWithMap_508) {
    YAML::Node node;
    YAML::Node item1;
    item1["a"] = 1;
    YAML::Node item2;
    item2["b"] = 2;
    node.push_back(item1);
    node.push_back(item2);
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsSequence());
    EXPECT_EQ(cloned.size(), 2u);
    EXPECT_EQ(cloned[0]["a"].as<int>(), 1);
    EXPECT_EQ(cloned[1]["b"].as<int>(), 2);
}

// Test that cloned nested node is deeply independent
TEST_F(CloneTest_508, ClonedNestedNodeIsDeepIndependent_508) {
    YAML::Node node;
    node["nested"]["key"] = "original";
    
    YAML::Node cloned = YAML::Clone(node);
    cloned["nested"]["key"] = "modified";
    
    EXPECT_EQ(node["nested"]["key"].as<std::string>(), "original");
    EXPECT_EQ(cloned["nested"]["key"].as<std::string>(), "modified");
}

// Test cloning a node created from YAML string
TEST_F(CloneTest_508, CloneFromParsedYAML_508) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    YAML::Node cloned = YAML::Clone(node);
    
    EXPECT_TRUE(cloned.IsMap());
    EXPECT_EQ(cloned["name"].as<std::string>(), "John");
    EXPECT_EQ(cloned["age"].as<int>(), 30);
}

// Test cloning preserves type for explicitly typed Null node
TEST_F(CloneTest_508, CloneExplicitNullType_508) {
    YAML::Node node(YAML::NodeType::Null);
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsNull());
}

// Test cloning an empty scalar
TEST_F(CloneTest_508, CloneEmptyScalar_508) {
    YAML::Node node("");
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_EQ(cloned.as<std::string>(), "");
}

// Test cloning a scalar node with special characters
TEST_F(CloneTest_508, CloneScalarWithSpecialChars_508) {
    YAML::Node node("hello\nworld\ttab");
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsScalar());
    EXPECT_EQ(cloned.as<std::string>(), "hello\nworld\ttab");
}

// Test cloning preserves tag
TEST_F(CloneTest_508, ClonePreservesTag_508) {
    YAML::Node node = YAML::Load("!custom_tag value");
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_EQ(cloned.Tag(), node.Tag());
    EXPECT_EQ(cloned.as<std::string>(), "value");
}

// Test cloning a large sequence
TEST_F(CloneTest_508, CloneLargeSequence_508) {
    YAML::Node node;
    for (int i = 0; i < 100; i++) {
        node.push_back(i);
    }
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsSequence());
    EXPECT_EQ(cloned.size(), 100u);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(cloned[i].as<int>(), i);
    }
}

// Test cloning a large map
TEST_F(CloneTest_508, CloneLargeMap_508) {
    YAML::Node node;
    for (int i = 0; i < 100; i++) {
        node["key" + std::to_string(i)] = i;
    }
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsMap());
    EXPECT_EQ(cloned.size(), 100u);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(cloned["key" + std::to_string(i)].as<int>(), i);
    }
}

// Test that cloned node is not the same identity as original
TEST_F(CloneTest_508, ClonedNodeIsNotSameIdentity_508) {
    YAML::Node node("test");
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_FALSE(node.is(cloned));
}

// Test cloning deeply nested structure
TEST_F(CloneTest_508, CloneDeeplyNestedStructure_508) {
    YAML::Node node;
    node["level1"]["level2"]["level3"]["level4"] = "deep_value";
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_EQ(cloned["level1"]["level2"]["level3"]["level4"].as<std::string>(), "deep_value");
}

// Test cloning complex YAML
TEST_F(CloneTest_508, CloneComplexYAML_508) {
    std::string yaml = R"(
database:
  host: localhost
  port: 5432
  credentials:
    username: admin
    password: secret
  tables:
    - users
    - orders
    - products
)";
    YAML::Node node = YAML::Load(yaml);
    YAML::Node cloned = YAML::Clone(node);
    
    EXPECT_EQ(cloned["database"]["host"].as<std::string>(), "localhost");
    EXPECT_EQ(cloned["database"]["port"].as<int>(), 5432);
    EXPECT_EQ(cloned["database"]["credentials"]["username"].as<std::string>(), "admin");
    EXPECT_EQ(cloned["database"]["credentials"]["password"].as<std::string>(), "secret");
    EXPECT_EQ(cloned["database"]["tables"].size(), 3u);
    EXPECT_EQ(cloned["database"]["tables"][0].as<std::string>(), "users");
    EXPECT_EQ(cloned["database"]["tables"][1].as<std::string>(), "orders");
    EXPECT_EQ(cloned["database"]["tables"][2].as<std::string>(), "products");
}

// Test modifying original after clone does not affect clone
TEST_F(CloneTest_508, ModifyOriginalAfterClone_508) {
    YAML::Node node;
    node["key"] = "value";
    
    YAML::Node cloned = YAML::Clone(node);
    node["key"] = "changed";
    node["newkey"] = "newvalue";
    
    EXPECT_EQ(cloned["key"].as<std::string>(), "value");
    EXPECT_FALSE(cloned["newkey"].IsDefined());
}

// Test cloning with YAML anchors/aliases
TEST_F(CloneTest_508, CloneWithAnchors_508) {
    std::string yaml = R"(
defaults: &defaults
  adapter: postgres
  host: localhost

development:
  <<: *defaults
  database: dev_db
)";
    YAML::Node node = YAML::Load(yaml);
    YAML::Node cloned = YAML::Clone(node);
    
    EXPECT_EQ(cloned["development"]["adapter"].as<std::string>(), "postgres");
    EXPECT_EQ(cloned["development"]["host"].as<std::string>(), "localhost");
    EXPECT_EQ(cloned["development"]["database"].as<std::string>(), "dev_db");
}

// Test cloning preserves style (flow vs block)
TEST_F(CloneTest_508, ClonePreservesStyle_508) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    node.push_back(1);
    node.push_back(2);
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_EQ(cloned.Style(), YAML::EmitterStyle::Flow);
}

// Test cloning a node with mixed types in sequence
TEST_F(CloneTest_508, CloneMixedTypeSequence_508) {
    YAML::Node node;
    node.push_back(42);
    node.push_back("hello");
    node.push_back(3.14);
    node.push_back(true);
    
    YAML::Node cloned = YAML::Clone(node);
    EXPECT_TRUE(cloned.IsSequence());
    EXPECT_EQ(cloned.size(), 4u);
    EXPECT_EQ(cloned[0].as<int>(), 42);
    EXPECT_EQ(cloned[1].as<std::string>(), "hello");
    EXPECT_DOUBLE_EQ(cloned[2].as<double>(), 3.14);
    EXPECT_EQ(cloned[3].as<bool>(), true);
}

}  // namespace
