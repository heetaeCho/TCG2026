#include <gtest/gtest.h>

// Include the header for the function under test
#include "./TestProjects/poppler/splash/SplashTypes.h"

// Test fixture class
class SplashTypesTest_1034 : public ::testing::Test {
protected:
    // Setup and teardown functions can be added here if necessary
    void SetUp() override {
        // Code for setting up before each test if needed
    }

    void TearDown() override {
        // Code for cleaning up after each test if needed
    }
};

// Test case for normal operation
TEST_F(SplashTypesTest_1034, splashRGB8G_NormalOperation_1034) {
    // Test for a valid RGB8 array
    unsigned char rgb8[3] = {255, 128, 64};  // Example: RGB values
    EXPECT_EQ(splashRGB8G(rgb8), 128);  // Expected green component (128)
}

// Test case for boundary condition: minimum values
TEST_F(SplashTypesTest_1034, splashRGB8G_BoundaryMinValue_1034) {
    // Test for the lowest possible RGB8 values (all 0s)
    unsigned char rgb8[3] = {0, 0, 0};
    EXPECT_EQ(splashRGB8G(rgb8), 0);  // Expected green component (0)
}

// Test case for boundary condition: maximum values
TEST_F(SplashTypesTest_1034, splashRGB8G_BoundaryMaxValue_1034) {
    // Test for the highest possible RGB8 values (all 255s)
    unsigned char rgb8[3] = {255, 255, 255};
    EXPECT_EQ(splashRGB8G(rgb8), 255);  // Expected green component (255)
}

// Test case for boundary condition: middle value
TEST_F(SplashTypesTest_1034, splashRGB8G_BoundaryMiddleValue_1034) {
    // Test for RGB8 values that are in the middle range
    unsigned char rgb8[3] = {255, 127, 64};  // Example: RGB values
    EXPECT_EQ(splashRGB8G(rgb8), 127);  // Expected green component (127)
}

// Exceptional case: Null pointer input
TEST_F(SplashTypesTest_1034, splashRGB8G_ExceptionalNullPointer_1034) {
    // Test for null pointer input
    SplashColorPtr rgb8 = nullptr;
    EXPECT_DEATH(splashRGB8G(rgb8), ".*");  // Expect the function to fail with a death test
}