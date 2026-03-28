#include <gtest/gtest.h>

#include "SplashOutputDev.cc"

#include "SplashTypes.h"



class SplashOutBlendOverlayTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables here

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(SplashOutBlendOverlayTest_1579, RGB8_NormalOperation_1579) {

    SplashColor src = {200, 150, 100};

    SplashColor dest = {50, 100, 150};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], (100 * 2 * 50) / 255);

    EXPECT_EQ(blend[1], (150 * 2 * 100) / 255);

    EXPECT_EQ(blend[2], (150 * 2 * 100) / 255);

}



TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_NormalOperation_1579) {

    SplashColor src = {200, 150, 100, 50};

    SplashColor dest = {50, 100, 150, 200};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 255 - (155 * 2 * 205) / 255);

    EXPECT_EQ(blend[1], 255 - (105 * 2 * 155) / 255);

    EXPECT_EQ(blend[2], 255 - (155 * 2 * 155) / 255);

    EXPECT_EQ(blend[3], 255 - (205 * 2 * 55) / 255);

}



TEST_F(SplashOutBlendOverlayTest_1579, RGB8_BoundaryConditions_1579) {

    SplashColor src = {0, 0, 0};

    SplashColor dest = {255, 255, 255};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_BoundaryConditions_1579) {

    SplashColor src = {0, 0, 0, 0};

    SplashColor dest = {255, 255, 255, 255};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 0);

}



TEST_F(SplashOutBlendOverlayTest_1579, RGB8_ExceptionalCases_1579) {

    SplashColor src = {256, -1, 128}; // Out of range values

    SplashColor dest = {-1, 256, 128}; // Out of range values

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

    EXPECT_EQ(blend[1], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

    EXPECT_EQ(blend[2], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

}



TEST_F(SplashOutBlendOverlayTest_1579, DeviceN8_NormalOperation_1579) {

    SplashColor src = {200, 150, 100};

    SplashColor dest = {50, 100, 150};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], (100 * 2 * 50) / 255);

    EXPECT_EQ(blend[1], (150 * 2 * 100) / 255);

    EXPECT_EQ(blend[2], (150 * 2 * 100) / 255);

}



TEST_F(SplashOutBlendOverlayTest_1579, DeviceN8_BoundaryConditions_1579) {

    SplashColor src = {0, 0, 0};

    SplashColor dest = {255, 255, 255};

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST_F(SplashOutBlendOverlayTest_1579, DeviceN8_ExceptionalCases_1579) {

    SplashColor src = {256, -1, 128}; // Out of range values

    SplashColor dest = {-1, 256, 128}; // Out of range values

    SplashColor blend;

    splashOutBlendOverlay(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

    EXPECT_EQ(blend[1], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

    EXPECT_EQ(blend[2], (128 * 2 * 128) / 255); // Assuming clamping or wrapping at the boundary

}
