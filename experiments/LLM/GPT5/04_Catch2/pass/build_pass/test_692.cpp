// File: tests/ApproxOperatorCall_692.cpp
#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

class ApproxOperatorCallTest_692 : public ::testing::Test {};

// Normal operation: operator() returns a new Approx with the new target value,
// and copies over configuration (tested via observable comparison behavior).
TEST_F(ApproxOperatorCallTest_692, CopiesMarginAndTargetsNewValue_692) {
    // Configure a non-default margin so we can observe it via comparisons.
    Approx base = Approx::custom().margin(0.5); // large enough to test pass/fail around target

    // Create a new Approx with a different value via operator()
    Approx around10 = base(10.0);

    // New target behaves as configured: within margin passes; outside fails.
    EXPECT_TRUE(10.49 == around10);   // within 0.5
    EXPECT_TRUE(9.51  == around10);   // within 0.5 (on the low side)
    EXPECT_FALSE(10.51 == around10);  // just outside margin
    EXPECT_FALSE(9.49  == around10);  // just outside margin

    // Original Approx (base) must remain unchanged (target still its original).
    EXPECT_FALSE(10.0 == base);
}

// Boundary condition: values exactly at the margin boundary should compare equal.
TEST_F(ApproxOperatorCallTest_692, EqualityAtExactMarginBoundary_692) {
    Approx base = Approx::custom().margin(0.5);
    Approx around10 = base(10.0);

    // Exactly at the margin: should be considered equal.
    EXPECT_TRUE(10.5 == around10);
    EXPECT_TRUE(9.5  == around10);

    // Slightly beyond the margin: should not be equal.
    EXPECT_FALSE(10.5000001 == around10);
    EXPECT_FALSE(9.4999999  == around10);
}

// Templated operator(): accepts integral floating-constructible types (int/float/long double).
TEST_F(ApproxOperatorCallTest_692, AcceptsVariousArithmeticTypes_692) {
    Approx base = Approx::custom().margin(0.1).epsilon(1e-6).scale(0.0);

    // int
    Approx a_int = base(3);             // int -> double
    EXPECT_TRUE(3.0 == a_int);
    EXPECT_FALSE(3.2 == a_int);

    // float
    float fv = 4.0f;
    Approx a_float = base(fv);
    EXPECT_TRUE(4.0 == a_float);
    EXPECT_FALSE(4.2 == a_float);

    // long double
    long double ldv = static_cast<long double>(5.0);
    Approx a_ld = base(ldv);
    EXPECT_TRUE(5.0 == a_ld);
    EXPECT_FALSE(5.2 == a_ld);
}

// Chaining configuration before operator(): ensure the returned Approx keeps those settings.
TEST_F(ApproxOperatorCallTest_692, KeepsChainedConfigurationOnReturnedObject_692) {
    // Use distinctive settings; margin is the easiest to observe deterministically.
    Approx configured = Approx::custom()
                            .epsilon(1e-4)  // not directly asserted, but allowed by interface
                            .margin(0.25)
                            .scale(0.0);

    Approx around2 = configured(2.0);

    // Should honor the 0.25 margin copied from `configured`.
    EXPECT_TRUE(2.24 == around2);   // inside
    EXPECT_FALSE(2.26 == around2);  // just outside

    // Original remains independent.
    EXPECT_FALSE(2.0 == configured);
}

// Non-mutating behavior: operator() should not change the source Approx instance.
TEST_F(ApproxOperatorCallTest_692, DoesNotMutateSourceApprox_692) {
    Approx source = Approx::custom().margin(0.3);
    // Source targeted value (constructed via Approx::custom()) is implementation-defined,
    // but we can still verify non-mutation by:
    // 1) Deriving a new Approx `b` with operator() and testing `b` around its target.
    // 2) Showing that comparisons around `source` do not behave as if its target became 10.0.
    Approx b = source(10.0);

    // `b` acts as expected around 10.0 with margin 0.3
    EXPECT_TRUE(10.29 == b);
    EXPECT_FALSE(10.31 == b);

    // `source` should not suddenly act like it's centered at 10.0.
    EXPECT_FALSE(10.0 == source);
}
