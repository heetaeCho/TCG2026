#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Declaration based on the provided implementation
namespace Catch {
namespace Detail {
bool directCompare(double lhs, double rhs);
}
}

using Catch::Detail::directCompare;

// Normal operation tests

TEST(DirectCompareTest_609, EqualPositiveIntegers_609) {
    EXPECT_TRUE(directCompare(1.0, 1.0));
}

TEST(DirectCompareTest_609, EqualNegativeIntegers_609) {
    EXPECT_TRUE(directCompare(-1.0, -1.0));
}

TEST(DirectCompareTest_609, EqualZeros_609) {
    EXPECT_TRUE(directCompare(0.0, 0.0));
}

TEST(DirectCompareTest_609, EqualFractionalValues_609) {
    EXPECT_TRUE(directCompare(3.14, 3.14));
}

TEST(DirectCompareTest_609, UnequalPositiveValues_609) {
    EXPECT_FALSE(directCompare(1.0, 2.0));
}

TEST(DirectCompareTest_609, UnequalNegativeValues_609) {
    EXPECT_FALSE(directCompare(-1.0, -2.0));
}

TEST(DirectCompareTest_609, PositiveAndNegative_609) {
    EXPECT_FALSE(directCompare(1.0, -1.0));
}

TEST(DirectCompareTest_609, EqualLargeValues_609) {
    EXPECT_TRUE(directCompare(1e308, 1e308));
}

TEST(DirectCompareTest_609, EqualSmallValues_609) {
    EXPECT_TRUE(directCompare(1e-308, 1e-308));
}

// Boundary condition tests

TEST(DirectCompareTest_609, PositiveZeroAndNegativeZero_609) {
    // IEEE 754: +0.0 == -0.0 should be true
    EXPECT_TRUE(directCompare(0.0, -0.0));
}

TEST(DirectCompareTest_609, NegativeZeroAndPositiveZero_609) {
    EXPECT_TRUE(directCompare(-0.0, 0.0));
}

TEST(DirectCompareTest_609, MaxDoubleEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
}

TEST(DirectCompareTest_609, MinDoubleEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::min(), std::numeric_limits<double>::min()));
}

TEST(DirectCompareTest_609, LowestDoubleEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()));
}

TEST(DirectCompareTest_609, DenormalizedEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::denorm_min(), std::numeric_limits<double>::denorm_min()));
}

TEST(DirectCompareTest_609, DenormalizedAndZero_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::denorm_min(), 0.0));
}

TEST(DirectCompareTest_609, EpsilonEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()));
}

TEST(DirectCompareTest_609, EpsilonAndZero_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::epsilon(), 0.0));
}

// Infinity tests

TEST(DirectCompareTest_609, PositiveInfinityEqual_609) {
    EXPECT_TRUE(directCompare(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()));
}

TEST(DirectCompareTest_609, NegativeInfinityEqual_609) {
    EXPECT_TRUE(directCompare(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()));
}

TEST(DirectCompareTest_609, PositiveAndNegativeInfinity_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()));
}

TEST(DirectCompareTest_609, InfinityAndFinite_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::infinity(), 1.0));
}

TEST(DirectCompareTest_609, FiniteAndInfinity_609) {
    EXPECT_FALSE(directCompare(1.0, std::numeric_limits<double>::infinity()));
}

TEST(DirectCompareTest_609, InfinityAndMax_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max()));
}

// NaN tests

TEST(DirectCompareTest_609, NaNNotEqualToNaN_609) {
    // IEEE 754: NaN != NaN
    double nan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(directCompare(nan, nan));
}

TEST(DirectCompareTest_609, NaNNotEqualToZero_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::quiet_NaN(), 0.0));
}

TEST(DirectCompareTest_609, NaNNotEqualToOne_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::quiet_NaN(), 1.0));
}

TEST(DirectCompareTest_609, NaNNotEqualToInfinity_609) {
    EXPECT_FALSE(directCompare(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity()));
}

TEST(DirectCompareTest_609, SignalingNaNNotEqualToSignalingNaN_609) {
    double snan = std::numeric_limits<double>::signaling_NaN();
    EXPECT_FALSE(directCompare(snan, snan));
}

// Precision and near-equal tests

TEST(DirectCompareTest_609, CloseButNotEqualValues_609) {
    double a = 1.0;
    double b = 1.0 + std::numeric_limits<double>::epsilon();
    EXPECT_FALSE(directCompare(a, b));
}

TEST(DirectCompareTest_609, VeryCloseValuesNotEqual_609) {
    double a = 0.1 + 0.2;
    double b = 0.3;
    // Due to floating point representation, 0.1 + 0.2 != 0.3 typically
    // We just test that directCompare gives the same result as ==
    EXPECT_EQ(directCompare(a, b), (a == b));
}

TEST(DirectCompareTest_609, SameComputationYieldsEqual_609) {
    double a = 1.0 / 3.0;
    double b = 1.0 / 3.0;
    EXPECT_TRUE(directCompare(a, b));
}
