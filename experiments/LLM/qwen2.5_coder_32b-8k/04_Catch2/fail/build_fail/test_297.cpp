#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_assertion_result.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::Return;



class AssertionResultTest_297 : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    AssertionResultTest_297()

        : info({StringRef("REQUIRE"), StringRef("1 == 1"), ResultDisposition::Normal}),

          result(info, std::move(data)) {}

};



TEST_F(AssertionResultTest_297, GetExpressionInMacro_ReturnsExpectedStringWithMacroName_297) {

    info.macroName = StringRef("REQUIRE");

    info.capturedExpression = StringRef("1 == 1");



    std::string expected = "REQUIRE( 1 == 1 )";

    EXPECT_EQ(expected, result.getExpressionInMacro());

}



TEST_F(AssertionResultTest_297, GetExpressionInMacro_ReturnsExpectedStringWithoutMacroName_297) {

    info.macroName = StringRef("");

    info.capturedExpression = StringRef("1 == 1");



    std::string expected = "1 == 1";

    EXPECT_EQ(expected, result.getExpressionInMacro());

}



TEST_F(AssertionResultTest_297, GetExpression_ReturnsCapturedExpression_297) {

    info.capturedExpression = StringRef("1 == 1");

    EXPECT_EQ("1 == 1", result.getExpression());

}



TEST_F(AssertionResultTest_297, HasExpression_ReturnsTrueWhenExpressionIsSet_297) {

    info.capturedExpression = StringRef("1 == 1");

    EXPECT_TRUE(result.hasExpression());

}



TEST_F(AssertionResultTest_297, HasExpression_ReturnsFalseWhenNoExpressionIsSet_297) {

    info.capturedExpression = StringRef("");

    EXPECT_FALSE(result.hasExpression());

}
