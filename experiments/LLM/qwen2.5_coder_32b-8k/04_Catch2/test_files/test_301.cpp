#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_assertion_result.hpp"

#include "catch2/catch_assertion_info.hpp"



using namespace Catch;

using namespace ::testing;



class AssertionResultTest_301 : public Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    void SetUp() override {

        info.macroName = StringRef("TEST_MACRO");

        info.capturedExpression = StringRef("1 == 1");

        info.resultDisposition = ResultDisposition::Normal;

        data.setMessage(StringRef("Test message"));

        result = AssertionResult(info, std::move(data));

    }

};



TEST_F(AssertionResultTest_301, GetSourceInfo_ReturnsCorrectLineInfo_301) {

    SourceLineInfo sourceInfo = result.getSourceInfo();

    EXPECT_EQ(sourceInfo.lineInfo.file, "");

    EXPECT_EQ(sourceInfo.lineInfo.line, 0);

}



TEST_F(AssertionResultTest_301, IsOk_ReturnsTrueForSuccessfulAssertion_301) {

    ON_CALL(info, succeeded()).WillByDefault(Return(true));

    EXPECT_TRUE(result.isOk());

}



TEST_F(AssertionResultTest_301, Succeeded_ReturnsTrueForSuccessfulAssertion_301) {

    ON_CALL(info, succeeded()).WillByDefault(Return(true));

    EXPECT_TRUE(result.succeeded());

}



TEST_F(AssertionResultTest_301, HasExpression_ReturnsTrueWhenExpressionExists_301) {

    EXPECT_TRUE(result.hasExpression());

}



TEST_F(AssertionResultTest_301, HasMessage_ReturnsTrueWhenMessageExists_301) {

    EXPECT_TRUE(result.hasMessage());

}



TEST_F(AssertionResultTest_301, GetExpression_ReturnsCapturedExpression_301) {

    EXPECT_EQ(result.getExpression(), "1 == 1");

}



TEST_F(AssertionResultTest_301, GetExpressionInMacro_ReturnsCapturedExpression_301) {

    EXPECT_EQ(result.getExpressionInMacro(), "1 == 1");

}



TEST_F(AssertionResultTest_301, HasExpandedExpression_ReturnsFalseWhenNoExpandedExpression_301) {

    EXPECT_FALSE(result.hasExpandedExpression());

}



TEST_F(AssertionResultTest_301, GetMessage_ReturnsSetMessage_301) {

    EXPECT_EQ(result.getMessage(), "Test message");

}



TEST_F(AssertionResultTest_301, GetTestMacroName_ReturnsCorrectMacroName_301) {

    EXPECT_EQ(result.getTestMacroName(), "TEST_MACRO");

}
