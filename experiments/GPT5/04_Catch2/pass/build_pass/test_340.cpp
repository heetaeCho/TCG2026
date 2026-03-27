// File: count_equidistant_floats_tests_340.cpp
#include <gtest/gtest.h>
#include <cmath>
#include "Catch2/src/catch2/internal/catch_random_floating_point_helpers.hpp"

namespace CD = Catch::Detail;

//
// Normal operation: aligned endpoints and typical spans
//
TEST(CountEquidistantFloatsTest_340, Aligned_FromZero_CountsSteps_340) {
    const double a = 0.0, b = 3.0, d = 1.0;
    // When perfectly aligned at multiples of distance, it should count the step distance across [a,b]
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 3);
}

TEST(CountEquidistantFloatsTest_340, Aligned_NegativeToPositive_UnitDistance_340) {
    const double a = -2.0, b = 2.0, d = 1.0;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 4);
}

TEST(CountEquidistantFloatsTest_340, Aligned_HalfStepDistance_340) {
    const double a = 0.0, b = 1.0, d = 0.5;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 2);
}

//
// Boundary conditions
//
TEST(CountEquidistantFloatsTest_340, ZeroLengthInterval_ReturnsZero_340) {
    const double a = 1.2345, b = 1.2345, d = 0.5;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 0);
}

TEST(CountEquidistantFloatsTest_340, VerySmallSpan_StillCountsAtLeastOneIfNeeded_340) {
    const double a = 0.2, b = 0.4, d = 1.0;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 1);
}

TEST(CountEquidistantFloatsTest_340, NonAligned_SpansTwoUnits_340) {
    const double a = 0.2, b = 2.2, d = 1.0;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 3);
}

TEST(CountEquidistantFloatsTest_340, HalfStep_NonAligned_340) {
    const double a = 0.1, b = 1.1, d = 0.5;
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 3);
}

//
// Edge case: exact integer span but with non-aligned endpoints (triggers the internal tie-break path)
//
TEST(CountEquidistantFloatsTest_340, IntegerSpanWithNonAlignedEndpoints_340) {
    const double a = 0.2, b = 3.2, d = 1.0; // (b - a) / d == 3 exactly, but endpoints are not aligned to d
    auto result = CD::count_equidistant_floats<double>(a, b, d);
    EXPECT_EQ(result, 4);
}

//
// Exceptional / error-like observable behavior
// The function asserts that a <= b. In debug builds, this should abort.
// Guard with NDEBUG so release builds (where assert may be disabled) don't produce false negatives.
//
#ifndef NDEBUG
TEST(CountEquidistantFloatsTest_340, AssertsWhenAIsGreaterThanB_340) {
    const double a = 2.0, b = 1.0, d = 1.0;
    // Using ASSERT_DEATH to verify the debug assertion (a <= b)
    ASSERT_DEATH({ (void)CD::count_equidistant_floats<double>(a, b, d); }, "");
}
#endif
