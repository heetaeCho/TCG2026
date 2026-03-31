#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include <vector>
#include <string>
#include <sstream>

class LoadAllTest_583 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LoadAll with empty input returns an empty vector
TEST_F(LoadAllTest_583, EmptyInput_ReturnsEmptyVector_583) {
    std::vector<YAML::Node> result = YAML::LoadAll("");
    EXPECT_TRUE(result.empty());
}

// Test that LoadAll with a single document returns one node
TEST_F(LoadAllTest_583, SingleDocument_ReturnsOneNode_583) {
    const char* input = "key: value";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0]["key"].as<std::string>(), "value");
}

// Test that LoadAll with multiple documents separated by --- returns multiple nodes
TEST_F(LoadAllTest_583, MultipleDocuments_ReturnsMultipleNodes_583) {
    const char* input = "---\nkey1: value1\n---\nkey2: value2\n---\nkey3: value3";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0]["key1"].as<std::string>(), "value1");
    EXPECT_EQ(result[1]["key2"].as<std::string>(), "value2");
    EXPECT_EQ(result[2]["key3"].as<std::string>(), "value3");
}

// Test that LoadAll with a single scalar returns one node
TEST_F(LoadAllTest_583, SingleScalar_ReturnsOneNode_583) {
    const char* input = "hello";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].as<std::string>(), "hello");
}

// Test that LoadAll with explicit document start and end markers
TEST_F(LoadAllTest_583, ExplicitDocumentMarkers_583) {
    const char* input = "---\nfoo: bar\n...\n---\nbaz: qux\n...";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0]["foo"].as<std::string>(), "bar");
    EXPECT_EQ(result[1]["baz"].as<std::string>(), "qux");
}

// Test that LoadAll with a sequence returns the correct node
TEST_F(LoadAllTest_583, SequenceDocument_583) {
    const char* input = "- item1\n- item2\n- item3";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    ASSERT_TRUE(result[0].IsSequence());
    EXPECT_EQ(result[0].size(), 3u);
    EXPECT_EQ(result[0][0].as<std::string>(), "item1");
    EXPECT_EQ(result[0][1].as<std::string>(), "item2");
    EXPECT_EQ(result[0][2].as<std::string>(), "item3");
}

// Test that LoadAll with numeric values
TEST_F(LoadAllTest_583, NumericValues_583) {
    const char* input = "---\n42\n---\n3.14";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].as<int>(), 42);
    EXPECT_NEAR(result[1].as<double>(), 3.14, 0.001);
}

// Test that LoadAll with null document
TEST_F(LoadAllTest_583, NullDocument_583) {
    const char* input = "---\n~";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_TRUE(result[0].IsNull());
}

// Test that LoadAll with boolean values
TEST_F(LoadAllTest_583, BooleanValues_583) {
    const char* input = "---\ntrue\n---\nfalse";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].as<bool>(), true);
    EXPECT_EQ(result[1].as<bool>(), false);
}

// Test that LoadAll with nested map
TEST_F(LoadAllTest_583, NestedMap_583) {
    const char* input = "outer:\n  inner: value";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0]["outer"]["inner"].as<std::string>(), "value");
}

// Test that LoadAll with whitespace-only input
TEST_F(LoadAllTest_583, WhitespaceOnlyInput_583) {
    const char* input = "   \n  \n  ";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    // Whitespace-only may produce an empty result or a single null node
    // depending on the implementation; we just ensure no crash
    SUCCEED();
}

// Test that LoadAll with two documents, one empty and one with content
TEST_F(LoadAllTest_583, MixedEmptyAndContentDocuments_583) {
    const char* input = "---\n---\nkey: value";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_GE(result.size(), 1u);
}

// Test that LoadAll with complex multi-document YAML
TEST_F(LoadAllTest_583, ComplexMultiDocument_583) {
    const char* input =
        "---\n"
        "name: Alice\n"
        "age: 30\n"
        "---\n"
        "- red\n"
        "- green\n"
        "- blue\n"
        "---\n"
        "message: hello world\n";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(result[0]["age"].as<int>(), 30);
    ASSERT_TRUE(result[1].IsSequence());
    EXPECT_EQ(result[1].size(), 3u);
    EXPECT_EQ(result[2]["message"].as<std::string>(), "hello world");
}

// Test that LoadAll with invalid YAML throws an exception
TEST_F(LoadAllTest_583, InvalidYaml_ThrowsException_583) {
    const char* input = "---\n{\ninvalid: [yaml: {{{";
    EXPECT_THROW(YAML::LoadAll(input), YAML::Exception);
}

// Test LoadAll via stream overload consistency - both should produce same results
TEST_F(LoadAllTest_583, CharAndStreamConsistency_583) {
    const char* input = "---\na: 1\n---\nb: 2";
    std::vector<YAML::Node> charResult = YAML::LoadAll(input);
    
    std::stringstream stream(input);
    std::vector<YAML::Node> streamResult = YAML::LoadAll(stream);
    
    ASSERT_EQ(charResult.size(), streamResult.size());
    for (size_t i = 0; i < charResult.size(); ++i) {
        EXPECT_EQ(charResult[i].Type(), streamResult[i].Type());
    }
}

// Test LoadAll with a single document that has explicit start
TEST_F(LoadAllTest_583, SingleDocumentExplicitStart_583) {
    const char* input = "---\nhello: world";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0]["hello"].as<std::string>(), "world");
}

// Test LoadAll with quoted strings
TEST_F(LoadAllTest_583, QuotedStrings_583) {
    const char* input = "key: \"hello world\"";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0]["key"].as<std::string>(), "hello world");
}

// Test LoadAll with multiline string
TEST_F(LoadAllTest_583, MultilineString_583) {
    const char* input = "key: |\n  line1\n  line2\n  line3";
    std::vector<YAML::Node> result = YAML::LoadAll(input);
    ASSERT_EQ(result.size(), 1u);
    std::string value = result[0]["key"].as<std::string>();
    EXPECT_NE(value.find("line1"), std::string::npos);
    EXPECT_NE(value.find("line2"), std::string::npos);
    EXPECT_NE(value.find("line3"), std::string::npos);
}
