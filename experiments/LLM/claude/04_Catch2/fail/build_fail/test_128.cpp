#include <gtest/gtest.h>

// Include the header under test
#include "catch2/internal/catch_decomposer.hpp"

// We need to include enough of Catch2's internals to use ExprLhs and UnaryExpr
#include "catch2/internal/catch_test_macro_impl.hpp"

// Test fixture
class ExprLhsTest_128 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ExprLhs can be constructed with an integer and makeUnaryExpr returns a UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromInt_128) {
    int value = 42;
    Catch::ExprLhs<int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    // UnaryExpr is an ITransientExpression; verify it can be evaluated
    // The unary expression of a non-zero int should be truthy
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test that ExprLhs with a zero integer produces a falsy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromZeroInt_128) {
    int value = 0;
    Catch::ExprLhs<int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_FALSE(unaryExpr.m_result);
}

// Test that ExprLhs with a boolean true produces a truthy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromBoolTrue_128) {
    bool value = true;
    Catch::ExprLhs<bool> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test that ExprLhs with a boolean false produces a falsy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromBoolFalse_128) {
    bool value = false;
    Catch::ExprLhs<bool> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_FALSE(unaryExpr.m_result);
}

// Test that ExprLhs with a negative integer produces a truthy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromNegativeInt_128) {
    int value = -1;
    Catch::ExprLhs<int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test that ExprLhs with a pointer (non-null) produces truthy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromNonNullPointer_128) {
    int x = 10;
    int* ptr = &x;
    Catch::ExprLhs<int*> exprLhs(ptr);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test that ExprLhs with a null pointer produces falsy UnaryExpr
TEST_F(ExprLhsTest_128, MakeUnaryExprFromNullPointer_128) {
    int* ptr = nullptr;
    Catch::ExprLhs<int*> exprLhs(ptr);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_FALSE(unaryExpr.m_result);
}

// Test that ExprLhs with a double value produces correct truthiness
TEST_F(ExprLhsTest_128, MakeUnaryExprFromDouble_128) {
    double value = 3.14;
    Catch::ExprLhs<double> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test that ExprLhs with a zero double produces falsy
TEST_F(ExprLhsTest_128, MakeUnaryExprFromZeroDouble_128) {
    double value = 0.0;
    Catch::ExprLhs<double> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_FALSE(unaryExpr.m_result);
}

// Test that ExprLhs with an unsigned int works
TEST_F(ExprLhsTest_128, MakeUnaryExprFromUnsignedInt_128) {
    unsigned int value = 1u;
    Catch::ExprLhs<unsigned int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test boundary: max int value
TEST_F(ExprLhsTest_128, MakeUnaryExprFromMaxInt_128) {
    int value = std::numeric_limits<int>::max();
    Catch::ExprLhs<int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}

// Test boundary: min int value
TEST_F(ExprLhsTest_128, MakeUnaryExprFromMinInt_128) {
    int value = std::numeric_limits<int>::min();
    Catch::ExprLhs<int> exprLhs(value);
    auto unaryExpr = exprLhs.makeUnaryExpr();
    EXPECT_TRUE(unaryExpr.m_result);
}
