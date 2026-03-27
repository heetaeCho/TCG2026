// LazyExpression_tests_65.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "Catch2/src/catch2/internal/catch_lazy_expr.hpp"

using Catch::LazyExpression;

// -------- Compile-time interface checks (no runtime behavior asserted) --------
static_assert(std::is_copy_constructible<LazyExpression>::value,
              "LazyExpression should be copy-constructible");
static_assert(!std::is_copy_assignable<LazyExpression>::value,
              "LazyExpression should not be copy-assignable");
static_assert(!std::is_convertible<LazyExpression, bool>::value,
              "Conversion to bool must be explicit (explicit operator bool)");

// -------- Runtime behavior tests --------

TEST(LazyExpressionTest_65, BoolConversion_IsFalse_OnFreshInstance_NegatedFalse_65) {
    LazyExpression e(false);                 // construct via public interface
    EXPECT_FALSE(static_cast<bool>(e));      // explicit conversion
    bool contextual = e ? true : false;      // contextual conversion allowed
    EXPECT_FALSE(contextual);
}

TEST(LazyExpressionTest_65, BoolConversion_IsFalse_OnFreshInstance_NegatedTrue_65) {
    LazyExpression e(true);                  // negation flag should not affect truthiness
    EXPECT_FALSE(static_cast<bool>(e));
}

TEST(LazyExpressionTest_65, CopyConstruction_PreservesBoolConversion_65) {
    LazyExpression e(false);
    LazyExpression copy(e);                  // public copy constructor
    EXPECT_EQ(static_cast<bool>(e), static_cast<bool>(copy));
}

TEST(LazyExpressionTest_65, ContextualConversion_WorksInIf_65) {
    LazyExpression e(false);
    int branch = 0;
    if (e) {
        branch = 1;
    } else {
        branch = 2;
    }
    EXPECT_EQ(branch, 2);                    // false branch taken for a fresh instance
}

TEST(LazyExpressionTest_65, BoolOperator_IsConstexpr_65) {
    constexpr LazyExpression e(false);                   // constexpr constructor (per interface)
    constexpr bool b = static_cast<bool>(e);             // constexpr operator bool
    static_assert(b == false, "operator bool must be usable in constant expressions");
    EXPECT_FALSE(b);
}
