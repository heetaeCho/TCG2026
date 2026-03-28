#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocking dependencies (if any)
// No external dependencies were provided, so no mocks are necessary for this case

// Assuming SplashColorPtr is a pointer to an array of unsigned chars
using SplashColorPtr = unsigned char*;

// Function to be tested (from provided code)
static inline unsigned char splashDeviceN8K(SplashColorPtr deviceN8) {
    return deviceN8[3];
}

// Test class
class SplashTypesTest_1046 : public ::testing::Test {
protected:
    // You can add any setup or teardown logic here if necessary
};

// Normal Operation Test
TEST_F(SplashTypesTest_1046, splashDeviceN8K_NormalOperation_1046) {
    unsigned char colorArray[] = {0, 0, 0, 255, 0, 0}; // Test case with the 4th element being 255
    SplashColorPtr deviceN8 = colorArray;
    EXPECT_EQ(splashDeviceN8K(deviceN8), 255); // Expect the 4th element to be returned
}

// Boundary Condition Test - Lower Bound
TEST_F(SplashTypesTest_1046, splashDeviceN8K_LowerBound_1046) {
    unsigned char colorArray[] = {0, 0, 0, 0, 0, 0}; // Test case with the 4th element being 0
    SplashColorPtr deviceN8 = colorArray;
    EXPECT_EQ(splashDeviceN8K(deviceN8), 0); // Expect the 4th element to be returned
}

// Boundary Condition Test - Upper Bound (with max unsigned char value)
TEST_F(SplashTypesTest_1046, splashDeviceN8K_UpperBound_1046) {
    unsigned char colorArray[] = {0, 0, 0, 255, 0, 255}; // Test case with the 4th element being 255
    SplashColorPtr deviceN8 = colorArray;
    EXPECT_EQ(splashDeviceN8K(deviceN8), 255); // Expect the 4th element to be returned
}

// Exceptional Case - Handling of null pointer (assuming undefined behavior, this can be adjusted)
TEST_F(SplashTypesTest_1046, splashDeviceN8K_NullPointer_1046) {
    SplashColorPtr deviceN8 = nullptr;
    EXPECT_DEATH(splashDeviceN8K(deviceN8), ".*"); // Expecting a crash due to null pointer access
}

// Exceptional Case - Accessing out-of-bounds memory (assuming undefined behavior, this can be adjusted)
TEST_F(SplashTypesTest_1046, splashDeviceN8K_OutOfBounds_1046) {
    unsigned char colorArray[] = {0, 0, 0}; // Only 3 elements, access 4th element
    SplashColorPtr deviceN8 = colorArray;
    EXPECT_DEATH(splashDeviceN8K(deviceN8), ".*"); // Expecting a crash due to out-of-bounds access
}