#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"

#include "TestProjects/poppler/poppler/SplashOutputDev.cc"



// Mocking or setting up any required fixtures

class BlendLightenTest : public ::testing::Test {

protected:

    static const int kNumComponentsCMYK8 = 4;

    static const int kNumComponentsDeviceN8 = 8;



    void SetUp() override {

        // Initialize color arrays with default values

        memset(src, 0, sizeof(src));

        memset(dest, 255, sizeof(dest));

        memset(blend, 0, sizeof(blend));

    }



    SplashColor src[8]; // Largest possible array for DeviceN8

    SplashColor dest[8];

    SplashColor blend[8];

};



TEST_F(BlendLightenTest_1581, CMYK8_Blending_Normally_1581) {

    cm = splashModeCMYK8;

    src[0] = 200; src[1] = 150; src[2] = 100; src[3] = 50;



    splashOutBlendLighten(src, dest, blend, cm);



    EXPECT_EQ(blend[0], 200);

    EXPECT_EQ(blend[1], 150);

    EXPECT_EQ(blend[2], 100);

    EXPECT_EQ(blend[3], 50);

}



TEST_F(BlendLightenTest_1581, DeviceN8_Blending_Normally_1581) {

    cm = splashModeDeviceN8;

    src[0] = 128; src[1] = 64; src[2] = 32; src[3] = 16;

    src[4] = 8; src[5] = 4; src[6] = 2; src[7] = 1;



    splashOutBlendLighten(src, dest, blend, cm);



    EXPECT_EQ(blend[0], 128);

    EXPECT_EQ(blend[1], 64);

    EXPECT_EQ(blend[2], 32);

    EXPECT_EQ(blend[3], 16);

    EXPECT_EQ(blend[4], 8);

    EXPECT_EQ(blend[5], 4);

    EXPECT_EQ(blend[6], 2);

    EXPECT_EQ(blend[7], 1);

}



TEST_F(BlendLightenTest_1581, CMYK8_Blending_BoundaryConditions_1581) {

    cm = splashModeCMYK8;

    src[0] = 0; src[1] = 255; src[2] = 0; src[3] = 255;



    splashOutBlendLighten(src, dest, blend, cm);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255);

}



TEST_F(BlendLightenTest_1581, DeviceN8_Blending_BoundaryConditions_1581) {

    cm = splashModeDeviceN8;

    src[0] = 0; src[1] = 255; src[2] = 0; src[3] = 255;

    src[4] = 0; src[5] = 255; src[6] = 0; src[7] = 255;



    splashOutBlendLighten(src, dest, blend, cm);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255);

    EXPECT_EQ(blend[4], 255);

    EXPECT_EQ(blend[5], 255);

    EXPECT_EQ(blend[6], 255);

    EXPECT_EQ(blend[7], 255);

}
