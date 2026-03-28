#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashBGR8GTest_1037 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: extracting green channel from BGR8 color
TEST_F(SplashBGR8GTest_1037, ReturnsGreenChannelFromBGR8_1037) {
    SplashColor bgr8;
    bgr8[0] = 10;   // Blue
    bgr8[1] = 128;  // Green
    bgr8[2] = 200;  // Red
    EXPECT_EQ(128, splashBGR8G(bgr8));
}

// Test with green channel set to zero
TEST_F(SplashBGR8GTest_1037, ReturnsZeroWhenGreenIsZero_1037) {
    SplashColor bgr8;
    bgr8[0] = 255;  // Blue
    bgr8[1] = 0;    // Green
    bgr8[2] = 255;  // Red
    EXPECT_EQ(0, splashBGR8G(bgr8));
}

// Test with green channel set to maximum value (255)
TEST_F(SplashBGR8GTest_1037, ReturnsMaxWhenGreenIsMax_1037) {
    SplashColor bgr8;
    bgr8[0] = 0;    // Blue
    bgr8[1] = 255;  // Green
    bgr8[2] = 0;    // Red
    EXPECT_EQ(255, splashBGR8G(bgr8));
}

// Test that the function returns index 1 regardless of other channel values
TEST_F(SplashBGR8GTest_1037, IndependentOfBlueChannel_1037) {
    SplashColor bgr8_a;
    bgr8_a[0] = 0;
    bgr8_a[1] = 42;
    bgr8_a[2] = 100;

    SplashColor bgr8_b;
    bgr8_b[0] = 255;
    bgr8_b[1] = 42;
    bgr8_b[2] = 50;

    EXPECT_EQ(splashBGR8G(bgr8_a), splashBGR8G(bgr8_b));
}

// Test that the function returns index 1 regardless of red channel values
TEST_F(SplashBGR8GTest_1037, IndependentOfRedChannel_1037) {
    SplashColor bgr8_a;
    bgr8_a[0] = 100;
    bgr8_a[1] = 77;
    bgr8_a[2] = 0;

    SplashColor bgr8_b;
    bgr8_b[0] = 100;
    bgr8_b[1] = 77;
    bgr8_b[2] = 255;

    EXPECT_EQ(splashBGR8G(bgr8_a), splashBGR8G(bgr8_b));
}

// Test boundary value: green channel at 1
TEST_F(SplashBGR8GTest_1037, ReturnsOneWhenGreenIsOne_1037) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 1;
    bgr8[2] = 0;
    EXPECT_EQ(1, splashBGR8G(bgr8));
}

// Test boundary value: green channel at 254
TEST_F(SplashBGR8GTest_1037, Returns254WhenGreenIs254_1037) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 254;
    bgr8[2] = 0;
    EXPECT_EQ(254, splashBGR8G(bgr8));
}

// Test mid-range value
TEST_F(SplashBGR8GTest_1037, ReturnsMidRangeGreenValue_1037) {
    SplashColor bgr8;
    bgr8[0] = 50;
    bgr8[1] = 127;
    bgr8[2] = 200;
    EXPECT_EQ(127, splashBGR8G(bgr8));
}

// Test all channels same value - green should still be index 1
TEST_F(SplashBGR8GTest_1037, AllChannelsSameValue_1037) {
    SplashColor bgr8;
    bgr8[0] = 100;
    bgr8[1] = 100;
    bgr8[2] = 100;
    EXPECT_EQ(100, splashBGR8G(bgr8));
}

// Test with all channels at max
TEST_F(SplashBGR8GTest_1037, AllChannelsMax_1037) {
    SplashColor bgr8;
    bgr8[0] = 255;
    bgr8[1] = 255;
    bgr8[2] = 255;
    EXPECT_EQ(255, splashBGR8G(bgr8));
}

// Test with all channels at zero
TEST_F(SplashBGR8GTest_1037, AllChannelsZero_1037) {
    SplashColor bgr8;
    bgr8[0] = 0;
    bgr8[1] = 0;
    bgr8[2] = 0;
    EXPECT_EQ(0, splashBGR8G(bgr8));
}
