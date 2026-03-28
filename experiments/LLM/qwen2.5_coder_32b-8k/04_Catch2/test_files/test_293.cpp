#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    void SetUp() override {

        info = AssertionInfo();

        data = AssertionResultData(ResultWas::OfType::Ok, LazyExpression());

        result = AssertionResult(info, std::move(data));

    }

};



TEST_F(AssertionResultTest_293, GetResultType_ReturnsInitializedType_293) {

    EXPECT_EQ(result.getResultType(), ResultWas::OfType::Ok);

}



TEST_F(AssertionResultTest_293, IsOk_ReturnsTrueForOkType_293) {

    EXPECT_TRUE(result.isOk());

}



TEST_F(AssertionResultTest_293, Succeeded_ReturnsTrueForOkType_293) {

    EXPECT_TRUE(result.succeeded());

}



TEST_F(AssertionResultTest_293, HasExpression_ReturnsFalseWithoutExpression_293) {

    EXPECT_FALSE(result.hasExpression());

}



TEST_F(AssertionResultTest_293, HasMessage_ReturnsFalseWithoutMessage_293) {

    EXPECT_FALSE(result.hasMessage());

}



TEST_F(AssertionResultTest_293, GetExpression_ReturnsEmptyStringWithoutExpression_293) {

    EXPECT_EQ(result.getExpression(), "");

}



TEST_F(AssertionResultTest_293, GetExpressionInMacro_ReturnsEmptyStringWithoutExpression_293) {

    EXPECT_EQ(result.getExpressionInMacro(), "");

}



TEST_F(AssertionResultTest_293, HasExpandedExpression_ReturnsFalseWithoutExpression_293) {

    EXPECT_FALSE(result.hasExpandedExpression());

}



TEST_F(AssertionResultTest_293, GetExpandedExpression_ReturnsEmptyStringWithoutExpression_293) {

    EXPECT_EQ(result.getExpandedExpression(), "");

}



TEST_F(AssertionResultTest_293, GetMessage_ReturnsEmptyStringRefWithoutMessage_293) {

    EXPECT_TRUE(result.getMessage().empty());

}



TEST_F(AssertionResultTest_293, GetSourceInfo_ReturnsDefaultConstructedSourceLineInfo_293) {

    SourceLineInfo defaultInfo;

    EXPECT_EQ(result.getSourceInfo(), defaultInfo);

}



TEST_F(AssertionResultTest_293, GetTestMacroName_ReturnsEmptyStringRefWithoutMacroName_293) {

    EXPECT_TRUE(result.getTestMacroName().empty());

}
