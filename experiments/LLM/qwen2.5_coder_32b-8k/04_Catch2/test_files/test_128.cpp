#include <gtest/gtest.h>

#include "catch2/internal/catch_decomposer.hpp"

#include <type_traits>



using namespace Catch;



// Mock class to simulate UnaryExpr for testing purposes

template <typename LhsT>

class MockUnaryExpr {

public:

    explicit MockUnaryExpr(LhsT lhs) : m_lhs(lhs) {}

private:

    LhsT m_lhs;

};



// Test Fixture

class ExprLhsTest_128 : public ::testing::Test {

protected:

    template <typename T>

    using MockExprLhs = ExprLhs<T>;



    template <typename T>

    using MockUnaryExprType = MockUnaryExpr<T>;

};



// Normal operation test

TEST_F(ExprLhsTest_128, MakeUnaryExpr_ReturnsUnaryExpr_128) {

    int value = 42;

    MockExprLhs<int> expr_lhs(value);

    auto unary_expr = expr_lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(unary_expr), UnaryExpr<int>>::value, "Return type mismatch");

}



// Boundary condition test with zero

TEST_F(ExprLhsTest_128, MakeUnaryExpr_ZeroValue_ReturnsUnaryExpr_128) {

    int value = 0;

    MockExprLhs<int> expr_lhs(value);

    auto unary_expr = expr_lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(unary_expr), UnaryExpr<int>>::value, "Return type mismatch");

}



// Boundary condition test with negative value

TEST_F(ExprLhsTest_128, MakeUnaryExpr_NegativeValue_ReturnsUnaryExpr_128) {

    int value = -42;

    MockExprLhs<int> expr_lhs(value);

    auto unary_expr = expr_lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(unary_expr), UnaryExpr<int>>::value, "Return type mismatch");

}



// Test with different data types

TEST_F(ExprLhsTest_128, MakeUnaryExpr_DoubleValue_ReturnsUnaryExpr_128) {

    double value = 3.14;

    MockExprLhs<double> expr_lhs(value);

    auto unary_expr = expr_lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(unary_expr), UnaryExpr<double>>::value, "Return type mismatch");

}



TEST_F(ExprLhsTest_128, MakeUnaryExpr_StringValue_ReturnsUnaryExpr_128) {

    std::string value = "test";

    MockExprLhs<std::string> expr_lhs(value);

    auto unary_expr = expr_lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(unary_expr), UnaryExpr<std::string>>::value, "Return type mismatch");

}
