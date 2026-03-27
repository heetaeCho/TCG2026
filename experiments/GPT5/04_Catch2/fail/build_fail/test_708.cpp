// File: tests/approx_literal_a_708_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>

#include "catch2/catch_approx.hpp"  // Adjust include path if needed

using Catch::Approx;
using namespace Catch::literals; // enables the "_a" literal

// Compile-time: the literal must produce Catch::Approx
TEST(ApproxLiteralA_708, TypeIsApprox_708) {
    static_assert(std::is_same<decltype(1_a), Approx>::value,
                  "\"_a\" must yield Catch::Approx");
    // Also ensure it's constructible and usable at runtime
    auto v = 5_a;
    (void)v;
}

// Normal operation: equality with the same integer value
TEST(ApproxLiteralA_708, EqualsSameInteger_708) {
    EXPECT_TRUE(1.0 == 1_a);
    EXPECT_TRUE(42.0 == 42_a);
}

// Normal operation: works inside expressions (observable via operator==)
TEST(ApproxLiteralA_708, WorksInArithmeticExpression_708) {
    EXPECT_TRUE((40.0 + 2.0) == 42_a);
    EXPECT_TRUE((100.0 - 58.0) == 42_a);
}

// Boundary condition: zero
TEST(ApproxLiteralA_708, ZeroBoundary_708) {
    EXPECT_TRUE(0.0 == 0_a);
    EXPECT_FALSE(1.0 == 0_a); // clearly outside any reasonable default tolerance
}

// Boundary-ish (still safe): large ULL that’s exactly representable as double (2^53)
TEST(ApproxLiteralA_708, LargeExactlyRepresentableULL_708) {
    constexpr unsigned long long val = 9007199254740992ULL; // 2^53
    EXPECT_TRUE(static_cast<double>(val) == val_a);
}

// Error/negative check (observable inequality): far-apart values should not match
TEST(ApproxLiteralA_708, ClearlyNotEqual_708) {
    EXPECT_FALSE(100.0 == 1_a);
    EXPECT_FALSE((-10.0) == 1_a);
}

// API surface sanity: ULL suffix should bind to this literal (no narrowing at call site)
TEST(ApproxLiteralA_708, OverloadResolvesForULL_708) {
    unsigned long long u = 123ULL;
    auto approxFromULL = 123_a; // ensures the UDL taking ULL is used
    EXPECT_TRUE(static_cast<double>(u) == approxFromULL);
}
