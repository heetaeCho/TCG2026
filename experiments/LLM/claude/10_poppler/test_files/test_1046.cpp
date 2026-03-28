#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashDeviceN8KTest_1046 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: returns the value at index 3
TEST_F(SplashDeviceN8KTest_1046, ReturnsValueAtIndex3_1046) {
    SplashColor deviceN8 = {10, 20, 30, 40, 50, 60, 70, 80};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(40, result);
}

// Test when all values are zero
TEST_F(SplashDeviceN8KTest_1046, AllZeros_1046) {
    SplashColor deviceN8 = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(0, result);
}

// Test when all values are maximum (255)
TEST_F(SplashDeviceN8KTest_1046, AllMaxValues_1046) {
    SplashColor deviceN8 = {255, 255, 255, 255, 255, 255, 255, 255};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(255, result);
}

// Test boundary: index 3 is 0 while others are non-zero
TEST_F(SplashDeviceN8KTest_1046, Index3ZeroOthersNonZero_1046) {
    SplashColor deviceN8 = {100, 150, 200, 0, 50, 75, 125, 175};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(0, result);
}

// Test boundary: index 3 is 255 while others are zero
TEST_F(SplashDeviceN8KTest_1046, Index3MaxOthersZero_1046) {
    SplashColor deviceN8 = {0, 0, 0, 255, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(255, result);
}

// Test boundary: index 3 is 1 (minimum non-zero)
TEST_F(SplashDeviceN8KTest_1046, Index3MinNonZero_1046) {
    SplashColor deviceN8 = {0, 0, 0, 1, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(1, result);
}

// Test boundary: index 3 is 254
TEST_F(SplashDeviceN8KTest_1046, Index3NearMax_1046) {
    SplashColor deviceN8 = {0, 0, 0, 254, 0, 0, 0, 0};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(254, result);
}

// Test that the function only reads index 3 and is independent of other indices
TEST_F(SplashDeviceN8KTest_1046, IndependentOfOtherIndices_1046) {
    SplashColor deviceN8_a = {0, 0, 0, 128, 0, 0, 0, 0};
    SplashColor deviceN8_b = {255, 255, 255, 128, 255, 255, 255, 255};
    EXPECT_EQ(splashDeviceN8K(deviceN8_a), splashDeviceN8K(deviceN8_b));
}

// Test with a mid-range value
TEST_F(SplashDeviceN8KTest_1046, MidRangeValue_1046) {
    SplashColor deviceN8 = {10, 20, 30, 128, 50, 60, 70, 80};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(128, result);
}

// Test with sequential values to confirm correct index extraction
TEST_F(SplashDeviceN8KTest_1046, SequentialValues_1046) {
    SplashColor deviceN8 = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned char result = splashDeviceN8K(deviceN8);
    EXPECT_EQ(4, result);
}
