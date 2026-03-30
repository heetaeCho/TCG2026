// File: tests/test_approx_gte_700.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

class ApproxGteTest_700 : public ::testing::Test {
protected:
    // Helper that zeroes epsilon so only explicit margin is used,
    // to avoid relying on any hidden default epsilon behavior.
    static Approx WithOnlyMargin(double value, double margin) {
        Approx a(value);
        a.epsilon(0.0);
        a.margin(margin);
        return a;
    }
};

// --- Normal operation ---

TEST_F(ApproxGteTest_700, ExactEqualityReturnsTrue_700) {
    // Exact equality should be treated as >=
    EXPECT_TRUE(Approx(5.0) >= 5.0);
}

TEST_F(ApproxGteTest_700, GreaterThanPlainDoubleReturnsTrue_700) {
    EXPECT_TRUE(Approx(2.0) >= 1.0);
}

// --- Boundary conditions around tolerance ---

TEST_F(ApproxGteTest_700, LessThanButWithinMarginIsTrue_700) {
    // lhs < rhs, but within margin => considered equal => >= should be true
    auto lhs = ApproxGteTest_700::WithOnlyMargin(10.0, /*margin=*/0.5);
    double rhs = 10.3; // |10.0 - 10.3| = 0.3 <= 0.5
    EXPECT_TRUE(lhs >= rhs);
}

TEST_F(ApproxGteTest_700, LessThanAndOutsideMarginIsFalse_700) {
    // lhs < rhs and outside margin => neither greater nor equal
    auto lhs = ApproxGteTest_700::WithOnlyMargin(10.0, /*margin=*/0.5);
    double rhs = 10.6; // |10.0 - 10.6| = 0.6 > 0.5
    EXPECT_FALSE(lhs >= rhs);
}

TEST_F(ApproxGteTest_700, NegativeValuesWithinMarginIsTrue_700) {
    // Checks behavior with negatives when within margin
    auto lhs = ApproxGteTest_700::WithOnlyMargin(-3.0, /*margin=*/0.2);
    double rhs = -2.9; // | -3.0 - (-2.9) | = 0.1 <= 0.2
    EXPECT_TRUE(lhs >= rhs);
}

TEST_F(ApproxGteTest_700, ZeroMarginRequiresTrueGreaterOrExact_700) {
    // With zero margin and epsilon, only strict greater-or-exact should pass
    Approx lhs(1.0);
    lhs.margin(0.0).epsilon(0.0);
    EXPECT_TRUE(lhs >= 1.0);     // exact
    EXPECT_FALSE(lhs >= 1.1);    // strictly less with no tolerance
}

// --- Type coverage (observable via overload resolution & conversion only) ---

TEST_F(ApproxGteTest_700, WorksWithIntegralRhs_700) {
    // Ensure the templated operator accepts integrals as rhs
    int rhs = 3;
    EXPECT_TRUE(Approx(3.0) >= rhs);   // equal
    EXPECT_TRUE(Approx(4.0) >= rhs);   // greater
    EXPECT_FALSE(Approx(2.0) >= rhs);  // less (no margin)
}

TEST_F(ApproxGteTest_700, WorksWithLongDoubleRhsAndMargin_700) {
    // Ensure it works with wider floating types and tolerance-based equality
    long double rhs = static_cast<long double>(100.2L);
    auto lhs = ApproxGteTest_700::WithOnlyMargin(100.0, /*margin=*/0.25);
    // lhs < rhs, but |100.0 - 100.2| = 0.2 <= 0.25 => treated equal => >= true
    EXPECT_TRUE(lhs >= rhs);

    // Outside margin => false
    rhs = static_cast<long double>(100.3L); // diff 0.3 > 0.25
    EXPECT_FALSE(lhs >= rhs);
}
