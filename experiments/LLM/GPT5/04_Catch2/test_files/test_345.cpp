// File: test_uniform_floating_point_distribution_b_345.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Use the header path provided in the prompt.
#include "Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"

namespace {

using std::numeric_limits;

//
// The tests below verify that the public accessor `b()` returns
// the upper bound value provided at construction, across types & edge cases.
// We do not assume or test any internal implementation details.
//

// Normal operation: distinct finite bounds
TEST(UniformFloatDistTest_345, ReturnsUpperBound_Double_345) {
    Catch::uniform_floating_point_distribution<double> dist(1.0, 3.5);
    EXPECT_DOUBLE_EQ(dist.b(), 3.5);
}

// Boundary: equal bounds (degenerate interval)
TEST(UniformFloatDistTest_345, ReturnsUpperBound_WhenBoundsEqual_345) {
    Catch::uniform_floating_point_distribution<double> dist(2.0, 2.0);
    EXPECT_DOUBLE_EQ(dist.b(), 2.0);
}

// Boundary: negative interval values
TEST(UniformFloatDistTest_345, ReturnsUpperBound_NegativeRange_345) {
    Catch::uniform_floating_point_distribution<double> dist(-5.0, -1.25);
    EXPECT_DOUBLE_EQ(dist.b(), -1.25);
}

// Boundary: positive infinity as upper bound (if constructible)
TEST(UniformFloatDistTest_345, ReturnsUpperBound_PositiveInfinity_345) {
    const double inf = numeric_limits<double>::infinity();
    Catch::uniform_floating_point_distribution<double> dist(-1.0, inf);
    EXPECT_TRUE(std::isinf(dist.b()));
    EXPECT_GT(dist.b(), 0.0);
}

// Type coverage: float
TEST(UniformFloatDistTest_345, ReturnsUpperBound_Float_345) {
    Catch::uniform_floating_point_distribution<float> dist(0.25f, 0.5f);
    EXPECT_FLOAT_EQ(dist.b(), 0.5f);
}

// Type coverage: long double
TEST(UniformFloatDistTest_345, ReturnsUpperBound_LongDouble_345) {
    long double a = static_cast<long double>(-0.125L);
    long double b = static_cast<long double>(123.456L);
    Catch::uniform_floating_point_distribution<long double> dist(a, b);
    EXPECT_EQ(dist.b(), b); // EXPECT_EQ is fine for exact long double literal here
}

// Const-correctness: b() callable on const reference
TEST(UniformFloatDistTest_345, BAccessorIsConst_345) {
    Catch::uniform_floating_point_distribution<double> dist(10.0, 20.0);
    const auto& cref = dist;
    EXPECT_DOUBLE_EQ(cref.b(), 20.0);
}

} // namespace
