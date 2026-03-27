#include <gtest/gtest.h>

#include <Catch2/catch_assertion_result.hpp>



using namespace Catch;



class AssertionResultTest_296 : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResult result;



    void SetUp() override {

        info.capturedExpression = "1 == 1";

        result = AssertionResult(info, AssertionResultData{});

    }

};



TEST_F(AssertionResultTest_296, GetExpression_ReturnsCapturedExpression_296) {

    EXPECT_EQ(result.getExpression(), "(1 == 1)");

}



TEST_F(AssertionResultTest_296, GetExpression_NoFalseDisposition_ReturnsPlainExpression_296) {

    info.resultDisposition = ResultDisposition::None;

    result = AssertionResult(info, AssertionResultData{});

    EXPECT_EQ(result.getExpression(), "1 == 1");

}



TEST_F(AssertionResultTest_296, GetExpression_EmptyCapturedExpression_ReturnsEmptyString_296) {

    info.capturedExpression = "";

    result = AssertionResult(info, AssertionResultData{});

    EXPECT_EQ(result.getExpression(), "");

}



TEST_F(AssertionResultTest_296, GetExpression_NonFalseDisposition_ReturnsNegatedExpression_296) {

    info.resultDisposition = ResultDisposition::False;

    result = AssertionResult(info, AssertionResultData{});

    EXPECT_EQ(result.getExpression(), "!(1 == 1)");

}



TEST_F(AssertionResultTest_296, HasExpression_NonEmptyCapturedExpression_ReturnsTrue_296) {

    EXPECT_TRUE(result.hasExpression());

}



TEST_F(AssertionResultTest_296, HasExpression_EmptyCapturedExpression_ReturnsFalse_296) {

    info.capturedExpression = "";

    result = AssertionResult(info, AssertionResultData{});

    EXPECT_FALSE(result.hasExpression());

}
