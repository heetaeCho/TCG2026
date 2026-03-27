#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"

#include "catch2/internal/catch_stringref.hpp"

#include "catch2/internal/catch_source_line_info.hpp"



using namespace Catch;



class AssertionResultTest_299 : public ::testing::Test {

protected:

    LazyExpression lazyExpr;

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    AssertionResultTest_299()

        : lazyExpr("some expression"),

          info("file.cpp", 10, "TEST_CASE"),

          data(ResultWas::OfType::Ok, lazyExpr),

          result(info, std::move(data)) {}

};



TEST_F(AssertionResultTest_299, GetExpression_ReturnsCorrectValue_299) {

    EXPECT_EQ(result.getExpression(), "some expression");

}



TEST_F(AssertionResultTest_299, HasExpression_ReturnsTrue_299) {

    EXPECT_TRUE(result.hasExpression());

}



TEST_F(AssertionResultTest_299, GetExpressionInMacro_ReturnsCorrectValue_299) {

    EXPECT_EQ(result.getExpressionInMacro(), "some expression");

}



TEST_F(AssertionResultTest_299, IsOk_ReturnsTrueForOkType_299) {

    EXPECT_TRUE(result.isOk());

}



TEST_F(AssertionResultTest_299, Succeeded_ReturnsTrueForOkType_299) {

    EXPECT_TRUE(result.succeeded());

}



TEST_F(AssertionResultTest_299, GetResultType_ReturnsCorrectValue_299) {

    EXPECT_EQ(result.getResultType(), ResultWas::OfType::Ok);

}



TEST_F(AssertionResultTest_299, HasMessage_ReturnsFalseWithoutMessage_299) {

    EXPECT_FALSE(result.hasMessage());

}



TEST_F(AssertionResultTest_299, GetMessage_ReturnsEmptyStringRefWithoutMessage_299) {

    EXPECT_EQ(result.getMessage(), StringRef{});

}



TEST_F(AssertionResultTest_299, GetSourceInfo_ReturnsCorrectValue_299) {

    SourceLineInfo expected("file.cpp", 10);

    EXPECT_EQ(result.getSourceInfo().line, expected.line);

    EXPECT_EQ(result.getSourceInfo().filename, expected.filename);

}



TEST_F(AssertionResultTest_299, GetTestMacroName_ReturnsCorrectValue_299) {

    EXPECT_EQ(result.getTestMacroName(), "TEST_CASE");

}



TEST_F(AssertionResultTest_299, HasExpandedExpression_ReturnsFalseWithoutReconstructedExpression_299) {

    EXPECT_FALSE(result.hasExpandedExpression());

}



TEST_F(AssertionResultTest_299, GetExpandedExpression_ReturnsOriginalExpressionIfEmpty_299) {

    EXPECT_EQ(result.getExpandedExpression(), "some expression");

}
