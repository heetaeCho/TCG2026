#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashDeviceN8YTest_1045 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: verify that the function returns the element at index 2
TEST_F(SplashDeviceN8YTest_1045, ReturnsThirdElement_1045) {
    SplashColor deviceN8 = {10, 20, 30, 40, 50, 60, 70, 80};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 30);
}

// Test with all zeros
TEST_F(SplashDeviceN8YTest_1045, AllZeros_1045) {
    SplashColor deviceN8 = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 0);
}

// Test with maximum value at index 2
TEST_F(SplashDeviceN8YTest_1045, MaxValueAtIndex2_1045) {
    SplashColor deviceN8 = {0, 0, 255, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 255);
}

// Test that it specifically reads index 2, not other indices
TEST_F(SplashDeviceN8YTest_1045, ReadsCorrectIndex_1045) {
    SplashColor deviceN8 = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 3);
    EXPECT_NE(result, 1);
    EXPECT_NE(result, 2);
    EXPECT_NE(result, 4);
}

// Test with all elements set to the same value
TEST_F(SplashDeviceN8YTest_1045, AllSameValue_1045) {
    SplashColor deviceN8 = {128, 128, 128, 128, 128, 128, 128, 128};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 128);
}

// Test boundary: minimum unsigned char value
TEST_F(SplashDeviceN8YTest_1045, MinBoundaryValue_1045) {
    SplashColor deviceN8 = {255, 255, 0, 255, 255, 255, 255, 255};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 0);
}

// Test boundary: maximum unsigned char value
TEST_F(SplashDeviceN8YTest_1045, MaxBoundaryValue_1045) {
    SplashColor deviceN8 = {0, 0, 255, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 255);
}

// Test with a mid-range value
TEST_F(SplashDeviceN8YTest_1045, MidRangeValue_1045) {
    SplashColor deviceN8 = {10, 20, 127, 40, 50, 60, 70, 80};
    unsigned char result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(result, 127);
}

// Test return type is unsigned char
TEST_F(SplashDeviceN8YTest_1045, ReturnTypeIsUnsignedChar_1045) {
    SplashColor deviceN8 = {0, 0, 200, 0, 0, 0, 0, 0};
    auto result = splashDeviceN8Y(deviceN8);
    EXPECT_EQ(sizeof(result), sizeof(unsigned char));
    EXPECT_EQ(result, 200);
}

// Test that changing index 2 changes the result
TEST_F(SplashDeviceN8YTest_1045, ChangingIndex2ChangesResult_1045) {
    SplashColor deviceN8 = {100, 100, 50, 100, 100, 100, 100, 100};
    EXPECT_EQ(splashDeviceN8Y(deviceN8), 50);

    deviceN8[2] = 75;
    EXPECT_EQ(splashDeviceN8Y(deviceN8), 75);

    deviceN8[2] = 200;
    EXPECT_EQ(splashDeviceN8Y(deviceN8), 200);
}

// Test that changing other indices does not affect the result
TEST_F(SplashDeviceN8YTest_1045, ChangingOtherIndicesDoesNotAffect_1045) {
    SplashColor deviceN8 = {0, 0, 42, 0, 0, 0, 0, 0};
    EXPECT_EQ(splashDeviceN8Y(deviceN8), 42);

    deviceN8[0] = 255;
    deviceN8[1] = 255;
    deviceN8[3] = 255;
    deviceN8[4] = 255;
    EXPECT_EQ(splashDeviceN8Y(deviceN8), 42);
}
