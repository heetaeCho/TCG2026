#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/parser.h>

#include <sstream>



using namespace YAML;



class ParserTest_505 : public ::testing::Test {

protected:

    std::istringstream input;

    Parser parser;

};



TEST_F(ParserTest_505, LoadWithStream_505) {

    input.str("key: value");

    parser.Load(input);

    EXPECT_TRUE(static_cast<bool>(parser));

}



TEST_F(ParserTest_505, LoadEmptyStream_505) {

    input.str("");

    parser.Load(input);

    EXPECT_FALSE(static_cast<bool>(parser));

}



TEST_F(ParserTest_505, HandleNextDocumentValid_505) {

    class MockEventHandler : public EventHandler {

    public:

        MOCK_METHOD(void, OnDocumentStart, (const Mark&), (override));

        MOCK_METHOD(void, OnDocumentEnd, (), (override));

    };



    MockEventHandler mockHandler;

    input.str("key: value");

    parser.Load(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(::testing::_)).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(1);

    parser.HandleNextDocument(mockHandler);

}



TEST_F(ParserTest_505, HandleNextDocumentInvalid_505) {

    class MockEventHandler : public EventHandler {

    public:

        MOCK_METHOD(void, OnDocumentStart, (const Mark&), (override));

        MOCK_METHOD(void, OnDocumentEnd, (), (override));

    };



    MockEventHandler mockHandler;

    input.str("invalid yaml");

    parser.Load(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(::testing::_)).Times(0);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(0);

    EXPECT_FALSE(parser.HandleNextDocument(mockHandler));

}



TEST_F(ParserTest_505, PrintTokensToStream_505) {

    input.str("key: value");

    parser.Load(input);

    std::ostringstream output;

    parser.PrintTokens(output);

    EXPECT_FALSE(output.str().empty());

}
