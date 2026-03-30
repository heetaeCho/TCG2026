#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.cc"



TEST(SaturationCalculationTests_1589, NormalOperation_1589) {

    EXPECT_EQ(getSat(255, 0, 0), 255);

    EXPECT_EQ(getSat(0, 255, 0), 255);

    EXPECT_EQ(getSat(0, 0, 255), 255);

    EXPECT_EQ(getSat(128, 128, 128), 0);

}



TEST(SaturationCalculationTests_1589, BoundaryConditions_1589) {

    EXPECT_EQ(getSat(0, 0, 0), 0);

    EXPECT_EQ(getSat(255, 255, 255), 0);

    EXPECT_EQ(getSat(255, 255, 0), 255);

    EXPECT_EQ(getSat(0, 255, 255), 255);

    EXPECT_EQ(getSat(255, 0, 255), 255);

}



TEST(SaturationCalculationTests_1589, MixedColors_1589) {

    EXPECT_EQ(getSat(192, 64, 0), 192 - 64);

    EXPECT_EQ(getSat(34, 139, 34), 139 - 34);

    EXPECT_EQ(getSat(255, 165, 0), 255 - 0);

}
