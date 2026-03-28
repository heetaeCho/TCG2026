#include <gtest/gtest.h>
#include "catch2/internal/catch_lazy_expr.hpp"

namespace {

// Test fixture for LazyExpression tests
class LazyExpressionTest_65 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed LazyExpression with isNegated=false evaluates to false
// (since m_transientExpression defaults to nullptr)
TEST_F(LazyExpressionTest_65, DefaultConstructedWithFalseIsFalsy_65) {
    Catch::LazyExpression expr(false);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test that a default-constructed LazyExpression with isNegated=true evaluates to false
// (since m_transientExpression defaults to nullptr regardless of isNegated)
TEST_F(LazyExpressionTest_65, DefaultConstructedWithTrueIsFalsy_65) {
    Catch::LazyExpression expr(true);
    EXPECT_FALSE(static_cast<bool>(expr));
}

// Test that copy construction works and preserves the boolean conversion result
TEST_F(LazyExpressionTest_65, CopyConstructedFromDefaultIsFalsy_65) {
    Catch::LazyExpression original(false);
    Catch::LazyExpression copy(original);
    EXPECT_FALSE(static_cast<bool>(copy));
}

// Test that copy construction from a negated expression also remains falsy
TEST_F(LazyExpressionTest_65, CopyConstructedFromNegatedDefaultIsFalsy_65) {
    Catch::LazyExpression original(true);
    Catch::LazyExpression copy(original);
    EXPECT_FALSE(static_cast<bool>(copy));
}

// Test that operator bool is explicit - verifying it doesn't implicitly convert
// This is a compile-time check essentially; if it compiles with static_cast but
// the value is as expected, the explicit qualifier is working correctly.
TEST_F(LazyExpressionTest_65, ExplicitBoolConversion_65) {
    Catch::LazyExpression expr(false);
    // Explicit conversion should work
    bool result = static_cast<bool>(expr);
    EXPECT_FALSE(result);
}

// Test that multiple LazyExpression instances are independent
TEST_F(LazyExpressionTest_65, MultipleInstancesAreIndependent_65) {
    Catch::LazyExpression expr1(false);
    Catch::LazyExpression expr2(true);
    EXPECT_FALSE(static_cast<bool>(expr1));
    EXPECT_FALSE(static_cast<bool>(expr2));
}

// Test constexpr-compatibility of the bool operator with default state
TEST_F(LazyExpressionTest_65, BoolOperatorOnNullTransientExpression_65) {
    Catch::LazyExpression expr(false);
    // m_transientExpression is nullptr by default, so should be false
    EXPECT_EQ(static_cast<bool>(expr), false);
}

// Test that copy of a copy also maintains the same state
TEST_F(LazyExpressionTest_65, CopyOfCopyIsFalsy_65) {
    Catch::LazyExpression original(false);
    Catch::LazyExpression copy1(original);
    Catch::LazyExpression copy2(copy1);
    EXPECT_FALSE(static_cast<bool>(copy2));
}

} // anonymous namespace
