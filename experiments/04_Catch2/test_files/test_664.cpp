#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace testing;



// Mock for BoundFlagRefBase and BoundValueRefBase to test external interactions

class MockBoundFlagRef : public Detail::BoundFlagRefBase {

public:

    MOCK_METHOD(Detail::ParseResult, setFlag, (bool), (override));

};



class MockBoundValueRef : public Detail::BoundValueRefBase {

public:

    MOCK_METHOD(Detail::ParseResult, setValue, (const std::string&), (override));

};



// Helper function to create a token stream

Detail::TokenStream makeTokenStream(Detail::TokenType type, const std::string& token) {

    return Detail::TokenStream(std::make_unique<Detail::Token>(type, token));

}



class OptTest_664 : public Test {

protected:

    NiceMock<MockBoundFlagRef> mockFlag;

    NiceMock<MockBoundValueRef> mockValue;



    Opt flagOpt{std::make_shared<Detail::BoundFlagRefBase>(mockFlag)};

    Opt valueOpt{std::make_shared<Detail::BoundValueRefBase>(mockValue)};



    Detail::TokenStream emptyTokens = nullptr;

};



// Normal operation tests

TEST_F(OptTest_664, FlagOptionMatched_664) {

    EXPECT_CALL(mockFlag, setFlag(true)).WillOnce(Return(Detail::ParseResult{Detail::ParseResultType::Ok}));



    auto result = flagOpt.parse("", makeTokenStream(Detail::TokenType::Option, "--flag"));

    

    ASSERT_TRUE(result);

    EXPECT_EQ(result.value().type, Detail::ParseResultType::Matched);

}



TEST_F(OptTest_664, ValueOptionMatchedWithArgument_664) {

    EXPECT_CALL(mockValue, setValue("value")).WillOnce(Return(Detail::ParseResult{Detail::ParseResultType::Ok}));



    auto tokens = makeTokenStream(Detail::TokenType::Option, "--option");

    auto result = valueOpt.parse("", std::move(tokens));

    

    ASSERT_TRUE(result);

    tokens = std::move(result.value().tokens);

    EXPECT_EQ(tokens->type, Detail::TokenType::Argument);

    EXPECT_EQ(tokens->token, "value");



    result = valueOpt.parse("", std::move(tokens));



    ASSERT_TRUE(result);

    EXPECT_EQ(result.value().type, Detail::ParseResultType::Matched);

}



// Boundary conditions

TEST_F(OptTest_664, NoTokensProvided_664) {

    auto result = flagOpt.parse("", emptyTokens);



    ASSERT_TRUE(result);

    EXPECT_EQ(result.value().type, Detail::ParseResultType::NoMatch);

}



TEST_F(OptTest_664, IncorrectTokenType_664) {

    auto tokens = makeTokenStream(Detail::TokenType::Argument, "value");

    auto result = flagOpt.parse("", std::move(tokens));



    ASSERT_TRUE(result);

    EXPECT_EQ(result.value().type, Detail::ParseResultType::NoMatch);

}



// Exceptional or error cases

TEST_F(OptTest_664, FlagSetFlagFails_664) {

    EXPECT_CALL(mockFlag, setFlag(true)).WillOnce(Return(Detail::ParseResult{Detail::ParseResultType::Error}));



    auto result = flagOpt.parse("", makeTokenStream(Detail::TokenType::Option, "--flag"));



    ASSERT_FALSE(result);

}



TEST_F(OptTest_664, ValueOptionNoArgument_664) {

    EXPECT_CALL(mockValue, setValue(_)).Times(0);



    auto tokens = makeTokenStream(Detail::TokenType::Option, "--option");

    auto result = valueOpt.parse("", std::move(tokens));



    ASSERT_TRUE(result);

    tokens = std::move(result.value().tokens);

    EXPECT_EQ(tokens->type, Detail::TokenType::Argument);

    EXPECT_EQ(tokens->token, "");



    result = valueOpt.parse("", std::move(tokens));



    ASSERT_FALSE(result);

}



TEST_F(OptTest_664, ValueOptionIncorrectArgumentType_664) {

    EXPECT_CALL(mockValue, setValue(_)).Times(0);



    auto tokens = makeTokenStream(Detail::TokenType::Option, "--option");

    auto result = valueOpt.parse("", std::move(tokens));



    ASSERT_TRUE(result);

    tokens = std::move(result.value().tokens);

    EXPECT_EQ(tokens->type, Detail::TokenType::Argument);

    EXPECT_EQ(tokens->token, "");



    tokens = makeTokenStream(Detail::TokenType::Option, "--another-option");

    result = valueOpt.parse("", std::move(tokens));



    ASSERT_FALSE(result);

}
