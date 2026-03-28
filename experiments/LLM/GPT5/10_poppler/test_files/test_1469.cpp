#include <gtest/gtest.h>
#include <cmath>

// Assuming GfxColor and isSameGfxColor are defined as in the provided code
struct GfxColor {
    double c[32];  // Array holding color components
};

static inline bool isSameGfxColor(const GfxColor &colorA, const GfxColor &colorB, unsigned int nComps, double delta) {
    for (unsigned int k = 0; k < nComps; ++k) {
        if (abs(colorA.c[k] - colorB.c[k]) > delta) {
            return false;
        }
    }
    return true;
}

// TEST CASES

TEST_F(GfxColorTest_1469, IdenticalColorsWithinDelta_1469) {
    GfxColor colorA = {{0.5, 0.5, 0.5}};
    GfxColor colorB = {{0.5, 0.5, 0.5}};
    double delta = 0.1;
    unsigned int nComps = 3;
    
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1470, ColorsDifferentByDelta_1470) {
    GfxColor colorA = {{0.5, 0.5, 0.5}};
    GfxColor colorB = {{0.5, 0.6, 0.5}};
    double delta = 0.1;
    unsigned int nComps = 3;
    
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1471, ColorsSameButDifferentByLargeDelta_1471) {
    GfxColor colorA = {{0.5, 0.5, 0.5}};
    GfxColor colorB = {{0.5, 0.5, 0.5}};
    double delta = 0.6;
    unsigned int nComps = 3;
    
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1472, ColorsMoreThanDeltaApart_1472) {
    GfxColor colorA = {{0.5, 0.5, 0.5}};
    GfxColor colorB = {{0.5, 0.5, 1.0}};
    double delta = 0.1;
    unsigned int nComps = 3;
    
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1473, BoundaryTest_ZeroComponents_1473) {
    GfxColor colorA = {{0.5}};
    GfxColor colorB = {{0.5}};
    double delta = 0.1;
    unsigned int nComps = 0;
    
    // Edge case where no components are being compared
    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1474, BoundaryTest_OneComponent_1474) {
    GfxColor colorA = {{0.5}};
    GfxColor colorB = {{0.6}};
    double delta = 0.1;
    unsigned int nComps = 1;
    
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));
}

TEST_F(GfxColorTest_1475, ErrorTest_TooManyComponents_1475) {
    GfxColor colorA = {{0.5, 0.5, 0.5}};
    GfxColor colorB = {{0.5, 0.5, 0.5}};
    double delta = 0.1;
    unsigned int nComps = 100;  // This is too large compared to the available components in GfxColor
    
    // Should handle invalid cases gracefully, depending on implementation specifics
    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));
}