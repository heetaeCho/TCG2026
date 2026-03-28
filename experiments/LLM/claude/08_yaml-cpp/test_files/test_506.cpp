#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"

using namespace YAML;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::InSequence;

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

class ParserTest_506 : public ::testing::Test {
protected:
    MockEventHandler handler;
};

// Test default constructor - no scanner, HandleNextDocument should return false
TEST_F(ParserTest_506, DefaultConstructorReturnsFalse_506) {
    Parser parser;
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test default constructor - operator bool should be false
TEST_F(ParserTest_506, DefaultConstructorOperatorBoolFalse_506) {
    Parser parser;
    EXPECT_FALSE(static_cast<bool>(parser));
}

// Test constructor with empty stream - operator bool
TEST_F(ParserTest_506, EmptyStreamOperatorBool_506) {
    std::stringstream ss("");
    Parser parser(ss);
    // An empty stream should have no documents
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with a simple scalar document
TEST_F(ParserTest_506, SimpleScalarDocument_506) {
    std::stringstream ss("hello");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument returns false when no more documents
TEST_F(ParserTest_506, NoMoreDocumentsReturnsFalse_506) {
    std::stringstream ss("hello");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test multiple documents separated by ---
TEST_F(ParserTest_506, MultipleDocuments_506) {
    std::stringstream ss("---\nhello\n---\nworld");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "world")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test with explicit document end marker
TEST_F(ParserTest_506, ExplicitDocumentEnd_506) {
    std::stringstream ss("---\nhello\n...\n---\nworld\n...");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test with a sequence
TEST_F(ParserTest_506, SequenceDocument_506) {
    std::stringstream ss("- item1\n- item2\n- item3");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with a map
TEST_F(ParserTest_506, MapDocument_506) {
    std::stringstream ss("key1: value1\nkey2: value2");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test Load method with new stream
TEST_F(ParserTest_506, LoadNewStream_506) {
    Parser parser;
    EXPECT_FALSE(parser.HandleNextDocument(handler));

    std::stringstream ss("hello");
    parser.Load(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test Load replaces previous stream
TEST_F(ParserTest_506, LoadReplacesStream_506) {
    std::stringstream ss1("first");
    Parser parser(ss1);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, "first")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "second")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));

    std::stringstream ss2("second");
    parser.Load(ss2);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test operator bool with valid stream
TEST_F(ParserTest_506, OperatorBoolWithValidStream_506) {
    std::stringstream ss("hello");
    Parser parser(ss);
    EXPECT_TRUE(static_cast<bool>(parser));
}

// Test null value document
TEST_F(ParserTest_506, NullDocument_506) {
    std::stringstream ss("~");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnNull(_, _)).Times(AtLeast(0));
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(AtLeast(0));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test flow sequence
TEST_F(ParserTest_506, FlowSequenceDocument_506) {
    std::stringstream ss("[a, b, c]");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test flow map
TEST_F(ParserTest_506, FlowMapDocument_506) {
    std::stringstream ss("{a: 1, b: 2}");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test anchor and alias
TEST_F(ParserTest_506, AnchorAndAlias_506) {
    std::stringstream ss("- &anchor value\n- *anchor");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "value")).Times(1);
    EXPECT_CALL(handler, OnAlias(_, _)).Times(1);
    EXPECT_CALL(handler, OnAnchor(_, _)).Times(AtLeast(0));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test YAML directive
TEST_F(ParserTest_506, YAMLDirective_506) {
    std::stringstream ss("%YAML 1.2\n---\nhello");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test TAG directive
TEST_F(ParserTest_506, TAGDirective_506) {
    std::stringstream ss("%TAG ! tag:example.com,2000:\n---\nhello");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test empty document with just document markers
TEST_F(ParserTest_506, EmptyDocumentWithMarkers_506) {
    std::stringstream ss("---\n...");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnNull(_, _)).Times(AtLeast(0));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test quoted scalar
TEST_F(ParserTest_506, QuotedScalar_506) {
    std::stringstream ss("\"hello world\"");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello world")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test single quoted scalar
TEST_F(ParserTest_506, SingleQuotedScalar_506) {
    std::stringstream ss("'hello world'");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello world")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test nested structure
TEST_F(ParserTest_506, NestedMapInSequence_506) {
    std::stringstream ss("- key: value");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test calling HandleNextDocument multiple times after exhaustion
TEST_F(ParserTest_506, MultipleCallsAfterExhaustion_506) {
    std::stringstream ss("hello");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test whitespace-only stream
TEST_F(ParserTest_506, WhitespaceOnlyStream_506) {
    std::stringstream ss("   \n\n  \n");
    Parser parser(ss);
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test comment-only stream
TEST_F(ParserTest_506, CommentOnlyStream_506) {
    std::stringstream ss("# this is a comment\n# another comment");
    Parser parser(ss);
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test block scalar (literal)
TEST_F(ParserTest_506, BlockLiteralScalar_506) {
    std::stringstream ss("|\n  hello\n  world");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test block scalar (folded)
TEST_F(ParserTest_506, BlockFoldedScalar_506) {
    std::stringstream ss(">\n  hello\n  world");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test tagged value
TEST_F(ParserTest_506, TaggedValue_506) {
    std::stringstream ss("!!str 42");
    Parser parser(ss);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "42")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test PrintTokens doesn't crash
TEST_F(ParserTest_506, PrintTokensDoesNotCrash_506) {
    std::stringstream ss("hello: world");
    Parser parser(ss);
    std::ostringstream out;
    EXPECT_NO_THROW(parser.PrintTokens(out));
}

// Test PrintTokens on default parser
TEST_F(ParserTest_506, PrintTokensDefaultParser_506) {
    Parser parser;
    std::ostringstream out;
    EXPECT_NO_THROW(parser.PrintTokens(out));
}
