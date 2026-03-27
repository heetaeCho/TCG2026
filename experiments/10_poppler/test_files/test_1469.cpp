#include <gtest/gtest.h>

#include "GfxState.h"



// Assuming GfxColor and isSameGfxColor are in the same namespace or properly included

extern bool isSameGfxColor(const GfxColor &colorA, const GfxColor &colorB, unsigned int nComps, double delta);



class ColorComparisonTest_1469 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize colors for testing

        for (unsigned int i = 0; i < 32; ++i) {

            colorA.c[i] = 0.0;

            colorB.c[i] = 0.0;

        }

    }



    GfxColor colorA, colorB;

};



TEST_F(ColorComparisonTest_1469, IdenticalColorsSameComponents_1469) {

    unsigned int nComps = 3;

    double delta = 0.01;

    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, DifferentColorsWithinDelta_1469) {

    unsigned int nComps = 3;

    double delta = 0.02;

    colorA.c[0] = 0.01;

    colorB.c[0] = 0.015;

    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, DifferentColorsOutsideDelta_1469) {

    unsigned int nComps = 3;

    double delta = 0.01;

    colorA.c[0] = 0.01;

    colorB.c[0] = 0.02;

    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, ZeroComponents_1469) {

    unsigned int nComps = 0;

    double delta = 0.01;

    colorA.c[0] = 0.5;

    colorB.c[0] = 0.7;

    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, AllComponentsDifferentWithinDelta_1469) {

    unsigned int nComps = 3;

    double delta = 0.2;

    colorA.c[0] = 0.1;

    colorB.c[0] = 0.25;

    colorA.c[1] = 0.3;

    colorB.c[1] = 0.45;

    colorA.c[2] = 0.6;

    colorB.c[2] = 0.75;

    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, AllComponentsDifferentOutsideDelta_1469) {

    unsigned int nComps = 3;

    double delta = 0.1;

    colorA.c[0] = 0.1;

    colorB.c[0] = 0.25;

    colorA.c[1] = 0.3;

    colorB.c[1] = 0.45;

    colorA.c[2] = 0.6;

    colorB.c[2] = 0.75;

    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, LargeNumberOfComponents_1469) {

    unsigned int nComps = 32;

    double delta = 0.01;

    for (unsigned int i = 0; i < nComps; ++i) {

        colorA.c[i] = static_cast<double>(i) / 32.0;

        colorB.c[i] = static_cast<double>(i + 1) / 32.0 - delta * 0.5;

    }

    EXPECT_TRUE(isSameGfxColor(colorA, colorB, nComps, delta));

}



TEST_F(ColorComparisonTest_1469, LargeNumberOfComponentsOutsideDelta_1469) {

    unsigned int nComps = 32;

    double delta = 0.01;

    for (unsigned int i = 0; i < nComps; ++i) {

        colorA.c[i] = static_cast<double>(i) / 32.0;

        colorB.c[i] = static_cast<double>(i + 1) / 32.0;

    }

    EXPECT_FALSE(isSameGfxColor(colorA, colorB, nComps, delta));

}
