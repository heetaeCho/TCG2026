#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



using namespace testing;



extern "C" {

    void splashOutBlendLuminosity(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

}



class BlendLuminosityTest_1595 : public ::testing::Test {

protected:

    unsigned char src[4];

    unsigned char dest[4];

    unsigned char blend[4];



    void SetUp() override {

        memset(src, 0, sizeof(src));

        memset(dest, 0, sizeof(dest));

        memset(blend, 0, sizeof(blend));

    }

};



TEST_F(BlendLuminosityTest_1595, Mono1_NormalOperation_1595) {

    src[0] = 255;

    dest[0] = 128;



    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);



    EXPECT_EQ(blend[0], 255);

}



TEST_F(BlendLuminosityTest_1595, Mono8_NormalOperation_1595) {

    src[0] = 192;

    dest[0] = 64;



    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);



    EXPECT_EQ(blend[0], 192);

}



TEST_F(BlendLuminosityTest_1595, RGB8_NormalOperation_1595) {

    src[0] = 255; src[1] = 128; src[2] = 64;

    dest[0] = 32; dest[1] = 16; dest[2] = 8;



    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 144);

    EXPECT_EQ(blend[2], 96);

}



TEST_F(BlendLuminosityTest_1595, BGR8_NormalOperation_1595) {

    src[0] = 64; src[1] = 128; src[2] = 255;

    dest[0] = 8; dest[1] = 16; dest[2] = 32;



    splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);



    EXPECT_EQ(blend[0], 96);

    EXPECT_EQ(blend[1], 144);

    EXPECT_EQ(blend[2], 255);

}



TEST_F(BlendLuminosityTest_1595, XBGR8_NormalOperation_1595) {

    src[3] = 0; // Alpha channel should be ignored

    dest[3] = 255;



    src[0] = 64; src[1] = 128; src[2] = 255;

    dest[0] = 8; dest[1] = 16; dest[2] = 32;



    splashOutBlendLuminosity(src, dest, blend, splashModeXBGR8);



    EXPECT_EQ(blend[0], 96);

    EXPECT_EQ(blend[1], 144);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255); // Alpha channel should be set to 255

}



TEST_F(BlendLuminosityTest_1595, CMYK8_NormalOperation_1595) {

    src[0] = 64; src[1] = 128; src[2] = 192; src[3] = 255;

    dest[0] = 32; dest[1] = 64; dest[2] = 96; dest[3] = 128;



    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 127);

    EXPECT_EQ(blend[1], 128);

    EXPECT_EQ(blend[2], 139);

    EXPECT_EQ(blend[3], 0); // CMYK8 K channel is inverted

}



TEST_F(BlendLuminosityTest_1595, DeviceN8_NormalOperation_1595) {

    src[0] = 64; src[1] = 128; src[2] = 192; src[3] = 255;

    dest[0] = 32; dest[1] = 64; dest[2] = 96; dest[3] = 128;



    splashOutBlendLuminosity(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], 127);

    EXPECT_EQ(blend[1], 128);

    EXPECT_EQ(blend[2], 139);

    EXPECT_EQ(blend[3], 0); // DeviceN8 K channel is inverted

}



TEST_F(BlendLuminosityTest_1595, Mono1_BoundaryCondition_1595) {

    src[0] = 0;

    dest[0] = 255;



    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);



    EXPECT_EQ(blend[0], 255);

}



TEST_F(BlendLuminosityTest_1595, Mono8_BoundaryCondition_1595) {

    src[0] = 255;

    dest[0] = 0;



    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);



    EXPECT_EQ(blend[0], 0);

}



TEST_F(BlendLuminosityTest_1595, RGB8_BoundaryCondition_1595) {

    src[0] = 255; src[1] = 255; src[2] = 255;

    dest[0] = 0; dest[1] = 0; dest[2] = 0;



    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST_F(BlendLuminosityTest_1595, BGR8_BoundaryCondition_1595) {

    src[0] = 0; src[1] = 0; src[2] = 0;

    dest[0] = 255; dest[1] = 255; dest[2] = 255;



    splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST_F(BlendLuminosityTest_1595, CMYK8_BoundaryCondition_1595) {

    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 255;

    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 0;



    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 0); // K channel is inverted

}



TEST_F(BlendLuminosityTest_1595, DeviceN8_BoundaryCondition_1595) {

    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 0;

    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 255;



    splashOutBlendLuminosity(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 255); // K channel is inverted

}
