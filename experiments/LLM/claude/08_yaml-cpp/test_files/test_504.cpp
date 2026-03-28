#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"

namespace YAML {

// Mock EventHandler for testing HandleNextDocument
class MockEventHandler : public EventHandler {
public:
    MOCK_METHOD(void, OnDocumentStart, (const Mark& mark), (override));
    MOCK_METHOD(void, OnDocumentEnd, (), (override));
    MOCK_METHOD(void, OnNull, (const Mark& mark, anchor_t anchor), (override));
    MOCK_METHOD(void, OnAlias, (const Mark& mark, anchor_t anchor), (override));
    MOCK_METHOD(void, OnScalar, (const Mark& mark, const std::string& tag, anchor_t anchor, const std::string& value), (override));
    MOCK_METHOD(void, OnSequenceStart, (const Mark& mark, const std::string& tag, anchor_t anchor, EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnSequenceEnd, (), (override));
    MOCK_METHOD(void, OnMapStart, (const Mark& mark, const std::string& tag, anchor_t anchor, EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnMapEnd, (), (override));
    MOCK_METHOD(void, OnAnchor, (const Mark& mark, const std::string& anchor_name), (override));
};

class ParserTest_504 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor - parser should be falsy (no scanner)
TEST_F(ParserTest_504, DefaultConstructorIsFalsy_504) {
    Parser parser;
    EXPECT_FALSE(static_cast<bool>(parser));
}

// Test constructor with empty stream
TEST_F(ParserTest_504, ConstructWithEmptyStream_504) {
    std::stringstream ss("");
    Parser parser(ss);
    // An empty stream should result in scanner being empty
    EXPECT_FALSE(static_cast<bool>(parser));
}

// Test constructor with valid YAML content
TEST_F(ParserTest_504, ConstructWithValidYAML_504) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
}

// Test Load method with valid content
TEST_F(ParserTest_504, LoadWithValidContent_504) {
    Parser parser;
    EXPECT_FALSE(static_cast<bool>(parser));
    
    std::stringstream ss("hello: world");
    parser.Load(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
}

// Test Load method with empty stream
TEST_F(ParserTest_504, LoadWithEmptyStream_504) {
    Parser parser;
    std::stringstream ss("");
    parser.Load(ss);
    EXPECT_FALSE(static_cast<bool>(parser));
}

// Test Load replaces previous content
TEST_F(ParserTest_504, LoadReplacesExistingContent_504) {
    std::stringstream ss1("key1: value1");
    Parser parser(ss1);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    std::stringstream ss2("key2: value2");
    parser.Load(ss2);
    EXPECT_TRUE(static_cast<bool>(parser));
}

// Test HandleNextDocument with valid YAML document
TEST_F(ParserTest_504, HandleNextDocumentWithSimpleScalar_504) {
    std::stringstream ss("hello");
    Parser parser(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument returns false when no documents remain
TEST_F(ParserTest_504, HandleNextDocumentReturnsFalseWhenEmpty_504) {
    Parser parser;
    MockEventHandler handler;
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_FALSE(result);
}

// Test HandleNextDocument with mapping
TEST_F(ParserTest_504, HandleNextDocumentWithMapping_504) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with sequence
TEST_F(ParserTest_504, HandleNextDocumentWithSequence_504) {
    std::stringstream ss("- item1\n- item2");
    Parser parser(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test multiple documents in a single stream
TEST_F(ParserTest_504, HandleMultipleDocuments_504) {
    std::stringstream ss("---\nhello\n---\nworld");
    Parser parser(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test that after consuming all documents, HandleNextDocument returns false
TEST_F(ParserTest_504, HandleNextDocumentExhaustsDocuments_504) {
    std::stringstream ss("hello");
    Parser parser(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test boolean operator after consuming all documents
TEST_F(ParserTest_504, BoolOperatorFalseAfterAllDocumentsConsumed_504) {
    std::stringstream ss("hello");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    parser.HandleNextDocument(handler);
    // After consuming the only document, parser should be falsy
    EXPECT_FALSE(static_cast<bool>(parser));
}

// Test PrintTokens with valid content
TEST_F(ParserTest_504, PrintTokensProducesOutput_504) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    
    std::ostringstream out;
    parser.PrintTokens(out);
    
    std::string output = out.str();
    EXPECT_FALSE(output.empty());
}

// Test PrintTokens with empty parser
TEST_F(ParserTest_504, PrintTokensWithDefaultParser_504) {
    Parser parser;
    std::ostringstream out;
    // Should not crash
    parser.PrintTokens(out);
}

// Test with whitespace-only content
TEST_F(ParserTest_504, WhitespaceOnlyContent_504) {
    std::stringstream ss("   \n\n   ");
    Parser parser(ss);
    // Whitespace-only content may or may not produce tokens depending on impl
    // Just ensure it doesn't crash
    MockEventHandler handler;
    parser.HandleNextDocument(handler);
}

// Test with YAML directive
TEST_F(ParserTest_504, YAMLWithDirective_504) {
    std::stringstream ss("%YAML 1.2\n---\nhello");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with tag directive
TEST_F(ParserTest_504, YAMLWithTagDirective_504) {
    std::stringstream ss("%TAG !yaml! tag:yaml.org,2002:\n---\nhello");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with flow sequence
TEST_F(ParserTest_504, FlowSequence_504) {
    std::stringstream ss("[1, 2, 3]");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(3);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with flow mapping
TEST_F(ParserTest_504, FlowMapping_504) {
    std::stringstream ss("{a: 1, b: 2}");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(4);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with anchor and alias
TEST_F(ParserTest_504, AnchorAndAlias_504) {
    std::stringstream ss("- &anchor value\n- *anchor");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(::testing::AtLeast(0));
    EXPECT_CALL(handler, OnAnchor(::testing::_, ::testing::_)).Times(::testing::AtLeast(0));
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with null value
TEST_F(ParserTest_504, NullValue_504) {
    std::stringstream ss("~");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    // Null represented as ~ may be parsed as scalar or null
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtMost(1));
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with quoted scalar
TEST_F(ParserTest_504, QuotedScalar_504) {
    std::stringstream ss("\"hello world\"");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "hello world")).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with single-quoted scalar
TEST_F(ParserTest_504, SingleQuotedScalar_504) {
    std::stringstream ss("'hello world'");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "hello world")).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with explicit document end
TEST_F(ParserTest_504, ExplicitDocumentEnd_504) {
    std::stringstream ss("---\nhello\n...");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test Load after consuming documents resets parser
TEST_F(ParserTest_504, LoadAfterConsuming_504) {
    std::stringstream ss1("first");
    Parser parser(ss1);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    
    parser.HandleNextDocument(handler);
    EXPECT_FALSE(static_cast<bool>(parser));
    
    std::stringstream ss2("second");
    parser.Load(ss2);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    parser.HandleNextDocument(handler);
}

// Test with nested structure
TEST_F(ParserTest_504, NestedStructure_504) {
    std::stringstream ss("outer:\n  inner: value");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    EXPECT_CALL(handler, OnMapEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(3);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with comment-only content
TEST_F(ParserTest_504, CommentOnlyContent_504) {
    std::stringstream ss("# just a comment\n");
    Parser parser(ss);
    // Comment-only content might not produce a valid document
    MockEventHandler handler;
    // Don't set strict expectations - just verify it doesn't crash
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    
    parser.HandleNextDocument(handler);
}

// Test block scalar (literal)
TEST_F(ParserTest_504, BlockLiteralScalar_504) {
    std::stringstream ss("|\n  hello\n  world");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test block scalar (folded)
TEST_F(ParserTest_504, BlockFoldedScalar_504) {
    std::stringstream ss(">\n  hello\n  world");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

}  // namespace YAML
