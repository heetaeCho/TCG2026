// directCompare_tests_609.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>

namespace Catch { namespace Detail {
    // Forward declaration of the function under test (interface only).
    bool directCompare(double lhs, double rhs);
}}

// Test suite: DirectCompareTest_609
using Catch::Detail::directCompare;

TEST(DirectCompareTest_609, EqualValues_ReturnsTrue_609) {
    EXPECT_TRUE(directCompare(42.0, 42.0));
    EXPECT_TRUE(directCompare(-13.5, -13.5));
    EXPECT_TRUE(directCompare(0.0, 0.0));
}

TEST(DirectCompareTest_609, UnequalValues_ReturnsFalse_609) {
    EXPECT_FALSE(directCompare(1.0, 2.0));
    EXPECT_FALSE(directCompare(-1.0, 1.0));
}

TEST(DirectCompareTest_609, PositiveAndNegativeZero_TreatedEqual_609) {
    const double posZero = 0.0;
    const double negZero = -0.0;
    // IEEE-754: +0.0 == -0.0 is true
    EXPECT_TRUE(directCompare(posZero, negZero));
    EXPECT_TRUE(directCompare(negZero, posZero));
}

TEST(DirectCompareTest_609, NaNComparedWithNaN_ReturnsFalse_609) {
    const double nanVal = std::numeric_limits<double>::quiet_NaN();
    // By definition, NaN == NaN is false
    EXPECT_FALSE(directCompare(nanVal, nanVal));
}

TEST(DirectCompareTest_609, NaNComparedWithNumber_ReturnsFalse_609) {
    const double nanVal = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(directCompare(nanVal, 0.0));
    EXPECT_FALSE(directCompare(1.0, nanVal));
}

TEST(DirectCompareTest_609, InfinityComparedWithItself_ReturnsTrue_609) {
    const double posInf = std::numeric_limits<double>::infinity();
    const double negInf = -std::numeric_limits<double>::infinity();

    EXPECT_TRUE(directCompare(posInf, posInf));
    EXPECT_TRUE(directCompare(negInf, negInf));
}

TEST(DirectCompareTest_609, PositiveInfinityVsNegativeInfinity_ReturnsFalse_609) {
    const double posInf = std::numeric_limits<double>::infinity();
    const double negInf = -std::numeric_limits<double>::infinity();

    EXPECT_FALSE(directCompare(posInf, negInf));
    EXPECT_FALSE(directCompare(negInf, posInf));
}

TEST(DirectCompareTest_609, VeryCloseButNotEqual_ReturnsFalse_609) {
    // Two representable doubles that are close but not bitwise-equal
    const double a = 1.0;
    const double b = std::nextafter(1.0, 2.0); // the next representable double > 1.0
    ASSERT_NE(a, b); // Guard to ensure the test is meaningful
    EXPECT_FALSE(directCompare(a, b));
}

TEST(DirectCompareTest_609, Symmetry_PropertyHolds_609) {
    const double x = 123.456;
    const double y = 789.012;
    EXPECT_EQ(directCompare(x, y), directCompare(y, x));
    EXPECT_EQ(directCompare(x, x), directCompare(x, x));
}
