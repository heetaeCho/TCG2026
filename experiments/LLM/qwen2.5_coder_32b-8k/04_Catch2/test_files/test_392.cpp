#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace Clara;



class OptTest_392 : public ::testing::Test {

protected:

    bool flag = false;

    Opt opt;



    OptTest_392() : opt(flag) {}

};



TEST_F(OptTest_392, ConstructorWithBoolReference_392) {

    EXPECT_FALSE(flag);

}



TEST_F(OptTest_392, OperatorArray_AddsOptName_392) {

    StringRef optName("test");

    opt[optName];

    EXPECT_EQ(opt.getHelpColumns().size(), 1u);

}



TEST_F(OptTest_392, IsMatch_ReturnsFalseForEmptyToken_392) {

    StringRef emptyToken("");

    EXPECT_FALSE(opt.isMatch(emptyToken));

}



TEST_F(OptTest_392, IsMatch_ReturnsTrueForMatchingOptName_392) {

    StringRef optName("test");

    opt[optName];

    EXPECT_TRUE(opt.isMatch(optName));

}



TEST_F(OptTest_392, Parse_ReturnsSuccessForEmptyUnnamedAndTokens_392) {

    std::string unnamed;

    Detail::TokenStream tokens;

    auto result = opt.parse(unnamed, tokens);

    EXPECT_EQ(result.m_type, Detail::InternalParseResultType::NoMatch);

}



TEST_F(OptTest_392, Validate_ReturnsSuccessForDefaultState_392) {

    auto result = opt.validate();

    EXPECT_TRUE(result);

}
