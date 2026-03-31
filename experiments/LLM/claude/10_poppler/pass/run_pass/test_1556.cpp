#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashAbsTest_1556 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(SplashAbsTest_1556, PositiveValueReturnsItself_1556) {
    SplashCoord x = 5.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(SplashAbsTest_1556, NegativeValueReturnsPositive_1556) {
    SplashCoord x = -5.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(SplashAbsTest_1556, SmallPositiveValue_1556) {
    SplashCoord x = 0.001;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

TEST_F(SplashAbsTest_1556, SmallNegativeValue_1556) {
    SplashCoord x = -0.001;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

TEST_F(SplashAbsTest_1556, LargePositiveValue_1556) {
    SplashCoord x = 1e10;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 1e10);
}

TEST_F(SplashAbsTest_1556, LargeNegativeValue_1556) {
    SplashCoord x = -1e10;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 1e10);
}

TEST_F(SplashAbsTest_1556, FractionalPositiveValue_1556) {
    SplashCoord x = 3.14159;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 3.14159);
}

TEST_F(SplashAbsTest_1556, FractionalNegativeValue_1556) {
    SplashCoord x = -3.14159;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 3.14159);
}

// Boundary condition tests

TEST_F(SplashAbsTest_1556, ZeroReturnsZero_1556) {
    SplashCoord x = 0.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(SplashAbsTest_1556, NegativeZeroReturnsZero_1556) {
    SplashCoord x = -0.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(SplashAbsTest_1556, OneReturnsOne_1556) {
    SplashCoord x = 1.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST_F(SplashAbsTest_1556, NegativeOneReturnsOne_1556) {
    SplashCoord x = -1.0;
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST_F(SplashAbsTest_1556, VerySmallPositiveEpsilon_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::epsilon();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::epsilon());
}

TEST_F(SplashAbsTest_1556, VerySmallNegativeEpsilon_1556) {
    SplashCoord x = -std::numeric_limits<SplashCoord>::epsilon();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::epsilon());
}

TEST_F(SplashAbsTest_1556, MaxValueReturnsMax_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::max();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::max());
}

TEST_F(SplashAbsTest_1556, NegativeMaxValueReturnsMax_1556) {
    SplashCoord x = -std::numeric_limits<SplashCoord>::max();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::max());
}

TEST_F(SplashAbsTest_1556, MinPositiveValueReturnsItself_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::min();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::min());
}

TEST_F(SplashAbsTest_1556, DenormalizedMinReturnsItself_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::denorm_min();
    SplashCoord result = splashAbs(x);
    EXPECT_DOUBLE_EQ(result, std::numeric_limits<SplashCoord>::denorm_min());
}

// Special floating-point cases

TEST_F(SplashAbsTest_1556, PositiveInfinityReturnsInfinity_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashAbs(x);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

TEST_F(SplashAbsTest_1556, NegativeInfinityReturnsPositiveInfinity_1556) {
    SplashCoord x = -std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashAbs(x);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

TEST_F(SplashAbsTest_1556, NaNReturnsNaN_1556) {
    SplashCoord x = std::numeric_limits<SplashCoord>::quiet_NaN();
    SplashCoord result = splashAbs(x);
    EXPECT_TRUE(std::isnan(result));
}

// Symmetry test

TEST_F(SplashAbsTest_1556, SymmetryProperty_1556) {
    SplashCoord x = 42.5;
    EXPECT_DOUBLE_EQ(splashAbs(x), splashAbs(-x));
}

TEST_F(SplashAbsTest_1556, ResultIsAlwaysNonNegative_1556) {
    SplashCoord values[] = {-100.0, -1.0, -0.5, 0.0, 0.5, 1.0, 100.0};
    for (SplashCoord v : values) {
        EXPECT_GE(splashAbs(v), 0.0) << "Failed for value: " << v;
    }
}
