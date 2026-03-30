// File: tests/lazy_expr_ostream_605_tests.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided interfaces
#include "catch2/internal/catch_lazy_expr.hpp"

using namespace Catch;

class LazyExpressionOstreamTest_605 : public ::testing::Test {};

// [605] Normal/observable behavior: empty LazyExpression streams the documented error text.
TEST_F(LazyExpressionOstreamTest_605, EmptyExpression_PrintsErrorToken_605) {
    LazyExpression expr(false); // constructible via interface; empty expression
    std::ostringstream oss;

    oss << expr;

    // Observable output for empty expressions from operator<< implementation
    EXPECT_EQ(oss.str(), "{** error - unchecked empty expression requested **}");
}

// [605] Negated empty expression: '!' is prefixed even when expression is empty.
TEST_F(LazyExpressionOstreamTest_605, NegatedEmptyExpression_PrefixesBangAndError_605) {
    LazyExpression negated(true);
    std::ostringstream oss;

    oss << negated;

    EXPECT_EQ(oss.str(), "!{** error - unchecked empty expression requested **}");
}

// [605] Return value behavior: operator<< returns ostream&, so chaining should append further output.
TEST_F(LazyExpressionOstreamTest_605, OstreamReturn_AllowsChaining_605) {
    LazyExpression expr(false);
    std::ostringstream oss;

    (oss << expr) << " trailing";

    EXPECT_EQ(oss.str(), "{** error - unchecked empty expression requested **} trailing");
}

// [605] Explicit bool conversion: empty LazyExpression evaluates to false (observable via interface).
TEST_F(LazyExpressionOstreamTest_605, BoolConversion_EmptyIsFalse_605) {
    LazyExpression expr(false);
    EXPECT_FALSE(static_cast<bool>(expr));
}
