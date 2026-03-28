#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_lazy_expr.hpp"

#include <sstream>



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockTransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD0(isBinaryExpression, bool());

    MOCK_CONST_METHOD0(getResult, bool());

    MOCK_METHOD1(streamReconstructedExpression, void(std::ostream&));

};



TEST_F(LazyExpressionTest_605, PositiveNonBinaryExpression_605) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockExpr, isBinaryExpression()).WillOnce(Return(false));

    EXPECT_CALL(mockExpr, getResult()).WillOnce(Return(true));



    LazyExpression lazyExpr(false);

    lazyExpr.m_transientExpression = &mockExpr;



    std::ostringstream os;

    os << lazyExpr;



    EXPECT_EQ(os.str(), "1");

}



TEST_F(LazyExpressionTest_605, NegativeNonBinaryExpression_605) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockExpr, isBinaryExpression()).WillOnce(Return(false));

    EXPECT_CALL(mockExpr, getResult()).WillOnce(Return(false));



    LazyExpression lazyExpr(true);

    lazyExpr.m_transientExpression = &mockExpr;



    std::ostringstream os;

    os << lazyExpr;



    EXPECT_EQ(os.str(), "!0");

}



TEST_F(LazyExpressionTest_605, PositiveBinaryExpression_605) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockExpr, isBinaryExpression()).WillOnce(Return(true));

    EXPECT_CALL(mockExpr, getResult()).WillOnce(Return(true));



    LazyExpression lazyExpr(false);

    lazyExpr.m_transientExpression = &mockExpr;



    std::ostringstream os;

    os << lazyExpr;



    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(LazyExpressionTest_605, NegativeBinaryExpression_605) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockExpr, isBinaryExpression()).WillOnce(Return(true));

    EXPECT_CALL(mockExpr, getResult()).WillOnce(Return(false));



    LazyExpression lazyExpr(true);

    lazyExpr.m_transientExpression = &mockExpr;



    std::ostringstream os;

    os << lazyExpr;



    EXPECT_EQ(os.str(), "(!1)");

}



TEST_F(LazyExpressionTest_605, UncheckedEmptyExpression_605) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockExpr, isBinaryExpression()).WillOnce(Return(true));

    EXPECT_CALL(mockExpr, getResult()).WillOnce(Return(false));



    LazyExpression lazyExpr(true);

    lazyExpr.m_transientExpression = nullptr;



    std::ostringstream os;

    os << lazyExpr;



    EXPECT_EQ(os.str(), "{** error - unchecked empty expression requested **}");

}
