#include <gtest/gtest.h>
#include "GfxState.h"

class GfxRGBTest_396 : public ::testing::Test {
protected:
    GfxRGB rgb1;
    GfxRGB rgb2;
};

TEST_F(GfxRGBTest_396, EqualityOperator_AllComponentsEqual_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 50;
    EXPECT_TRUE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_RDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 101;
    rgb2.g = 200;
    rgb2.b = 50;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_GDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 201;
    rgb2.b = 50;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_BDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 51;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_AllComponentsDiffer_396) {
    rgb1.r = 10;
    rgb1.g = 20;
    rgb1.b = 30;
    rgb2.r = 40;
    rgb2.g = 50;
    rgb2.b = 60;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_ZeroValues_396) {
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 0;
    rgb2.r = 0;
    rgb2.g = 0;
    rgb2.b = 0;
    EXPECT_TRUE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_Symmetry_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 50;
    EXPECT_TRUE(rgb1 == rgb2);
    EXPECT_TRUE(rgb2 == rgb1);
}

TEST_F(GfxRGBTest_396, EqualityOperator_SymmetryWhenNotEqual_396) {
    rgb1.r = 1;
    rgb1.g = 2;
    rgb1.b = 3;
    rgb2.r = 4;
    rgb2.g = 5;
    rgb2.b = 6;
    EXPECT_FALSE(rgb1 == rgb2);
    EXPECT_FALSE(rgb2 == rgb1);
}

TEST_F(GfxRGBTest_396, EqualityOperator_Reflexive_396) {
    rgb1.r = 42;
    rgb1.g = 84;
    rgb1.b = 126;
    EXPECT_TRUE(rgb1 == rgb1);
}

TEST_F(GfxRGBTest_396, EqualityOperator_MaxValues_396) {
    GfxColorComp maxVal = 65535; // typical max for GfxColorComp
    rgb1.r = maxVal;
    rgb1.g = maxVal;
    rgb1.b = maxVal;
    rgb2.r = maxVal;
    rgb2.g = maxVal;
    rgb2.b = maxVal;
    EXPECT_TRUE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_OnlyREqual_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 0;
    rgb2.b = 0;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_OnlyGEqual_396) {
    rgb1.r = 0;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 0;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_OnlyBEqual_396) {
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 50;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_RAndGEqualBDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 200;
    rgb2.b = 99;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_RAndBEqualGDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 100;
    rgb2.g = 99;
    rgb2.b = 50;
    EXPECT_FALSE(rgb1 == rgb2);
}

TEST_F(GfxRGBTest_396, EqualityOperator_GAndBEqualRDiffers_396) {
    rgb1.r = 100;
    rgb1.g = 200;
    rgb1.b = 50;
    rgb2.r = 99;
    rgb2.g = 200;
    rgb2.b = 50;
    EXPECT_FALSE(rgb1 == rgb2);
}
