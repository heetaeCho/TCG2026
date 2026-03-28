#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "parser.h"

#include "eventhandler.h"  // Assuming EventHandler is defined in this header



using namespace YAML;

using ::testing::_;

using ::testing::NiceMock;



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD(void, OnDocumentStart, (), (override));

    MOCK_METHOD(void, OnDocumentEnd, (), (override));

    MOCK_METHOD(void, OnNull, (), (override));

    MOCK_METHOD(void, OnAlias, (const std::string&), (override));

    MOCK_METHOD(void, OnScalar, (const Mark&, const std::string&, anchor_t, const std::string&), (override));

    MOCK_METHOD(void, OnSequenceStart, (const Mark&, const std::string&, anchor_t, EmitterStyle::value), (override));

    MOCK_METHOD(void, OnSequenceEnd, (), (override));

    MOCK_METHOD(void, OnMapStart, (const Mark&, const std::string&, anchor_t, EmitterStyle::value), (override));

    MOCK_METHOD(void, OnMapEnd, (), (override));

};



class ParserTest_683 : public ::testing::Test {

protected:

    std::istringstream input;

    Parser parser;



    ParserTest_683() : input(""), parser(input) {}

};



TEST_F(ParserTest_683, ConstructorWithStream_LoadsInput_683) {

    EXPECT_TRUE(parser);

}



TEST_F(ParserTest_683, HandleNextDocument_ValidDocument_ReturnsTrue_683) {

    NiceMock<MockEventHandler> handler;

    input.str("---\nkey: value\n");

    EXPECT_CALL(handler, OnDocumentStart()).Times(1);

    EXPECT_CALL(handler, OnScalar(_, "value", _, _)).Times(1);

    EXPECT_CALL(handler, OnMapEnd()).Times(1);



    bool result = parser.HandleNextDocument(handler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_683, HandleNextDocument_EndOfStream_ReturnsFalse_683) {

    NiceMock<MockEventHandler> handler;

    input.str("");

    bool result = parser.HandleNextDocument(handler);

    EXPECT_FALSE(result);

}



TEST_F(ParserTest_683, PrintTokens_ValidInput_OutputsTokens_683) {

    std::ostringstream output;

    input.str("---\nkey: value\n");

    parser.PrintTokens(output);



    EXPECT_THAT(output.str(), ::testing::HasSubstr("KEY"));

    EXPECT_THAT(output.str(), ::testing::HasSubstr("VALUE"));

}



TEST_F(ParserTest_683, PrintTokens_EmptyInput_OutputsNothing_683) {

    std::ostringstream output;

    input.str("");

    parser.PrintTokens(output);



    EXPECT_EQ(output.str(), "");

}



TEST_F(ParserTest_683, HandleNextDocument_MultipleDocuments_HandlesAll_683) {

    NiceMock<MockEventHandler> handler;

    input.str("---\nkey1: value1\n---\nkey2: value2\n");



    EXPECT_CALL(handler, OnDocumentStart()).Times(2);

    EXPECT_CALL(handler, OnScalar(_, "value1", _, _)).Times(1);

    EXPECT_CALL(handler, OnMapEnd()).Times(2);



    bool result = parser.HandleNextDocument(handler);

    EXPECT_TRUE(result);



    result = parser.HandleNextDocument(handler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_683, HandleNextDocument_InvalidDocument_ReturnsFalse_683) {

    NiceMock<MockEventHandler> handler;

    input.str("invalid yaml");

    bool result = parser.HandleNextDocument(handler);

    EXPECT_FALSE(result);

}
