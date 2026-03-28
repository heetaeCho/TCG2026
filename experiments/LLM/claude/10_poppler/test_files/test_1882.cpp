#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/poppler/poppler/GfxState_helpers.h"

// Test normal values within [0, 1]
TEST(Clip01Test_1882, ValueWithinRange_Middle_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.5), 0.5);
}

TEST(Clip01Test_1882, ValueWithinRange_Quarter_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.25), 0.25);
}

TEST(Clip01Test_1882, ValueWithinRange_ThreeQuarters_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.75), 0.75);
}

TEST(Clip01Test_1882, ValueWithinRange_SmallPositive_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.001), 0.001);
}

TEST(Clip01Test_1882, ValueWithinRange_NearOne_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.999), 0.999);
}

// Test boundary values
TEST(Clip01Test_1882, BoundaryExactlyZero_1882) {
    EXPECT_DOUBLE_EQ(clip01(0.0), 0.0);
}

TEST(Clip01Test_1882, BoundaryExactlyOne_1882) {
    EXPECT_DOUBLE_EQ(clip01(1.0), 1.0);
}

// Test values below range (should be clipped to 0)
TEST(Clip01Test_1882, BelowRange_NegativeSmall_1882) {
    EXPECT_DOUBLE_EQ(clip01(-0.001), 0.0);
}

TEST(Clip01Test_1882, BelowRange_NegativeOne_1882) {
    EXPECT_DOUBLE_EQ(clip01(-1.0), 0.0);
}

TEST(Clip01Test_1882, BelowRange_LargeNegative_1882) {
    EXPECT_DOUBLE_EQ(clip01(-1000.0), 0.0);
}

TEST(Clip01Test_1882, BelowRange_NegativeMinDouble_1882) {
    EXPECT_DOUBLE_EQ(clip01(-1e308), 0.0);
}

// Test values above range (should be clipped to 1)
TEST(Clip01Test_1882, AboveRange_SlightlyAboveOne_1882) {
    EXPECT_DOUBLE_EQ(clip01(1.001), 1.0);
}

TEST(Clip01Test_1882, AboveRange_Two_1882) {
    EXPECT_DOUBLE_EQ(clip01(2.0), 1.0);
}

TEST(Clip01Test_1882, AboveRange_LargePositive_1882) {
    EXPECT_DOUBLE_EQ(clip01(1000.0), 1.0);
}

TEST(Clip01Test_1882, AboveRange_MaxDouble_1882) {
    EXPECT_DOUBLE_EQ(clip01(1e308), 1.0);
}

// Test very small positive values (epsilon-like)
TEST(Clip01Test_1882, VerySmallPositive_1882) {
    double tiny = 1e-15;
    EXPECT_DOUBLE_EQ(clip01(tiny), tiny);
}

// Test very small negative values
TEST(Clip01Test_1882, VerySmallNegative_1882) {
    double tiny = -1e-15;
    EXPECT_DOUBLE_EQ(clip01(tiny), 0.0);
}

// Test negative zero
TEST(Clip01Test_1882, NegativeZero_1882) {
    double neg_zero = -0.0;
    // -0.0 is not < 0 in IEEE 754, so should return -0.0 (which equals 0.0)
    EXPECT_DOUBLE_EQ(clip01(neg_zero), 0.0);
}

// Test with special floating point values
TEST(Clip01Test_1882, PositiveInfinity_1882) {
    double pos_inf = std::numeric_limits<double>::infinity();
    EXPECT_DOUBLE_EQ(clip01(pos_inf), 1.0);
}

TEST(Clip01Test_1882, NegativeInfinity_1882) {
    double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_DOUBLE_EQ(clip01(neg_inf), 0.0);
}

// Test with denormalized numbers
TEST(Clip01Test_1882, DenormalizedPositive_1882) {
    double denorm = std::numeric_limits<double>::denorm_min();
    EXPECT_DOUBLE_EQ(clip01(denorm), denorm);
}

TEST(Clip01Test_1882, DenormalizedNegative_1882) {
    double denorm = -std::numeric_limits<double>::denorm_min();
    EXPECT_DOUBLE_EQ(clip01(denorm), 0.0);
}

// Test with smallest normal positive
TEST(Clip01Test_1882, SmallestNormalPositive_1882) {
    double smallest = std::numeric_limits<double>::min();
    EXPECT_DOUBLE_EQ(clip01(smallest), smallest);
}
