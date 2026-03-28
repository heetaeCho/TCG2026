// File: tests/approx_operator_eq_693_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

// Test fixture kept minimal as we treat Approx as a black box.
class ApproxEqualsTest_693 : public ::testing::Test {};

// ----------------------------------------------------------------------------
// Normal operation: exact equality with same numeric value (double lhs)
TEST_F(ApproxEqualsTest_693, ExactEquality_Double_693) {
    EXPECT_TRUE(1.23 == Approx(1.23));
}

// Normal operation: exact equality when lhs is an int
TEST_F(ApproxEqualsTest_693, ExactEquality_IntLhs_693) {
    EXPECT_TRUE(5 == Approx(5.0));
}

// Normal operation: exact equality when lhs is float, rhs Approx(double)
TEST_F(ApproxEqualsTest_693, ExactEquality_FloatLhs_693) {
    float lhs = 10.0f;
    EXPECT_TRUE(lhs == Approx(10.0));
}

// ----------------------------------------------------------------------------
// Boundary-ish: clearly different values should not compare equal
TEST_F(ApproxEqualsTest_693, Inequality_FarApart_693) {
    EXPECT_FALSE(1000.0 == Approx(1.0));
    EXPECT_FALSE(-100.0 == Approx(100.0));
}

// ----------------------------------------------------------------------------
// Unary minus: observable via comparison on negative values
TEST_F(ApproxEqualsTest_693, UnaryMinus_ComparesNegatives_693) {
    // -(Approx(2.5)) should compare equal to -2.5 through operator==
    const Approx neg = -Approx(2.5);
    EXPECT_TRUE(-2.5 == neg);
    EXPECT_FALSE(-2.4 == neg); // sufficiently far to be observably unequal
}

// ----------------------------------------------------------------------------
// Operator(): rebinding the target value should change comparison behavior,
// verifiable only via operator== outcomes.
TEST_F(ApproxEqualsTest_693, CallOperator_RebindsTargetValue_693) {
    const Approx a(0.0);
    const Approx b = a(10.0); // create a new Approx targeting 10
    EXPECT_TRUE(10.0 == b);
    EXPECT_FALSE(9.0 == b);   // well outside any tiny default tolerance
}

// ----------------------------------------------------------------------------
// Margin: increasing margin should allow a previously unequal comparison to pass.
// We avoid assuming any internal tolerance formula and only assert observable change.
TEST_F(ApproxEqualsTest_693, Margin_ExpandsAcceptanceWindow_693) {
    Approx a(1.0);

    // Choose a delta large enough that default comparison should be unequal,
    // then verify it becomes equal after increasing margin.
    const double probe = 1.1; // 0.1 away from 1.0

    // First: typically unequal without extra margin
    bool initiallyEqual = (probe == a);
    // We only assert that AFTER adding a clearly larger margin, it must be equal.
    a.margin(0.2);
    bool afterMarginEqual = (probe == a);

    // If initial comparison was already equal (unlikely but possible depending
    // on implementation), we at least require it to remain equal after margin.
    if (!initiallyEqual) {
        EXPECT_FALSE(initiallyEqual);
        EXPECT_TRUE(afterMarginEqual);
    } else {
        // Still acceptable: comparison should not flip to false after increasing margin.
        EXPECT_TRUE(afterMarginEqual);
    }
}

// ----------------------------------------------------------------------------
// Template constructibility of various arithmetic types on both sides of ==
// (verifies only that comparisons compile and behave through the public API).
TEST_F(ApproxEqualsTest_693, TemplateConstructibility_VariousTypes_693) {
    // rhs constructed from int
    EXPECT_TRUE(42.0 == Approx(42));
    // rhs constructed from float
    EXPECT_TRUE(3 == Approx(3.0f));
    // lhs long double
    long double ld = 7.0L;
    EXPECT_TRUE(ld == Approx(7.0));
    // Cross-check inequality remains observable
    EXPECT_FALSE(ld == Approx(7.5));
}
