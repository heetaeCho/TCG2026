#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace ::testing;



class ParserTest_397 : public Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_397, AddOptUsingOperator_ShouldIncreaseOptionsCount_397) {

    bool flag = false;

    Opt opt(flag);

    parser |= std::move(opt);



    EXPECT_EQ(parser.getHelpColumns().size(), 1);

}



TEST_F(ParserTest_397, ParseWithValidOption_ShouldReturnSuccess_397) {

    bool flag = false;

    Opt opt(flag);

    parser |= opt["-f"];



    Detail::TokenStream tokens = {"-f"};

    auto result = parser.parse("test", tokens);



    EXPECT_TRUE(result.ok());

}



TEST_F(ParserTest_397, ParseWithInvalidOption_ShouldReturnFailure_397) {

    bool flag = false;

    Opt opt(flag);

    parser |= opt["-f"];



    Detail::TokenStream tokens = {"-g"};

    auto result = parser.parse("test", tokens);



    EXPECT_FALSE(result.ok());

}



TEST_F(ParserTest_397, ValidateWithNoOptions_ShouldReturnSuccess_397) {

    auto result = parser.validate();



    EXPECT_TRUE(result.ok());

}



TEST_F(ParserTest_397, WriteToStream_ShouldProduceOutput_397) {

    bool flag = false;

    Opt opt(flag);

    parser |= opt["-f"];



    std::ostringstream oss;

    parser.writeToStream(oss);



    EXPECT_FALSE(oss.str().empty());

}



TEST_F(ParserTest_397, AddMultipleOpts_ShouldIncreaseOptionsCount_397) {

    bool flag1 = false, flag2 = false;

    Opt opt1(flag1), opt2(flag2);

    parser |= opt1["-f"];

    parser |= opt2["-g"];



    EXPECT_EQ(parser.getHelpColumns().size(), 2);

}



TEST_F(ParserTest_397, ParseWithMultipleValidOptions_ShouldReturnSuccess_397) {

    bool flag1 = false, flag2 = false;

    Opt opt1(flag1), opt2(flag2);

    parser |= opt1["-f"];

    parser |= opt2["-g"];



    Detail::TokenStream tokens = {"-f", "-g"};

    auto result = parser.parse("test", tokens);



    EXPECT_TRUE(result.ok());

}



TEST_F(ParserTest_397, ParseWithMixedValidAndInvalidOptions_ShouldReturnFailure_397) {

    bool flag1 = false;

    Opt opt1(flag1);

    parser |= opt1["-f"];



    Detail::TokenStream tokens = {"-f", "-g"};

    auto result = parser.parse("test", tokens);



    EXPECT_FALSE(result.ok());

}



TEST_F(ParserTest_397, ParseWithNoTokens_ShouldReturnSuccess_397) {

    bool flag = false;

    Opt opt(flag);

    parser |= opt["-f"];



    Detail::TokenStream tokens = {};

    auto result = parser.parse("test", tokens);



    EXPECT_TRUE(result.ok());

}
