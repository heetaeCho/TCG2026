#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_random_floating_point_helpers.hpp"

// Test fixture for gamma function tests
class GammaTest_339 : public ::testing::Test {
protected:
    // Helper to get the ULP at a given float value (going upward)
    template <typename T>
    T ulp_up(T val) {
        return std::nextafter(val, std::numeric_limits<T>::infinity()) - val;
    }

    // Helper to get the ULP at a given float value (going downward)
    template <typename T>
    T ulp_down(T val) {
        return val - std::nextafter(val, -std::numeric_limits<T>::infinity());
    }
};

// Test: gamma with identical endpoints (a == b) for double
TEST_F(GammaTest_339, SameEndpointsDouble_339) {
    double val = 1.0;
    double result = Catch::Detail::gamma(val, val);
    // When a == b, gamma_up = nextafter(a, +inf) - a, gamma_down = b - nextafter(b, -inf)
    // Result should be max of those two
    double expected_up = ulp_up(val);
    double expected_down = ulp_down(val);
    double expected = std::max(expected_up, expected_down);
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma with identical endpoints (a == b) for float
TEST_F(GammaTest_339, SameEndpointsFloat_339) {
    float val = 1.0f;
    float result = Catch::Detail::gamma(val, val);
    float expected_up = ulp_up(val);
    float expected_down = ulp_down(val);
    float expected = std::max(expected_up, expected_down);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test: gamma with zero endpoints
TEST_F(GammaTest_339, ZeroEndpoints_339) {
    double result = Catch::Detail::gamma(0.0, 0.0);
    // At 0, the ULP going up is the smallest subnormal
    // The ULP going down is also the smallest subnormal (nextafter(0, -inf) = -min_subnormal)
    // So gamma_down = 0 - (-min_subnormal) = min_subnormal
    // gamma_up = min_subnormal - 0 = min_subnormal
    // They should be equal
    double expected = std::numeric_limits<double>::denorm_min();
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma at 1.0 for double
TEST_F(GammaTest_339, AtOneDouble_339) {
    double result = Catch::Detail::gamma(1.0, 1.0);
    EXPECT_GT(result, 0.0);
}

// Test: gamma with a small range around 1.0
TEST_F(GammaTest_339, SmallRangeAroundOneDouble_339) {
    double a = 1.0;
    double b = 1.0 + 1e-10;
    double result = Catch::Detail::gamma(a, b);
    // Should return the max ULP magnitude in [a, b]
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    double expected = std::max(gamma_up, gamma_down);
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma with large values for double
TEST_F(GammaTest_339, LargeValuesDouble_339) {
    double a = 1e15;
    double b = 1e15 + 1.0;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    double expected = std::max(gamma_up, gamma_down);
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma with negative range
TEST_F(GammaTest_339, NegativeRange_339) {
    double a = -2.0;
    double b = -1.0;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    double expected = std::max(gamma_up, gamma_down);
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma with range crossing zero
TEST_F(GammaTest_339, RangeCrossingZero_339) {
    double a = -1.0;
    double b = 1.0;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    double expected = std::max(gamma_up, gamma_down);
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test: gamma result is always positive
TEST_F(GammaTest_339, ResultAlwaysPositive_339) {
    EXPECT_GT(Catch::Detail::gamma(0.0, 0.0), 0.0);
    EXPECT_GT(Catch::Detail::gamma(1.0, 2.0), 0.0);
    EXPECT_GT(Catch::Detail::gamma(-1.0, 0.0), 0.0);
    EXPECT_GT(Catch::Detail::gamma(-2.0, -1.0), 0.0);
}

// Test: gamma with very small positive values (subnormals)
TEST_F(GammaTest_339, SubnormalRange_339) {
    double a = std::numeric_limits<double>::denorm_min();
    double b = std::numeric_limits<double>::denorm_min() * 2;
    double result = Catch::Detail::gamma(a, b);
    EXPECT_GT(result, 0.0);
}

// Test: gamma with float type
TEST_F(GammaTest_339, FloatRange_339) {
    float a = 1.0f;
    float b = 2.0f;
    float result = Catch::Detail::gamma(a, b);
    float gamma_up = ulp_up(a);
    float gamma_down = ulp_down(b);
    float expected = std::max(gamma_up, gamma_down);
    EXPECT_FLOAT_EQ(result, expected);
}

// Test: gamma where gamma_up is larger (near power of 2 boundary going up)
TEST_F(GammaTest_339, GammaUpLargerAtPowerOfTwo_339) {
    // At a power of 2, the ULP on the upper side is larger than on the lower side
    double a = 2.0;
    double b = 2.0;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    // At exactly 2.0, gamma_up should be twice gamma_down
    EXPECT_DOUBLE_EQ(result, std::max(gamma_up, gamma_down));
}

// Test: gamma where gamma_down is larger (just below a power of 2)
TEST_F(GammaTest_339, GammaDownLargerBelowPowerOfTwo_339) {
    // Just below a power of 2, the ULP on the lower side is larger
    double val = std::nextafter(2.0, -std::numeric_limits<double>::infinity());
    double a = val;
    double b = 2.0;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    EXPECT_DOUBLE_EQ(result, std::max(gamma_up, gamma_down));
}

// Test: gamma with max double value as b
TEST_F(GammaTest_339, MaxDoubleAsB_339) {
    double a = std::numeric_limits<double>::max();
    double b = std::numeric_limits<double>::max();
    double result = Catch::Detail::gamma(a, b);
    // gamma_up at max will be infinity - max = infinity, but the function uses nextafter
    // nextafter(max, +inf) = infinity, so gamma_up = inf - max = inf
    // This is an edge case; just verify it doesn't crash and returns something
    EXPECT_GT(result, 0.0);
}

// Test: gamma with smallest normal value
TEST_F(GammaTest_339, SmallestNormalValue_339) {
    double a = std::numeric_limits<double>::min();
    double b = std::numeric_limits<double>::min();
    double result = Catch::Detail::gamma(a, b);
    EXPECT_GT(result, 0.0);
}

// Test: gamma symmetry property - gamma(a,b) >= max(ulp(a), ulp(b)) at boundaries
TEST_F(GammaTest_339, GammaIsMaxOfBoundaryULPs_339) {
    double a = 3.14;
    double b = 3.15;
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    EXPECT_DOUBLE_EQ(result, std::max(gamma_up, gamma_down));
}

// Test: gamma with negative zero
TEST_F(GammaTest_339, NegativeZero_339) {
    double a = -0.0;
    double b = 0.0;
    double result = Catch::Detail::gamma(a, b);
    EXPECT_GT(result, 0.0);
}

// Test: gamma with wide range
TEST_F(GammaTest_339, WideRange_339) {
    double a = 1.0;
    double b = 1e10;
    double result = Catch::Detail::gamma(a, b);
    // The gamma should be determined by the larger ULP, which is at b
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    EXPECT_DOUBLE_EQ(result, std::max(gamma_up, gamma_down));
}

// Test: gamma with adjacent floating point values
TEST_F(GammaTest_339, AdjacentValues_339) {
    double a = 1.0;
    double b = std::nextafter(1.0, std::numeric_limits<double>::infinity());
    double result = Catch::Detail::gamma(a, b);
    double gamma_up = ulp_up(a);
    double gamma_down = ulp_down(b);
    EXPECT_DOUBLE_EQ(result, std::max(gamma_up, gamma_down));
}
