#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



extern "C" {

    void splashOutBlendColor(unsigned char* src, unsigned char* dest, unsigned char* blend, SplashColorMode cm);

}



class SplashOutputDevTest_1594 : public ::testing::Test {};



TEST_F(SplashOutputDevTest_1594, BlendMono1Normal_1594) {

    unsigned char src[] = { 255 };

    unsigned char dest[] = { 0 };

    unsigned char blend[] = { 0 };

    splashOutBlendColor(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);

}



TEST_F(SplashOutputDevTest_1594, BlendMono8Normal_1594) {

    unsigned char src[] = { 255 };

    unsigned char dest[] = { 0 };

    unsigned char blend[] = { 0 };

    splashOutBlendColor(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);

}



TEST_F(SplashOutputDevTest_1594, BlendRGB8Normal_1594) {

    unsigned char src[] = { 255, 0, 0 };

    unsigned char dest[] = { 0, 255, 0 };

    unsigned char blend[] = { 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 128);

    EXPECT_EQ(blend[1], 128);

    EXPECT_EQ(blend[2], 0);

}



TEST_F(SplashOutputDevTest_1594, BlendBGR8Normal_1594) {

    unsigned char src[] = { 0, 0, 255 };

    unsigned char dest[] = { 0, 255, 0 };

    unsigned char blend[] = { 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeBGR8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 128);

    EXPECT_EQ(blend[2], 128);

}



TEST_F(SplashOutputDevTest_1594, BlendXBGR8Normal_1594) {

    unsigned char src[] = { 0, 0, 255, 255 };

    unsigned char dest[] = { 0, 255, 0, 255 };

    unsigned char blend[] = { 0, 0, 0, 255 };

    splashOutBlendColor(src, dest, blend, splashModeXBGR8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 128);

    EXPECT_EQ(blend[2], 128);

    EXPECT_EQ(blend[3], 255);

}



TEST_F(SplashOutputDevTest_1594, BlendCMYK8Normal_1594) {

    unsigned char src[] = { 0, 255, 0, 0 };

    unsigned char dest[] = { 255, 0, 255, 0 };

    unsigned char blend[] = { 0, 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 128);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 128);

    EXPECT_EQ(blend[3], 255);

}



TEST_F(SplashOutputDevTest_1594, BlendDeviceN8Normal_1594) {

    unsigned char src[] = { 0, 255, 0, 0 };

    unsigned char dest[] = { 255, 0, 255, 0 };

    unsigned char blend[] = { 0, 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeDeviceN8);

    EXPECT_EQ(blend[0], 128);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 128);

    EXPECT_EQ(blend[3], 255);

}



TEST_F(SplashOutputDevTest_1594, BlendMono1Boundary_1594) {

    unsigned char src[] = { 0 };

    unsigned char dest[] = { 0 };

    unsigned char blend[] = { 0 };

    splashOutBlendColor(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);

}



TEST_F(SplashOutputDevTest_1594, BlendRGB8Boundary_1594) {

    unsigned char src[] = { 255, 255, 255 };

    unsigned char dest[] = { 255, 255, 255 };

    unsigned char blend[] = { 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST_F(SplashOutputDevTest_1594, BlendCMYK8Boundary_1594) {

    unsigned char src[] = { 0, 0, 0, 0 };

    unsigned char dest[] = { 0, 0, 0, 255 };

    unsigned char blend[] = { 0, 0, 0, 0 };

    splashOutBlendColor(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 255);

}
