#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

class LoadAllTest_584 : public ::testing::Test {
protected:
    std::vector<YAML::Node> LoadAllFromString(const std::string& input) {
        std::istringstream stream(input);
        return YAML::LoadAll(stream);
    }
};

// Test with empty input
TEST_F(LoadAllTest_584, EmptyInput_584) {
    auto docs = LoadAllFromString("");
    EXPECT_EQ(docs.size(), 0u);
}

// Test with a single simple scalar document
TEST_F(LoadAllTest_584, SingleScalarDocument_584) {
    auto docs = LoadAllFromString("hello");
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0].as<std::string>(), "hello");
}

// Test with multiple documents separated by ---
TEST_F(LoadAllTest_584, MultipleDocumentsSeparatedByDashes_584) {
    std::string input = "---\nfoo\n---\nbar\n---\nbaz\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 3u);
    EXPECT_EQ(docs[0].as<std::string>(), "foo");
    EXPECT_EQ(docs[1].as<std::string>(), "bar");
    EXPECT_EQ(docs[2].as<std::string>(), "baz");
}

// Test with two documents, one map and one sequence
TEST_F(LoadAllTest_584, MapAndSequenceDocuments_584) {
    std::string input = "---\nkey: value\n---\n- item1\n- item2\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_TRUE(docs[0].IsMap());
    EXPECT_EQ(docs[0]["key"].as<std::string>(), "value");
    EXPECT_TRUE(docs[1].IsSequence());
    EXPECT_EQ(docs[1].size(), 2u);
    EXPECT_EQ(docs[1][0].as<std::string>(), "item1");
    EXPECT_EQ(docs[1][1].as<std::string>(), "item2");
}

// Test with document end marker (...)
TEST_F(LoadAllTest_584, DocumentEndMarker_584) {
    std::string input = "---\nfirst\n...\n---\nsecond\n...\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0].as<std::string>(), "first");
    EXPECT_EQ(docs[1].as<std::string>(), "second");
}

// Test with a single document with explicit start
TEST_F(LoadAllTest_584, SingleDocumentWithExplicitStart_584) {
    std::string input = "---\nhello world\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0].as<std::string>(), "hello world");
}

// Test with integer scalar documents
TEST_F(LoadAllTest_584, IntegerScalarDocuments_584) {
    std::string input = "---\n42\n---\n100\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0].as<int>(), 42);
    EXPECT_EQ(docs[1].as<int>(), 100);
}

// Test with boolean documents
TEST_F(LoadAllTest_584, BooleanDocuments_584) {
    std::string input = "---\ntrue\n---\nfalse\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0].as<bool>(), true);
    EXPECT_EQ(docs[1].as<bool>(), false);
}

// Test with a complex nested map
TEST_F(LoadAllTest_584, ComplexNestedMapDocument_584) {
    std::string input = "---\nouter:\n  inner: value\n  list:\n    - a\n    - b\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsMap());
    EXPECT_EQ(docs[0]["outer"]["inner"].as<std::string>(), "value");
    EXPECT_TRUE(docs[0]["outer"]["list"].IsSequence());
    EXPECT_EQ(docs[0]["outer"]["list"].size(), 2u);
}

// Test with null document
TEST_F(LoadAllTest_584, NullDocument_584) {
    std::string input = "---\n~\n";
    auto docs = LoadAllFromString(input);
    // A null document: depending on implementation, it may or may not be included
    // The code checks builder.Root().IsNull() and breaks if true
    // So a null scalar document should cause a break
    EXPECT_EQ(docs.size(), 0u);
}

// Test with whitespace-only input
TEST_F(LoadAllTest_584, WhitespaceOnlyInput_584) {
    std::string input = "   \n  \n  ";
    auto docs = LoadAllFromString(input);
    EXPECT_EQ(docs.size(), 0u);
}

// Test with multiple documents, some with maps and scalars
TEST_F(LoadAllTest_584, MixedDocumentTypes_584) {
    std::string input =
        "---\nscalar_value\n"
        "---\n- seq1\n- seq2\n"
        "---\nkey1: val1\nkey2: val2\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 3u);
    EXPECT_TRUE(docs[0].IsScalar());
    EXPECT_TRUE(docs[1].IsSequence());
    EXPECT_TRUE(docs[2].IsMap());
}

// Test with floating point values
TEST_F(LoadAllTest_584, FloatingPointDocuments_584) {
    std::string input = "---\n3.14\n---\n2.718\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_DOUBLE_EQ(docs[0].as<double>(), 3.14);
    EXPECT_DOUBLE_EQ(docs[1].as<double>(), 2.718);
}

// Test with anchors and aliases within a single document
TEST_F(LoadAllTest_584, AnchorAndAliasInDocument_584) {
    std::string input = "---\n- &anchor value\n- *anchor\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsSequence());
    EXPECT_EQ(docs[0][0].as<std::string>(), "value");
    EXPECT_EQ(docs[0][1].as<std::string>(), "value");
}

// Test with tagged values
TEST_F(LoadAllTest_584, TaggedDocument_584) {
    std::string input = "---\n!!str 42\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0].as<std::string>(), "42");
}

// Test document size preservation
TEST_F(LoadAllTest_584, DocumentSizePreservation_584) {
    std::string input = "---\na: 1\nb: 2\nc: 3\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0].size(), 3u);
}

// Test multiple documents with document end markers and start markers
TEST_F(LoadAllTest_584, MixedEndAndStartMarkers_584) {
    std::string input = "---\nfirst\n...\n---\nsecond\n---\nthird\n...\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 3u);
    EXPECT_EQ(docs[0].as<std::string>(), "first");
    EXPECT_EQ(docs[1].as<std::string>(), "second");
    EXPECT_EQ(docs[2].as<std::string>(), "third");
}

// Test with empty map document
TEST_F(LoadAllTest_584, EmptyMapDocument_584) {
    std::string input = "---\n{}\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsMap());
    EXPECT_EQ(docs[0].size(), 0u);
}

// Test with empty sequence document
TEST_F(LoadAllTest_584, EmptySequenceDocument_584) {
    std::string input = "---\n[]\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsSequence());
    EXPECT_EQ(docs[0].size(), 0u);
}

// Test with a single document without explicit markers
TEST_F(LoadAllTest_584, SingleDocumentNoMarkers_584) {
    std::string input = "key: value\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsMap());
    EXPECT_EQ(docs[0]["key"].as<std::string>(), "value");
}

// Test with multiline string document
TEST_F(LoadAllTest_584, MultilineStringDocument_584) {
    std::string input = "---\n|\n  line1\n  line2\n  line3\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsScalar());
    std::string val = docs[0].as<std::string>();
    EXPECT_NE(val.find("line1"), std::string::npos);
    EXPECT_NE(val.find("line2"), std::string::npos);
    EXPECT_NE(val.find("line3"), std::string::npos);
}

// Test that returned nodes are independent copies
TEST_F(LoadAllTest_584, ReturnedNodesAreAccessible_584) {
    std::string input = "---\na: 1\n---\nb: 2\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    // Verify we can independently access both documents
    EXPECT_EQ(docs[0]["a"].as<int>(), 1);
    EXPECT_EQ(docs[1]["b"].as<int>(), 2);
    // First doc shouldn't have key "b"
    EXPECT_FALSE(docs[0]["b"].IsDefined());
    // Second doc shouldn't have key "a"
    EXPECT_FALSE(docs[1]["a"].IsDefined());
}

// Test with flow-style sequences in multiple documents
TEST_F(LoadAllTest_584, FlowStyleSequenceDocuments_584) {
    std::string input = "---\n[1, 2, 3]\n---\n[4, 5, 6]\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0].size(), 3u);
    EXPECT_EQ(docs[0][0].as<int>(), 1);
    EXPECT_EQ(docs[0][2].as<int>(), 3);
    EXPECT_EQ(docs[1].size(), 3u);
    EXPECT_EQ(docs[1][0].as<int>(), 4);
    EXPECT_EQ(docs[1][2].as<int>(), 6);
}

// Test with flow-style map documents
TEST_F(LoadAllTest_584, FlowStyleMapDocuments_584) {
    std::string input = "---\n{a: 1, b: 2}\n---\n{c: 3}\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0]["a"].as<int>(), 1);
    EXPECT_EQ(docs[0]["b"].as<int>(), 2);
    EXPECT_EQ(docs[1]["c"].as<int>(), 3);
}

// Test with comments in documents
TEST_F(LoadAllTest_584, CommentsInDocuments_584) {
    std::string input = "---\n# This is a comment\nfoo: bar  # inline comment\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0]["foo"].as<std::string>(), "bar");
}

// Test with many documents
TEST_F(LoadAllTest_584, ManyDocuments_584) {
    std::string input;
    const int numDocs = 50;
    for (int i = 0; i < numDocs; ++i) {
        input += "---\nvalue: " + std::to_string(i) + "\n";
    }
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), static_cast<size_t>(numDocs));
    for (int i = 0; i < numDocs; ++i) {
        EXPECT_EQ(docs[i]["value"].as<int>(), i);
    }
}

// Test istream-based LoadAll directly
TEST_F(LoadAllTest_584, IstreamBasedLoadAll_584) {
    std::istringstream stream("---\ntest: 123\n---\ntest: 456\n");
    auto docs = YAML::LoadAll(stream);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0]["test"].as<int>(), 123);
    EXPECT_EQ(docs[1]["test"].as<int>(), 456);
}

// Test with quoted strings
TEST_F(LoadAllTest_584, QuotedStrings_584) {
    std::string input = "---\n\"hello world\"\n---\n'single quoted'\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0].as<std::string>(), "hello world");
    EXPECT_EQ(docs[1].as<std::string>(), "single quoted");
}

// Test with nested sequences
TEST_F(LoadAllTest_584, NestedSequences_584) {
    std::string input = "---\n- - 1\n  - 2\n- - 3\n  - 4\n";
    auto docs = LoadAllFromString(input);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0].IsSequence());
    EXPECT_EQ(docs[0][0][0].as<int>(), 1);
    EXPECT_EQ(docs[0][0][1].as<int>(), 2);
    EXPECT_EQ(docs[0][1][0].as<int>(), 3);
    EXPECT_EQ(docs[0][1][1].as<int>(), 4);
}
