#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest : public ::testing::Test {

protected:

    AssertionInfo info;

    AssertionResultData data{ResultWas::OfType::Ok, LazyExpression{"expression"}};

    AssertionResult result{info, std::move(data)};

};



TEST_F(AssertionResultTest_300, GetMessage_ReturnsCorrectMessage_300) {

    EXPECT_EQ(result.getMessage().c_str(), "message");

}



TEST_F(AssertionResultTest_300, IsOk_ReturnsTrueForOkType_300) {

    result.m_resultData.resultType = ResultWas::OfType::Ok;

    EXPECT_TRUE(result.isOk());

}



TEST_F(AssertionResultTest_300, Succeeded_ReturnsTrueForOkType_300) {

    result.m_resultData.resultType = ResultWas::OfType::Ok;

    EXPECT_TRUE(result.succeeded());

}



TEST_F(AssertionResultTest_300, IsOk_ReturnsFalseForNonOkType_300) {

    result.m_resultData.resultType = ResultWas::OfType::ExpressionFailed;

    EXPECT_FALSE(result.isOk());

}



TEST_F(AssertionResultTest_300, Succeeded_ReturnsFalseForNonOkType_300) {

    result.m_resultData.resultType = ResultWas::OfType::ExpressionFailed;

    EXPECT_FALSE(result.succeeded());

}



TEST_F(AssertionResultTest_300, HasMessage_ReturnsTrueWhenMessageExists_300) {

    result.m_resultData.message = "message";

    EXPECT_TRUE(result.hasMessage());

}



TEST_F(AssertionResultTest_300, HasMessage_ReturnsFalseWhenNoMessage_300) {

    result.m_resultData.message.clear();

    EXPECT_FALSE(result.hasMessage());

}
