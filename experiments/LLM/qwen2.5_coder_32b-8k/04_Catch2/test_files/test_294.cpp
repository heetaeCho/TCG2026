#include <gtest/gtest.h>

#include <catch2/catch_assertion_result.hpp>



using namespace Catch;



class AssertionResultTest_294 : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data;

    AssertionResult result;



    void SetUp() override {

        info.capturedExpression = "someExpression";

        result = AssertionResult(info, std::move(data));

    }

};



TEST_F(AssertionResultTest_294, HasExpression_ReturnsTrueWhenCapturedExpressionIsNotEmpty_294) {

    EXPECT_TRUE(result.hasExpression());

}



TEST_F(AssertionResultTest_294, HasExpression_ReturnsFalseWhenCapturedExpressionIsEmpty_294) {

    info.capturedExpression = "";

    AssertionResult emptyResult(info, std::move(data));

    EXPECT_FALSE(emptyResult.hasExpression());

}
