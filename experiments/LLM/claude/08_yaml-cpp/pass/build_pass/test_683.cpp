#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"

// Mock EventHandler for testing HandleNextDocument
class MockEventHandler : public YAML::EventHandler {
public:
    MOCK_METHOD(void, OnDocumentStart, (const YAML::Mark& mark), (override));
    MOCK_METHOD(void, OnDocumentEnd, (), (override));
    MOCK_METHOD(void, OnNull, (const YAML::Mark& mark, YAML::anchor_t anchor), (override));
    MOCK_METHOD(void, OnAlias, (const YAML::Mark& mark, YAML::anchor_t anchor), (override));
    MOCK_METHOD(void, OnScalar, (const YAML::Mark& mark, const std::string& tag, YAML::anchor_t anchor, const std::string& value), (override));
    MOCK_METHOD(void, OnSequenceStart, (const YAML::Mark& mark, const std::string& tag, YAML::anchor_t anchor, YAML::EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnSequenceEnd, (), (override));
    MOCK_METHOD(void, OnMapStart, (const YAML::Mark& mark, const std::string& tag, YAML::anchor_t anchor, YAML::EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnMapEnd, (), (override));
    MOCK_METHOD(void, OnAnchor, (const YAML::Mark& mark, const std::string& anchor_name), (override));
};

class ParserTest_683 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(ParserTest_683, DefaultConstructor_683) {
    YAML::Parser parser;
    // Default-constructed parser should evaluate to false (no input loaded)
    EXPECT_FALSE(parser);
}

// Test constructor with input stream
TEST_F(ParserTest_683, ConstructorWithInputStream_683) {
    std::stringstream ss("key: value");
    YAML::Parser parser(ss);
    EXPECT_TRUE(parser);
}

// Test operator bool after loading valid YAML
TEST_F(ParserTest_683, OperatorBoolAfterLoad_683) {
    YAML::Parser parser;
    std::stringstream ss("hello: world");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test operator bool with empty stream
TEST_F(ParserTest_683, OperatorBoolWithEmptyStream_683) {
    std::stringstream ss("");
    YAML::Parser parser(ss);
    // An empty stream may still be valid but have no documents
    // The parser should still be in a valid state
}

// Test Load with valid YAML
TEST_F(ParserTest_683, LoadValidYAML_683) {
    YAML::Parser parser;
    std::stringstream ss("foo: bar");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test Load replaces previous content
TEST_F(ParserTest_683, LoadReplacesContent_683) {
    std::stringstream ss1("first: doc");
    YAML::Parser parser(ss1);
    EXPECT_TRUE(parser);

    std::stringstream ss2("second: doc");
    parser.Load(ss2);
    EXPECT_TRUE(parser);
}

// Test HandleNextDocument with simple scalar
TEST_F(ParserTest_683, HandleNextDocumentSimpleScalar_683) {
    std::stringstream ss("hello");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with no more documents returns false
TEST_F(ParserTest_683, HandleNextDocumentNoMoreDocuments_683) {
    std::stringstream ss("hello");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(testing::_, testing::_)).Times(testing::AnyNumber());

    // First call should succeed
    parser.HandleNextDocument(handler);
    // Second call should return false (no more documents)
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with default-constructed parser
TEST_F(ParserTest_683, HandleNextDocumentDefaultConstructed_683) {
    YAML::Parser parser;
    MockEventHandler handler;
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with mapping
TEST_F(ParserTest_683, HandleNextDocumentMapping_683) {
    std::stringstream ss("key: value\nfoo: bar");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with sequence
TEST_F(ParserTest_683, HandleNextDocumentSequence_683) {
    std::stringstream ss("- item1\n- item2\n- item3");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(3));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with multiple documents
TEST_F(ParserTest_683, HandleNextDocumentMultipleDocuments_683) {
    std::stringstream ss("---\nhello\n---\nworld");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AnyNumber());

    // First document
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    // Second document
    EXPECT_TRUE(parser.HandleNextDocument(handler));
    // No more documents
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with null value
TEST_F(ParserTest_683, HandleNextDocumentNullValue_683) {
    std::stringstream ss("~");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnNull(testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AnyNumber());

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test PrintTokens
TEST_F(ParserTest_683, PrintTokensValidYAML_683) {
    std::stringstream ss("key: value");
    YAML::Parser parser(ss);

    std::stringstream out;
    parser.PrintTokens(out);
    // PrintTokens should output something for valid YAML
    EXPECT_FALSE(out.str().empty());
}

// Test PrintTokens with empty input
TEST_F(ParserTest_683, PrintTokensEmptyInput_683) {
    std::stringstream ss("");
    YAML::Parser parser(ss);

    std::stringstream out;
    parser.PrintTokens(out);
    // Even empty input may produce some tokens or no output
}

// Test PrintTokens with default constructed parser
TEST_F(ParserTest_683, PrintTokensDefaultConstructed_683) {
    YAML::Parser parser;
    std::stringstream out;
    // Should not crash
    parser.PrintTokens(out);
}

// Test Load with stream containing only whitespace
TEST_F(ParserTest_683, LoadWhitespaceOnly_683) {
    std::stringstream ss("   \n\n   \t  ");
    YAML::Parser parser(ss);
    // Parser may be valid even with whitespace-only input
    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnNull(testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AnyNumber());

    // May or may not have a document
    parser.HandleNextDocument(handler);
}

// Test YAML directive handling
TEST_F(ParserTest_683, HandleYAMLDirective_683) {
    std::stringstream ss("%YAML 1.2\n---\nhello");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test TAG directive handling
TEST_F(ParserTest_683, HandleTagDirective_683) {
    std::stringstream ss("%TAG ! tag:example.com,2000:\n---\nhello");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with complex nested structure
TEST_F(ParserTest_683, HandleNextDocumentNestedStructure_683) {
    std::stringstream ss(
        "root:\n"
        "  child1:\n"
        "    - item1\n"
        "    - item2\n"
        "  child2: value\n"
    );
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with document end marker
TEST_F(ParserTest_683, HandleNextDocumentWithEndMarker_683) {
    std::stringstream ss("---\nhello\n...");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test with anchors and aliases
TEST_F(ParserTest_683, HandleNextDocumentAnchorsAndAliases_683) {
    std::stringstream ss("- &anchor value\n- *anchor");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnAlias(testing::_, testing::_)).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test that copy constructor is deleted (compile-time check would be needed,
// but we verify parser works normally after construction)
TEST_F(ParserTest_683, ParserIsNotCopyable_683) {
    // This is a compile-time property; we just verify the parser works
    EXPECT_TRUE(std::is_copy_constructible<YAML::Parser>::value == false);
    EXPECT_TRUE(std::is_copy_assignable<YAML::Parser>::value == false);
}

// Test that move constructor is deleted
TEST_F(ParserTest_683, ParserIsNotMovable_683) {
    EXPECT_TRUE(std::is_move_constructible<YAML::Parser>::value == false);
    EXPECT_TRUE(std::is_move_assignable<YAML::Parser>::value == false);
}

// Test loading multiple times resets state
TEST_F(ParserTest_683, LoadMultipleTimesResetsState_683) {
    YAML::Parser parser;

    std::stringstream ss1("first");
    parser.Load(ss1);
    EXPECT_TRUE(parser);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AnyNumber());
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, "first")).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));

    // Load new content
    std::stringstream ss2("second");
    parser.Load(ss2);
    EXPECT_TRUE(parser);

    MockEventHandler handler2;
    EXPECT_CALL(handler2, OnDocumentStart(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(handler2, OnDocumentEnd()).Times(testing::AnyNumber());
    EXPECT_CALL(handler2, OnScalar(testing::_, testing::_, testing::_, "second")).Times(testing::AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler2));
}

// Test with flow-style mapping
TEST_F(ParserTest_683, HandleNextDocumentFlowMapping_683) {
    std::stringstream ss("{key1: val1, key2: val2}");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnMapEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(4));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with flow-style sequence
TEST_F(ParserTest_683, HandleNextDocumentFlowSequence_683) {
    std::stringstream ss("[a, b, c]");
    YAML::Parser parser(ss);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceStart(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(testing::AtLeast(1));
    EXPECT_CALL(handler, OnScalar(testing::_, testing::_, testing::_, testing::_)).Times(testing::AtLeast(3));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}
