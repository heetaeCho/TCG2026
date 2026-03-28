#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashTypesTest_1033 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: splashRGB8R returns the first byte (red channel)
TEST_F(SplashTypesTest_1033, SplashRGB8R_ReturnsFirstByte_1033) {
    SplashColor color;
    color[0] = 128;
    color[1] = 64;
    color[2] = 32;
    EXPECT_EQ(128, splashRGB8R(color));
}

// Test with zero value for red channel
TEST_F(SplashTypesTest_1033, SplashRGB8R_ZeroValue_1033) {
    SplashColor color;
    color[0] = 0;
    color[1] = 255;
    color[2] = 255;
    EXPECT_EQ(0, splashRGB8R(color));
}

// Test with maximum value for red channel
TEST_F(SplashTypesTest_1033, SplashRGB8R_MaxValue_1033) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    EXPECT_EQ(255, splashRGB8R(color));
}

// Test that splashRGB8R only reads index 0, not affected by other channels
TEST_F(SplashTypesTest_1033, SplashRGB8R_IndependentOfOtherChannels_1033) {
    SplashColor color1;
    color1[0] = 42;
    color1[1] = 0;
    color1[2] = 0;

    SplashColor color2;
    color2[0] = 42;
    color2[1] = 200;
    color2[2] = 100;

    EXPECT_EQ(splashRGB8R(color1), splashRGB8R(color2));
}

// Test boundary value: 1
TEST_F(SplashTypesTest_1033, SplashRGB8R_BoundaryValueOne_1033) {
    SplashColor color;
    color[0] = 1;
    color[1] = 0;
    color[2] = 0;
    EXPECT_EQ(1, splashRGB8R(color));
}

// Test boundary value: 254
TEST_F(SplashTypesTest_1033, SplashRGB8R_BoundaryValue254_1033) {
    SplashColor color;
    color[0] = 254;
    color[1] = 0;
    color[2] = 0;
    EXPECT_EQ(254, splashRGB8R(color));
}

// Test with midpoint value
TEST_F(SplashTypesTest_1033, SplashRGB8R_MidpointValue_1033) {
    SplashColor color;
    color[0] = 127;
    color[1] = 127;
    color[2] = 127;
    EXPECT_EQ(127, splashRGB8R(color));
}

// Test that return type is unsigned char
TEST_F(SplashTypesTest_1033, SplashRGB8R_ReturnTypeIsUnsignedChar_1033) {
    SplashColor color;
    color[0] = 200;
    color[1] = 100;
    color[2] = 50;
    unsigned char result = splashRGB8R(color);
    EXPECT_EQ(200, result);
}

// Test with all channels set to the same value
TEST_F(SplashTypesTest_1033, SplashRGB8R_AllChannelsSameValue_1033) {
    SplashColor color;
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    EXPECT_EQ(100, splashRGB8R(color));
}

// Test with a pointer to an array (using SplashColorPtr directly)
TEST_F(SplashTypesTest_1033, SplashRGB8R_WithExplicitPointer_1033) {
    unsigned char rgb[3] = {75, 150, 225};
    SplashColorPtr ptr = rgb;
    EXPECT_EQ(75, splashRGB8R(ptr));
}
