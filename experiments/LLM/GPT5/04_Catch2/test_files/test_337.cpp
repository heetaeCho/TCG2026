// File: tests/uniform_integer_distribution_a_tests_337.cpp

#include <gtest/gtest.h>
#include <limits>
#include "catch2/internal/catch_uniform_integer_distribution.hpp"

using Catch::uniform_integer_distribution;

// Verifies that a() returns the lower bound for a typical positive range.
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundForPositiveRange_337) {
    uniform_integer_distribution<int> dist(3, 10);
    EXPECT_EQ(dist.a(), 3);
}

// Verifies that a() returns the lower bound for a negative range.
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundForNegativeRange_337) {
    uniform_integer_distribution<int> dist(-10, -3);
    EXPECT_EQ(dist.a(), -10);
}

// Verifies that a() returns the bound when a == b (degenerate/singleton range).
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundWhenEqualBounds_337) {
    uniform_integer_distribution<int> dist(42, 42);
    EXPECT_EQ(dist.a(), 42);
}

// Boundary: minimal int as lower bound should be observable via a().
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundAtIntMin_337) {
    const int amin = std::numeric_limits<int>::min();
    uniform_integer_distribution<int> dist(amin, amin + 5);
    EXPECT_EQ(dist.a(), amin);
}

// Boundary: large mixed-sign range; a() should still return the provided lower bound.
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundForMixedSignRange_337) {
    uniform_integer_distribution<int> dist(-1000000, 2000000);
    EXPECT_EQ(dist.a(), -1000000);
}

// Unsigned type: a() should return the unsigned lower bound unchanged.
TEST(UniformIntegerDistributionTest_337, ReturnsLowerBoundForUnsignedRange_337) {
    uniform_integer_distribution<unsigned int> dist(5u, 20u);
    EXPECT_EQ(dist.a(), 5u);
}
