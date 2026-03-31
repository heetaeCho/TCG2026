#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <sstream>

// Test normal YAML string parsing
TEST(YamlLoadTest_579, LoadSimpleScalar_579) {
    YAML::Node node = YAML::Load("hello");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(YamlLoadTest_579, LoadInteger_579) {
    YAML::Node node = YAML::Load("42");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(YamlLoadTest_579, LoadSimpleMap_579) {
    YAML::Node node = YAML::Load("key: value");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(YamlLoadTest_579, LoadSimpleSequence_579) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(YamlLoadTest_579, LoadNestedMap_579) {
    const char* yaml = "outer:\n  inner: value";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(YamlLoadTest_579, LoadEmptyString_579) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

TEST(YamlLoadTest_579, LoadNullValue_579) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(YamlLoadTest_579, LoadBooleanTrue_579) {
    YAML::Node node = YAML::Load("true");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST(YamlLoadTest_579, LoadBooleanFalse_579) {
    YAML::Node node = YAML::Load("false");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<bool>(), false);
}

TEST(YamlLoadTest_579, LoadFloatingPoint_579) {
    YAML::Node node = YAML::Load("3.14");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST(YamlLoadTest_579, LoadMultipleKeysMap_579) {
    const char* yaml = "a: 1\nb: 2\nc: 3";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

TEST(YamlLoadTest_579, LoadSequenceOfMaps_579) {
    const char* yaml = "- name: Alice\n- name: Bob";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[1]["name"].as<std::string>(), "Bob");
}

TEST(YamlLoadTest_579, LoadQuotedString_579) {
    YAML::Node node = YAML::Load("\"hello world\"");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST(YamlLoadTest_579, LoadInvalidYamlThrows_579) {
    EXPECT_THROW(YAML::Load("[invalid: yaml: ::"), YAML::Exception);
}

TEST(YamlLoadTest_579, LoadFlowMap_579) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST(YamlLoadTest_579, LoadNullPointerThrows_579) {
    const char* input = nullptr;
    EXPECT_THROW(YAML::Load(input), std::exception);
}

TEST(YamlLoadTest_579, LoadOnlyWhitespace_579) {
    YAML::Node node = YAML::Load("   ");
    EXPECT_TRUE(node.IsNull());
}

TEST(YamlLoadTest_579, LoadMultilineString_579) {
    const char* yaml = "key: |\n  line1\n  line2";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    std::string val = node["key"].as<std::string>();
    EXPECT_TRUE(val.find("line1") != std::string::npos);
    EXPECT_TRUE(val.find("line2") != std::string::npos);
}

TEST(YamlLoadTest_579, LoadEmptySequence_579) {
    YAML::Node node = YAML::Load("[]");
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST(YamlLoadTest_579, LoadEmptyMap_579) {
    YAML::Node node = YAML::Load("{}");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

TEST(YamlLoadTest_579, LoadNegativeInteger_579) {
    YAML::Node node = YAML::Load("-99");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), -99);
}

TEST(YamlLoadTest_579, LoadStringWithSpecialCharacters_579) {
    YAML::Node node = YAML::Load("\"special: chars [here]\"");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "special: chars [here]");
}

// Test loading from stream (which Load(const char*) delegates to)
TEST(YamlLoadStreamTest_579, LoadFromStream_579) {
    std::stringstream ss("key: value");
    YAML::Node node = YAML::Load(ss);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST(YamlLoadStreamTest_579, LoadFromEmptyStream_579) {
    std::stringstream ss("");
    YAML::Node node = YAML::Load(ss);
    EXPECT_TRUE(node.IsNull());
}
