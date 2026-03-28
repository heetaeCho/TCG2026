#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

class LoadAllTest_582 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test loading an empty string returns no nodes
TEST_F(LoadAllTest_582, EmptyStringReturnsEmpty_582) {
    std::string input = "";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    EXPECT_TRUE(nodes.empty());
}

// Test loading a single YAML document
TEST_F(LoadAllTest_582, SingleDocument_582) {
    std::string input = "key: value";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_EQ(nodes[0]["key"].as<std::string>(), "value");
}

// Test loading multiple YAML documents separated by ---
TEST_F(LoadAllTest_582, MultipleDocuments_582) {
    std::string input = "---\nfoo: bar\n---\nbaz: qux\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 2u);
    EXPECT_EQ(nodes[0]["foo"].as<std::string>(), "bar");
    EXPECT_EQ(nodes[1]["baz"].as<std::string>(), "qux");
}

// Test loading multiple documents with explicit end markers
TEST_F(LoadAllTest_582, MultipleDocumentsWithEndMarkers_582) {
    std::string input = "---\na: 1\n...\n---\nb: 2\n...\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 2u);
    EXPECT_EQ(nodes[0]["a"].as<int>(), 1);
    EXPECT_EQ(nodes[1]["b"].as<int>(), 2);
}

// Test loading a single scalar value
TEST_F(LoadAllTest_582, SingleScalar_582) {
    std::string input = "hello";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_EQ(nodes[0].as<std::string>(), "hello");
}

// Test loading a sequence
TEST_F(LoadAllTest_582, SingleSequence_582) {
    std::string input = "- 1\n- 2\n- 3\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    ASSERT_TRUE(nodes[0].IsSequence());
    EXPECT_EQ(nodes[0].size(), 3u);
    EXPECT_EQ(nodes[0][0].as<int>(), 1);
    EXPECT_EQ(nodes[0][1].as<int>(), 2);
    EXPECT_EQ(nodes[0][2].as<int>(), 3);
}

// Test loading a map
TEST_F(LoadAllTest_582, SingleMap_582) {
    std::string input = "name: John\nage: 30\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    ASSERT_TRUE(nodes[0].IsMap());
    EXPECT_EQ(nodes[0]["name"].as<std::string>(), "John");
    EXPECT_EQ(nodes[0]["age"].as<int>(), 30);
}

// Test loading three documents
TEST_F(LoadAllTest_582, ThreeDocuments_582) {
    std::string input = "---\na: 1\n---\nb: 2\n---\nc: 3\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 3u);
    EXPECT_EQ(nodes[0]["a"].as<int>(), 1);
    EXPECT_EQ(nodes[1]["b"].as<int>(), 2);
    EXPECT_EQ(nodes[2]["c"].as<int>(), 3);
}

// Test loading invalid YAML throws an exception
TEST_F(LoadAllTest_582, InvalidYamlThrows_582) {
    std::string input = ":\n  :\n    - :\n      bad: [unmatched";
    EXPECT_THROW(YAML::LoadAll(input), YAML::Exception);
}

// Test loading null document
TEST_F(LoadAllTest_582, NullDocument_582) {
    std::string input = "---\n~\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_TRUE(nodes[0].IsNull());
}

// Test loading document with only whitespace
TEST_F(LoadAllTest_582, WhitespaceOnly_582) {
    std::string input = "   \n   \n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    // Whitespace-only input may yield an empty result or a null node
    // depending on the implementation
    if (!nodes.empty()) {
        EXPECT_TRUE(nodes[0].IsNull());
    }
}

// Test loading nested map
TEST_F(LoadAllTest_582, NestedMap_582) {
    std::string input = "outer:\n  inner: value\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_EQ(nodes[0]["outer"]["inner"].as<std::string>(), "value");
}

// Test loading boolean values
TEST_F(LoadAllTest_582, BooleanValues_582) {
    std::string input = "flag: true\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_EQ(nodes[0]["flag"].as<bool>(), true);
}

// Test loading floating point values
TEST_F(LoadAllTest_582, FloatingPointValues_582) {
    std::string input = "pi: 3.14159\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_DOUBLE_EQ(nodes[0]["pi"].as<double>(), 3.14159);
}

// Test loading mixed document types
TEST_F(LoadAllTest_582, MixedDocumentTypes_582) {
    std::string input = "---\nhello\n---\n- 1\n- 2\n---\nkey: value\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 3u);
    EXPECT_TRUE(nodes[0].IsScalar());
    EXPECT_TRUE(nodes[1].IsSequence());
    EXPECT_TRUE(nodes[2].IsMap());
}

// Test loading document with explicit document start and end
TEST_F(LoadAllTest_582, ExplicitDocumentStartEnd_582) {
    std::string input = "---\nfoo: bar\n...\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    EXPECT_EQ(nodes[0]["foo"].as<std::string>(), "bar");
}

// Test loading flow-style sequence
TEST_F(LoadAllTest_582, FlowStyleSequence_582) {
    std::string input = "[1, 2, 3]";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    ASSERT_TRUE(nodes[0].IsSequence());
    EXPECT_EQ(nodes[0].size(), 3u);
}

// Test loading flow-style map
TEST_F(LoadAllTest_582, FlowStyleMap_582) {
    std::string input = "{a: 1, b: 2}";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_EQ(nodes.size(), 1u);
    ASSERT_TRUE(nodes[0].IsMap());
    EXPECT_EQ(nodes[0]["a"].as<int>(), 1);
    EXPECT_EQ(nodes[0]["b"].as<int>(), 2);
}

// Test empty documents between separators
TEST_F(LoadAllTest_582, EmptyDocumentsBetweenSeparators_582) {
    std::string input = "---\n---\n";
    std::vector<YAML::Node> nodes = YAML::LoadAll(input);
    ASSERT_GE(nodes.size(), 1u);
    // First document should be null since it's empty between --- markers
    EXPECT_TRUE(nodes[0].IsNull());
}
