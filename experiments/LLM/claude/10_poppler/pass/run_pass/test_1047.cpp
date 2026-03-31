#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashDeviceN8STest_1047 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: accessing the first spot color (nSpot = 0)
TEST_F(SplashDeviceN8STest_1047, FirstSpotColor_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(50, splashDeviceN8S(deviceN8, 0));
}

// Test normal operation: accessing the second spot color (nSpot = 1)
TEST_F(SplashDeviceN8STest_1047, SecondSpotColor_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(60, splashDeviceN8S(deviceN8, 1));
}

// Test normal operation: accessing the third spot color (nSpot = 2)
TEST_F(SplashDeviceN8STest_1047, ThirdSpotColor_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(70, splashDeviceN8S(deviceN8, 2));
}

// Test normal operation: accessing the fourth spot color (nSpot = 3)
TEST_F(SplashDeviceN8STest_1047, FourthSpotColor_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(80, splashDeviceN8S(deviceN8, 3));
}

// Test boundary: spot color value at minimum (0)
TEST_F(SplashDeviceN8STest_1047, MinSpotColorValue_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 0, 0, 0, 0};
    EXPECT_EQ(0, splashDeviceN8S(deviceN8, 0));
}

// Test boundary: spot color value at maximum (255)
TEST_F(SplashDeviceN8STest_1047, MaxSpotColorValue_1047) {
    unsigned char deviceN8[8] = {10, 20, 30, 40, 255, 255, 255, 255};
    EXPECT_EQ(255, splashDeviceN8S(deviceN8, 0));
    EXPECT_EQ(255, splashDeviceN8S(deviceN8, 3));
}

// Test that the function correctly offsets by 4 (CMYK components before spot colors)
TEST_F(SplashDeviceN8STest_1047, OffsetByFour_1047) {
    unsigned char deviceN8[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    // nSpot=0 should return deviceN8[4] = 4
    EXPECT_EQ(4, splashDeviceN8S(deviceN8, 0));
    // nSpot=1 should return deviceN8[5] = 5
    EXPECT_EQ(5, splashDeviceN8S(deviceN8, 1));
    // nSpot=2 should return deviceN8[6] = 6
    EXPECT_EQ(6, splashDeviceN8S(deviceN8, 2));
    // nSpot=3 should return deviceN8[7] = 7
    EXPECT_EQ(7, splashDeviceN8S(deviceN8, 3));
}

// Test with a larger array to simulate more spot colors
TEST_F(SplashDeviceN8STest_1047, MultipleSpotColors_1047) {
    unsigned char deviceN8[12] = {0, 0, 0, 0, 100, 110, 120, 130, 140, 150, 160, 170};
    EXPECT_EQ(100, splashDeviceN8S(deviceN8, 0));
    EXPECT_EQ(110, splashDeviceN8S(deviceN8, 1));
    EXPECT_EQ(120, splashDeviceN8S(deviceN8, 2));
    EXPECT_EQ(130, splashDeviceN8S(deviceN8, 3));
    EXPECT_EQ(140, splashDeviceN8S(deviceN8, 4));
    EXPECT_EQ(150, splashDeviceN8S(deviceN8, 5));
    EXPECT_EQ(160, splashDeviceN8S(deviceN8, 6));
    EXPECT_EQ(170, splashDeviceN8S(deviceN8, 7));
}

// Test that CMYK values (first 4 bytes) are independent of spot color access
TEST_F(SplashDeviceN8STest_1047, CMYKIndependence_1047) {
    unsigned char deviceN8a[8] = {0, 0, 0, 0, 42, 43, 44, 45};
    unsigned char deviceN8b[8] = {255, 255, 255, 255, 42, 43, 44, 45};
    // Regardless of CMYK values, spot color access should return the same values
    EXPECT_EQ(splashDeviceN8S(deviceN8a, 0), splashDeviceN8S(deviceN8b, 0));
    EXPECT_EQ(splashDeviceN8S(deviceN8a, 1), splashDeviceN8S(deviceN8b, 1));
    EXPECT_EQ(splashDeviceN8S(deviceN8a, 2), splashDeviceN8S(deviceN8b, 2));
    EXPECT_EQ(splashDeviceN8S(deviceN8a, 3), splashDeviceN8S(deviceN8b, 3));
}

// Test return type is unsigned char
TEST_F(SplashDeviceN8STest_1047, ReturnTypeUnsignedChar_1047) {
    unsigned char deviceN8[8] = {0, 0, 0, 0, 200, 0, 0, 0};
    unsigned char result = splashDeviceN8S(deviceN8, 0);
    EXPECT_EQ(200, result);
    // Ensure it's treated as unsigned (200 should not be negative)
    EXPECT_GT(result, 128);
}
