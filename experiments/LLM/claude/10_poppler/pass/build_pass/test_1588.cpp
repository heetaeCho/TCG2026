#include <gtest/gtest.h>

// Declaration of the function under test
static int getLum(int r, int g, int b) { return ((r * 77 + g * 151 + b * 28 + 0x80) >> 8); }

// Normal operation tests
TEST(GetLumTest_1588, BlackReturnsZero_1588) {
    EXPECT_EQ(getLum(0, 0, 0), 0);
}

TEST(GetLumTest_1588, WhiteReturnsMaxLuminance_1588) {
    // (255*77 + 255*151 + 255*28 + 128) >> 8 = (255*256 + 128) >> 8 = (65280 + 128) >> 8 = 65408 >> 8 = 255
    EXPECT_EQ(getLum(255, 255, 255), 255);
}

TEST(GetLumTest_1588, PureRedLuminance_1588) {
    // (255*77 + 0*151 + 0*28 + 128) >> 8 = (19635 + 128) >> 8 = 19763 >> 8 = 77
    EXPECT_EQ(getLum(255, 0, 0), 77);
}

TEST(GetLumTest_1588, PureGreenLuminance_1588) {
    // (0*77 + 255*151 + 0*28 + 128) >> 8 = (38505 + 128) >> 8 = 38633 >> 8 = 150
    EXPECT_EQ(getLum(0, 255, 0), 150);
}

TEST(GetLumTest_1588, PureBlueLuminance_1588) {
    // (0*77 + 0*151 + 255*28 + 128) >> 8 = (7140 + 128) >> 8 = 7268 >> 8 = 28
    EXPECT_EQ(getLum(0, 0, 255), 28);
}

TEST(GetLumTest_1588, GreenDominatesLuminance_1588) {
    // Green has the largest coefficient (151), so green channel should contribute most
    int lumGreen = getLum(0, 128, 0);
    int lumRed = getLum(128, 0, 0);
    int lumBlue = getLum(0, 0, 128);
    EXPECT_GT(lumGreen, lumRed);
    EXPECT_GT(lumGreen, lumBlue);
    EXPECT_GT(lumRed, lumBlue);
}

TEST(GetLumTest_1588, MidGrayLuminance_1588) {
    // (128*77 + 128*151 + 128*28 + 128) >> 8 = (128*256 + 128) >> 8 = (32768 + 128) >> 8 = 32896 >> 8 = 128
    EXPECT_EQ(getLum(128, 128, 128), 128);
}

TEST(GetLumTest_1588, ArbitraryColor_1588) {
    // (100*77 + 150*151 + 200*28 + 128) >> 8 = (7700 + 22650 + 5600 + 128) >> 8 = 36078 >> 8 = 140
    EXPECT_EQ(getLum(100, 150, 200), 140);
}

TEST(GetLumTest_1588, SingleUnitValues_1588) {
    // (1*77 + 1*151 + 1*28 + 128) >> 8 = (77 + 151 + 28 + 128) >> 8 = 384 >> 8 = 1
    EXPECT_EQ(getLum(1, 1, 1), 1);
}

TEST(GetLumTest_1588, OnlyRedOne_1588) {
    // (1*77 + 0 + 0 + 128) >> 8 = 205 >> 8 = 0
    EXPECT_EQ(getLum(1, 0, 0), 0);
}

TEST(GetLumTest_1588, OnlyGreenOne_1588) {
    // (0 + 1*151 + 0 + 128) >> 8 = 279 >> 8 = 1
    EXPECT_EQ(getLum(0, 1, 0), 1);
}

TEST(GetLumTest_1588, OnlyBlueOne_1588) {
    // (0 + 0 + 1*28 + 128) >> 8 = 156 >> 8 = 0
    EXPECT_EQ(getLum(0, 0, 1), 0);
}

// Boundary condition: maximum individual channels
TEST(GetLumTest_1588, MaxRedOnly_1588) {
    EXPECT_EQ(getLum(255, 0, 0), (255 * 77 + 0 + 0 + 0x80) >> 8);
}

TEST(GetLumTest_1588, MaxGreenOnly_1588) {
    EXPECT_EQ(getLum(0, 255, 0), (0 + 255 * 151 + 0 + 0x80) >> 8);
}

TEST(GetLumTest_1588, MaxBlueOnly_1588) {
    EXPECT_EQ(getLum(0, 0, 255), (0 + 0 + 255 * 28 + 0x80) >> 8);
}

// Linearity/additivity property
TEST(GetLumTest_1588, AdditivityProperty_1588) {
    // getLum(r1+r2, g1+g2, b1+b2) should be approximately getLum(r1,g1,b1) + getLum(r2,g2,b2)
    // Due to integer rounding with the 0x80 offset, this won't be exact, but we can verify the formula
    int r1 = 50, g1 = 60, b1 = 70;
    int r2 = 30, g2 = 40, b2 = 50;
    int combined = getLum(r1 + r2, g1 + g2, b1 + b2);
    int expected = ((r1 + r2) * 77 + (g1 + g2) * 151 + (b1 + b2) * 28 + 0x80) >> 8;
    EXPECT_EQ(combined, expected);
}

// Test with typical skin tone color
TEST(GetLumTest_1588, TypicalSkinTone_1588) {
    int lum = getLum(200, 160, 130);
    int expected = (200 * 77 + 160 * 151 + 130 * 28 + 0x80) >> 8;
    EXPECT_EQ(lum, expected);
}

// Verify the rounding behavior (0x80 = 128 acts as rounding)
TEST(GetLumTest_1588, RoundingBehavior_1588) {
    // Without rounding: (2*77 + 0 + 0) >> 8 = 154 >> 8 = 0
    // With rounding: (154 + 128) >> 8 = 282 >> 8 = 1
    EXPECT_EQ(getLum(2, 0, 0), 1);
}

TEST(GetLumTest_1588, SymmetricGray_1588) {
    // All gray values should return approximately the same value
    for (int v = 0; v <= 255; v++) {
        int expected = (v * 77 + v * 151 + v * 28 + 0x80) >> 8;
        EXPECT_EQ(getLum(v, v, v), expected);
    }
}
