#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Declaration based on the provided implementation
namespace Catch {
namespace Detail {
    bool directCompare(float lhs, float rhs);
}
}

// Normal operation tests

TEST(DirectCompareTest_608, EqualPositiveIntegers_608) {
    EXPECT_TRUE(Catch::Detail::directCompare(1.0f, 1.0f));
}

TEST(DirectCompareTest_608, EqualNegativeIntegers_608) {
    EXPECT_TRUE(Catch::Detail::directCompare(-5.0f, -5.0f));
}

TEST(DirectCompareTest_608, EqualFractionalValues_608) {
    EXPECT_TRUE(Catch::Detail::directCompare(0.5f, 0.5f));
}

TEST(DirectCompareTest_608, DifferentValues_608) {
    EXPECT_FALSE(Catch::Detail::directCompare(1.0f, 2.0f));
}

TEST(DirectCompareTest_608, DifferentSignValues_608) {
    EXPECT_FALSE(Catch::Detail::directCompare(1.0f, -1.0f));
}

TEST(DirectCompareTest_608, BothZero_608) {
    EXPECT_TRUE(Catch::Detail::directCompare(0.0f, 0.0f));
}

TEST(DirectCompareTest_608, PositiveZeroAndNegativeZero_608) {
    // IEEE 754: +0.0 == -0.0 is true
    EXPECT_TRUE(Catch::Detail::directCompare(0.0f, -0.0f));
}

TEST(DirectCompareTest_608, NegativeZeroAndPositiveZero_608) {
    EXPECT_TRUE(Catch::Detail::directCompare(-0.0f, 0.0f));
}

// Boundary conditions

TEST(DirectCompareTest_608, MaxFloatEqual_608) {
    float maxVal = std::numeric_limits<float>::max();
    EXPECT_TRUE(Catch::Detail::directCompare(maxVal, maxVal));
}

TEST(DirectCompareTest_608, MinFloatEqual_608) {
    float minVal = std::numeric_limits<float>::min();
    EXPECT_TRUE(Catch::Detail::directCompare(minVal, minVal));
}

TEST(DirectCompareTest_608, LowestFloatEqual_608) {
    float lowestVal = std::numeric_limits<float>::lowest();
    EXPECT_TRUE(Catch::Detail::directCompare(lowestVal, lowestVal));
}

TEST(DirectCompareTest_608, DenormalizedEqual_608) {
    float denorm = std::numeric_limits<float>::denorm_min();
    EXPECT_TRUE(Catch::Detail::directCompare(denorm, denorm));
}

TEST(DirectCompareTest_608, EpsilonEqual_608) {
    float eps = std::numeric_limits<float>::epsilon();
    EXPECT_TRUE(Catch::Detail::directCompare(eps, eps));
}

TEST(DirectCompareTest_608, InfinityEqual_608) {
    float inf = std::numeric_limits<float>::infinity();
    EXPECT_TRUE(Catch::Detail::directCompare(inf, inf));
}

TEST(DirectCompareTest_608, NegativeInfinityEqual_608) {
    float negInf = -std::numeric_limits<float>::infinity();
    EXPECT_TRUE(Catch::Detail::directCompare(negInf, negInf));
}

TEST(DirectCompareTest_608, PositiveInfinityVsNegativeInfinity_608) {
    float posInf = std::numeric_limits<float>::infinity();
    float negInf = -std::numeric_limits<float>::infinity();
    EXPECT_FALSE(Catch::Detail::directCompare(posInf, negInf));
}

TEST(DirectCompareTest_608, InfinityVsMaxFloat_608) {
    float inf = std::numeric_limits<float>::infinity();
    float maxVal = std::numeric_limits<float>::max();
    EXPECT_FALSE(Catch::Detail::directCompare(inf, maxVal));
}

// NaN behavior

TEST(DirectCompareTest_608, NaNNotEqualToNaN_608) {
    float nan = std::numeric_limits<float>::quiet_NaN();
    // IEEE 754: NaN != NaN
    EXPECT_FALSE(Catch::Detail::directCompare(nan, nan));
}

TEST(DirectCompareTest_608, NaNNotEqualToZero_608) {
    float nan = std::numeric_limits<float>::quiet_NaN();
    EXPECT_FALSE(Catch::Detail::directCompare(nan, 0.0f));
}

TEST(DirectCompareTest_608, NaNNotEqualToOne_608) {
    float nan = std::numeric_limits<float>::quiet_NaN();
    EXPECT_FALSE(Catch::Detail::directCompare(nan, 1.0f));
}

TEST(DirectCompareTest_608, SignalingNaNNotEqualToItself_608) {
    float snan = std::numeric_limits<float>::signaling_NaN();
    EXPECT_FALSE(Catch::Detail::directCompare(snan, snan));
}

// Near values that are not equal

TEST(DirectCompareTest_608, CloseButNotEqual_608) {
    float a = 1.0f;
    float b = 1.0f + std::numeric_limits<float>::epsilon();
    EXPECT_FALSE(Catch::Detail::directCompare(a, b));
}

TEST(DirectCompareTest_608, VerySmallDifference_608) {
    float a = 0.1f;
    float b = 0.1f;
    EXPECT_TRUE(Catch::Detail::directCompare(a, b));
}

TEST(DirectCompareTest_608, FloatingPointRepresentationIssue_608) {
    // 0.1 + 0.2 may not equal 0.3 in floating point
    float sum = 0.1f + 0.2f;
    float expected = 0.3f;
    // This tests the direct bitwise comparison behavior
    // The result depends on floating point arithmetic
    bool result = Catch::Detail::directCompare(sum, expected);
    EXPECT_EQ(result, (sum == expected));
}

TEST(DirectCompareTest_608, LargeValuesEqual_608) {
    float large = 1.0e38f;
    EXPECT_TRUE(Catch::Detail::directCompare(large, large));
}

TEST(DirectCompareTest_608, LargeValuesDifferent_608) {
    float a = 1.0e38f;
    float b = 1.0e37f;
    EXPECT_FALSE(Catch::Detail::directCompare(a, b));
}
