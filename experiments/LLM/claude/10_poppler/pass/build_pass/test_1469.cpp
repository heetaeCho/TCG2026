#include <gtest/gtest.h>
#include <cmath>
#include <cstdlib>

// Reproduce the necessary types and the function under test
typedef int GfxColorComp;

struct GfxColor {
    GfxColorComp c[32];
};

// Copy the function under test exactly as provided
static inline bool isSameGfxColor(const GfxColor &colorA, const GfxColor &colorB, unsigned int nComps, double delta)
{
    for (unsigned int k = 0; k < nComps; ++k) {
        if (abs(colorA.c[k] - colorB.c[k]) > delta) {
            return false;
        }
    }
    return true;
}

class IsSameGfxColorTest_1469 : public ::testing::Test {
protected:
    GfxColor colorA;
    GfxColor colorB;

    void SetUp() override {
        memset(&colorA, 0, sizeof(colorA));
        memset(&colorB, 0, sizeof(colorB));
    }
};

// Normal operation: identical colors should be the same
TEST_F(IsSameGfxColorTest_1469, IdenticalColors_1469) {
    colorA.c[0] = 100;
    colorA.c[1] = 200;
    colorA.c[2] = 300;
    colorB.c[0] = 100;
    colorB.c[1] = 200;
    colorB.c[2] = 300;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 3, 0.0));
}

// Normal operation: colors differ but within delta
TEST_F(IsSameGfxColorTest_1469, ColorsWithinDelta_1469) {
    colorA.c[0] = 100;
    colorA.c[1] = 200;
    colorA.c[2] = 300;
    colorB.c[0] = 102;
    colorB.c[1] = 198;
    colorB.c[2] = 301;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 3, 5.0));
}

// Normal operation: colors differ beyond delta
TEST_F(IsSameGfxColorTest_1469, ColorsBeyondDelta_1469) {
    colorA.c[0] = 100;
    colorA.c[1] = 200;
    colorA.c[2] = 300;
    colorB.c[0] = 110;
    colorB.c[1] = 200;
    colorB.c[2] = 300;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 3, 5.0));
}

// Boundary: difference exactly equal to delta (should be considered same since !(abs(diff) > delta))
TEST_F(IsSameGfxColorTest_1469, DifferenceExactlyEqualToDelta_1469) {
    colorA.c[0] = 100;
    colorB.c[0] = 105;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Boundary: difference is one more than delta
TEST_F(IsSameGfxColorTest_1469, DifferenceOneMoreThanDelta_1469) {
    colorA.c[0] = 100;
    colorB.c[0] = 106;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Boundary: nComps is 0, should always return true regardless of color values
TEST_F(IsSameGfxColorTest_1469, ZeroComponents_1469) {
    colorA.c[0] = 1000;
    colorB.c[0] = 0;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 0, 0.0));
}

// Boundary: nComps is 1
TEST_F(IsSameGfxColorTest_1469, SingleComponent_1469) {
    colorA.c[0] = 50;
    colorB.c[0] = 50;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 0.0));
}

// Boundary: nComps is maximum (32)
TEST_F(IsSameGfxColorTest_1469, MaxComponents_1469) {
    for (int i = 0; i < 32; ++i) {
        colorA.c[i] = i * 10;
        colorB.c[i] = i * 10;
    }
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 32, 0.0));
}

// Test with maximum components where last component differs
TEST_F(IsSameGfxColorTest_1469, MaxComponentsLastDiffers_1469) {
    for (int i = 0; i < 32; ++i) {
        colorA.c[i] = 100;
        colorB.c[i] = 100;
    }
    colorB.c[31] = 200;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 32, 50.0));
}

// Negative component values: colorA < colorB
TEST_F(IsSameGfxColorTest_1469, NegativeValues_1469) {
    colorA.c[0] = -100;
    colorB.c[0] = -95;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Negative component values beyond delta
TEST_F(IsSameGfxColorTest_1469, NegativeValuesBeyondDelta_1469) {
    colorA.c[0] = -100;
    colorB.c[0] = -90;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Mixed positive and negative
TEST_F(IsSameGfxColorTest_1469, MixedPositiveNegative_1469) {
    colorA.c[0] = -3;
    colorB.c[0] = 3;
    // abs(-3 - 3) = 6 > 5
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Mixed positive and negative within delta
TEST_F(IsSameGfxColorTest_1469, MixedPositiveNegativeWithinDelta_1469) {
    colorA.c[0] = -2;
    colorB.c[0] = 2;
    // abs(-2 - 2) = 4 <= 5
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 5.0));
}

// Delta is zero: only identical colors pass
TEST_F(IsSameGfxColorTest_1469, ZeroDeltaIdentical_1469) {
    colorA.c[0] = 42;
    colorB.c[0] = 42;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 0.0));
}

TEST_F(IsSameGfxColorTest_1469, ZeroDeltaDifferent_1469) {
    colorA.c[0] = 42;
    colorB.c[0] = 43;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 1, 0.0));
}

// Only some components differ: first component within, second beyond
TEST_F(IsSameGfxColorTest_1469, FirstWithinSecondBeyond_1469) {
    colorA.c[0] = 100;
    colorA.c[1] = 100;
    colorB.c[0] = 102;
    colorB.c[1] = 120;
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 2, 5.0));
}

// Only first component checked when nComps = 1 even if others differ
TEST_F(IsSameGfxColorTest_1469, OnlyRequestedComponentsChecked_1469) {
    colorA.c[0] = 100;
    colorA.c[1] = 100;
    colorB.c[0] = 100;
    colorB.c[1] = 999;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 0.0));
}

// Large delta: everything passes
TEST_F(IsSameGfxColorTest_1469, LargeDelta_1469) {
    colorA.c[0] = 0;
    colorB.c[0] = 10000;
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 100000.0));
}

// All zero colors
TEST_F(IsSameGfxColorTest_1469, AllZeroColors_1469) {
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 32, 0.0));
}

// Symmetry: isSameGfxColor(A, B) == isSameGfxColor(B, A)
TEST_F(IsSameGfxColorTest_1469, Symmetry_1469) {
    colorA.c[0] = 100;
    colorB.c[0] = 105;
    bool ab = isSameGfxColor(colorA, colorB, 1, 5.0);
    bool ba = isSameGfxColor(colorB, colorA, 1, 5.0);
    EXPECT_EQ(ab, ba);
}

// Fractional delta: since abs works on integers, delta 4.5 means > 4.5 fails
TEST_F(IsSameGfxColorTest_1469, FractionalDelta_1469) {
    colorA.c[0] = 100;
    colorB.c[0] = 105;
    // abs(100 - 105) = 5 > 4.5 => false
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, 1, 4.5));
}

TEST_F(IsSameGfxColorTest_1469, FractionalDeltaPass_1469) {
    colorA.c[0] = 100;
    colorB.c[0] = 104;
    // abs(100 - 104) = 4 > 4.5? No => true
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, 1, 4.5));
}
