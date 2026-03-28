#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class YamlLoadTest_580 : public ::testing::Test {
protected:
};

// Test loading a simple scalar value
TEST_F(YamlLoadTest_580, LoadSimpleScalar_580) {
    std::istringstream input("hello");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test loading an empty stream returns undefined/null node
TEST_F(YamlLoadTest_580, LoadEmptyStream_580) {
    std::istringstream input("");
    YAML::Node node = YAML::Load(input);
    EXPECT_FALSE(node.IsDefined());
}

// Test loading a simple integer scalar
TEST_F(YamlLoadTest_580, LoadIntegerScalar_580) {
    std::istringstream input("42");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test loading a simple sequence
TEST_F(YamlLoadTest_580, LoadSimpleSequence_580) {
    std::istringstream input("- one\n- two\n- three");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "one");
    EXPECT_EQ(node[1].as<std::string>(), "two");
    EXPECT_EQ(node[2].as<std::string>(), "three");
}

// Test loading a simple map
TEST_F(YamlLoadTest_580, LoadSimpleMap_580) {
    std::istringstream input("key1: value1\nkey2: value2");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
    EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// Test loading a null value
TEST_F(YamlLoadTest_580, LoadNullValue_580) {
    std::istringstream input("~");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_TRUE(node.IsNull());
}

// Test loading a boolean value
TEST_F(YamlLoadTest_580, LoadBooleanTrue_580) {
    std::istringstream input("true");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(YamlLoadTest_580, LoadBooleanFalse_580) {
    std::istringstream input("false");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<bool>(), false);
}

// Test loading a floating point value
TEST_F(YamlLoadTest_580, LoadFloatingPoint_580) {
    std::istringstream input("3.14");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

// Test loading nested maps
TEST_F(YamlLoadTest_580, LoadNestedMap_580) {
    std::istringstream input("outer:\n  inner: value");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

// Test loading nested sequences
TEST_F(YamlLoadTest_580, LoadNestedSequence_580) {
    std::istringstream input("- - a\n  - b\n- - c\n  - d");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    ASSERT_TRUE(node[0].IsSequence());
    EXPECT_EQ(node[0][0].as<std::string>(), "a");
    EXPECT_EQ(node[0][1].as<std::string>(), "b");
}

// Test loading a map with sequence values
TEST_F(YamlLoadTest_580, LoadMapWithSequenceValues_580) {
    std::istringstream input("fruits:\n  - apple\n  - banana\nvegs:\n  - carrot");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["fruits"].IsSequence());
    EXPECT_EQ(node["fruits"].size(), 2u);
    EXPECT_EQ(node["fruits"][0].as<std::string>(), "apple");
    ASSERT_TRUE(node["vegs"].IsSequence());
    EXPECT_EQ(node["vegs"].size(), 1u);
}

// Test loading a quoted string
TEST_F(YamlLoadTest_580, LoadQuotedString_580) {
    std::istringstream input("\"hello world\"");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test loading a single-quoted string
TEST_F(YamlLoadTest_580, LoadSingleQuotedString_580) {
    std::istringstream input("'hello world'");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Test loading with document markers
TEST_F(YamlLoadTest_580, LoadWithDocumentStart_580) {
    std::istringstream input("---\nhello");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test loading with document start and end markers
TEST_F(YamlLoadTest_580, LoadWithDocumentStartAndEnd_580) {
    std::istringstream input("---\nhello\n...");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test loading only the first document when multiple documents exist
TEST_F(YamlLoadTest_580, LoadFirstDocumentOnly_580) {
    std::istringstream input("---\nfirst\n---\nsecond");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "first");
}

// Test loading an anchor and alias
TEST_F(YamlLoadTest_580, LoadAnchorAndAlias_580) {
    std::istringstream input("- &anchor value\n- *anchor");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "value");
    EXPECT_EQ(node[1].as<std::string>(), "value");
}

// Test loading flow-style sequence
TEST_F(YamlLoadTest_580, LoadFlowSequence_580) {
    std::istringstream input("[a, b, c]");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}

// Test loading flow-style map
TEST_F(YamlLoadTest_580, LoadFlowMap_580) {
    std::istringstream input("{key1: val1, key2: val2}");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "val1");
    EXPECT_EQ(node["key2"].as<std::string>(), "val2");
}

// Test loading a stream with only whitespace
TEST_F(YamlLoadTest_580, LoadWhitespaceOnly_580) {
    std::istringstream input("   \n   \n");
    YAML::Node node = YAML::Load(input);
    EXPECT_FALSE(node.IsDefined());
}

// Test loading a stream with only comments
TEST_F(YamlLoadTest_580, LoadCommentsOnly_580) {
    std::istringstream input("# this is a comment\n# another comment\n");
    YAML::Node node = YAML::Load(input);
    EXPECT_FALSE(node.IsDefined());
}

// Test loading a multiline string (literal block scalar)
TEST_F(YamlLoadTest_580, LoadLiteralBlockScalar_580) {
    std::istringstream input("|\n  line1\n  line2\n  line3");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    std::string expected = "line1\nline2\nline3\n";
    EXPECT_EQ(node.as<std::string>(), expected);
}

// Test loading a folded block scalar
TEST_F(YamlLoadTest_580, LoadFoldedBlockScalar_580) {
    std::istringstream input(">\n  line1\n  line2\n  line3");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    // Folded scalar replaces newlines with spaces
    std::string result = node.as<std::string>();
    EXPECT_FALSE(result.empty());
}

// Test loading an empty sequence
TEST_F(YamlLoadTest_580, LoadEmptyFlowSequence_580) {
    std::istringstream input("[]");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

// Test loading an empty map
TEST_F(YamlLoadTest_580, LoadEmptyFlowMap_580) {
    std::istringstream input("{}");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// Test loading with invalid YAML throws an exception
TEST_F(YamlLoadTest_580, LoadInvalidYamlThrows_580) {
    std::istringstream input(":\n  - :\n    - : ][");
    EXPECT_THROW(YAML::Load(input), YAML::Exception);
}

// Test loading a complex nested structure
TEST_F(YamlLoadTest_580, LoadComplexNestedStructure_580) {
    std::string yamlStr =
        "name: test\n"
        "items:\n"
        "  - id: 1\n"
        "    value: first\n"
        "  - id: 2\n"
        "    value: second\n";
    std::istringstream input(yamlStr);
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "test");
    ASSERT_TRUE(node["items"].IsSequence());
    EXPECT_EQ(node["items"].size(), 2u);
    EXPECT_EQ(node["items"][0]["id"].as<int>(), 1);
    EXPECT_EQ(node["items"][0]["value"].as<std::string>(), "first");
    EXPECT_EQ(node["items"][1]["id"].as<int>(), 2);
    EXPECT_EQ(node["items"][1]["value"].as<std::string>(), "second");
}

// Test loading a negative integer
TEST_F(YamlLoadTest_580, LoadNegativeInteger_580) {
    std::istringstream input("-42");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), -42);
}

// Test loading a string with special characters
TEST_F(YamlLoadTest_580, LoadStringWithSpecialChars_580) {
    std::istringstream input("\"hello\\nworld\"");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello\nworld");
}

// Test loading a tagged value
TEST_F(YamlLoadTest_580, LoadTaggedValue_580) {
    std::istringstream input("!!str 42");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "42");
}

// Test that the stream position is consumed
TEST_F(YamlLoadTest_580, LoadConsumesStream_580) {
    std::istringstream input("hello");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test loading a map with integer keys
TEST_F(YamlLoadTest_580, LoadMapWithIntegerKeys_580) {
    std::istringstream input("1: one\n2: two");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
}

// Test loading explicit null value in a map
TEST_F(YamlLoadTest_580, LoadExplicitNullInMap_580) {
    std::istringstream input("key: ~");
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsMap());
    EXPECT_TRUE(node["key"].IsNull());
}

// Test loading a large sequence
TEST_F(YamlLoadTest_580, LoadLargeSequence_580) {
    std::ostringstream oss;
    for (int i = 0; i < 100; ++i) {
        oss << "- item" << i << "\n";
    }
    std::istringstream input(oss.str());
    YAML::Node node = YAML::Load(input);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 100u);
    EXPECT_EQ(node[0].as<std::string>(), "item0");
    EXPECT_EQ(node[99].as<std::string>(), "item99");
}
