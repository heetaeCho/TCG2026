#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
    bool isnan(float f);
}

// Normal operation tests
TEST(CatchIsnanTest_635, RegularPositiveNumberIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(1.0f));
}

TEST(CatchIsnanTest_635, RegularNegativeNumberIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(-1.0f));
}

TEST(CatchIsnanTest_635, ZeroIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(0.0f));
}

TEST(CatchIsnanTest_635, NegativeZeroIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(-0.0f));
}

TEST(CatchIsnanTest_635, NaNReturnsTrue_635) {
    EXPECT_TRUE(Catch::isnan(std::nanf("")));
}

TEST(CatchIsnanTest_635, QuietNaNReturnsTrue_635) {
    EXPECT_TRUE(Catch::isnan(std::numeric_limits<float>::quiet_NaN()));
}

TEST(CatchIsnanTest_635, SignalingNaNReturnsTrue_635) {
    EXPECT_TRUE(Catch::isnan(std::numeric_limits<float>::signaling_NaN()));
}

// Boundary condition tests
TEST(CatchIsnanTest_635, PositiveInfinityIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::infinity()));
}

TEST(CatchIsnanTest_635, NegativeInfinityIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(-std::numeric_limits<float>::infinity()));
}

TEST(CatchIsnanTest_635, MaxFloatIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::max()));
}

TEST(CatchIsnanTest_635, MinFloatIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::min()));
}

TEST(CatchIsnanTest_635, LowestFloatIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::lowest()));
}

TEST(CatchIsnanTest_635, DenormMinIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::denorm_min()));
}

TEST(CatchIsnanTest_635, EpsilonIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::epsilon()));
}

// NaN generated via arithmetic
TEST(CatchIsnanTest_635, NaNFromArithmeticReturnsTrue_635) {
    float result = 0.0f / 0.0f;
    EXPECT_TRUE(Catch::isnan(result));
}

TEST(CatchIsnanTest_635, NaNFromInfinityMinusInfinityReturnsTrue_635) {
    float inf = std::numeric_limits<float>::infinity();
    float result = inf - inf;
    EXPECT_TRUE(Catch::isnan(result));
}

TEST(CatchIsnanTest_635, SmallPositiveValueIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(1e-38f));
}

TEST(CatchIsnanTest_635, LargePositiveValueIsNotNaN_635) {
    EXPECT_FALSE(Catch::isnan(1e38f));
}
