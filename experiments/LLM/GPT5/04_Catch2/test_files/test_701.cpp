// File: tests/approx_epsilon_701_tests.cpp
#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <cmath>      // for std::fabs
#include <limits>     // for std::numeric_limits

using Catch::Approx;

class ApproxEpsilonTest_701 : public ::testing::Test {};

// [701] Returns self by reference (enables chaining) with integral input
TEST_F(ApproxEpsilonTest_701, EpsilonReturnsSelf_Int_701) {
    Approx a{1.0};
    auto* original = &a;
    auto& ret = a.epsilon(1);  // int -> allowed by is_constructible<double, int>
    EXPECT_EQ(&ret, original);
}

// [701] Returns self by reference with floating inputs (float/double/long double)
TEST_F(ApproxEpsilonTest_701, EpsilonReturnsSelf_Floating_701) {
    Approx a{2.0};
    auto* original = &a;

    float f = 0.01f;
    auto& r1 = a.epsilon(f);
    EXPECT_EQ(&r1, original);

    double d = 0.001;
    auto& r2 = a.epsilon(d);
    EXPECT_EQ(&r2, original);

    long double ld = static_cast<long double>(0.0001L);
    auto& r3 = a.epsilon(ld);
    EXPECT_EQ(&r3, original);
}

// [701] Chaining with other public modifiers remains well-formed and returns same object
TEST_F(ApproxEpsilonTest_701, EpsilonChainsWithOtherModifiers_701) {
    Approx a{3.14};
    auto* original = &a;

    auto& ref = a.epsilon(0.01).margin(0.0).scale(0.0);
    EXPECT_EQ(&ref, original);
}

// [701] Epsilon influences observable equality behavior (small epsilon -> unequal; larger -> equal)
// Note: We only assert observable results through the public == operator with Approx.
TEST_F(ApproxEpsilonTest_701, EpsilonAffectsEquality_701) {
    const double base = 1000.0;
    const double near  = 1000.5;

    // With a very small epsilon, values that differ by 0.5 should not compare equal
    EXPECT_FALSE( near == Approx(base).epsilon(1e-9) );

    // With a larger epsilon, the same values are considered equal
    EXPECT_TRUE( near == Approx(base).epsilon(1.0) );
}

// [701] Zero epsilon behaves consistently: exact matches compare equal
TEST_F(ApproxEpsilonTest_701, ZeroEpsilonExactEquality_701) {
    const double v = 1.2345;
    // Exact same value should compare equal even with epsilon(0)
    EXPECT_TRUE( v == Approx(v).epsilon(0.0) );
}

// [701] Typical values for epsilon should not throw; method is noexcept by observable behavior
TEST_F(ApproxEpsilonTest_701, EpsilonNoThrowTypicalValues_701) {
    Approx a{0.0};
    EXPECT_NO_THROW({
        a.epsilon(0.0);
        a.epsilon(1e-12);
        a.epsilon(0.5);
        a.epsilon(1.0);
    });
}

// [701] Passing very large epsilon should allow wider equality tolerance (observable via ==)
TEST_F(ApproxEpsilonTest_701, VeryLargeEpsilonWidensEquality_701) {
    const double base = 10.0;
    const double far  = 25.0;  // quite far from base

    // With modest epsilon, not equal
    EXPECT_FALSE( far == Approx(base).epsilon(0.01) );

    // With a very large epsilon, becomes equal (observable change only)
    EXPECT_TRUE(  far == Approx(base).epsilon(2.0) );
}
