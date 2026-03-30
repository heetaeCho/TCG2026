#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/catch_assertion_result.hpp"



using namespace Catch;



class AssertionResultTest_295 : public ::testing::Test {

protected:

    AssertionInfo m_info;

    AssertionResultData m_resultData;

    AssertionResult* m_assertionResult;



    void SetUp() override {

        m_resultData = AssertionResultData(ResultWas::OfType::Ok, LazyExpression());

        m_assertionResult = new AssertionResult(m_info, std::move(m_resultData));

    }



    void TearDown() override {

        delete m_assertionResult;

    }

};



TEST_F(AssertionResultTest_295, IsOk_ReturnsTrue_295) {

    EXPECT_TRUE(m_assertionResult->isOk());

}



TEST_F(AssertionResultTest_295, Succeeded_ReturnsTrue_295) {

    EXPECT_TRUE(m_assertionResult->succeeded());

}



TEST_F(AssertionResultTest_295, GetResultType_ReturnsOk_295) {

    EXPECT_EQ(m_assertionResult->getResultType(), ResultWas::OfType::Ok);

}



TEST_F(AssertionResultTest_295, HasMessage_ReturnsFalse_WhenNoMessage_295) {

    EXPECT_FALSE(m_assertionResult->hasMessage());

}



TEST_F(AssertionResultTest_295, GetMessage_ReturnsEmptyString_WhenNoMessage_295) {

    EXPECT_EQ(m_assertionResult->getMessage().c_str(), "");

}



TEST_F(AssertionResultTest_295, HasExpression_ReturnsFalse_WhenNoExpression_295) {

    EXPECT_FALSE(m_assertionResult->hasExpression());

}



TEST_F(AssertionResultTest_295, GetExpression_ReturnsEmptyString_WhenNoExpression_295) {

    EXPECT_EQ(m_assertionResult->getExpression(), "");

}



TEST_F(AssertionResultTest_295, HasExpandedExpression_ReturnsFalse_WhenNoExpression_295) {

    EXPECT_FALSE(m_assertionResult->hasExpandedExpression());

}



TEST_F(AssertionResultTest_295, GetExpandedExpression_ReturnsEmptyString_WhenNoExpression_295) {

    EXPECT_EQ(m_assertionResult->getExpandedExpression(), "");

}



TEST_F(AssertionResultTest_295, HasMessage_ReturnsTrue_WhenMessageSet_295) {

    m_resultData.message = "Test message";

    AssertionResult assertionWithMessage(m_info, std::move(m_resultData));

    EXPECT_TRUE(assertionWithMessage.hasMessage());

}



TEST_F(AssertionResultTest_295, GetMessage_ReturnsCorrectMessage_WhenMessageSet_295) {

    m_resultData.message = "Test message";

    AssertionResult assertionWithMessage(m_info, std::move(m_resultData));

    EXPECT_EQ(assertionWithMessage.getMessage().c_str(), "Test message");

}



TEST_F(AssertionResultTest_295, GetExpression_ReturnsCorrectExpression_WhenExpressionSet_295) {

    LazyExpression expression("1 == 1");

    m_resultData = AssertionResultData(ResultWas::OfType::Ok, expression);

    AssertionResult assertionWithExpression(m_info, std::move(m_resultData));

    EXPECT_EQ(assertionWithExpression.getExpression(), "1 == 1");

}



TEST_F(AssertionResultTest_295, GetExpandedExpression_ReturnsCorrectExpression_WhenExpressionSet_295) {

    LazyExpression expression("1 == 1");

    m_resultData = AssertionResultData(ResultWas::OfType::Ok, expression);

    AssertionResult assertionWithExpression(m_info, std::move(m_resultData));

    EXPECT_EQ(assertionWithExpression.getExpandedExpression(), "1 == 1");

}
