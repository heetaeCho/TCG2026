#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashBGR8RTest_1036 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: splashBGR8R returns the third byte (index 2) which is the Red component in BGR8 format
TEST_F(SplashBGR8RTest_1036, ReturnsThirdByteAsRed_1036) {
    SplashColor bgr8;
    bgr8[0] = 10;  // B
    bgr8[1] = 20;  // G
    bgr8[2] = 30;  // R
    EXPECT_EQ(30, splashBGR8R(bgr8));
}

// Test with zero values
TEST_F(SplashBGR8RTest_1036, ReturnsZeroWhenRedIsZero_1036) {
    SplashColor bgr8;
    bgr8[0] = 255;
    bgr8[1] = 128;
    bgr8[2] = 0;
    EXPECT_EQ(0, splashBGR8R(bgr8));
}

// Test with maximum value for red component
TEST_F(SplashBGR8RTest_1036, ReturnsMaxWhenRedIs255_1036) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 255;
    EXPECT_EQ(255, splashBGR8R(bgr8));
}

// Test that it correctly reads index 2 regardless of other byte values
TEST_F(SplashBGR8RTest_1036, IndependentOfOtherComponents_1036) {
    SplashColor bgr8;
    bgr8[0] = 100;
    bgr8[1] = 200;
    bgr8[2] = 150;
    EXPECT_EQ(150, splashBGR8R(bgr8));

    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 150;
    EXPECT_EQ(150, splashBGR8R(bgr8));

    bgr8[0] = 255;
    bgr8[1] = 255;
    bgr8[2] = 150;
    EXPECT_EQ(150, splashBGR8R(bgr8));
}

// Test boundary value: 1
TEST_F(SplashBGR8RTest_1036, ReturnsBoundaryValueOne_1036) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 1;
    EXPECT_EQ(1, splashBGR8R(bgr8));
}

// Test boundary value: 254
TEST_F(SplashBGR8RTest_1036, ReturnsBoundaryValue254_1036) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 254;
    EXPECT_EQ(254, splashBGR8R(bgr8));
}

// Test boundary value: 128 (mid-range)
TEST_F(SplashBGR8RTest_1036, ReturnsMidRangeValue_1036) {
    SplashColor bgr8;
    bgr8[0] = 64;
    bgr8[1] = 192;
    bgr8[2] = 128;
    EXPECT_EQ(128, splashBGR8R(bgr8));
}

// Test that all components set to same value still returns correct index
TEST_F(SplashBGR8RTest_1036, AllComponentsSameValue_1036) {
    SplashColor bgr8;
    bgr8[0] = 42;
    bgr8[1] = 42;
    bgr8[2] = 42;
    EXPECT_EQ(42, splashBGR8R(bgr8));
}

// Test with a pointer offset scenario (using array directly)
TEST_F(SplashBGR8RTest_1036, WorksWithSplashColorPtr_1036) {
    unsigned char data[4] = {11, 22, 33, 44};
    SplashColorPtr ptr = data;
    EXPECT_EQ(33, splashBGR8R(ptr));
}

// Verify the return type is unsigned char
TEST_F(SplashBGR8RTest_1036, ReturnTypeIsUnsignedChar_1036) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 200;
    unsigned char result = splashBGR8R(bgr8);
    EXPECT_EQ(200, result);
}
