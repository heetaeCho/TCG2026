// File: tests/test_approx_not_equal_696.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch_approx.hpp"  // Adjust include path if needed

using Catch::Approx;

class ApproxNotEqualTest_696 : public ::testing::Test {};

// Normal operation: clearly different values should compare "not equal"
TEST_F(ApproxNotEqualTest_696, FarApartValuesAreNotEqual_696) {
    Approx a = Approx(1.0);
    double v = 2.0;

    // Approx != T
    EXPECT_TRUE(a != v);
    // T != Approx (symmetry of availability)
    EXPECT_TRUE(v != a);

    // As a sanity check on negation relationship (observable via public ops)
    EXPECT_EQ(!(a == v), (a != v));
    EXPECT_EQ(!(v == a), (v != a));
}

// Boundary-ish via margin: within a user-set absolute margin should be equal, thus != false
TEST_F(ApproxNotEqualTest_696, WithinMarginIsEqualSoNotEqualIsFalse_696) {
    Approx a = Approx(1.0).margin(0.5); // do not reason about internals; just use public API
    double v = 1.4; // |1.4 - 1.0| = 0.4, inside the margin

    EXPECT_FALSE(a != v);
    EXPECT_FALSE(v != a);

    // Negation consistency
    EXPECT_EQ(a == v, !(a != v));
    EXPECT_EQ(v == a, !(v != a));
}

// Exact equality: identical numeric values should make != false
TEST_F(ApproxNotEqualTest_696, ExactEqualValuesYieldNotEqualFalse_696) {
    Approx a = Approx(42.0);
    int v = 42; // T constructible to double

    EXPECT_FALSE(a != v);
    EXPECT_FALSE(v != a);

    EXPECT_TRUE(a == v);
    EXPECT_TRUE(v == a);

    EXPECT_EQ(!(a == v), (a != v));
    EXPECT_EQ(!(v == a), (v != a));
}

// Type coverage: int and float work through the templated operator (constructible to double)
TEST_F(ApproxNotEqualTest_696, MixedTypesIntAndFloat_696) {
    Approx a = Approx(10.0).margin(0.25f);
    int vi = 10;
    float vf = 10.1f;

    // vi should be equal (=> != false), vf possibly outside unless covered by margin
    EXPECT_FALSE(a != vi);
    EXPECT_EQ(!(a == vi), (a != vi));

    // We only assert relationships observable via the interface.
    // If vf is inside margin, != should be false; otherwise true.
    // In either case, != must be a logical negation of ==.
    EXPECT_EQ(!(a == vf), (a != vf));
    EXPECT_EQ(!(vf == a), (vf != a));
}

// Exceptional-ish numeric case: NaN is not approximately equal to a finite value => != true
TEST_F(ApproxNotEqualTest_696, NaNComparedToFiniteIsNotEqual_696) {
    double nanv = std::numeric_limits<double>::quiet_NaN();
    Approx a = Approx(0.0).margin(1.0).epsilon(0.5).scale(0.0); // use public mutators only

    // We avoid asserting == directly with NaN semantics; we only assert observable != is true.
    EXPECT_TRUE(a != nanv);
    EXPECT_TRUE(nanv != a);

    // And still, != must be the negation of ==
    EXPECT_EQ(!(a == nanv), (a != nanv));
    EXPECT_EQ(!(nanv == a), (nanv != a));
}

// Strengthened symmetry check: both orders agree and negate ==
TEST_F(ApproxNotEqualTest_696, NegationAndOrderConsistency_696) {
    Approx left = Approx(3.0).margin(0.2);
    double right_close = 3.1;  // plausibly within margin
    double right_far   = 3.5;  // plausibly outside margin

    // Close
    EXPECT_EQ(!(left == right_close), (left != right_close));
    EXPECT_EQ(!(right_close == left), (right_close != left));
    // Far
    EXPECT_EQ(!(left == right_far), (left != right_far));
    EXPECT_EQ(!(right_far == left), (right_far != left));
}
