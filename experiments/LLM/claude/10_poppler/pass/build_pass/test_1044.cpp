#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashDeviceN8MTest_1044 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: returns the second element (index 1) of the array
TEST_F(SplashDeviceN8MTest_1044, ReturnsSecondElement_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[0] = 10;
    deviceN8[1] = 42;
    deviceN8[2] = 99;
    EXPECT_EQ(42, splashDeviceN8M(deviceN8));
}

// Test with zero value at index 1
TEST_F(SplashDeviceN8MTest_1044, ReturnsZeroWhenSecondElementIsZero_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[0] = 255;
    deviceN8[1] = 0;
    deviceN8[2] = 128;
    EXPECT_EQ(0, splashDeviceN8M(deviceN8));
}

// Test with maximum value (255) at index 1
TEST_F(SplashDeviceN8MTest_1044, ReturnsMaxValueWhenSecondElementIs255_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[0] = 0;
    deviceN8[1] = 255;
    deviceN8[2] = 0;
    EXPECT_EQ(255, splashDeviceN8M(deviceN8));
}

// Test boundary: value 1 at index 1
TEST_F(SplashDeviceN8MTest_1044, ReturnsOneWhenSecondElementIsOne_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[1] = 1;
    EXPECT_EQ(1, splashDeviceN8M(deviceN8));
}

// Test boundary: value 254 at index 1
TEST_F(SplashDeviceN8MTest_1044, Returns254WhenSecondElementIs254_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[1] = 254;
    EXPECT_EQ(254, splashDeviceN8M(deviceN8));
}

// Test that the function is independent of other array elements
TEST_F(SplashDeviceN8MTest_1044, IndependentOfOtherElements_1044) {
    unsigned char deviceN8_a[SPOT_NCOMPS + 4] = {0};
    unsigned char deviceN8_b[SPOT_NCOMPS + 4] = {0};

    deviceN8_a[0] = 100;
    deviceN8_a[1] = 77;
    deviceN8_a[2] = 200;
    deviceN8_a[3] = 50;

    deviceN8_b[0] = 0;
    deviceN8_b[1] = 77;
    deviceN8_b[2] = 0;
    deviceN8_b[3] = 255;

    EXPECT_EQ(splashDeviceN8M(deviceN8_a), splashDeviceN8M(deviceN8_b));
}

// Test with all elements set to the same value
TEST_F(SplashDeviceN8MTest_1044, AllElementsSameValue_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4];
    memset(deviceN8, 128, sizeof(deviceN8));
    EXPECT_EQ(128, splashDeviceN8M(deviceN8));
}

// Test return type is unsigned char
TEST_F(SplashDeviceN8MTest_1044, ReturnTypeIsUnsignedChar_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[1] = 200;
    unsigned char result = splashDeviceN8M(deviceN8);
    EXPECT_EQ(200, result);
}

// Test mid-range value
TEST_F(SplashDeviceN8MTest_1044, MidRangeValue_1044) {
    unsigned char deviceN8[SPOT_NCOMPS + 4] = {0};
    deviceN8[1] = 127;
    EXPECT_EQ(127, splashDeviceN8M(deviceN8));
}
