#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <cmath>

// Include the necessary Exiv2 headers
#include "types.hpp"

namespace {

using Exiv2::Rational;
using Exiv2::floatToRationalCast;

// Helper to check that a rational approximately equals a float value
void ExpectRationalApproxEquals(float expected, Rational r, float tolerance = 1e-4f) {
    if (r.second == 0) {
        // Infinity case
        if (expected > 0) {
            EXPECT_GT(r.first, 0);
        } else {
            EXPECT_LT(r.first, 0);
        }
    } else {
        float actual = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(expected, actual, tolerance);
    }
}

// Test zero
TEST(FloatToRationalCastTest_1161, Zero_1161) {
    Rational r = floatToRationalCast(0.0f);
    EXPECT_EQ(r.first, 0);
    EXPECT_NE(r.second, 0); // denominator should not be zero for valid number
}

// Test positive integer
TEST(FloatToRationalCastTest_1161, PositiveInteger_1161) {
    Rational r = floatToRationalCast(5.0f);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

// Test negative integer
TEST(FloatToRationalCastTest_1161, NegativeInteger_1161) {
    Rational r = floatToRationalCast(-5.0f);
    EXPECT_EQ(r.first, -5);
    EXPECT_EQ(r.second, 1);
}

// Test positive one
TEST(FloatToRationalCastTest_1161, PositiveOne_1161) {
    Rational r = floatToRationalCast(1.0f);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 1);
}

// Test negative one
TEST(FloatToRationalCastTest_1161, NegativeOne_1161) {
    Rational r = floatToRationalCast(-1.0f);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 1);
}

// Test simple fraction 0.5
TEST(FloatToRationalCastTest_1161, Half_1161) {
    Rational r = floatToRationalCast(0.5f);
    ExpectRationalApproxEquals(0.5f, r);
    // 0.5 * 1000000 = 500000, gcd(500000, 1000000) = 500000 => 1/2
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test 0.25
TEST(FloatToRationalCastTest_1161, Quarter_1161) {
    Rational r = floatToRationalCast(0.25f);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 4);
}

// Test negative fraction
TEST(FloatToRationalCastTest_1161, NegativeHalf_1161) {
    Rational r = floatToRationalCast(-0.5f);
    ExpectRationalApproxEquals(-0.5f, r);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 2);
}

// Test small positive fraction
TEST(FloatToRationalCastTest_1161, SmallPositiveFraction_1161) {
    Rational r = floatToRationalCast(0.000001f);
    ExpectRationalApproxEquals(0.000001f, r, 1e-5f);
    EXPECT_GT(r.second, 0);
}

// Test a typical decimal like 3.14
TEST(FloatToRationalCastTest_1161, TypicalDecimal_1161) {
    Rational r = floatToRationalCast(3.14f);
    ExpectRationalApproxEquals(3.14f, r, 1e-4f);
    EXPECT_GT(r.second, 0);
}

// Test very large positive value exceeding int32_max => should return {1, 0}
TEST(FloatToRationalCastTest_1161, VeryLargePositive_1161) {
    float large = static_cast<float>(std::numeric_limits<int32_t>::max()) * 2.0f;
    Rational r = floatToRationalCast(large);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

// Test very large negative value exceeding int32_max => should return {-1, 0}
TEST(FloatToRationalCastTest_1161, VeryLargeNegative_1161) {
    float large = -static_cast<float>(std::numeric_limits<int32_t>::max()) * 2.0f;
    Rational r = floatToRationalCast(large);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 0);
}

// Test boundary: value just within int32_max range (den=1 path)
TEST(FloatToRationalCastTest_1161, BoundaryInt32MaxDen1_1161) {
    // A value that is <= int32_max but > int32_max/100
    float val = static_cast<float>(std::numeric_limits<int32_t>::max()) * 0.9f;
    Rational r = floatToRationalCast(val);
    // Should use den=1
    EXPECT_EQ(r.second, 1);
    ExpectRationalApproxEquals(val, r, val * 0.01f);
}

// Test boundary: value that uses den=100 path
TEST(FloatToRationalCastTest_1161, BoundaryDen100_1161) {
    // Value > int32_max/10000 but <= int32_max/100
    float val = static_cast<float>(std::numeric_limits<int32_t>::max()) / 100.0f * 0.9f;
    Rational r = floatToRationalCast(val);
    ExpectRationalApproxEquals(val, r, val * 0.01f);
    EXPECT_GT(r.second, 0);
}

// Test boundary: value that uses den=10000 path
TEST(FloatToRationalCastTest_1161, BoundaryDen10000_1161) {
    // Value > int32_max/1000000 but <= int32_max/10000
    float val = static_cast<float>(std::numeric_limits<int32_t>::max()) / 10000.0f * 0.9f;
    Rational r = floatToRationalCast(val);
    ExpectRationalApproxEquals(val, r, val * 0.001f);
    EXPECT_GT(r.second, 0);
}

// Test value that uses den=1000000 path (small value)
TEST(FloatToRationalCastTest_1161, SmallValueDen1000000_1161) {
    float val = 1.234567f;
    Rational r = floatToRationalCast(val);
    ExpectRationalApproxEquals(val, r, 1e-5f);
    EXPECT_GT(r.second, 0);
}

// Test 1/3 approximation
TEST(FloatToRationalCastTest_1161, OneThirdApprox_1161) {
    Rational r = floatToRationalCast(1.0f / 3.0f);
    ExpectRationalApproxEquals(1.0f / 3.0f, r, 1e-5f);
    EXPECT_GT(r.second, 0);
}

// Test GCD reduction: 0.5 should be reduced to 1/2, not 500000/1000000
TEST(FloatToRationalCastTest_1161, GCDReduction_1161) {
    Rational r = floatToRationalCast(0.5f);
    // After GCD reduction, this should be 1/2
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test 0.1
TEST(FloatToRationalCastTest_1161, PointOne_1161) {
    Rational r = floatToRationalCast(0.1f);
    ExpectRationalApproxEquals(0.1f, r, 1e-5f);
    EXPECT_GT(r.second, 0);
}

// Test negative zero (should behave like zero)
TEST(FloatToRationalCastTest_1161, NegativeZero_1161) {
    Rational r = floatToRationalCast(-0.0f);
    EXPECT_EQ(r.first, 0);
    EXPECT_NE(r.second, 0);
}

// Test very small positive number close to zero
TEST(FloatToRationalCastTest_1161, VerySmallPositive_1161) {
    Rational r = floatToRationalCast(1e-7f);
    // This is within int32_max / 1000000, so den = 1000000
    // 1e-7 * 1000000 = 0.1, rounds to 0
    EXPECT_EQ(r.first, 0);
    EXPECT_NE(r.second, 0);
}

// Test large positive float that is exactly at boundary (int32_max)
TEST(FloatToRationalCastTest_1161, ExactlyInt32Max_1161) {
    float val = static_cast<float>(std::numeric_limits<int32_t>::max());
    Rational r = floatToRationalCast(val);
    // fabs(d) <= int32_max, so den=1
    // But float representation of int32_max may not be exact
    EXPECT_GT(r.second, -1); // Just check it doesn't crash and returns something
}

// Test positive infinity => should return {1, 0}
TEST(FloatToRationalCastTest_1161, PositiveInfinity_1161) {
    float val = std::numeric_limits<float>::infinity();
    Rational r = floatToRationalCast(val);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

// Test negative infinity => should return {-1, 0}
TEST(FloatToRationalCastTest_1161, NegativeInfinity_1161) {
    float val = -std::numeric_limits<float>::infinity();
    Rational r = floatToRationalCast(val);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 0);
}

// Test that the rational has correct sign for positive values
TEST(FloatToRationalCastTest_1161, PositiveSign_1161) {
    Rational r = floatToRationalCast(2.5f);
    EXPECT_GT(r.first, 0);
    EXPECT_GT(r.second, 0);
}

// Test that the rational has correct sign for negative values
TEST(FloatToRationalCastTest_1161, NegativeSign_1161) {
    Rational r = floatToRationalCast(-2.5f);
    EXPECT_LT(r.first, 0);
    EXPECT_GT(r.second, 0);
}

// Test 0.75 = 3/4
TEST(FloatToRationalCastTest_1161, ThreeQuarters_1161) {
    Rational r = floatToRationalCast(0.75f);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

// Test 0.2 = 1/5
TEST(FloatToRationalCastTest_1161, OneFifth_1161) {
    Rational r = floatToRationalCast(0.2f);
    ExpectRationalApproxEquals(0.2f, r, 1e-5f);
    EXPECT_GT(r.second, 0);
}

// Test 100.0
TEST(FloatToRationalCastTest_1161, Hundred_1161) {
    Rational r = floatToRationalCast(100.0f);
    EXPECT_EQ(r.first, 100);
    EXPECT_EQ(r.second, 1);
}

// Test -100.0
TEST(FloatToRationalCastTest_1161, NegativeHundred_1161) {
    Rational r = floatToRationalCast(-100.0f);
    EXPECT_EQ(r.first, -100);
    EXPECT_EQ(r.second, 1);
}

} // namespace
