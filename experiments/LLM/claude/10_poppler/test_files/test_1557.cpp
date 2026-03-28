#include <gtest/gtest.h>
#include <cmath>
#include <climits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashFloorTest_1557 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test floor of positive integer value
TEST_F(SplashFloorTest_1557, PositiveIntegerValue_1557) {
    EXPECT_EQ(5, splashFloor(5.0));
}

// Test floor of negative integer value
TEST_F(SplashFloorTest_1557, NegativeIntegerValue_1557) {
    EXPECT_EQ(-5, splashFloor(-5.0));
}

// Test floor of zero
TEST_F(SplashFloorTest_1557, ZeroValue_1557) {
    EXPECT_EQ(0, splashFloor(0.0));
}

// Test floor of positive fractional value
TEST_F(SplashFloorTest_1557, PositiveFractionalValue_1557) {
    EXPECT_EQ(3, splashFloor(3.7));
}

// Test floor of negative fractional value
TEST_F(SplashFloorTest_1557, NegativeFractionalValue_1557) {
    EXPECT_EQ(-4, splashFloor(-3.7));
}

// Test floor of positive value just above an integer
TEST_F(SplashFloorTest_1557, PositiveJustAboveInteger_1557) {
    EXPECT_EQ(2, splashFloor(2.0001));
}

// Test floor of positive value just below an integer
TEST_F(SplashFloorTest_1557, PositiveJustBelowInteger_1557) {
    EXPECT_EQ(1, splashFloor(1.9999));
}

// Test floor of negative value just above an integer
TEST_F(SplashFloorTest_1557, NegativeJustAboveInteger_1557) {
    EXPECT_EQ(-2, splashFloor(-1.9999));
}

// Test floor of negative value just below an integer
TEST_F(SplashFloorTest_1557, NegativeJustBelowInteger_1557) {
    EXPECT_EQ(-3, splashFloor(-2.0001));
}

// Test floor of 0.5
TEST_F(SplashFloorTest_1557, PositiveHalf_1557) {
    EXPECT_EQ(0, splashFloor(0.5));
}

// Test floor of -0.5
TEST_F(SplashFloorTest_1557, NegativeHalf_1557) {
    EXPECT_EQ(-1, splashFloor(-0.5));
}

// Test floor of 1.0
TEST_F(SplashFloorTest_1557, OnePointZero_1557) {
    EXPECT_EQ(1, splashFloor(1.0));
}

// Test floor of -1.0
TEST_F(SplashFloorTest_1557, NegativeOnePointZero_1557) {
    EXPECT_EQ(-1, splashFloor(-1.0));
}

// Test floor of very small positive value
TEST_F(SplashFloorTest_1557, VerySmallPositive_1557) {
    EXPECT_EQ(0, splashFloor(0.0000001));
}

// Test floor of very small negative value
TEST_F(SplashFloorTest_1557, VerySmallNegative_1557) {
    EXPECT_EQ(-1, splashFloor(-0.0000001));
}

// Test floor of negative zero
TEST_F(SplashFloorTest_1557, NegativeZero_1557) {
    EXPECT_EQ(0, splashFloor(-0.0));
}

// Test floor of a large positive value
TEST_F(SplashFloorTest_1557, LargePositiveValue_1557) {
    EXPECT_EQ(100000, splashFloor(100000.99));
}

// Test floor of a large negative value
TEST_F(SplashFloorTest_1557, LargeNegativeValue_1557) {
    EXPECT_EQ(-100001, splashFloor(-100000.01));
}

// Test floor of value with fractional part exactly 0.25
TEST_F(SplashFloorTest_1557, FractionalQuarter_1557) {
    EXPECT_EQ(7, splashFloor(7.25));
}

// Test floor of value with fractional part exactly 0.75
TEST_F(SplashFloorTest_1557, FractionalThreeQuarters_1557) {
    EXPECT_EQ(7, splashFloor(7.75));
}

// Test floor of negative value with fractional part 0.25
TEST_F(SplashFloorTest_1557, NegativeFractionalQuarter_1557) {
    EXPECT_EQ(-8, splashFloor(-7.25));
}

// Test floor of negative value with fractional part 0.75
TEST_F(SplashFloorTest_1557, NegativeFractionalThreeQuarters_1557) {
    EXPECT_EQ(-8, splashFloor(-7.75));
}

// Test consistency with standard floor function for positive values
TEST_F(SplashFloorTest_1557, ConsistencyWithStdFloorPositive_1557) {
    for (double x = 0.1; x < 10.0; x += 0.3) {
        EXPECT_EQ((int)floor(x), splashFloor((SplashCoord)x))
            << "Failed for x = " << x;
    }
}

// Test consistency with standard floor function for negative values
TEST_F(SplashFloorTest_1557, ConsistencyWithStdFloorNegative_1557) {
    for (double x = -0.1; x > -10.0; x -= 0.3) {
        EXPECT_EQ((int)floor(x), splashFloor((SplashCoord)x))
            << "Failed for x = " << x;
    }
}

// Test floor of value 0.999...
TEST_F(SplashFloorTest_1557, AlmostOne_1557) {
    EXPECT_EQ(0, splashFloor(0.999999));
}

// Test floor of value -0.999...
TEST_F(SplashFloorTest_1557, AlmostNegativeOne_1557) {
    EXPECT_EQ(-1, splashFloor(-0.999999));
}
