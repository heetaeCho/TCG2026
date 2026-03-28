#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest_302 : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    void SetUp() override {

        // Initialize AssertionInfo and AssertionResult for testing

        info.macroName = "TEST_MACRO";

        result = AssertionResult(info, std::move(data));

    }

};



// Test normal operation of isOk()

TEST_F(AssertionResultTest_302, IsOk_ReturnsTrue_302) {

    EXPECT_TRUE(result.isOk());

}



// Test normal operation of succeeded()

TEST_F(AssertionResultTest_302, Succeeded_ReturnsFalse_302) {

    EXPECT_FALSE(result.succeeded());

}



// Test boundary condition of getResultType()

TEST_F(AssertionResultTest_302, GetResultType_DefaultValue_302) {

    EXPECT_EQ(result.getResultType(), ResultWas::Unknown);

}



// Test normal operation of hasExpression()

TEST_F(AssertionResultTest_302, HasExpression_ReturnsFalse_302) {

    EXPECT_FALSE(result.hasExpression());

}



// Test normal operation of hasMessage()

TEST_F(AssertionResultTest_302, HasMessage_ReturnsFalse_302) {

    EXPECT_FALSE(result.hasMessage());

}



// Test normal operation of getExpression()

TEST_F(AssertionResultTest_302, GetExpression_DefaultValue_302) {

    EXPECT_EQ(result.getExpression(), "");

}



// Test normal operation of getExpressionInMacro()

TEST_F(AssertionResultTest_302, GetExpressionInMacro_DefaultValue_302) {

    EXPECT_EQ(result.getExpressionInMacro(), "");

}



// Test normal operation of hasExpandedExpression()

TEST_F(AssertionResultTest_302, HasExpandedExpression_ReturnsFalse_302) {

    EXPECT_FALSE(result.hasExpandedExpression());

}



// Test normal operation of getExpandedExpression()

TEST_F(AssertionResultTest_302, GetExpandedExpression_DefaultValue_302) {

    EXPECT_EQ(result.getExpandedExpression(), "");

}



// Test normal operation of getMessage()

TEST_F(AssertionResultTest_302, GetMessage_DefaultValue_302) {

    EXPECT_EQ(result.getMessage(), StringRef(""));

}



// Test normal operation of getSourceInfo()

TEST_F(AssertionResultTest_302, GetSourceInfo_DefaultValue_302) {

    SourceLineInfo defaultInfo;

    EXPECT_EQ(result.getSourceInfo().line, defaultInfo.line);

    EXPECT_EQ(result.getSourceInfo().file, defaultInfo.file);

}



// Test normal operation of getTestMacroName()

TEST_F(AssertionResultTest_302, GetTestMacroName_ReturnsMacroName_302) {

    EXPECT_EQ(result.getTestMacroName(), "TEST_MACRO");

}
