#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest_291 : public ::testing::Test {

protected:

    AssertionInfo m_info;

    LazyExpression m_lazyExpression;

    AssertionResultData m_resultData;

    AssertionResult m_assertionResult;



    void SetUp() override {

        m_resultData = AssertionResultData(ResultWas::Ok, m_lazyExpression);

        m_assertionResult = AssertionResult(m_info, std::move(m_resultData));

    }

};



TEST_F(AssertionResultTest_291, Succeeded_ReturnsTrueWhenResultIsOk_291) {

    EXPECT_TRUE(m_assertionResult.succeeded());

}



TEST_F(AssertionResultTest_291, IsOk_ReturnsTrueWhenResultIsOk_291) {

    EXPECT_TRUE(m_assertionResult.isOk());

}



TEST_F(AssertionResultTest_291, GetResultType_ReturnsOkWhenInitializedWithOk_291) {

    EXPECT_EQ(ResultWas::Ok, m_assertionResult.getResultType());

}



TEST_F(AssertionResultTest_291, HasExpression_ReturnsFalseByDefault_291) {

    EXPECT_FALSE(m_assertionResult.hasExpression());

}



TEST_F(AssertionResultTest_291, HasMessage_ReturnsFalseByDefault_291) {

    EXPECT_FALSE(m_assertionResult.hasMessage());

}



TEST_F(AssertionResultTest_291, GetExpression_ReturnsEmptyStringByDefault_291) {

    EXPECT_EQ("", m_assertionResult.getExpression());

}



TEST_F(AssertionResultTest_291, GetExpressionInMacro_ReturnsEmptyStringByDefault_291) {

    EXPECT_EQ("", m_assertionResult.getExpressionInMacro());

}



TEST_F(AssertionResultTest_291, HasExpandedExpression_ReturnsFalseByDefault_291) {

    EXPECT_FALSE(m_assertionResult.hasExpandedExpression());

}



TEST_F(AssertionResultTest_291, GetExpandedExpression_ReturnsEmptyStringByDefault_291) {

    EXPECT_EQ("", m_assertionResult.getExpandedExpression());

}



TEST_F(AssertionResultTest_291, GetMessage_ReturnsEmptyStringRefByDefault_291) {

    EXPECT_TRUE(m_assertionResult.getMessage().empty());

}



TEST_F(AssertionResultTest_291, GetSourceInfo_ReturnsValidSourceLineInfo_291) {

    SourceLineInfo sourceInfo = m_assertionResult.getSourceInfo();

    EXPECT_EQ("", sourceInfo.file);

    EXPECT_EQ(0u, sourceInfo.line);

}



TEST_F(AssertionResultTest_291, GetTestMacroName_ReturnsEmptyStringRefByDefault_291) {

    EXPECT_TRUE(m_assertionResult.getTestMacroName().empty());

}



TEST_F(AssertionResultTest_291, Succeeded_ReturnsFalseWhenResultIsNotOk_291) {

    AssertionResultData data(ResultWas::ExpressionFailed, m_lazyExpression);

    AssertionResult result(m_info, std::move(data));

    EXPECT_FALSE(result.succeeded());

}



TEST_F(AssertionResultTest_291, IsOk_ReturnsFalseWhenResultIsNotOk_291) {

    AssertionResultData data(ResultWas::ExpressionFailed, m_lazyExpression);

    AssertionResult result(m_info, std::move(data));

    EXPECT_FALSE(result.isOk());

}



TEST_F(AssertionResultTest_291, GetResultType_ReturnsExpressionFailedWhenInitializedWithExpressionFailed_291) {

    AssertionResultData data(ResultWas::ExpressionFailed, m_lazyExpression);

    AssertionResult result(m_info, std::move(data));

    EXPECT_EQ(ResultWas::ExpressionFailed, result.getResultType());

}
