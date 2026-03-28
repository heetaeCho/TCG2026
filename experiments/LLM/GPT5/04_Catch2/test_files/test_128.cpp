// File: tests/expr_lhs_make_unary_expr_128.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <memory>

// Use the real interface only.
#include "catch2/internal/catch_decomposer.hpp"

using namespace Catch;

// -----------------------------
// Test Fixture
// -----------------------------
class ExprLhsTest_128 : public ::testing::Test {};

// -----------------------------
// Tests
// -----------------------------

// [Normal operation] For a simple arithmetic type, makeUnaryExpr returns UnaryExpr<LhsT>.
TEST_F(ExprLhsTest_128, MakeUnaryExpr_ReturnsUnaryExprType_Int_128) {
    ExprLhs<int> lhs(42);
    auto expr = lhs.makeUnaryExpr();

    // Type validation at compile time (black-box: only interface types)
    static_assert(std::is_same<decltype(expr), UnaryExpr<int>>::value,
                  "makeUnaryExpr() must return UnaryExpr<LhsT> for LhsT=int");

    // Also check basic value semantics of the returned type (interface-level)
    static_assert(std::is_copy_constructible<decltype(expr)>::value,
                  "UnaryExpr<int> should be copy-constructible");
    static_assert(std::is_move_constructible<decltype(expr)>::value,
                  "UnaryExpr<int> should be move-constructible");

    SUCCEED(); // If we got here, the interface behaved as expected.
}

// [Boundary condition] Ensure cv-qualification on LhsT is preserved by the returned template instantiation.
TEST_F(ExprLhsTest_128, MakeUnaryExpr_PreservesConstQualification_128) {
    using L = const int;
    ExprLhs<L> lhs(7);
    auto expr = lhs.makeUnaryExpr();

    static_assert(std::is_same<decltype(expr), UnaryExpr<const int>>::value,
                  "makeUnaryExpr() must return UnaryExpr<const int> when LhsT is const int");

    SUCCEED();
}

// [Boundary condition] Move-only types should be supported since ExprLhs takes LhsT by value.
// We verify only the interface-level template instantiation and constructibility.
TEST_F(ExprLhsTest_128, MakeUnaryExpr_SupportsMoveOnlyLhs_128) {
    using Ptr = std::unique_ptr<int>;
    ExprLhs<Ptr> lhs(Ptr(new int(5)));

    // Creating the expression should work and produce the correct template instantiation.
    auto expr = lhs.makeUnaryExpr();
    static_assert(std::is_same<decltype(expr), UnaryExpr<Ptr>>::value,
                  "makeUnaryExpr() must return UnaryExpr<std::unique_ptr<int>> for move-only LhsT");

    // Basic value semantics on the returned interface type.
    static_assert(std::is_move_constructible<decltype(expr)>::value,
                  "UnaryExpr<unique_ptr<int>> should be move-constructible");

    SUCCEED();
}

// [Exceptional / edge behavior at interface level] Verify makeUnaryExpr is usable in a constexpr context
// when LhsT itself is a literal/constexpr-suitable type. This checks the 'constexpr' on the function.
TEST_F(ExprLhsTest_128, MakeUnaryExpr_IsUsableInConstexpr_ForLiteralType_128) {
    // Note: unique_ptr is not constexpr-constructible; use int.
    constexpr ExprLhs<int> lhs(3);
    // If makeUnaryExpr is not constexpr as specified, this will fail to compile.
    constexpr auto expr = lhs.makeUnaryExpr();

    // We can't inspect internal state; just assert we got the right type at compile-time.
    (void)expr; // silence unused warning
    static_assert(std::is_same<decltype(expr), UnaryExpr<int>>::value,
                  "constexpr makeUnaryExpr() must yield UnaryExpr<int> for LhsT=int");

    SUCCEED();
}
