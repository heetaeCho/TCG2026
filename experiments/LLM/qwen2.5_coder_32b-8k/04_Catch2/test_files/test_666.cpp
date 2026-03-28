#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_clara.cpp"



using namespace Catch::Clara;

using namespace Catch::Detail;



class ExeNameTest : public ::testing::Test {

protected:

    ExeName exeName;

};



TEST_F(ExeNameTest_ParseNormalOperation_666, EmptyStringAndTokens_ReturnsNoMatch_666) {

    TokenStream tokens;

    auto result = exeName.parse("", tokens);

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

}



TEST_F(ExeNameTest_ParseBoundaryConditions_666, NonEmptyStringAndEmptyTokens_ReturnsNoMatch_666) {

    std::string input = "test";

    TokenStream tokens;

    auto result = exeName.parse(input, tokens);

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

}



TEST_F(ExeNameTest_ParseBoundaryConditions_666, EmptyStringAndNonEmptyTokens_ReturnsNoMatch_666) {

    std::string input = "";

    TokenStream tokens;

    tokens.push_back("token1");

    auto result = exeName.parse(input, tokens);

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

}



TEST_F(ExeNameTest_ParseNormalOperation_666, NonEmptyStringAndNonEmptyTokens_ReturnsNoMatch_666) {

    std::string input = "test";

    TokenStream tokens;

    tokens.push_back("token1");

    auto result = exeName.parse(input, tokens);

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

}



TEST_F(ExeNameTest_ParseVerificationOfExternalInteractions_666, TokensPreservedAfterParse_666) {

    std::string input = "test";

    TokenStream tokens;

    tokens.push_back("token1");

    tokens.push_back("token2");

    auto result = exeName.parse(input, tokens);

    const auto& remainingTokens = result.remainingTokens();

    EXPECT_EQ(remainingTokens.size(), 2);

    EXPECT_EQ(remainingTokens[0], "token1");

    EXPECT_EQ(remainingTokens[1], "token2");

}
