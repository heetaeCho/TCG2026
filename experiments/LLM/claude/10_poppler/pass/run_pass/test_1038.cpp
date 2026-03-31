#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashBGR8BTest_1038 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: splashBGR8B returns the first byte (index 0) of the BGR8 color
TEST_F(SplashBGR8BTest_1038, ReturnsFirstByte_1038) {
    unsigned char bgr8[3] = {100, 150, 200};
    EXPECT_EQ(100, splashBGR8B(bgr8));
}

// Test with zero value at index 0
TEST_F(SplashBGR8BTest_1038, ReturnsZeroWhenFirstByteIsZero_1038) {
    unsigned char bgr8[3] = {0, 128, 255};
    EXPECT_EQ(0, splashBGR8B(bgr8));
}

// Test with maximum value (255) at index 0
TEST_F(SplashBGR8BTest_1038, ReturnsMaxWhenFirstByteIsMax_1038) {
    unsigned char bgr8[3] = {255, 0, 0};
    EXPECT_EQ(255, splashBGR8B(bgr8));
}

// Test that splashBGR8B only reads index 0 and is independent of other bytes
TEST_F(SplashBGR8BTest_1038, IndependentOfOtherBytes_1038) {
    unsigned char bgr8_a[3] = {42, 0, 0};
    unsigned char bgr8_b[3] = {42, 100, 200};
    unsigned char bgr8_c[3] = {42, 255, 255};
    EXPECT_EQ(splashBGR8B(bgr8_a), splashBGR8B(bgr8_b));
    EXPECT_EQ(splashBGR8B(bgr8_b), splashBGR8B(bgr8_c));
}

// Test boundary: value 1 (just above minimum)
TEST_F(SplashBGR8BTest_1038, ReturnsBoundaryValueOne_1038) {
    unsigned char bgr8[3] = {1, 127, 254};
    EXPECT_EQ(1, splashBGR8B(bgr8));
}

// Test boundary: value 254 (just below maximum)
TEST_F(SplashBGR8BTest_1038, ReturnsBoundaryValue254_1038) {
    unsigned char bgr8[3] = {254, 1, 1};
    EXPECT_EQ(254, splashBGR8B(bgr8));
}

// Test with midpoint value 128
TEST_F(SplashBGR8BTest_1038, ReturnsMidpointValue_1038) {
    unsigned char bgr8[3] = {128, 64, 32};
    EXPECT_EQ(128, splashBGR8B(bgr8));
}

// Test with all bytes the same
TEST_F(SplashBGR8BTest_1038, AllBytesSameValue_1038) {
    unsigned char bgr8[3] = {77, 77, 77};
    EXPECT_EQ(77, splashBGR8B(bgr8));
}

// Test with all bytes set to 255
TEST_F(SplashBGR8BTest_1038, AllBytesMax_1038) {
    unsigned char bgr8[3] = {255, 255, 255};
    EXPECT_EQ(255, splashBGR8B(bgr8));
}

// Test with all bytes set to 0
TEST_F(SplashBGR8BTest_1038, AllBytesZero_1038) {
    unsigned char bgr8[3] = {0, 0, 0};
    EXPECT_EQ(0, splashBGR8B(bgr8));
}

// Test return type is unsigned char
TEST_F(SplashBGR8BTest_1038, ReturnTypeIsUnsignedChar_1038) {
    unsigned char bgr8[3] = {200, 100, 50};
    unsigned char result = splashBGR8B(bgr8);
    EXPECT_EQ(200, result);
}

// Test with a larger array to ensure only index 0 is accessed
TEST_F(SplashBGR8BTest_1038, WorksWithLargerArray_1038) {
    unsigned char bgr8[8] = {33, 44, 55, 66, 77, 88, 99, 110};
    EXPECT_EQ(33, splashBGR8B(bgr8));
}
