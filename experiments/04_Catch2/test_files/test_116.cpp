#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_decomposer.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockTransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD0(getResult, bool());

    MOCK_CONST_METHOD0(isBinaryExpression, bool());

    MOCK_METHOD1(streamReconstructedExpression, void(std::ostream&));

};



TEST_F(MockTransientExpressionTest_116, GetResult_ReturnsTrue_116) {

    MockTransientExpression mock(true, true);

    EXPECT_CALL(mock, getResult()).WillOnce(Return(true));

    ASSERT_TRUE(mock.getResult());

}



TEST_F(MockTransientExpressionTest_116, GetResult_ReturnsFalse_116) {

    MockTransientExpression mock(false, false);

    EXPECT_CALL(mock, getResult()).WillOnce(Return(false));

    ASSERT_FALSE(mock.getResult());

}



TEST_F(MockTransientExpressionTest_116, IsBinaryExpression_ReturnsTrue_116) {

    MockTransientExpression mock(true, true);

    EXPECT_CALL(mock, isBinaryExpression()).WillOnce(Return(true));

    ASSERT_TRUE(mock.isBinaryExpression());

}



TEST_F(MockTransientExpressionTest_116, IsBinaryExpression_ReturnsFalse_116) {

    MockTransientExpression mock(false, false);

    EXPECT_CALL(mock, isBinaryExpression()).WillOnce(Return(false));

    ASSERT_FALSE(mock.isBinaryExpression());

}



TEST_F(MockTransientExpressionTest_116, StreamReconstructedExpression_CallsStream_116) {

    MockTransientExpression mock(true, true);

    std::ostringstream oss;

    EXPECT_CALL(mock, streamReconstructedExpression(_)).Times(1);

    mock.streamReconstructedExpression(oss);

}
