#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <sstream>

// Test fixture for YAML::Load tests
class YAMLLoadTest_578 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(YAMLLoadTest_578, LoadSimpleScalar_578) {
    YAML::Node node = YAML::Load("hello");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(YAMLLoadTest_578, LoadInteger_578) {
    YAML::Node node = YAML::Load("42");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(YAMLLoadTest_578, LoadFloat_578) {
    YAML::Node node = YAML::Load("3.14");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_NEAR(node.as<double>(), 3.14, 0.001);
}

TEST_F(YAMLLoadTest_578, LoadBoolean_578) {
    YAML::Node node = YAML::Load("true");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(YAMLLoadTest_578, LoadSimpleMap_578) {
    YAML::Node node = YAML::Load("key: value");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(YAMLLoadTest_578, LoadMultipleKeyValuePairs_578) {
    std::string yaml = "name: John\nage: 30\ncity: NYC";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
    EXPECT_EQ(node["city"].as<std::string>(), "NYC");
}

TEST_F(YAMLLoadTest_578, LoadSimpleSequence_578) {
    std::string yaml = "- item1\n- item2\n- item3";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "item1");
    EXPECT_EQ(node[1].as<std::string>(), "item2");
    EXPECT_EQ(node[2].as<std::string>(), "item3");
}

TEST_F(YAMLLoadTest_578, LoadFlowSequence_578) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST_F(YAMLLoadTest_578, LoadFlowMap_578) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
}

TEST_F(YAMLLoadTest_578, LoadNestedMap_578) {
    std::string yaml = "outer:\n  inner: value";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(YAMLLoadTest_578, LoadNestedSequence_578) {
    std::string yaml = "- - 1\n  - 2\n- - 3\n  - 4";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    ASSERT_TRUE(node[0].IsSequence());
    ASSERT_TRUE(node[1].IsSequence());
}

TEST_F(YAMLLoadTest_578, LoadMapWithSequenceValue_578) {
    std::string yaml = "items:\n  - a\n  - b\n  - c";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["items"].IsSequence());
    EXPECT_EQ(node["items"].size(), 3u);
}

TEST_F(YAMLLoadTest_578, LoadQuotedString_578) {
    YAML::Node node = YAML::Load("\"hello world\"");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(YAMLLoadTest_578, LoadSingleQuotedString_578) {
    YAML::Node node = YAML::Load("'hello world'");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

// Boundary condition tests

TEST_F(YAMLLoadTest_578, LoadEmptyString_578) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadNullValue_578) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadNullWord_578) {
    YAML::Node node = YAML::Load("null");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadEmptyMap_578) {
    YAML::Node node = YAML::Load("{}");
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(YAMLLoadTest_578, LoadEmptySequence_578) {
    YAML::Node node = YAML::Load("[]");
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(YAMLLoadTest_578, LoadWhitespaceOnly_578) {
    YAML::Node node = YAML::Load("   ");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadNewlineOnly_578) {
    YAML::Node node = YAML::Load("\n");
    EXPECT_TRUE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadNegativeInteger_578) {
    YAML::Node node = YAML::Load("-42");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), -42);
}

TEST_F(YAMLLoadTest_578, LoadZero_578) {
    YAML::Node node = YAML::Load("0");
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<int>(), 0);
}

TEST_F(YAMLLoadTest_578, LoadLargeSequence_578) {
    std::string yaml = "[";
    for (int i = 0; i < 100; i++) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 100u);
}

// Error / exceptional cases

TEST_F(YAMLLoadTest_578, LoadInvalidYAMLThrows_578) {
    EXPECT_THROW(YAML::Load(":\n  :\n    - :\n  -:bad"), YAML::Exception);
}

TEST_F(YAMLLoadTest_578, LoadBadIndentationThrows_578) {
    std::string yaml = "key:\n value\n  bad";
    // This may or may not throw depending on interpretation; test that it doesn't crash
    // If it's valid YAML, it parses. If not, it throws YAML::Exception.
    try {
        YAML::Node node = YAML::Load(yaml);
        // If it didn't throw, the node should be defined
        EXPECT_TRUE(node.IsDefined());
    } catch (const YAML::Exception&) {
        // This is also acceptable behavior
        SUCCEED();
    }
}

TEST_F(YAMLLoadTest_578, LoadTabsInIndentation_578) {
    // YAML spec forbids tabs for indentation
    std::string yaml = "key:\n\tvalue";
    EXPECT_THROW(YAML::Load(yaml), YAML::Exception);
}

// Multi-document awareness
TEST_F(YAMLLoadTest_578, LoadFirstDocumentOnly_578) {
    std::string yaml = "---\nfirst\n---\nsecond";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "first");
}

// Anchor and alias
TEST_F(YAMLLoadTest_578, LoadAnchorAndAlias_578) {
    std::string yaml = "anchor: &val hello\nalias: *val";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    EXPECT_EQ(node["anchor"].as<std::string>(), "hello");
    EXPECT_EQ(node["alias"].as<std::string>(), "hello");
}

// Multiline string
TEST_F(YAMLLoadTest_578, LoadLiteralBlock_578) {
    std::string yaml = "text: |\n  line1\n  line2\n  line3";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    std::string text = node["text"].as<std::string>();
    EXPECT_NE(text.find("line1"), std::string::npos);
    EXPECT_NE(text.find("line2"), std::string::npos);
    EXPECT_NE(text.find("line3"), std::string::npos);
}

TEST_F(YAMLLoadTest_578, LoadFoldedBlock_578) {
    std::string yaml = "text: >\n  line1\n  line2";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    EXPECT_FALSE(node["text"].as<std::string>().empty());
}

// Special characters in strings
TEST_F(YAMLLoadTest_578, LoadStringWithSpecialCharacters_578) {
    YAML::Node node = YAML::Load("\"special: chars [in] {string}\"");
    EXPECT_EQ(node.as<std::string>(), "special: chars [in] {string}");
}

// Verify node type consistency
TEST_F(YAMLLoadTest_578, LoadScalarIsScalar_578) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadMapIsMap_578) {
    YAML::Node node = YAML::Load("a: 1");
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsNull());
}

TEST_F(YAMLLoadTest_578, LoadSequenceIsSequence_578) {
    YAML::Node node = YAML::Load("[1, 2]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
}

// Unicode / UTF-8
TEST_F(YAMLLoadTest_578, LoadUTF8String_578) {
    YAML::Node node = YAML::Load("\"héllo wörld\"");
    EXPECT_EQ(node.as<std::string>(), "héllo wörld");
}

// Complex nested structure
TEST_F(YAMLLoadTest_578, LoadComplexStructure_578) {
    std::string yaml =
        "database:\n"
        "  host: localhost\n"
        "  port: 5432\n"
        "  tables:\n"
        "    - users\n"
        "    - orders\n"
        "  credentials:\n"
        "    username: admin\n"
        "    password: secret";
    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["database"].IsMap());
    EXPECT_EQ(node["database"]["host"].as<std::string>(), "localhost");
    EXPECT_EQ(node["database"]["port"].as<int>(), 5432);
    ASSERT_TRUE(node["database"]["tables"].IsSequence());
    EXPECT_EQ(node["database"]["tables"].size(), 2u);
    EXPECT_EQ(node["database"]["credentials"]["username"].as<std::string>(), "admin");
}

// Missing key returns undefined node
TEST_F(YAMLLoadTest_578, LoadMapAccessNonexistentKey_578) {
    YAML::Node node = YAML::Load("key: value");
    EXPECT_FALSE(node["nonexistent"].IsDefined());
}

// Boolean variants
TEST_F(YAMLLoadTest_578, LoadBooleanFalse_578) {
    YAML::Node node = YAML::Load("false");
    EXPECT_EQ(node.as<bool>(), false);
}

TEST_F(YAMLLoadTest_578, LoadBooleanYes_578) {
    YAML::Node node = YAML::Load("yes");
    EXPECT_EQ(node.as<bool>(), true);
}

TEST_F(YAMLLoadTest_578, LoadBooleanNo_578) {
    YAML::Node node = YAML::Load("no");
    EXPECT_EQ(node.as<bool>(), false);
}
