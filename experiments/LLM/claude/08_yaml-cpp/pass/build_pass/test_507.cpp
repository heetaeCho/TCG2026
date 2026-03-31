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

class ParserTest_507 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates a parser that evaluates to false
TEST_F(ParserTest_507, DefaultConstructorEvaluatesToFalse_507) {
    Parser parser;
    EXPECT_FALSE(parser);
}

// Test constructor with input stream evaluates to true
TEST_F(ParserTest_507, StreamConstructorEvaluatesToTrue_507) {
    std::stringstream ss("hello: world");
    Parser parser(ss);
    EXPECT_TRUE(parser);
}

// Test constructor with empty input stream
TEST_F(ParserTest_507, StreamConstructorWithEmptyStream_507) {
    std::stringstream ss("");
    Parser parser(ss);
    // Even an empty stream should initialize the scanner
    EXPECT_TRUE(parser);
}

// Test Load with a valid stream
TEST_F(ParserTest_507, LoadWithValidStream_507) {
    Parser parser;
    EXPECT_FALSE(parser);
    std::stringstream ss("key: value");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test Load replaces previous state
TEST_F(ParserTest_507, LoadReplacesState_507) {
    std::stringstream ss1("first: doc");
    Parser parser(ss1);
    EXPECT_TRUE(parser);
    
    std::stringstream ss2("second: doc");
    parser.Load(ss2);
    EXPECT_TRUE(parser);
}

// Test PrintTokens on default-constructed parser (no scanner)
TEST_F(ParserTest_507, PrintTokensWithNoScanner_507) {
    Parser parser;
    std::ostringstream out;
    parser.PrintTokens(out);
    // Should not crash and output should be empty since m_pScanner is null
    EXPECT_EQ(out.str(), "");
}

// Test PrintTokens with a valid stream produces some output
TEST_F(ParserTest_507, PrintTokensWithValidStream_507) {
    std::stringstream ss("hello: world");
    Parser parser(ss);
    std::ostringstream out;
    parser.PrintTokens(out);
    // Should have produced some token output
    EXPECT_FALSE(out.str().empty());
}

// Test PrintTokens with empty stream
TEST_F(ParserTest_507, PrintTokensWithEmptyStream_507) {
    std::stringstream ss("");
    Parser parser(ss);
    std::ostringstream out;
    parser.PrintTokens(out);
    // Even empty stream may produce stream start/end tokens
    // Just verify no crash
}

// Test HandleNextDocument with a simple scalar document
TEST_F(ParserTest_507, HandleNextDocumentSimpleScalar_507) {
    std::stringstream ss("hello");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument returns false when no more documents
TEST_F(ParserTest_507, HandleNextDocumentNoMoreDocuments_507) {
    std::stringstream ss("hello");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAnchor(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    
    // First document should succeed
    parser.HandleNextDocument(handler);
    // Second call should return false (no more documents)
    bool result = parser.HandleNextDocument(handler);
    EXPECT_FALSE(result);
}

// Test HandleNextDocument with a mapping
TEST_F(ParserTest_507, HandleNextDocumentMapping_507) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "key")).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "value")).Times(1);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with a sequence
TEST_F(ParserTest_507, HandleNextDocumentSequence_507) {
    std::stringstream ss("- item1\n- item2");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "item1")).Times(1);
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "item2")).Times(1);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with multiple documents
TEST_F(ParserTest_507, HandleNextDocumentMultipleDocuments_507) {
    std::stringstream ss("---\nhello\n---\nworld");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAnchor(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    
    bool result1 = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result1);
    
    bool result2 = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result2);
}

// Test that Parser is not copyable (compile-time check would fail if uncommented)
// This is a design constraint test - we verify it compiles with non-copyable semantics
TEST_F(ParserTest_507, ParserIsNotCopyable_507) {
    EXPECT_FALSE(std::is_copy_constructible<Parser>::value);
    EXPECT_FALSE(std::is_copy_assignable<Parser>::value);
}

// Test that Parser is not movable
TEST_F(ParserTest_507, ParserIsNotMovable_507) {
    EXPECT_FALSE(std::is_move_constructible<Parser>::value);
    EXPECT_FALSE(std::is_move_assignable<Parser>::value);
}

// Test operator bool after Load with empty stream
TEST_F(ParserTest_507, OperatorBoolAfterLoadEmptyStream_507) {
    Parser parser;
    std::stringstream ss("");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test PrintTokens with complex YAML
TEST_F(ParserTest_507, PrintTokensComplexYaml_507) {
    std::stringstream ss("---\nkey1: value1\nkey2:\n  - item1\n  - item2\n...");
    Parser parser(ss);
    std::ostringstream out;
    parser.PrintTokens(out);
    EXPECT_FALSE(out.str().empty());
}

// Test HandleNextDocument with null value
TEST_F(ParserTest_507, HandleNextDocumentNullValue_507) {
    std::stringstream ss("key: ~");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with flow sequence
TEST_F(ParserTest_507, HandleNextDocumentFlowSequence_507) {
    std::stringstream ss("[1, 2, 3]");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(3);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with flow mapping
TEST_F(ParserTest_507, HandleNextDocumentFlowMapping_507) {
    std::stringstream ss("{a: 1, b: 2}");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(4);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test HandleNextDocument with anchor and alias
TEST_F(ParserTest_507, HandleNextDocumentAnchorAlias_507) {
    std::stringstream ss("- &anchor value\n- *anchor");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnAnchor(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AnyNumber());
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test Load followed by HandleNextDocument
TEST_F(ParserTest_507, LoadThenHandleDocument_507) {
    Parser parser;
    std::stringstream ss("test: value");
    parser.Load(ss);
    
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(2);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

// Test PrintTokens with quoted scalar
TEST_F(ParserTest_507, PrintTokensQuotedScalar_507) {
    std::stringstream ss("\"hello world\"");
    Parser parser(ss);
    std::ostringstream out;
    parser.PrintTokens(out);
    EXPECT_FALSE(out.str().empty());
}

// Test HandleNextDocument with document end marker
TEST_F(ParserTest_507, HandleNextDocumentWithDocEndMarker_507) {
    std::stringstream ss("---\nhello\n...");
    Parser parser(ss);
    MockEventHandler handler;
    
    EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(::testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "hello")).Times(1);
    
    bool result = parser.HandleNextDocument(handler);
    EXPECT_TRUE(result);
}

}  // namespace YAML
