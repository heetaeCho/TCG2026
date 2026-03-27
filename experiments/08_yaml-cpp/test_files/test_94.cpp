#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "singledocparser.h"

#include "eventhandler.h"

#include "token.h"



using namespace YAML;

using ::testing::_;

using ::testing::Mock;



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD(void, OnDocumentStart, (const Mark& mark), (override));

    MOCK_METHOD(void, OnDocumentEnd, (), (override));

};



class SingleDocParserTest_94 : public ::testing::Test {

protected:

    std::istringstream input;

    Scanner scanner;

    Directives directives;

    SingleDocParser parser;



    SingleDocParserTest_94() : input(""), scanner(input), directives(), parser(scanner, directives) {}

};



TEST_F(SingleDocParserTest_94, HandleDocument_NormalOperation_NoDocStartToken_94) {

    MockEventHandler mockEventHandler;

    Token token(Token::VALUE, Mark());

    EXPECT_CALL(mockEventHandler, OnDocumentStart(_));

    EXPECT_CALL(mockEventHandler, OnDocumentEnd());



    scanner.m_tokens.push(token);

    parser.HandleDocument(mockEventHandler);

}



TEST_F(SingleDocParserTest_94, HandleDocument_NormalOperation_WithDocStartToken_94) {

    MockEventHandler mockEventHandler;

    Token docStart(Token::DOC_START, Mark());

    Token value(Token::VALUE, Mark());



    EXPECT_CALL(mockEventHandler, OnDocumentStart(_));

    EXPECT_CALL(mockEventHandler, OnDocumentEnd());



    scanner.m_tokens.push(docStart);

    scanner.m_tokens.push(value);



    parser.HandleDocument(mockEventHandler);

}



TEST_F(SingleDocParserTest_94, HandleDocument_BoundaryCondition_EmptyScanner_94) {

    MockEventHandler mockEventHandler;



    EXPECT_THROW(parser.HandleDocument(mockEventHandler), std::exception);

}



TEST_F(SingleDocParserTest_94, HandleDocument_ExceptionalCase_MultipleDocEndTokens_94) {

    MockEventHandler mockEventHandler;

    Token docStart(Token::DOC_START, Mark());

    Token value(Token::VALUE, Mark());

    Token docEnd1(Token::DOC_END, Mark());

    Token docEnd2(Token::DOC_END, Mark());



    EXPECT_CALL(mockEventHandler, OnDocumentStart(_));

    EXPECT_CALL(mockEventHandler, OnDocumentEnd()).Times(1);



    scanner.m_tokens.push(docStart);

    scanner.m_tokens.push(value);

    scanner.m_tokens.push(docEnd1);

    scanner.m_tokens.push(docEnd2);



    parser.HandleDocument(mockEventHandler);

}
