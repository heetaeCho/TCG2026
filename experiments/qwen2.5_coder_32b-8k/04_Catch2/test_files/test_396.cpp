#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class ParserTest_396 : public ::testing::Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_396, AddOptionIncreasesCount_396) {

    bool flag = false;

    Opt opt(flag);

    size_t initialCount = parser.getHelpColumns().size();

    parser | opt;

    EXPECT_EQ(parser.getHelpColumns().size(), initialCount + 1);

}



TEST_F(ParserTest_396, ValidateInitiallySuccessful_396) {

    EXPECT_TRUE(parser.validate().isOk());

}



TEST_F(ParserTest_396, ParseEmptyTokensNoError_396) {

    Detail::TokenStream tokens;

    auto result = parser.parse("test.exe", tokens);

    EXPECT_TRUE(result.m_parseResult.isOk());

}



TEST_F(ParserTest_396, AddExeNameDoesNotIncreaseOptionCount_396) {

    size_t initialCount = parser.getHelpColumns().size();

    parser |= ExeName("test.exe");

    EXPECT_EQ(parser.getHelpColumns().size(), initialCount);

}



TEST_F(ParserTest_396, AddMultipleOptionsIncreasesCountProportionally_396) {

    bool flag1 = false;

    bool flag2 = false;

    Opt opt1(flag1);

    Opt opt2(flag2);

    size_t initialCount = parser.getHelpColumns().size();

    parser | opt1 | opt2;

    EXPECT_EQ(parser.getHelpColumns().size(), initialCount + 2);

}



TEST_F(ParserTest_396, ParseWithUnknownOptionFails_396) {

    Detail::TokenStream tokens({"--unknown"});

    auto result = parser.parse("test.exe", tokens);

    EXPECT_FALSE(result.m_parseResult.isOk());

}
