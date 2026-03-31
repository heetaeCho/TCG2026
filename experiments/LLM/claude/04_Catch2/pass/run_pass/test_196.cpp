#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>

#include "catch2/internal/catch_floating_point_helpers.hpp"

// ============================================================
// Tests for ulpDistance with double
// ============================================================

class UlpDistanceDoubleTest_196 : public ::testing::Test {};

// Normal operation: identical values should have zero ULP distance
TEST_F(UlpDistanceDoubleTest_196, IdenticalValuesReturnZero_196) {
    EXPECT_EQ(Catch::ulpDistance(1.0, 1.0), 0u);
    EXPECT_EQ(Catch::ulpDistance(-1.0, -1.0), 0u);
    EXPECT_EQ(Catch::ulpDistance(0.0, 0.0), 0u);
    EXPECT_EQ(Catch::ulpDistance(123.456, 123.456), 0u);
}

// Normal operation: positive zero and negative zero should have zero distance
TEST_F(UlpDistanceDoubleTest_196, PositiveZeroAndNegativeZeroReturnZero_196) {
    EXPECT_EQ(Catch::ulpDistance(0.0, -0.0), 0u);
    EXPECT_EQ(Catch::ulpDistance(-0.0, 0.0), 0u);
}

// Normal operation: adjacent doubles should have ULP distance of 1
TEST_F(UlpDistanceDoubleTest_196, AdjacentDoublesHaveDistanceOne_196) {
    double a = 1.0;
    double b = std::nextafter(1.0, 2.0);
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Normal operation: distance is symmetric
TEST_F(UlpDistanceDoubleTest_196, DistanceIsSymmetric_196) {
    double a = 1.0;
    double b = std::nextafter(std::nextafter(1.0, 2.0), 2.0);
    EXPECT_EQ(Catch::ulpDistance(a, b), Catch::ulpDistance(b, a));
}

// Normal operation: distance of N nextafter steps should be N
TEST_F(UlpDistanceDoubleTest_196, MultipleUlpSteps_196) {
    double a = 1.0;
    double b = a;
    for (int i = 0; i < 10; ++i) {
        b = std::nextafter(b, 2.0);
    }
    EXPECT_EQ(Catch::ulpDistance(a, b), 10u);
}

// Boundary: very small positive numbers near zero
TEST_F(UlpDistanceDoubleTest_196, SmallPositiveNumbersNearZero_196) {
    double a = std::numeric_limits<double>::denorm_min();
    double b = 0.0;
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Boundary: smallest denormalized doubles
TEST_F(UlpDistanceDoubleTest_196, DenormalizedNumbers_196) {
    double a = std::numeric_limits<double>::denorm_min();
    double b = 2.0 * std::numeric_limits<double>::denorm_min();
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Cross-sign: small positive and small negative should sum distances from zero
TEST_F(UlpDistanceDoubleTest_196, CrossSignDistance_196) {
    double a = std::numeric_limits<double>::denorm_min();
    double b = -std::numeric_limits<double>::denorm_min();
    // Each is 1 ULP from zero, so total should be 2
    EXPECT_EQ(Catch::ulpDistance(a, b), 2u);
}

// Cross-sign: larger values across zero
TEST_F(UlpDistanceDoubleTest_196, CrossSignLargerValues_196) {
    double a = 1.0;
    double b = -1.0;
    uint64_t dist_a_zero = Catch::ulpDistance(a, 0.0);
    uint64_t dist_b_zero = Catch::ulpDistance(b, 0.0);
    EXPECT_EQ(Catch::ulpDistance(a, b), dist_a_zero + dist_b_zero);
}

// Normal operation: negative adjacent doubles
TEST_F(UlpDistanceDoubleTest_196, NegativeAdjacentDoubles_196) {
    double a = -1.0;
    double b = std::nextafter(-1.0, -2.0);
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Boundary: max double value distance from itself
TEST_F(UlpDistanceDoubleTest_196, MaxDoubleToItself_196) {
    double maxd = std::numeric_limits<double>::max();
    EXPECT_EQ(Catch::ulpDistance(maxd, maxd), 0u);
}

// Boundary: max and one step below max
TEST_F(UlpDistanceDoubleTest_196, MaxDoubleToNextBelow_196) {
    double maxd = std::numeric_limits<double>::max();
    double below = std::nextafter(maxd, 0.0);
    EXPECT_EQ(Catch::ulpDistance(maxd, below), 1u);
}

// Normal: distance from positive zero to denorm_min
TEST_F(UlpDistanceDoubleTest_196, ZeroToDenormMin_196) {
    EXPECT_EQ(Catch::ulpDistance(0.0, std::numeric_limits<double>::denorm_min()), 1u);
}

// Normal: distance from negative zero to negative denorm_min
TEST_F(UlpDistanceDoubleTest_196, NegativeZeroToNegativeDenormMin_196) {
    EXPECT_EQ(Catch::ulpDistance(-0.0, -std::numeric_limits<double>::denorm_min()), 1u);
}

// Verify distance across exponent boundary
TEST_F(UlpDistanceDoubleTest_196, AcrossExponentBoundary_196) {
    // From just below 2.0 to 2.0
    double below2 = std::nextafter(2.0, 1.0);
    EXPECT_EQ(Catch::ulpDistance(below2, 2.0), 1u);
}

// ============================================================
// Tests for ulpDistance with float
// ============================================================

class UlpDistanceFloatTest_196 : public ::testing::Test {};

// Normal operation: identical float values
TEST_F(UlpDistanceFloatTest_196, IdenticalValuesReturnZero_196) {
    EXPECT_EQ(Catch::ulpDistance(1.0f, 1.0f), 0u);
    EXPECT_EQ(Catch::ulpDistance(-1.0f, -1.0f), 0u);
    EXPECT_EQ(Catch::ulpDistance(0.0f, 0.0f), 0u);
}

// Normal: positive and negative zero
TEST_F(UlpDistanceFloatTest_196, FloatPositiveAndNegativeZero_196) {
    EXPECT_EQ(Catch::ulpDistance(0.0f, -0.0f), 0u);
    EXPECT_EQ(Catch::ulpDistance(-0.0f, 0.0f), 0u);
}

// Normal: adjacent floats
TEST_F(UlpDistanceFloatTest_196, AdjacentFloats_196) {
    float a = 1.0f;
    float b = std::nextafter(1.0f, 2.0f);
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Normal: multiple ULP steps for float
TEST_F(UlpDistanceFloatTest_196, MultipleUlpStepsFloat_196) {
    float a = 1.0f;
    float b = a;
    for (int i = 0; i < 5; ++i) {
        b = std::nextafter(b, 2.0f);
    }
    EXPECT_EQ(Catch::ulpDistance(a, b), 5u);
}

// Symmetric for floats
TEST_F(UlpDistanceFloatTest_196, FloatSymmetric_196) {
    float a = 1.0f;
    float b = std::nextafter(std::nextafter(1.0f, 2.0f), 2.0f);
    EXPECT_EQ(Catch::ulpDistance(a, b), Catch::ulpDistance(b, a));
}

// Cross-sign for floats
TEST_F(UlpDistanceFloatTest_196, FloatCrossSign_196) {
    float a = std::numeric_limits<float>::denorm_min();
    float b = -std::numeric_limits<float>::denorm_min();
    EXPECT_EQ(Catch::ulpDistance(a, b), 2u);
}

// Float: zero to denorm_min
TEST_F(UlpDistanceFloatTest_196, FloatZeroToDenormMin_196) {
    EXPECT_EQ(Catch::ulpDistance(0.0f, std::numeric_limits<float>::denorm_min()), 1u);
}

// Float: max float to itself
TEST_F(UlpDistanceFloatTest_196, FloatMaxToItself_196) {
    float maxf = std::numeric_limits<float>::max();
    EXPECT_EQ(Catch::ulpDistance(maxf, maxf), 0u);
}

// Float: max to one below max
TEST_F(UlpDistanceFloatTest_196, FloatMaxToNextBelow_196) {
    float maxf = std::numeric_limits<float>::max();
    float below = std::nextafter(maxf, 0.0f);
    EXPECT_EQ(Catch::ulpDistance(maxf, below), 1u);
}

// Float: negative adjacent
TEST_F(UlpDistanceFloatTest_196, FloatNegativeAdjacent_196) {
    float a = -1.0f;
    float b = std::nextafter(-1.0f, -2.0f);
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Float cross-sign larger values
TEST_F(UlpDistanceFloatTest_196, FloatCrossSignLargerValues_196) {
    float a = 1.0f;
    float b = -1.0f;
    uint64_t dist_a = Catch::ulpDistance(a, 0.0f);
    uint64_t dist_b = Catch::ulpDistance(b, 0.0f);
    EXPECT_EQ(Catch::ulpDistance(a, b), dist_a + dist_b);
}

// Double: infinity to max should be exactly 1
TEST_F(UlpDistanceDoubleTest_196, InfinityToMax_196) {
    double inf = std::numeric_limits<double>::infinity();
    double maxd = std::numeric_limits<double>::max();
    EXPECT_EQ(Catch::ulpDistance(inf, maxd), 1u);
}

// Float: infinity to max should be exactly 1
TEST_F(UlpDistanceFloatTest_196, FloatInfinityToMax_196) {
    float inf = std::numeric_limits<float>::infinity();
    float maxf = std::numeric_limits<float>::max();
    EXPECT_EQ(Catch::ulpDistance(inf, maxf), 1u);
}

// Double: infinity to itself
TEST_F(UlpDistanceDoubleTest_196, InfinityToItself_196) {
    double inf = std::numeric_limits<double>::infinity();
    EXPECT_EQ(Catch::ulpDistance(inf, inf), 0u);
}

// Double: negative infinity to itself
TEST_F(UlpDistanceDoubleTest_196, NegativeInfinityToItself_196) {
    double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_EQ(Catch::ulpDistance(neg_inf, neg_inf), 0u);
}

// Double: epsilon from 1.0
TEST_F(UlpDistanceDoubleTest_196, EpsilonFrom1_196) {
    double a = 1.0;
    double b = 1.0 + std::numeric_limits<double>::epsilon();
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}

// Float: epsilon from 1.0f
TEST_F(UlpDistanceFloatTest_196, FloatEpsilonFrom1_196) {
    float a = 1.0f;
    float b = 1.0f + std::numeric_limits<float>::epsilon();
    EXPECT_EQ(Catch::ulpDistance(a, b), 1u);
}
