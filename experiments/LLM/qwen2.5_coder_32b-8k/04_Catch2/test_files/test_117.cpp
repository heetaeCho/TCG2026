#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_decomposer.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class MockITransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD1(streamReconstructedExpression, void(std::ostream& os));

    MOCK_CONST_METHOD0(isBinaryExpression, bool());

    MOCK_CONST_METHOD0(getResult, bool());



    MockITransientExpression(bool isBinaryExpression, bool result)

        : ITransientExpression(isBinaryExpression, result) {}

};



class ITransientExpressionTest_117 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(ITransientExpressionTest_117, IsBinaryExpression_ReturnsTrue_117) {

    MockITransientExpression expr(true, true);

    EXPECT_CALL(expr, isBinaryExpression()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(expr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_117, IsBinaryExpression_ReturnsFalse_117) {

    MockITransientExpression expr(false, true);

    EXPECT_CALL(expr, isBinaryExpression()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(expr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_117, GetResult_ReturnsTrue_117) {

    MockITransientExpression expr(true, true);

    EXPECT_CALL(expr, getResult()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(expr.getResult());

}



TEST_F(ITransientExpressionTest_117, GetResult_ReturnsFalse_117) {

    MockITransientExpression expr(true, false);

    EXPECT_CALL(expr, getResult()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(expr.getResult());

}



TEST_F(ITransientExpressionTest_117, StreamReconstructedExpression_CallsStreamReconstructedExpression_117) {

    MockITransientExpression expr(true, true);

    EXPECT_CALL(expr, streamReconstructedExpression(_)).Times(1);

    oss << expr;

}
