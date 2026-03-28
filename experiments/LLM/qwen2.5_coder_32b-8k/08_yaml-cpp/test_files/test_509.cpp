#include <gtest/gtest.h>

#include "scanner.h"

#include "token.h"



using namespace YAML;



class SimpleKeyTest_509 : public ::testing::Test {

protected:

    Token token1;

    Token token2;

    Token token3;

    IndentMarker indentMarker;

    SimpleKey simpleKey;



    SimpleKeyTest_509() 

        : token1(Token::Type::STREAM_START, Mark()),

          token2(Token::Type::BLOCK_SEQUENCE_START, Mark()),

          token3(Token::Type::KEY, Mark()),

          indentMarker(0, IndentMarker::IndentType::NONE),

          simpleKey(Mark(), 0) {

        

        simpleKey.pIndent = &indentMarker;

        simpleKey.pMapStart = &token2;

        simpleKey.pKey = &token3;

    }

};



TEST_F(SimpleKeyTest_509, ValidateSetsIndentStatusToValid_509) {

    indentMarker.status = Token::STATUS::INVALID;

    simpleKey.Validate();

    EXPECT_EQ(indentMarker.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateSetsMapStartStatusToValid_509) {

    token2.status = Token::STATUS::INVALID;

    simpleKey.Validate();

    EXPECT_EQ(token2.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateSetsKeyStatusToValid_509) {

    token3.status = Token::STATUS::INVALID;

    simpleKey.Validate();

    EXPECT_EQ(token3.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateDoesNotChangeAlreadyValidIndentStatus_509) {

    indentMarker.status = Token::STATUS::VALID;

    simpleKey.Validate();

    EXPECT_EQ(indentMarker.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateDoesNotChangeAlreadyValidMapStartStatus_509) {

    token2.status = Token::STATUS::VALID;

    simpleKey.Validate();

    EXPECT_EQ(token2.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateDoesNotChangeAlreadyValidKeyStatus_509) {

    token3.status = Token::STATUS::VALID;

    simpleKey.Validate();

    EXPECT_EQ(token3.status, Token::STATUS::VALID);

}



TEST_F(SimpleKeyTest_509, ValidateHandlesNullIndentPointerGracefully_509) {

    simpleKey.pIndent = nullptr;

    EXPECT_NO_THROW(simpleKey.Validate());

}



TEST_F(SimpleKeyTest_509, ValidateHandlesNullMapStartPointerGracefully_509) {

    simpleKey.pMapStart = nullptr;

    EXPECT_NO_THROW(simpleKey.Validate());

}



TEST_F(SimpleKeyTest_509, ValidateHandlesNullKeyPointerGracefully_509) {

    simpleKey.pKey = nullptr;

    EXPECT_NO_THROW(simpleKey.Validate());

}
