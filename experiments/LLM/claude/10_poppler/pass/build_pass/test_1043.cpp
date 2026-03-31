#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashDeviceN8CTest_1043 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: returns the first byte of the array
TEST_F(SplashDeviceN8CTest_1043, ReturnsFirstElement_1043) {
    SplashColor deviceN8 = {42, 100, 200, 255, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 42);
}

// Test with zero value at first position
TEST_F(SplashDeviceN8CTest_1043, ReturnsZeroWhenFirstElementIsZero_1043) {
    SplashColor deviceN8 = {0, 100, 200, 255, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 0);
}

// Test with maximum value (255) at first position
TEST_F(SplashDeviceN8CTest_1043, ReturnsMaxValueWhenFirstElementIs255_1043) {
    SplashColor deviceN8 = {255, 0, 0, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 255);
}

// Test that the function only reads the first element, regardless of other values
TEST_F(SplashDeviceN8CTest_1043, IgnoresOtherElements_1043) {
    SplashColor deviceN8_a = {128, 0, 0, 0, 0, 0, 0, 0};
    SplashColor deviceN8_b = {128, 255, 255, 255, 255, 255, 255, 255};
    EXPECT_EQ(splashDeviceN8C(deviceN8_a), splashDeviceN8C(deviceN8_b));
}

// Test boundary value 1
TEST_F(SplashDeviceN8CTest_1043, ReturnsBoundaryValueOne_1043) {
    SplashColor deviceN8 = {1, 0, 0, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 1);
}

// Test boundary value 254
TEST_F(SplashDeviceN8CTest_1043, ReturnsBoundaryValue254_1043) {
    SplashColor deviceN8 = {254, 0, 0, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 254);
}

// Test mid-range value
TEST_F(SplashDeviceN8CTest_1043, ReturnsMidRangeValue_1043) {
    SplashColor deviceN8 = {127, 50, 60, 70, 80, 90, 100, 110};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 127);
}

// Test return type is unsigned char
TEST_F(SplashDeviceN8CTest_1043, ReturnTypeIsUnsignedChar_1043) {
    SplashColor deviceN8 = {200, 0, 0, 0, 0, 0, 0, 0};
    auto result = splashDeviceN8C(deviceN8);
    EXPECT_TRUE((std::is_same<decltype(result), unsigned char>::value));
    EXPECT_EQ(result, 200);
}

// Test with all elements set to the same value
TEST_F(SplashDeviceN8CTest_1043, AllElementsSameValue_1043) {
    SplashColor deviceN8 = {99, 99, 99, 99, 99, 99, 99, 99};
    unsigned char result = splashDeviceN8C(deviceN8);
    EXPECT_EQ(result, 99);
}

// Test multiple calls with different first elements
TEST_F(SplashDeviceN8CTest_1043, MultipleCallsConsistentResults_1043) {
    for (int i = 0; i < 256; ++i) {
        SplashColor deviceN8 = {static_cast<unsigned char>(i), 0, 0, 0, 0, 0, 0, 0};
        unsigned char result = splashDeviceN8C(deviceN8);
        EXPECT_EQ(result, static_cast<unsigned char>(i));
    }
}
