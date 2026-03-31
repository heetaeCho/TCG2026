#include <gtest/gtest.h>

// Include necessary headers
#include "poppler/GfxState.h"
#include "poppler/GfxState_helpers.h"

class Clip01Test_1881 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(Clip01Test_1881, ZeroReturnsZero_1881) {
    GfxColorComp result = clip01(0);
    EXPECT_EQ(result, 0);
}

TEST_F(Clip01Test_1881, MaxValueReturnsMax_1881) {
    GfxColorComp result = clip01(gfxColorComp1);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, MidValueReturnsSame_1881) {
    GfxColorComp midValue = gfxColorComp1 / 2;
    GfxColorComp result = clip01(midValue);
    EXPECT_EQ(result, midValue);
}

TEST_F(Clip01Test_1881, QuarterValueReturnsSame_1881) {
    GfxColorComp quarterValue = gfxColorComp1 / 4;
    GfxColorComp result = clip01(quarterValue);
    EXPECT_EQ(result, quarterValue);
}

TEST_F(Clip01Test_1881, ThreeQuarterValueReturnsSame_1881) {
    GfxColorComp threeQuarterValue = (gfxColorComp1 * 3) / 4;
    GfxColorComp result = clip01(threeQuarterValue);
    EXPECT_EQ(result, threeQuarterValue);
}

TEST_F(Clip01Test_1881, OneReturnsSame_1881) {
    GfxColorComp result = clip01(1);
    EXPECT_EQ(result, 1);
}

TEST_F(Clip01Test_1881, ValueJustBelowMaxReturnsSame_1881) {
    GfxColorComp result = clip01(gfxColorComp1 - 1);
    EXPECT_EQ(result, gfxColorComp1 - 1);
}

// Boundary condition tests

TEST_F(Clip01Test_1881, NegativeValueClipsToZero_1881) {
    GfxColorComp result = clip01(-1);
    EXPECT_EQ(result, 0);
}

TEST_F(Clip01Test_1881, LargeNegativeValueClipsToZero_1881) {
    GfxColorComp result = clip01(-1000000);
    EXPECT_EQ(result, 0);
}

TEST_F(Clip01Test_1881, ValueAboveMaxClipsToMax_1881) {
    GfxColorComp result = clip01(gfxColorComp1 + 1);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, LargePositiveValueClipsToMax_1881) {
    GfxColorComp result = clip01(gfxColorComp1 * 2);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, VeryLargePositiveValueClipsToMax_1881) {
    GfxColorComp result = clip01(1000000);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, MinNegativeClipsToZero_1881) {
    GfxColorComp result = clip01(-32768);
    EXPECT_EQ(result, 0);
}

// Edge cases around the boundaries

TEST_F(Clip01Test_1881, ExactlyGfxColorComp1ReturnsExact_1881) {
    GfxColorComp val = 65536;
    GfxColorComp result = clip01(val);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, ValueGfxColorComp1PlusTwoClipsToMax_1881) {
    GfxColorComp result = clip01(gfxColorComp1 + 2);
    EXPECT_EQ(result, gfxColorComp1);
}

TEST_F(Clip01Test_1881, NegativeTwoClipsToZero_1881) {
    GfxColorComp result = clip01(-2);
    EXPECT_EQ(result, 0);
}

// Verify clipping preserves values within range
TEST_F(Clip01Test_1881, SmallPositiveReturnsSame_1881) {
    GfxColorComp result = clip01(100);
    EXPECT_EQ(result, 100);
}

TEST_F(Clip01Test_1881, LargeInRangeReturnsSame_1881) {
    GfxColorComp result = clip01(60000);
    EXPECT_EQ(result, 60000);
}

// Verify return value is within [0, gfxColorComp1] for any input
TEST_F(Clip01Test_1881, ResultAlwaysNonNegative_1881) {
    for (GfxColorComp v = -100; v <= 0; ++v) {
        EXPECT_GE(clip01(v), 0);
    }
}

TEST_F(Clip01Test_1881, ResultAlwaysLessOrEqualMax_1881) {
    for (GfxColorComp v = gfxColorComp1 - 10; v <= gfxColorComp1 + 100; ++v) {
        EXPECT_LE(clip01(v), gfxColorComp1);
    }
}
