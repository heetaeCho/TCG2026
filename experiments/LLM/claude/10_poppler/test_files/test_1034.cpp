#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashRGB8GTest_1034 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: verify that splashRGB8G returns the second element (index 1)
TEST_F(SplashRGB8GTest_1034, ReturnsGreenChannel_1034) {
    SplashColor rgb8;
    rgb8[0] = 100; // R
    rgb8[1] = 150; // G
    rgb8[2] = 200; // B
    EXPECT_EQ(splashRGB8G(rgb8), 150);
}

// Test with zero value for green channel
TEST_F(SplashRGB8GTest_1034, ReturnsZeroGreen_1034) {
    SplashColor rgb8;
    rgb8[0] = 255;
    rgb8[1] = 0;
    rgb8[2] = 255;
    EXPECT_EQ(splashRGB8G(rgb8), 0);
}

// Test with maximum value for green channel
TEST_F(SplashRGB8GTest_1034, ReturnsMaxGreen_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 255;
    rgb8[2] = 0;
    EXPECT_EQ(splashRGB8G(rgb8), 255);
}

// Test that green channel is independent of red channel value
TEST_F(SplashRGB8GTest_1034, GreenIndependentOfRed_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 42;
    rgb8[2] = 0;
    EXPECT_EQ(splashRGB8G(rgb8), 42);

    rgb8[0] = 255;
    EXPECT_EQ(splashRGB8G(rgb8), 42);
}

// Test that green channel is independent of blue channel value
TEST_F(SplashRGB8GTest_1034, GreenIndependentOfBlue_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 77;
    rgb8[2] = 0;
    EXPECT_EQ(splashRGB8G(rgb8), 77);

    rgb8[2] = 255;
    EXPECT_EQ(splashRGB8G(rgb8), 77);
}

// Test boundary value: 1
TEST_F(SplashRGB8GTest_1034, ReturnsBoundaryValueOne_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 1;
    rgb8[2] = 0;
    EXPECT_EQ(splashRGB8G(rgb8), 1);
}

// Test boundary value: 254
TEST_F(SplashRGB8GTest_1034, ReturnsBoundaryValue254_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 254;
    rgb8[2] = 0;
    EXPECT_EQ(splashRGB8G(rgb8), 254);
}

// Test mid-range value: 128
TEST_F(SplashRGB8GTest_1034, ReturnsMidRangeValue_1034) {
    SplashColor rgb8;
    rgb8[0] = 64;
    rgb8[1] = 128;
    rgb8[2] = 192;
    EXPECT_EQ(splashRGB8G(rgb8), 128);
}

// Test all channels same value - verify it still returns index 1
TEST_F(SplashRGB8GTest_1034, AllChannelsSameValue_1034) {
    SplashColor rgb8;
    rgb8[0] = 99;
    rgb8[1] = 99;
    rgb8[2] = 99;
    EXPECT_EQ(splashRGB8G(rgb8), 99);
}

// Test with all channels set to different known values
TEST_F(SplashRGB8GTest_1034, AllChannelsDifferent_1034) {
    SplashColor rgb8;
    rgb8[0] = 10;
    rgb8[1] = 20;
    rgb8[2] = 30;
    EXPECT_EQ(splashRGB8G(rgb8), 20);
}

// Test return type is unsigned char
TEST_F(SplashRGB8GTest_1034, ReturnTypeIsUnsignedChar_1034) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 200;
    rgb8[2] = 0;
    unsigned char result = splashRGB8G(rgb8);
    EXPECT_EQ(result, 200);
}
