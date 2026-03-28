#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch_decomposer.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class ITransientExpressionTest_539 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(ITransientExpressionTest_539, StreamReconstructedExpression_DefaultMessage_539) {

    ITransientExpression expr(true, true);

    expr.streamReconstructedExpression(oss);

    EXPECT_EQ(oss.str(), "Some class derived from ITransientExpression without overriding streamReconstructedExpression");

}



TEST_F(ITransientExpressionTest_539, IsBinaryExpression_ReturnsTrue_539) {

    ITransientExpression expr(true, true);

    EXPECT_TRUE(expr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_539, IsBinaryExpression_ReturnsFalse_539) {

    ITransientExpression expr(false, true);

    EXPECT_FALSE(expr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_539, GetResult_ReturnsTrue_539) {

    ITransientExpression expr(true, true);

    EXPECT_TRUE(expr.getResult());

}



TEST_F(ITransientExpressionTest_539, GetResult_ReturnsFalse_539) {

    ITransientExpression expr(true, false);

    EXPECT_FALSE(expr.getResult());

}
