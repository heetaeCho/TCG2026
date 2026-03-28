#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    void SetUp() override {

        // Initialize with default values for simplicity

        info = AssertionInfo("file.cpp", 10, "TEST_CASE", "expression");

        data = AssertionResultData();

        result = AssertionResult(info, std::move(data));

    }

};



// Test if hasExpandedExpression returns false when no expanded expression is present

TEST_F(AssertionResultTest_298, HasNoExpandedExpression_298) {

    EXPECT_FALSE(result.hasExpandedExpression());

}



// Test if hasExpandedExpression returns true when an expanded expression is set

TEST_F(AssertionResultTest_298, HasExpandedExpression_298) {

    data.setExpandedExpression("expanded_expression");

    result = AssertionResult(info, std::move(data));

    EXPECT_TRUE(result.hasExpandedExpression());

}



// Test if getExpression returns the correct expression

TEST_F(AssertionResultTest_298, GetExpression_ReturnsCorrectExpression_298) {

    info.expression = "expression";

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ("expression", result.getExpression());

}



// Test if getExpandedExpression returns the correct expanded expression

TEST_F(AssertionResultTest_298, GetExpandedExpression_ReturnsCorrectExpandedExpression_298) {

    data.setExpandedExpression("expanded_expression");

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ("expanded_expression", result.getExpandedExpression());

}



// Test if hasMessage returns false when no message is present

TEST_F(AssertionResultTest_298, HasNoMessage_298) {

    EXPECT_FALSE(result.hasMessage());

}



// Test if hasMessage returns true when a message is set

TEST_F(AssertionResultTest_298, HasMessage_298) {

    data.setMessage("message");

    result = AssertionResult(info, std::move(data));

    EXPECT_TRUE(result.hasMessage());

}



// Test if getMessage returns the correct message

TEST_F(AssertionResultTest_298, GetMessage_ReturnsCorrectMessage_298) {

    data.setMessage("message");

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ("message", result.getMessage().toString());

}



// Test if getSourceInfo returns the correct SourceLineInfo

TEST_F(AssertionResultTest_298, GetSourceInfo_ReturnsCorrectSourceInfo_298) {

    info.lineInfo = SourceLineInfo("file.cpp", 10);

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ(SourceLineInfo("file.cpp", 10), result.getSourceInfo());

}



// Test if getTestMacroName returns the correct test macro name

TEST_F(AssertionResultTest_298, GetTestMacroName_ReturnsCorrectTestMacroName_298) {

    info.macroName = "TEST_CASE";

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ("TEST_CASE", result.getTestMacroName().toString());

}



// Test if succeeded returns true when the assertion is successful

TEST_F(AssertionResultTest_298, Succeeded_ReturnsTrueForSuccess_298) {

    data.setResultType(ResultWas::Ok);

    result = AssertionResult(info, std::move(data));

    EXPECT_TRUE(result.succeeded());

}



// Test if succeeded returns false when the assertion fails

TEST_F(AssertionResultTest_298, Succeeded_ReturnsFalseForFailure_298) {

    data.setResultType(ResultWas::Failed);

    result = AssertionResult(info, std::move(data));

    EXPECT_FALSE(result.succeeded());

}



// Test if isOk returns true when the assertion is successful

TEST_F(AssertionResultTest_298, IsOk_ReturnsTrueForSuccess_298) {

    data.setResultType(ResultWas::Ok);

    result = AssertionResult(info, std::move(data));

    EXPECT_TRUE(result.isOk());

}



// Test if isOk returns false when the assertion fails

TEST_F(AssertionResultTest_298, IsOk_ReturnsFalseForFailure_298) {

    data.setResultType(ResultWas::Failed);

    result = AssertionResult(info, std::move(data));

    EXPECT_FALSE(result.isOk());

}



// Test if getResultType returns the correct ResultWas type

TEST_F(AssertionResultTest_298, GetResultType_ReturnsCorrectResultType_298) {

    data.setResultType(ResultWas::ExpressionFailed);

    result = AssertionResult(info, std::move(data));

    EXPECT_EQ(ResultWas::ExpressionFailed, result.getResultType());

}
