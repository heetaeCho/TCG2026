#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"

using namespace YAML;
using ::testing::_;
using ::testing::AtLeast;

// Mock EventHandler for testing HandleNextDocument
class MockEventHandler : public YAML::EventHandler {
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

// Test fixture
class ParserTest_505 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor - parser should be invalid (operator bool returns false)
TEST_F(ParserTest_505, DefaultConstructorIsInvalid_505) {
    Parser parser;
    EXPECT_FALSE(parser);
}

// Test constructor with input stream - parser should be valid
TEST_F(ParserTest_505, ConstructorWithStreamIsValid_505) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    EXPECT_TRUE(parser);
}

// Test Load method makes parser valid
TEST_F(ParserTest_505, LoadMakesParserValid_505) {
    Parser parser;
    EXPECT_FALSE(parser);
    std::stringstream ss("key: value");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test Load with empty stream
TEST_F(ParserTest_505, LoadWithEmptyStream_505) {
    Parser parser;
    std::stringstream ss("");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test HandleNextDocument with simple scalar
TEST_F(ParserTest_505, HandleNextDocumentSimpleScalar_505) {
    std::stringstream ss("hello");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument returns false when no more documents
TEST_F(ParserTest_505, HandleNextDocumentReturnsFalseWhenEmpty_505) {
    std::stringstream ss("");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with key-value pair
TEST_F(ParserTest_505, HandleNextDocumentWithMapping_505) {
    std::stringstream ss("key: value");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument with sequence
TEST_F(ParserTest_505, HandleNextDocumentWithSequence_505) {
    std::stringstream ss("- item1\n- item2\n- item3");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test multiple documents
TEST_F(ParserTest_505, HandleMultipleDocuments_505) {
    std::stringstream ss("---\nhello\n---\nworld");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test multiple documents - third call returns false
TEST_F(ParserTest_505, HandleNextDocumentReturnsFalseAfterAllDocuments_505) {
    std::stringstream ss("---\nhello\n...");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(AtLeast(1));
    EXPECT_CALL(handler, OnDocumentEnd()).Times(AtLeast(1));
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(AtLeast(1));

    parser.HandleNextDocument(handler);
    // After processing all documents, should return false
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test Load can be called multiple times (resets the parser)
TEST_F(ParserTest_505, LoadCanBeCalledMultipleTimes_505) {
    Parser parser;
    
    std::stringstream ss1("first");
    parser.Load(ss1);
    EXPECT_TRUE(parser);

    MockEventHandler handler;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, "first")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "second")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));

    std::stringstream ss2("second");
    parser.Load(ss2);
    EXPECT_TRUE(parser);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test PrintTokens with simple input
TEST_F(ParserTest_505, PrintTokensSimpleInput_505) {
    std::stringstream input("key: value");
    Parser parser(input);
    
    std::stringstream output;
    parser.PrintTokens(output);
    
    std::string result = output.str();
    // PrintTokens should produce some output for valid YAML
    EXPECT_FALSE(result.empty());
}

// Test PrintTokens with empty input
TEST_F(ParserTest_505, PrintTokensEmptyInput_505) {
    std::stringstream input("");
    Parser parser(input);
    
    std::stringstream output;
    parser.PrintTokens(output);
    // Should not crash, output may or may not be empty
}

// Test HandleNextDocument without loading (default constructed parser)
TEST_F(ParserTest_505, HandleNextDocumentWithoutLoad_505) {
    Parser parser;
    MockEventHandler handler;
    
    // Default constructed parser has no scanner, should return false
    EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test with YAML directive
TEST_F(ParserTest_505, HandleDocumentWithYAMLDirective_505) {
    std::stringstream ss("%YAML 1.2\n---\nhello");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with TAG directive
TEST_F(ParserTest_505, HandleDocumentWithTagDirective_505) {
    std::stringstream ss("%TAG !yaml! tag:yaml.org,2002:\n---\nhello");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with null value
TEST_F(ParserTest_505, HandleDocumentWithNullValue_505) {
    std::stringstream ss("~");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnNull(_, _)).Times(1);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test nested mapping
TEST_F(ParserTest_505, HandleDocumentNestedMapping_505) {
    std::stringstream ss("outer:\n  inner: value");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(2);
    EXPECT_CALL(handler, OnMapEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with anchor and alias
TEST_F(ParserTest_505, HandleDocumentWithAnchorAndAlias_505) {
    std::stringstream ss("- &anchor value\n- *anchor");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(AtLeast(1));
    EXPECT_CALL(handler, OnAlias(_, _)).Times(AtLeast(1));

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test operator bool after loading stream
TEST_F(ParserTest_505, OperatorBoolAfterLoad_505) {
    Parser parser;
    EXPECT_FALSE(parser);
    
    std::stringstream ss("test");
    parser.Load(ss);
    EXPECT_TRUE(parser);
}

// Test copy constructor is deleted (compile-time check - just ensure it compiles)
TEST_F(ParserTest_505, ParserIsNotCopyable_505) {
    EXPECT_FALSE(std::is_copy_constructible<Parser>::value);
    EXPECT_FALSE(std::is_copy_assignable<Parser>::value);
}

// Test move constructor is deleted
TEST_F(ParserTest_505, ParserIsNotMovable_505) {
    EXPECT_FALSE(std::is_move_constructible<Parser>::value);
    EXPECT_FALSE(std::is_move_assignable<Parser>::value);
}

// Test with flow-style sequence
TEST_F(ParserTest_505, HandleDocumentFlowSequence_505) {
    std::stringstream ss("[1, 2, 3]");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with flow-style mapping
TEST_F(ParserTest_505, HandleDocumentFlowMapping_505) {
    std::stringstream ss("{a: 1, b: 2}");
    Parser parser(ss);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4);

    EXPECT_TRUE(parser.HandleNextDocument(handler));
}
