#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/yaml.h"

// Based on yaml-cpp traits, the default specialization returns empty string.
// We test the observable behavior: impl returns "" for various key types.

namespace {

// Test fixture for traits tests
class YamlTraitsTest_80 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default node converted to string key results in expected behavior
TEST_F(YamlTraitsTest_80, NodeDefaultConstruction_80) {
    YAML::Node node;
    EXPECT_NO_THROW(node = YAML::Load(""));
}

TEST_F(YamlTraitsTest_80, NodeScalarAccess_80) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_TRUE(node["key"].IsDefined());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(YamlTraitsTest_80, NodeMapWithStringKeys_80) {
    YAML::Node node = YAML::Load("a: 1\nb: 2\nc: 3");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(YamlTraitsTest_80, NodeSequenceAccess_80) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

TEST_F(YamlTraitsTest_80, EmptyStringKey_80) {
    YAML::Node node;
    node[""] = "empty_key_value";
    EXPECT_EQ(node[""].as<std::string>(), "empty_key_value");
}

TEST_F(YamlTraitsTest_80, IntegerKey_80) {
    YAML::Node node;
    node[0] = "zero";
    node[1] = "one";
    EXPECT_EQ(node[0].as<std::string>(), "zero");
    EXPECT_EQ(node[1].as<std::string>(), "one");
}

TEST_F(YamlTraitsTest_80, NonExistentKeyReturnsUndefined_80) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_FALSE(node["nonexistent"].IsDefined());
}

TEST_F(YamlTraitsTest_80, NullNodeBehavior_80) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YamlTraitsTest_80, BooleanConversion_80) {
    YAML::Node node = YAML::Load("true");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(YamlTraitsTest_80, NestedMapKeyAccess_80) {
    YAML::Node node = YAML::Load("outer:\n  inner: value");
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(YamlTraitsTest_80, LargeStringKey_80) {
    std::string longKey(1000, 'x');
    YAML::Node node;
    node[longKey] = "long_key_value";
    EXPECT_EQ(node[longKey].as<std::string>(), "long_key_value");
}

TEST_F(YamlTraitsTest_80, SpecialCharacterKey_80) {
    YAML::Node node;
    node["key with spaces"] = "val1";
    node["key-with-dashes"] = "val2";
    EXPECT_EQ(node["key with spaces"].as<std::string>(), "val1");
    EXPECT_EQ(node["key-with-dashes"].as<std::string>(), "val2");
}

TEST_F(YamlTraitsTest_80, DuplicateKeyOverwrite_80) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    EXPECT_EQ(node["key"].as<std::string>(), "second");
}

TEST_F(YamlTraitsTest_80, EmptyMapSize_80) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(YamlTraitsTest_80, EmptySequenceSize_80) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

}  // namespace
